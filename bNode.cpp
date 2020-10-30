#include "bNode.h"

BNode::BNode():_key(" "),_author(" "),_parent(nullptr),_left(nullptr),_right(nullptr),_flag(0){}

BNode::BNode(string key, string author, string text){
  _key = key;
  _author = author;
  _left = nullptr;
  _right = nullptr;
  createTextTree(text);
}

BNode::~BNode(){

}

void BNode::createTextTree(string text){
  istringstream iss(text);
  vector<string> tokens;
  copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
  for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
    _tree.insert(*it);
  }
}

int BNode::findFrequency(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    Node* node = _tree.find(word);
    if(node != nullptr)
        return  node->getFrequency();
    return 0;
}

int BNode::searchCount(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  return _tree.searchCount(word);
}

int BNode::getTextTreeHeight(){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  return _tree.getRootHeight();
}

int BNode::getNodeHeight(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  return _tree.getNodeHeight(word);
}
