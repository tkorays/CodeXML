#ifndef __TK_XML_H__
#define __TK_XML_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

#define XML_STRING_MAX_SIZE 1024

typedef struct mem_pool_s mem_pool_t;

typedef struct xml_attr_s xml_attr_t;
typedef struct xml_node_s xml_node_t;
typedef struct xml_doc_s xml_doc_t;
typedef struct xml_raw_item_s xml_raw_item_t;

// xml attribute struct,name-value pair
struct xml_attr_s {
    char *name;
    char *value;
    xml_attr_t *next;
};

// xml node struct
struct xml_node_s {
    char *name;
    char *inner_text;
    xml_attr_t *first_attr;
    xml_node_t *parent;
    xml_node_t *first_child;
    xml_node_t *next_brother;
};

// xml doc,represent the whole xml document
struct xml_doc_s {
    mem_pool_t *pool;
    xml_node_t *root;
    xml_raw_item_t* _raw_item_head;
    xml_raw_item_t* _raw_item_cur;
};

typedef enum {
    item_type_none,
    item_type_raw,
    item_type_str,
    item_type_lt,
    item_type_gt,
    item_type_qt,
    item_type_eq,
    item_type_slash,
    item_type_sep,
    item_type_minus
} xml_raw_item_type;

struct xml_raw_item_s {
    int type;
    char *data; // not use if type != item_type_str
    size_t size; // data size
    xml_raw_item_t *next;
};

// Interfaces
xml_raw_item_t *xml_raw_item_create(mem_pool_t *pool, int type, const char *data, size_t size);

xml_doc_t *xml_doc_create();

xml_doc_t *xml_doc_load(const char *filename);

#ifdef __cplusplus
}
#endif

#endif // __TK_XML_H__