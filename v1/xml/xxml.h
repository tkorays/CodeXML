#ifndef __XXML_H__
#define __XXML_H__

#include <string>
#include <map>
#include <cstdint>
using namespace std;

namespace tk {

    class XMLNode {
    private:
        string               name;
        string               text;
        map<string,string>   attributes;
        XMLNode*             parent;
        XMLNode*             firstChild;
        XMLNode*             next;


        XMLNode(const XMLNode&);
        XMLNode& operator=(const XMLNode&);
    public:
        XMLNode();
        XMLNode(string _name);
        ~XMLNode();
        string getName();
        void   setName(string _name);
        string getAttribute(string _name);

        int32_t getIntAttribute(string _name,int32_t dft=0);

        void   setAttribute(string _name, string _value);
        void   removeAttribute(string _name);
        XMLNode* getParent();
        void     setParent(XMLNode* _parent);

        XMLNode* getFirstChild();
        void addChild(XMLNode* node);
        void removeChildren();

        XMLNode* getNext();
        void setNext(XMLNode* node);
        void insertNext(XMLNode* node);
        void removeNext();

        void setText(string _text);

        string toString();
        static XMLNode* loadFromFile(string fn);
        static XMLNode* loadFromString(string s);
    };
};


#endif // __XXML_H__