//
// Created by tkorays on 3/23/16.
//

#ifndef INVOKER_XXML_H
#define INVOKER_XXML_H

typedef struct xml_raw_item_t;

class state {
public:
    xml_raw_item_t* get_item(char* buf, size_t size);
    state* next_state();
protected:
    state* next;
    size_t next_size;
};

class state_tag_open : public state {
public:
    xml_raw_item_t* get_item(char* buf, size_t size);
    state* next_state();
};


#endif //INVOKER_XXML_H
