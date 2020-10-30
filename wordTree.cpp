#include "wordTree.h"

Node* store;

WordTree::~WordTree(){
  /***********************************
   *      To be implemented
   * ********************************/
    clearTree(_root);
}

void WordTree::clearTree(Node* aNode){
  /***********************************
   *      To be implemented
   * ********************************/
    if (aNode == nullptr)
    {
        return;
    }
    else
    {
        clearTree(aNode->_left);
        clearTree(aNode->_right);
        delete aNode;
    }
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
  /***********************************
   *      Do not modify
   * ********************************/
  if (aNode != nullptr){
    ostr << "[";
    inOrder(aNode->_left, ostr);
    ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
    inOrder(aNode->_right, ostr);
    ostr << "]";
  }
}

Node* WordTree::find(Node* aNode, const string& element){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/


    if (element.compare(aNode->_value) == 0)
    {
        store = aNode;
    }
    if(aNode->_left!=nullptr)
        find(aNode->_left, element);
    if(aNode->_right!=nullptr)
        find(aNode->_right, element);

    return store;
}

/*void WordTree::print_tree(Node* root){
    cout << root->getValue() << endl;
    if(root->_left != nullptr)
        prin(root->_left);
    if(root->_right != nullptr)
        prin(root->_right);

}*/

int WordTree::height(Node* node){
    if (node == nullptr)
        return -1;
    return node->getHeight();

}

Node* WordTree::find(const string& element){
  /***********************************
   *      To be implemented
   * ********************************/

    if (element.compare(_root->_value) == 0)
    {
        return _root;
    }
   else
   {
        Node* temp = find(_root, element);
        if(temp != nullptr)
            return temp;
        return nullptr;
   }
}

void WordTree::updateHeight(Node *aNode) {
  /***********************************
   *      To be implemented
   *********************************/

   if(aNode->_left != nullptr){
        updateHeight(aNode->_left);
   }
   aNode->_height = 1 + max(height(aNode->_left), height(aNode->_right));
   if(aNode->_right != nullptr){
        updateHeight(aNode->_right);
   }

    /*if (aNode == nullptr) {
        return;
    }
    if (aNode->_left == nullptr && aNode->_right == nullptr) {
        aNode->_height = 0;     // no child, the height is 0
        return;
    }
    if (aNode->_left != nullptr && aNode->_right != nullptr) {
        aNode->_height = max(aNode->_left->_height, aNode->_right->_height)+1;
    }*/
}

Node* WordTree::leftRotation(Node* aNode){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    Node* left = aNode->_right;
    Node* T2 = left->_left;

    // Perform rotation
    left->_left = aNode;
    aNode->_right = T2;

    // Update heights
    updateHeight(aNode);
    updateHeight(left);

    // Return new root
    return left;
}

Node* WordTree::rightRotation(Node* aNode){     //Need check
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    Node* right = aNode->_left;
    Node* T2 = right->_right;

    // Perform rotation
    right->_right = aNode;
    aNode->_left = T2;

    // Update heights
    updateHeight(aNode);
    updateHeight(right);


    // Return new root
    return right;
}

int WordTree::checkBalance(Node* aNode){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    if (aNode == nullptr) {

        return 0;
    }
    /*if (aNode->_left == nullptr && aNode->_right == nullptr) {

        return 0;
    }
    else if (aNode->_left != nullptr && aNode->_right != nullptr)
    {
        int diff = aNode->_left->getHeight() - aNode->_right->getHeight();
        return diff;
    }*/

    return height(aNode->_left)-height(aNode->_right);
}



Node* WordTree::reBalance(Node* aNode){     //Need to figure it out
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/



  if (aNode->_left->getHeight() - aNode->_right->getHeight() > 1)
    {
      if (aNode->_left->_left->getHeight() > aNode->_left->_right->getHeight())
      {
          aNode = rightRotation(aNode);
      }
      else
      {
          aNode = leftRotation(aNode);
          aNode = rightRotation(aNode);
      }
    }
  else if (aNode->_left->getHeight() - aNode->_right->getHeight() < 1)
  {
      if (aNode->_right->_left->getHeight() > aNode->_right->_right->getHeight())
      {
          aNode = rightRotation(aNode);
          return aNode;
      }
      else
      {
          aNode = leftRotation(aNode);
          aNode = rightRotation(aNode);
          return aNode;
      }
  }
  if (aNode->_parent == nullptr)
  {
      _root = aNode;
      return _root;
  }
  return nullptr;
}

void WordTree::insert(const string& element){   //Incomplete
  /***********************************
   *      To be implemented
   * ********************************/

    _root = insert(element, _root);



}

Node* WordTree::insert(const string& element, Node*& aNode){        //Why the warning // because of initializing of private members: Line no 14
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.

   * ********************************/

   if(aNode == nullptr){
        aNode =  new Node(element);
        aNode->_count = 1;
        //return aNode;
    }
    else if (element.compare(aNode->_value) > 0)
    {
        aNode->_right = insert(element, aNode->_right);

    }
    else if(element.compare(aNode->_value) < 0)
    {
        aNode->_left = insert(element, aNode->_left);
    }
    else                               //In case of equality
    {
        aNode->_count += 1;
        return aNode;
    }

    aNode->_height = 1 + max(height(aNode->_left), height(aNode->_right));


    int balance = checkBalance(aNode);   //Balance checks (easier to do it here than to use rebalance)

    if (balance >= 2 && element.compare(aNode->_left->_value) < 0)   //left left case
    {
        return rightRotation(aNode);
    }
    if (balance <= -2 && element.compare(aNode->_right->_value) > 0)   //right right case
    {
        return leftRotation(aNode);
    }
    if (balance >= 2 && element.compare(aNode->_left->_value) > 0 )      //left right case
    {
        aNode->_left = leftRotation(aNode->_left);
        return rightRotation(aNode);
    }
    if (balance <= -2 && element.compare(aNode->_right->_value) < 0)          //right left case
    {
        aNode->_right = rightRotation(aNode->_right);
        return leftRotation(aNode);
    }

    return aNode;

}

void WordTree::dump(std::ostream& ostr){
  /***********************************
   *      Do not modify
   * ********************************/
  inOrder(_root, ostr);
}

int hold;

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/


   if(word.compare(aNode->_value) == 0){
        hold = counter;
    }
    if (word.compare(aNode->_value) > 0)
    {
        if(aNode->_right != nullptr){
            counter++;
            searchCountHelp(aNode->_right, word, counter);
        }
    }
    else
    if(word.compare(aNode->_value) < 0)
    {
        if(aNode->_left != nullptr){
            counter++;
            searchCountHelp(aNode->_left, word, counter);
        }
    }

    return hold;

}

int WordTree::searchCount(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

    int c = 0;

    if (word.compare(_root->_value) == 0)
    {
        return 1;
    }
    else{
        int temp;
        temp = searchCountHelp(_root, word, c);
        return temp;
    }
}



int WordTree::getRootHeight(){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    if(_root)
    {
        return _root->getHeight();
    }
    return -1;
}

int WordTree::getNodeHeight(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
    if (word.compare(_root->_value) == 0)
    {
        return _root->_height;
    }
   else
   {
        int temp = getNodeHeightHelp(_root, word);
            return temp;
   }
}

int heigh = -1;

int WordTree::getNodeHeightHelp(Node* aNode, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/


    if (word.compare(aNode->_value) == 0)
    {
        heigh = aNode->_height;
    }

    if(aNode->_left!=nullptr)
        getNodeHeightHelp(aNode->_left, word);
    if(aNode->_right!=nullptr)
        getNodeHeightHelp(aNode->_right, word);

    return heigh;

}
