//
// Created by tkorays on 3/25/16.
//

#ifndef PCAPREADER_DATAPARSER_H
#define PCAPREADER_DATAPARSER_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include <stdint.h>
#include <stddef.h>

typedef struct data_item {
    char        name[16];
    uint16_t    bytes;
    uint16_t    bits;
} data_item_t;

// "dst_mac,6,0;src_mac,6,0;type,2,0";

class DataRule {
public:
    DataRule(string rule);  // 从字符串中解析出rule
    vector<data_item_t> getItemInfo(); // 获取rule信息
    string getName() const {return name;} // 该rule名字
    bool appendItem(data_item_t a); // 加入一个字段
private:
    vector<data_item_t> items;
    string name;
};


class DataStruct {
public:
    bool parse(const char* dt, size_t size, DataRule* info);
    uint64_t getInt(string name);
    const char* getRaw(string name);
private:
    char*       data;
    size_t      size;
protected:
};


#endif //PCAPREADER_DATAPARSER_H
