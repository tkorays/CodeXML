#ifndef __XXML_H__
#define __XXML_H__

#include <string>
#include <map>
using namespace std;

namespace tk {
    typedef int xml_ret;
    typedef enum {
        XML_NO_ERROR=0,
        XML_SUCCESS=0,
        XML_ERROR,
        XML_NO_ATTRIBUTE,
        XML_PARSE_ERR,

    };
    class XMLNode;
    class XMLElement;

    class XMLNode {
    private:
        string               name;
        string               text;
        map<string,string>   attributes;
        XMLNode*             parent;
        XMLNode*             firstChild;
        XMLNode*             next;


        XMLNode(const XMLNode&);
    public:
        XMLNode();
        XMLNode(string _name);
        ~XMLNode();
        string getName();
        void   setName(string _name);
        string getAttribute(string _name);
        void   setAttribute(string _name, string _value);
        void   removeAttribute(string _name);
        XMLNode* getParent();
        void     setParent(XMLNode* _parent);

        XMLNode* getFirstChild();
        void addChild(XMLNode* node);

        XMLNode* getNext();
        void setNext(XMLNode* node);
        void insertNext(XMLNode* node);
        void removeNext();

        void setText(string _text);

        string toString();
        string fromString(string s);
    };
};


#endif // __XXML_H__