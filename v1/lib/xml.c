#include "xml.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "mem_pool.h"

// &lt; &gt;&amp; &quot; &apos;
// < > & " '

// local definitions
static size_t parse_xml_to_list(xml_doc_t* doc, const char* data, size_t size, size_t offset);

xml_raw_item_t* xml_raw_item_create(mem_pool_t* pool,int type, const char* data, size_t size){
    xml_raw_item_t* item;
    if((type==item_type_str && data==0) || !pool){
        return 0;
    }
    item = (xml_raw_item_t*)mem_pool_alloc(pool,sizeof(xml_raw_item_t));
    if(!item){
        return 0;
    }

    item->type = type;
    item->next = 0;
    item->size = size;
    if(type == item_type_str){
        // size can be zero, so item->data = NULL
        item->data = mem_pool_alloc(pool,size);
        if(item->data){
            memcpy(item->data,data,size);
        }
    }
    return item;
}


xml_doc_t* xml_doc_create(){
    xml_doc_t*      doc;
    mem_pool_t*     pool;

    pool = mem_pool_create();
    if(!pool){
        return 0;
    }
    doc = (xml_doc_t*)mem_pool_alloc(pool,sizeof(xml_doc_t));
    if(!doc){
        mem_pool_destroy(pool);
        return 0;
    }
    doc->pool           = pool;
    doc->root           = 0;
    doc->_raw_item_head = xml_raw_item_create(doc->pool,item_type_none,0,0);
    doc->_raw_item_cur  = doc->_raw_item_head;
    return doc;
}


xml_doc_t* xml_doc_load(const char* filename){
    xml_doc_t*      doc;
    FILE*           fh;
    void*           data;
    char            buf[XML_STRING_MAX_SIZE];
    size_t          read_size;
    int             read_num;

    if(!filename){
        return 0;
    }
    fh = fopen(filename,"r");
    if(!fh){
        return 0;
    }

    // 读取文件,按一个个元素分割
    while(feof(fh)==0) {
        read_size = fread(buf,1,XML_STRING_MAX_SIZE,fh);
        read_num = parse_xml_to_list(doc,buf,read_size,0);

        if(read_num == 0){
            break;
        }
        // 回退
        if(read_num < read_size) {
            fseek(fh, read_num, SEEK_CUR);
            continue;
        }

    }
    fclose(fh);


    if(read_num == 0){
        return 0;
    }
    doc = xml_doc_create(); // no more check
    // 状态鸡...

    return doc;
}


// this is a local function
// 返回读取字节数,如果出错则返回0
size_t parse_xml_to_list(xml_doc_t* doc, const char* data, size_t size, size_t offset){
    size_t  i,j;
    const char*   buf = data;
    char    ch;
    int     tag_not_close = 0;      // 标签是否闭合,xml <>内外字符串处理与区别
    int     read_num = 0;

    i = offset;
    while(i<size){
        ch = data[i];

        // 标签没有关闭,只处理 空白 换行 > = " / - ? name 标签字符串
        if(tag_not_close){
            switch(ch){
                case ' ':
                case '\t':
                    if(doc->_raw_item_cur->type == item_type_sep) break; // 多个分割合并为一个
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_sep,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '>':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_gt,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    tag_not_close = 0;
                    read_num += 1;
                    break;
                case '=':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_eq,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '/':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_slash,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '-':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_minus,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '?':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_qs,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '\r':
                case '\n':
                    read_num += 1;
                    break; // 回车换行直接跳过
                case '"':
                    j = i + 1;
                    while (j < size) {
                        if (buf[j] == '"') {
                            doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_qt, 0, 0);
                            doc->_raw_item_cur = doc->_raw_item_cur->next;

                            doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_str, buf + i + 1,
                                                                           j - i - 1);
                            doc->_raw_item_cur = doc->_raw_item_cur->next;

                            doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_qt, 0, 0);
                            doc->_raw_item_cur = doc->_raw_item_cur->next;

                            read_num += (j-i+1);
                            i = j;
                            break;
                        }
                        j++;
                    }
                    if (j == size) {
                        // 在1024字节中都没有找到匹配的",说明字符串太长,返回错误
                        if(size-i >= XML_STRING_MAX_SIZE){
                            return 0;
                        }
                        // 字符长不够,直接返回
                        return i;
                    }
                    break;
                default:
                    j = i;
                    while(j < size){
                        if(buf[j] == '=' || buf[j] == ' ' || buf[j] == '\t'
                           || buf[j] == '\r' || buf[j] == '\n' || buf[j] == '/'
                           || buf[j] == '>'){
                            doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_str,buf+i,j-i);
                            doc->_raw_item_cur = doc->_raw_item_cur->next;
                            read_num += (j-i);
                            i = j-1;
                            break;
                        }
                        j++;
                    }
                    if(j==size){
                        // 在1024字节中都没有找到匹配的",说明字符串太长,返回错误
                        if(size-i >= XML_STRING_MAX_SIZE){
                            return 0;
                        }
                        // 字符长不够
                        return i;
                    }
                    break;
            }
        }else{ // 标签关闭会,除了< ,其他均按照字符处理(指导遇到<)
            switch(ch){
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    if(doc->_raw_item_cur->type == item_type_sep) break; // 多个分割合并为一个
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_sep,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    break;
                case '<':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_lt,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    read_num += 1;
                    tag_not_close = 1;
                    break;
                    // 读取inner text
                default:
                    j = i;
                    while(j < size){
                        if(buf[j] == '<'){
                            doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_str,buf+i,j-i);
                            doc->_raw_item_cur = doc->_raw_item_cur->next;
                            read_num += (j-i);
                            i = j-1;
                            break;
                        }
                        j++;
                    }
                    if(j==size){
                        // 在1024字节中都没有找到匹配的",说明字符串太长,返回错误
                        if(size-i >= XML_STRING_MAX_SIZE){
                            return 0;
                        }
                        // 字符长不够
                        return i;
                    }
                    break;
            }
        }
        i++;
    }
    return read_num;
}