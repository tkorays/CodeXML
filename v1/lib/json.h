#ifndef __TK_JSON_H__
#define __TK_JSON_H__

typedef struct json_str_s {
    char*   data;
    size_t  size;
} json_str_t;

typedef struct json_num_s {
    double  num;
} json_num_t;

typedef enum {
    JSON_TRUE,
    JSON_FALSE
} json_boolean_t;

typedef enum {
    json_null,
    json_number,
    json_string,
    json_boolean,
    json_object,
    json_array
} json_data_type;

typedef struct json_data_s {
    int     type;
    char*   data;
} json_data_t;

typedef struct json_node_s {
    char*           name;
    size_t          size;
    json_data_t*    data;
} json_node_t;

#endif // __TK_JSON_H__
