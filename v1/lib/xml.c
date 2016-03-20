#include "xml.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "mem_pool.h"

// &lt; &gt;&amp; &quot; &apos;
// < > & " '

// local definitions


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
    char            ch;
    size_t          read_size;
    size_t          i,j;
    long            read_pos;
    char            tag_not_close = 0;

    if(!filename){
        return 0;
    }
    fh = fopen(filename,"r");
    if(!fh){
        return 0;
    }

    doc = xml_doc_create(); // no more check

    while(feof(fh)==0) {
        read_size = fread(buf,1,XML_STRING_MAX_SIZE,fh);
        i = 0;
        while(i < read_size){
            ch = buf[i];
            switch(ch){
                case ' ':
                case '\t':
                    if(doc->_raw_item_cur->type == item_type_sep) break;
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_sep,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    break;
                case '<':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_lt,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    tag_not_close = 1;
                    break;
                case '>':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_gt,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    tag_not_close = 0;
                    break;
                case '=':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_eq,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    break;
                case '/':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_slash,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    break;
                case '-':
                    doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_minus,0,0);
                    doc->_raw_item_cur = doc->_raw_item_cur->next;
                    break;
                case '\r':
                case '\n':
                    break;
                case '"':
                    // attribute value
                    if(tag_not_close) {
                        j = i + 1;
                        while (j < read_size) {
                            // 我怎么会写出这样的代码!!! : if(j == '"') {
                            if (buf[j] == '"') {
                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_qt, 0, 0);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;

                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_str, buf + i + 1,
                                                                               j - i - 1);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;

                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool, item_type_qt, 0, 0);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;

                                i = j;
                                break;
                            }
                            j++;
                        }
                        if (j == read_size) {
                            // force to read from current "
                            read_pos = ftell(fh);
                            read_pos -= (read_size - i);
                            fseek(fh, read_pos, SEEK_SET);
                            i = read_size;
                        }
                    }else{ // common inner text, read until '<'
                        j = i;
                        while(j < read_size){
                            if(buf[j] == '<'){
                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_str,buf+i,j-i);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;

                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_lt,0,0);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;
                                tag_not_close = 1;
                                i = j;
                                break;
                            }
                            j++;
                        }
                        if(j==read_size){
                            // force to read from current "
                            read_pos = ftell(fh);
                            read_pos -= (read_size-i);
                            fseek(fh,read_pos,SEEK_SET);
                            i = read_size;
                        }
                    }
                    break;
                default:
                    // attribute name
                    if(tag_not_close){
                        j = i;
                        while(j < read_size){
                            if(buf[j] == '=' || buf[j] == ' ' || buf[j] == '\t'
                               || buf[j] == '\r' || buf[j] == '\n' || buf[j] == '/'
                               || buf[j] == '>'){
                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_str,buf+i,j-i);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;
                                i = j-1;
                                break;
                            }
                            j++;
                        }
                        if(j==read_size){
                            // force to read from current "
                            read_pos = ftell(fh);
                            read_pos -= (read_size-i);
                            fseek(fh,read_pos,SEEK_SET);
                            i = read_size;
                        }
                    }else{ // common inner text ,read untl <
                        j = i;
                        while(j < read_size){
                            if(buf[j] == '<'){
                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_str,buf+i,j-i);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;

                                doc->_raw_item_cur->next = xml_raw_item_create(doc->pool,item_type_lt,0,0);
                                doc->_raw_item_cur = doc->_raw_item_cur->next;
                                tag_not_close = 1;
                                i = j;
                                break;
                            }
                            j++;
                        }
                        if(j==read_size){
                            // force to read from current "
                            read_pos = ftell(fh);
                            read_pos -= (read_size-i);
                            fseek(fh,read_pos,SEEK_SET);
                            i = read_size;
                        }
                    }

                    break;
            }
            i++;
        }
    }

    fclose(fh);
    return doc;
}