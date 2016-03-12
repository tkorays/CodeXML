#include "xxml.h"

#include <sstream>
#include <fstream>

namespace tk{

    XMLNode::XMLNode():parent(0),firstChild(0),next(0) {

    }
    XMLNode::XMLNode(string _name):parent(0),firstChild(0),next(0) ,name(_name) {
    }
    XMLNode::~XMLNode() {
        this->removeChildren();
    }
    string XMLNode::getName() {
        return this->name;
    }
    void XMLNode::setName(string _name) {
        this->name = _name;
    }
    string XMLNode::getAttribute(string _name) {
        map<string,string>::iterator it = \
                attributes.find(_name);
        if(it ==  attributes.end()){
            return "";
        }else{
            return it->second;
        }
    }
    void XMLNode::setAttribute(string _name, string _value) {
        map<string,string>::iterator it = \
                attributes.find(_name);
        if(it != attributes.end()){
            it->second = _value;
        }else{
            attributes.insert(pair<string,string>(_name,_value));
        }
    }
    void XMLNode::removeAttribute(string _name){
        map<string,string>::iterator it = \
                attributes.find(_name);
        if(it!=attributes.end()){
            attributes.erase(it);
        }
    }
    XMLNode* XMLNode::getParent() {
        return this->parent;
    }

    void XMLNode::setParent(XMLNode *_parent) {
        this->parent = _parent;
    }
    XMLNode* XMLNode::getFirstChild() {
        return this->firstChild;
    }
    void XMLNode::addChild(XMLNode *node) {
        XMLNode* first = this->firstChild;
        if(!first){
            this->firstChild = node;
            node->parent = this;
            return ;
        }
        while(first->next){
            first = first->next;
        }

        first->next = node;
        node->parent = this;

    }

    void XMLNode::removeChildren() {
        XMLNode* node = this->firstChild;
        XMLNode* del  = 0;
        if(!node){
            return ;
        }
        while(node){
            del = node;
            node = node->next;
            if(del->firstChild){
                del->removeChildren();
            }else{
                delete del;
            }
        }
        this->firstChild = 0;
    }

    XMLNode* XMLNode::getNext() {
        return this->next;
    }
    void XMLNode::setNext(XMLNode *node) {
        this->next = node;
    }

    void XMLNode::insertNext(XMLNode *node) {
        XMLNode* next_org = this->next;
        this->next = node;
        node->next = next_org;
    }
    void XMLNode::removeNext() {
        XMLNode* node = 0;
        if(this->next){
            node = this->next->next;
            delete this->next;
        }
        this->next = node;
    }

    void XMLNode::setText(string _text) {
        this->text = _text;
    }

    // TODO 需要美化输出格式
    string XMLNode::toString() {
        stringstream ss;
        ss<<"<"<<this->name;
        map<string,string>::iterator it = attributes.begin();
        while(it!=attributes.end()){
            ss<<" "<<it->first<<"=\""<<it->second<<"\"";
            it++;
        }
        // 不存在子结点且text为空,则闭合标签
        // 首先考虑是否存在子结点
        if(!firstChild && text.empty()){
            ss<<"/>";
        }else if(firstChild){
            ss<<">";
            while(firstChild){
                ss<<firstChild->toString();
                firstChild = firstChild->getNext();
            }
            ss<<"</"<<this->name<<">";
        }else{
            ss<<">"<<this->text<<"</"<<this->name<<">";
        }
        return ss.str();
    }


    XMLDoc::XMLDoc() {
        version     = "1.0";
        encoding    = "UTF-8";
        root        = 0;
    }
    XMLDoc::~XMLDoc() {
        release();
    }
    void XMLDoc::release() {
        if(root){
            delete root;
            root = 0;
        }
    }
    void XMLDoc::setRoot(XMLNode *r) {
        root = r;
    }

    string XMLDoc::toString() {
        stringstream ss;
        ss<<"<?xml version=\""<<
            version<<"\" encoding=\""<<
            encoding<<"\"?>";
        if(root){
            ss<<root->toString();
        }
        return ss.str();
    }

    XMLDoc* XMLDoc::loadFromFile(string fn) {
        XMLDoc* doc = new XMLDoc();
        fstream fs(fn);

        // 先判断文件是否存在
        if(!fs.is_open()){
            delete doc;
            return 0;
        }

        
    }




};