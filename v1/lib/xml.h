#ifndef __TK_XML_H__
#define __TK_XML_H__

typedef struct mem_pool_s mem_pool_t;

typedef struct xml_attr_s xml_attr_t;
typedef struct xml_node_s xml_node_t;
typedef struct xml_doc_s xml_doc_t;

// xml attribute struct,name-value pair
struct xml_attr_s {
    char*           name;
    char*           value;
    xml_attr_t*     next;
};

// xml node struct
struct xml_node_s {
    char*           name;
    char*           inner_text;
    xml_attr_t*     first_attr;
    xml_node_t*     parent;
    xml_node_t*     first_child;
    xml_node_t*     next_brother;
};

// xml doc,represent the whole xml document
struct xml_doc_s {
    mem_pool_t*     pool;
    xml_node_t*     root;
};

// Interfaces




#endif // __TK_XML_H__