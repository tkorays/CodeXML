//
// Created by tkorays on 3/25/16.
//
#include "DataParser.h"

#include <fstream>
#include <iostream>
using namespace std;

int main(){
    // 试着用它去解析一个pcap文件:
    fstream ff("a.cap",ios::out | ios::in);

    DataRuleManager::add("pcap_file_header","...");
    DataRuleManager::add("pkthdr","");
    DataRuleManager::add("eth","...");
    DataRuleManager::add("ipv4","...");
    DataRuleManager::add("udp","...");

    DataStruct pcap_fh(DataRuleManager::get("pcap_file_header"));
    ff>>pcap_fh;
    cout<<pcap_fh.getInt("magic");

    DataStruct pkthdr(DataRuleManager::get("pkthdr"));
    uint64_t datalen = pkthdr.getInt("len");

    DataStruct eth(DataRuleManager::get("eth"));
    ff>>eth;
    cout<<eth.getInt(0);

    DataStruct ipv4(DataRuleManager::get("ipv4"));
    ff>>ipv4;
    cout<<ipv4.getInt("version");



    return 0;
}
