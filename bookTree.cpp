#include "bookTree.h"

BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
  /***********************************
   *      To be implemented
   * ********************************/
    clear(_root);

}


BNode* BookTree::makeSplay(BNode* root, string key){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    if (root == nullptr || key.compare(root->_key) == 0)       //If key is within root, just return root
        return root;

    if (key.compare(root->_key) < 0)
    {
        if (root->_left == nullptr)                             //Key is not in the tree, root returned
           return root;

        if (key.compare(root->_left->_key) < 0)                          //Zig-Zig (Left Left)
        {
            root->_left->_left = makeSplay(root->_left->_left, key);    //Makes key as root of left-left
            root = rightRotate(root);                                   //First rotation for root
        }
        else if (key.compare(root->_left->_key) > 0)            //Zig-Zag (Left Right)
        {
            root->_left->_right = makeSplay(root->_left->_right, key);      //make key the root of left-right node

            if (root->_left->_right != nullptr)                            //First rotation for root->left
                root->_left = leftRotate(root->_left);
        }
        return (root->_left == nullptr) ? root : root = rightRotate(root);     //Second root rotation performed
    }
    else
    {
        if (root->_right == nullptr)                                    //Key is not in the tree, root returned
            return root;

        if (key.compare(root->_right->_key) < 0)                    //Zig-Zag (Right Left)
        {

            root->_right->_left = makeSplay(root->_right->_left, key);       //Bring the key as root of right-left


            if (root->_right->_left != nullptr)                                //rotation for right-left
                root->_right = rightRotate(root->_right);
        }
        else if (key.compare(root->_right->_key) > 0)               //Zag-Zag (Right Right)
        {
            root->_right->_right = makeSplay(root->_right->_right, key);    //right-right rotation
            root = leftRotate(root);
        }

        return (root->_right == nullptr) ? root : leftRotate(root);         //Second rotation for root
    }
}

BNode* BookTree::rightRotate(BNode* x){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    BNode* y = x->_left;
    x->_left = y->_right;
    y->_right = x;

    return y;
}

BNode* BookTree::leftRotate(BNode* x){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    BNode* y = x->_right;
    x->_right = y->_left;
    y->_left = x;

    return y;
}

bool BookTree::insert(string key, string author, string text){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
   if (_root != nullptr && key.compare(_root->_key) == 0)
        return false;

    if (_root == nullptr)                   //if tree is empty
    {
        BNode* newNode = new BNode();
        newNode->_key = key;
        newNode->_author = author;
        newNode->createTextTree(text);
        newNode->_left = newNode->_right = nullptr;
        _root = newNode;
        _root = makeSplay(_root, key);

    }
    else if (_root != nullptr && key.compare(_root->_key) < 0)
    {
        BNode* newNode = new BNode();               //New node for insertion
        newNode->_key = key;
        newNode->_author = author;
        newNode->createTextTree(text);
        newNode->_left = newNode->_right = nullptr;

        newNode->_right = _root;
        newNode->_left = _root->_left;
        _root->_left = nullptr;
        _root = newNode;
    }
    else
    {
        BNode* newNode = new BNode();               //New node for insertion
        newNode->_key = key;
        newNode->_author = author;
        newNode->createTextTree(text);
        newNode->_left = newNode->_right = nullptr;

        newNode->_left = _root;
        newNode->_right = _root->_right;
        _root->_right = nullptr;
        _root = newNode;
    }


  return true;
}

void BookTree::clear(BNode* root){
  /***********************************
   *      To be implemented
   * ********************************/
    if (root == nullptr)
    {
        return;
    }
    else
    {
        clear(root->_left);
        clear(root->_right);
        delete root;

    }
}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
  /***********************************
   *      Do not modify
   * ********************************/
  if (root != nullptr){
    if (verbose){
      cout << "(";
      inorderHelp( root->_left, verbose );
      cout << root->_key << ":" << root->_author;
      root->_tree.dump();
      inorderHelp( root->_right, verbose );
      cout << ")";
    }
    else{
      inorderHelp( root->_left, verbose );
      cout << root->_key;
      inorderHelp( root->_right, verbose );
    }
  }
}

void BookTree::dump(bool verbose){
  /***********************************
   *      Do not modify
   * ********************************/
  inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    //get title node
   _root = makeSplay(_root, title);
    //get word node
    return _root->findFrequency(word);
}

void BookTree::dumpTitle(string title){
  /***********************************
   *      To be implemente
   * ********************************/

   _root = makeSplay(_root, title);
    _root->_tree.dump();

}

int BookTree::searchCount(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    _root = makeSplay(_root, title);
    int temp = _root->_tree.searchCount(word);
    return temp;
}

int BookTree::getTextTreeHeight(string title){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
   _root = makeSplay(_root, title);
   return _root->getTextTreeHeight();

}

int BookTree::getWordHeight(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
   BNode* title_node = makeSplay(_root, title);
   return title_node->getNodeHeight(word);

}

string BookTree::getRootKey(){
  /***********************************
   *      Do not modify
   * ********************************/
  return _root->_key;
}

void BookTree::loadData(string dataFile){
  /***********************************
   *      This function is implemented
   *      to help you. You should't need
   *      to modify it.
   * ********************************/
  //read the entire file at once
  std::ifstream t(dataFile);
  std::stringstream buffer;
  buffer << t.rdbuf();

  //time to parse the information
  string titleDelimiter = "<==>";
  string itemsDeleimiter = "<=>";
  string s = buffer.str();
  size_t pos = 0;
  string token;
  while ((pos = s.find(titleDelimiter)) != string::npos) {
    token = s.substr(0, pos);//token is complete data for one title
    //get the title
    int tempPos = token.find(itemsDeleimiter);
    string title = token.substr(0,tempPos);
    //convert title to lower case
    std::transform (title.begin(), title.end(), title.begin(), ::tolower);
    token.erase(0, tempPos + itemsDeleimiter.length()+1);
    //get the author
    tempPos = token.find(itemsDeleimiter);
    string author = token.substr(0,tempPos);
    //convert author to lower case
    std::transform (author.begin(), author.end(), author.begin(), ::tolower);
    token.erase(0, tempPos + itemsDeleimiter.length()+1);
    //get the text
    string text = token.substr(0,token.length() - 1);//remove last newline
    //clean up the text, remove all non-alphanumeric characters
    for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
      if( !std::isalnum(*iter) && *iter != ' ')
	iter = text.erase(iter) ;
      else
	++iter ; // not erased, increment iterator
    }
    //convert text to lower case
    std::transform (text.begin(), text.end(), text.begin(), ::tolower);

    insert(title,author,text);

    //move to info for the next title
    s.erase(0, pos + titleDelimiter.length()+1);
  }

}
