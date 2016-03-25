//
// Created by tkorays on 3/25/16.
//

#ifndef PCAPREADER_PCAPREADER_H
#define PCAPREADER_PCAPREADER_H

#include <string>
#include <map>
using namespace std;


// 如何定义一个协议?协议之间有相互关联该怎么办?
// 协议需要一个编号维护关联?
// ProtocolSet->Registe(Protocol);

// 支持继承以及反序列化
class Protocol {
public:
    string getName() const {return name;}
private:
protected:
    string name;
};

class ProtocolSet {
public:
    bool reg(const Protocol& p);
    Protocol* get(uint32_t id);
    Protocol* get(string name);
private:
    map<string,uint32_t>   protIds;
    map<uint32_t,Protocol> protocols;
};

class data_info_t {
public:
    bool validCheck();
    uint16_t bytes;
    uint16_t bits;
};


// "dst_mac",6,0
// "src_mac",6,0
// "type",2,0
class ProtocolRule {
public:
private:
    map<string,data_info_t> fields;
};

class ProtocolHdr {
public:
    ProtocolHdr* createProtocol(string name, ProtocolRule r);
private:
    string name;
    ProtocolRule r;
};


#endif //PCAPREADER_PCAPREADER_H
