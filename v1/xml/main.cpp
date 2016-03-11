#include <iostream>

using namespace std;

#include "xxml.h"
using namespace tk;

int main() {

    XMLNode* root = new XMLNode("root");
    root->setAttribute("cmd","fuck");
    root->setAttribute("abc","efg");
    root->setText("hello world");
    cout<<root->toString()<<endl;





    return 0;
}