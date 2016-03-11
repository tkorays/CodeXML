#include <iostream>

using namespace std;

#include "xxml.h"
using namespace tk;

int main() {

    XMLNode* root = new XMLNode("root");
    root->setAttribute("cmd","fuck");
    root->setAttribute("abc","efg");
    //root->setText("hello world");

    XMLNode* node_1 = new XMLNode("abc");
    node_1->setAttribute("bi","aaaa");

    XMLNode* node_2 = new XMLNode("bcd");
    node_2->setText("hello world");

    root->addChild(node_1);
    root->addChild(node_2);

    node_1 = 0;
    node_2 = 0;

    XMLNode* n = root->getFirstChild();
    if(n){
        cout<<n->getName()<<endl;
    }

    root->removeChildren();



    cout<<root->toString()<<endl;





    return 0;
}