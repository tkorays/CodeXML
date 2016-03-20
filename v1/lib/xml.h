#ifndef __TK_XML_H__
#define __TK_XML_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

#define XML_STRING_MAX_SIZE 1024    ///< strlen("\"str.....str\"") <= XML_STRING_MAX_LENGTH

typedef struct mem_pool_s mem_pool_t;
typedef struct xml_attr_s xml_attr_t;
typedef struct xml_node_s xml_node_t;
typedef struct xml_doc_s xml_doc_t;
typedef struct xml_raw_item_s xml_raw_item_t;

// xml attribute struct
struct xml_attr_s {
    char *name;         ///< attribute name
    char *value;        ///< attribute value
    xml_attr_t *next;   ///< next attribute
};

// xml node struct
struct xml_node_s {
    char *name;                 ///< node tag name
    char *inner_text;           ///< node inner text
    xml_attr_t *first_attr;     ///< first attribute
    xml_node_t *parent;         ///< parent node
    xml_node_t *first_child;    ///< first child node
    xml_node_t *next_brother;   ///< next brother node
};

// xml doc struct
struct xml_doc_s {
    mem_pool_t *pool;               ///< xml_doc_s' memory pool
    xml_node_t *root;               ///< root node
    xml_raw_item_t* _raw_item_head; ///< first raw data item
    xml_raw_item_t* _raw_item_cur;  ///< current raw data item
};

// raw data item type
typedef enum {
    item_type_none, // none
    item_type_raw,  // raw data
    item_type_str,  // string
    item_type_lt,   // <
    item_type_gt,   // >
    item_type_qt,   // "
    item_type_eq,   // =
    item_type_slash,// /
    item_type_qs,   // question
    item_type_sep,  // separation
    item_type_minus // -
} xml_raw_item_type;

// save xml file raw data
struct xml_raw_item_s {
    int type;               ///< item type
    char *data;             ///< not use if type != item_type_str
    size_t size;            ///< data size
    xml_raw_item_t *next;   ///< next raw data item
};

// Interfaces
/*!
 * @brief create xml_raw_item_t
 * @param pool memory pool to allocate memory for item struct and data field
 * @param type item type
 * @param data string data
 * @param size data size
 * @return xml_raw_item_t
 */
xml_raw_item_t *xml_raw_item_create(mem_pool_t *pool, int type, const char *data, size_t size);

/*!
 * @brief create xml_doc_t
 * @return xml_doc_t
 */
xml_doc_t *xml_doc_create();

/*!
 * @brief load xml data from file
 * @param filename
 * @return xml_doc_t,return 0 if loading failed
 */
xml_doc_t *xml_doc_load(const char *filename);

#ifdef __cplusplus
}
#endif

#endif // __TK_XML_H__