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

        string      toString();
    public:
        XMLNode();
        XMLNode(string _name);
        ~XMLNode();

        string      getName();
        void        setName(string _name);

        string      getAttribute(string _name);
        int32_t     getIntAttribute(string _name,int32_t dft=0);
        void        setAttribute(string _name, string _value);
        void        removeAttribute(string _name);

        XMLNode*    getParent();
        void        setParent(XMLNode* _parent);

        XMLNode*    getFirstChild();
        void        addChild(XMLNode* node);
        void        removeChildren();

        XMLNode*    getNext();
        void        setNext(XMLNode* node);
        void        insertNext(XMLNode* node);
        void        removeNext();

        void        setText(string _text);


        friend  class XMLDoc;

    };


    class XMLDoc {
    private:
        string                  version;
        string                  encoding;
        XMLNode*                root;
        uint32_t                err;
        static map<uint16_t,string> errInfo;
    public:
        XMLDoc();
        ~XMLDoc();
        void        release();
        void        setRoot(XMLNode* r);

        string      toString();
        uint16_t    getErrCode();
        string      getErrInfo();
        string      getErrInfo(uint16_t code);

        static XMLDoc* loadFromFile(string fn);
        static XMLDoc* loadFromString(string s);
    };
};


#endif // __XXML_H__