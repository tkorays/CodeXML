//
// Created by tkorays on 3/20/16.
//

#include "xml.h"
#include <stdio.h>

int main(){
    xml_doc_t* doc = xml_doc_load("a.xml");
    xml_raw_item_t* item = doc->_raw_item_head;
    size_t i;
    while(item){
        switch(item->type){
            case item_type_lt:
                printf("<\n");
                break;
            case item_type_gt:
                printf(">\n");
                break;
            case item_type_sep:
                printf("sep\n");
                break;
            case item_type_qt:
                printf("\"\n");
                break;
            case item_type_eq:
                printf("=\n");
                break;
            case item_type_slash:
                printf("/\n");
                break;
            case item_type_str:
                i=0;
                while(i<item->size){
                    printf("%c",item->data[i]);
                    i++;
                }
                printf("\n");
                break;
            default:
                printf("others\n");
        }
        item = item->next;
    }
    return 0;
}
