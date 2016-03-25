//
// Created by tkorays on 3/25/16.
//
#include "DataParser.h"

#include <fstream>
using namespace std;

int main(){
    fstream fs("abc",ios::out | ios::in);

    DataStruct eth(new DataRule("eth","dst_mac,6,0;src_mac,6,0;type,2,0"));
    eth.getInt("dst_mac");
    const char* dt  = eth.getRaw("src_mac");
    fs>>eth;

    DataStruct ipv4(new DataRule("ipv4","..."));
    fs>>ipv4;
    ipv4.getInt("version");

    return 0;
}
