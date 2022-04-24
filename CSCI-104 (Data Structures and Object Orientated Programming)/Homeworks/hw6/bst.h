#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cmath>

// DO NOT USE NAMESPACE

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
    // No need to do anything
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO (COMPLETE)
    virtual ~BinarySearchTree(); //TODO (COMPLETE)
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO (COMPLETE)
    virtual void remove(const Key& key); //TODO (COMPLETE)
    void clear(); //TODO (Complete)
    bool isBalanced() const; //TODO (COMPLETE)
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO (COMPLETE)
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO (COMPLETE)
    Node<Key, Value> *getSmallestNode() const;  // TODO (COMPLETE)
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO (COMPLETE)
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
    
    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current); // for interator (just copy pred) (COMPLETE)
    int height(Node<Key, Value> *node) const; // To find the height (COMPLETE)
    bool isBalancedParam(Node<Key, Value> *root) const; // We add this because regular isBalanced allows for no parameters (COMPLETE)
    Node<Key, Value>* InsertHelper(Node<Key, Value> *node);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO (Complete)
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    // TODO (Complete)
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO (Complete)
    bool condition;
    if (current_ == rhs.current_) {
        condition = true;
    }
    else {
        condition = false;
    }
    return condition;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO (Complete)
    bool condition;
    if (current_ != rhs.current_){
        condition = true;
    }
    else {
        condition = false;
    }
    return condition;
}

/**
* Advances the iterator's location using an in-order sequencing
*/
// Assuming this means you count up?
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO (Complete)
    // Note* Successor = in order sequencing 
    current_ = successor(current_);
    return *this; // Returns next iteration (successor also has an error check where NULL is returned if max)
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO (COMPLETE)
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO (COMPLETE)
    // Destructor
    clear(); // PROMPT says just call this (assume)
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
// If key is in tree, overwrite value. When inserting, dynamically insert new node.
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO (Complete)
    // VALUE HAS NOTHING TO DO WITH ORGANIZATION OF TREE (MISINTERPRETED)
    // Call Helper Function
    Node <Key, Value> *Node1 = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
    InsertHelper(Node1);
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
// If key DNE, do nothing, SWAP WITH PREDECESSOR (if two children), 
// If we hit a NULL node, element does not exist
 // Four phase 
    // Node to remove is a leaf node.
    // Node has one subtree
    // Node has two subtrees
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO (complete)
    Node<Key, Value> *FindNode = internalFind(key); // Find if key exists

    if (FindNode == NULL) { // Element does not exist
        return; // do nothing
    }
    else { // Element does exist
        // CHECK THE CONDITIONS 
        Node<Key, Value> *temp = FindNode;

        if ((FindNode->getLeft() == NULL) && (FindNode->getRight() == NULL)) { // If leaf node
            // If leaf node, just remove and set appropriate parent pointers
            temp = temp->getParent(); // Temp is parent of node we are deleting
            // Make sure we don't delete other child of parent
            if (temp == NULL) { // THIS MEANS it is a Root
                root_ = NULL;
            }
            else if (temp->getLeft() == FindNode) {
                temp->setLeft(NULL);
            }
            else { // exhaustive
                temp->setRight(NULL);
            }
            delete FindNode;
        }        
        else if ((FindNode->getLeft() != NULL) && (FindNode->getRight() != NULL)) { // Node with double child
            // Find value, find successor, copy successor into deletion node, delete successer node, set successor parents

            // Find in-order Predecessor (prompt)
            // Swap the Predecessor into the node you are removing
            Node<Key, Value> *Predecessor = predecessor(temp); 
            nodeSwap(Predecessor, temp);
            // Since Predecessor is now in a new spot, delete old successor (temp).
            // Assume nodeSwap works, now attempt to delete temp

            if ((temp->getLeft() == NULL) && (temp->getRight() == NULL)) { // If leaf node
                // If leaf node, just remove and set appropriate parent pointers
                temp = temp->getParent(); // Temp is parent of node we are deleting
                // Make sure we don't delete other child of parent
                if (temp->getLeft() == FindNode) {
                    temp->setLeft(NULL);
                }
                else { // exhaustive
                    temp->setRight(NULL);
                }
                delete FindNode;
            }
            else { // Single Child
                Node<Key, Value> *Parent = FindNode->getParent();
                Node<Key, Value> *RightChild = FindNode->getRight();
                Node<Key, Value> *LeftChild = FindNode->getLeft();
                if (Parent == NULL) { // need to do things with root
                    if (FindNode->getLeft() != NULL) { 
                        LeftChild->setParent(NULL); // since now root.
                        root_ = LeftChild;
                        delete FindNode;
                    }
                    else { 
                        RightChild->setParent(NULL);
                        root_ = RightChild;
                        delete FindNode;
                    }
                }
                else {
                    if (Parent->getLeft() == FindNode) { // Node is to the left
                        if (FindNode->getLeft() != NULL) {
                            Parent->setLeft(LeftChild);
                            LeftChild->setParent(Parent);
                            delete FindNode;
                        }
                        else {
                            Parent->setLeft(RightChild);
                            RightChild->setParent(Parent);
                            delete FindNode;
                        }
                    }
                    else {  // Node is to the right
                        if (FindNode->getRight() != NULL) {
                            Parent->setRight(RightChild);
                            RightChild->setParent(Parent);
                            delete FindNode;
                        }
                        else {
                            Parent->setRight(LeftChild);
                            LeftChild->setParent(Parent);
                            delete FindNode;
                        }
                    }
                }
            }
        }
        else { // exhaustive conditon (Single child)
            // If node has single child, promote predecessor/successor
            Node<Key, Value> *Parent = FindNode->getParent();
            Node<Key, Value> *RightChild = FindNode->getRight();
            Node<Key, Value> *LeftChild = FindNode->getLeft();

            if (Parent == NULL) { // need to do things with root
                if (LeftChild != NULL) { 
                    LeftChild->setParent(NULL); // since now root.
                    root_ = LeftChild;
                    delete FindNode;
                }
                else { 
                    RightChild->setParent(NULL);
                    root_ = RightChild;
                    delete FindNode;
                }
            }
            else {
                if (Parent->getLeft() == FindNode) { // Node is to the left
                    if (LeftChild != NULL) {
                        Parent->setLeft(LeftChild);
                        LeftChild->setParent(Parent);
                        delete FindNode;
                    }
                    else {
                        Parent->setLeft(RightChild);
                        RightChild->setParent(Parent);
                        delete FindNode;
                    }
                }
                else {  // Node is to the right
                    if (RightChild != NULL) {
                        Parent->setRight(RightChild);
                        RightChild->setParent(Parent);
                        delete FindNode;
                    }
                    else {
                        Parent->setRight(LeftChild);
                        LeftChild->setParent(Parent);
                        delete FindNode;
                    }
                }            
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) //  Predecessor is right-most element in the left sub-tree
{
    // TODO (Complete)
    Node<Key, Value> *node = current;
    if (node->getLeft() != NULL) { // CORRECT (one left, all the way right)
        node = node->getLeft(); // Move one left
        while(node->getRight() != NULL) { // Go until (right-most element)
            node = node->getRight();
        }
        return node; // returns right most element
    }
    else { // If left subtree doesn't exist, value is one of the ancestors. (move up the tree) // CHECK
        bool condition = false;
        while (node->getParent() != NULL) {
            Node<Key, Value> *prevNode = node;
            node = node->getParent(); // Find the "hitch"
            if (node->getLeft() != prevNode) {  // We compare until the node is the very top, or satisfies (property of BST)
                condition = true; // True once this happens
                break;
            }
            if (node->getParent() == NULL) { // Parent node is exhausted
                condition = false;
                break;
            }
        }
        if (condition == true) { // If we find a node that is less than current node 
            return node;
        }
        return NULL; // When the value is the left most node (where parents are exhausted) and nothing can be found
    }
}

template<class Key, class Value> // (NOT INCLUDED BUT JUST IN CASE (COPY PASTE PREDESSEOR))
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) // Left-Most element in the right sub-tree
{
    // TODO (Complete)
    Node<Key, Value> *node = current;
    if (node->getRight() != NULL) { // CORRECT
        node = node->getRight(); // Move one left
        while(node->getLeft() != NULL) { // Go until (right-most element)
            node = node->getLeft();
        }
        return node; // returns right most element
    }
    else { // If right subtree doesn't exist, value is one of the ancestors. (move up the tree) // CHECK
        bool condition = false;
        while (node->getParent() != NULL) {
            Node<Key, Value> *prevNode = node;
            node = node->getParent(); // Find the "hitch"
            if (node->getRight() != prevNode) {  // We compare until the node is the very top, or satisfies (property of BST)
                condition = true; // True once this happens 
                break;
            }
            if (node->getParent() == NULL) { // Parent node is exhausted
                condition = false;
            }
        }
        if (condition == true) { // If we find a node that is less than current node 
            return node;
        }
        return NULL; // When the value is the left most node (where parents are exhausted) and nothing can be found
    }
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // Deletes all nodes inside the tree, resetting it to the empty tree. (Call Remove)
    while(root_ != NULL) { // Start from root (if this is true, means something is still in tree)
        remove(root_->getKey());
        // Remove function calls deletes (so don't have too)
    }
    root_ = NULL; // initialize to NULL
    // If this doesn't work, something is wrong with remove
}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO (COMPLETE)
    // Returns a pointer to the node with the smallest key (used by the iterator)
    Node <Key, Value> *tempRoot = root_; // Never want to use real root
    if (tempRoot == NULL) { // Root doesn't exist
        return NULL;
    }
    // Here we need to iterate to the bottom most left-most node (smallest node)
    // Initial approach would be to call predecessor until NULL -> bad runtime
    while(tempRoot->getLeft() != NULL) { 
        tempRoot = tempRoot->getLeft();
    }
    return tempRoot;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO (Complete)
    // Returns a pointer to the node with the specified key
    Node <Key, Value> *tempRoot = root_;
    if (tempRoot == NULL) { // tree is empty (error check)
        return NULL;
    }
    else {
        while (tempRoot != NULL && tempRoot->getKey() != key) {
            if (key > tempRoot->getKey()){ // Greater than -> Right
                tempRoot = tempRoot->getRight();
            }
            else if (key < tempRoot->getKey()){ // Less than -> Left
                tempRoot = tempRoot->getLeft();
            }
            else if (key == tempRoot->getKey()) { // If equal then it must be it
                return tempRoot;
            }
            // These conditions are exhaustive (will go or the other)
        }
    }
    return tempRoot; 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO (COMPLETE)
    // Returns true if the BST is an AVL Tree
        // That is, for every node, the height of its left subtree is within 1 of the height
        // of its right subtree
    if (root_ == NULL) { // balanced if empty
        return true;
    }
    else{
        return isBalancedParam(root_);
    }
}

// Pass parameters
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedParam(Node<Key, Value> *root) const
{
    // TODO (COMPLETE)
    // Returns true if the BST is an AVL Tree
        // That is, for every node, the height of its left subtree is within 1 of the height
        // of its right subtree
    if (root == NULL) { // balanced if empty
        return true;
    }

    // Create objects so we don't necessarily affect original root
    Node <Key, Value> *tempLeftNode = root; // Get Left Sub-Tree
    Node <Key, Value> *tempRightNode = root; // Get Right Sub-Tree

    int leftheight = height(tempLeftNode->getLeft());
    int rightheight = height(tempRightNode->getRight());

    // Lab 11 bst.cpp (similar)
    if (std::abs(leftheight-rightheight) <= 1 && isBalancedParam(tempLeftNode->getLeft()) && isBalancedParam(tempRightNode->getRight())) {
        return true; // AVL INVARIANT DIFFER BY 1 and subtle recursion
    }
    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value> *node) const // Helper to find the height (I think recursive) (We need to find height of each node so a while loop would not work.)
{
    // TODO (COMPLETE)
    int leftHeight = 0;
    int rightHeight = 0;
    Node <Key, Value> *tempLeftNode = node; // We will iteratate this toward left side
    Node <Key, Value> *tempRightNode = node; // We will iterate this toward right side
    if (node == NULL) { // HEIGHT IS 0 
        return 0;
    }
    else { // MUST use recursion
        leftHeight = 1 + (height(tempLeftNode->getLeft()));
        rightHeight = 1 + (height(tempRightNode->getRight()));
        // While loop implementation is wrong because the max tree can go either left or right. (not just straight left and straight right)
    }
    int maxHeight = std::max(leftHeight, rightHeight); // Choose longest line
    return maxHeight;
    // still thinking to myself, can we use a while loop for this?
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::InsertHelper(Node<Key, Value> *node) 
{
    // TODO (Complete)
    // VALUE HAS NOTHING TO DO WITH ORGANIZATION OF TREE (MISINTERPRETED)
    Node<Key, Value> *duplicateNode = internalFind(node->getKey()); // Find if key exists
    if (duplicateNode != NULL) { // Node already exists
        duplicateNode->setValue(node->getValue()); // just change value (prompt)
        return NULL;
    }
    else if (root_ == NULL){ // nothing exist in the tree
        root_ = node; // (Key, Value, Parent (should be NULL))
        return root_;
    }
    else {
        Node<Key, Value> *temp = root_; // Always start at root
        while ((temp->getLeft() != NULL) || (temp->getRight() != NULL)) { // Condition runs until a Leaf
            // TREE IS ORGANIZED BY KEY NOT VALUE (PROMPT)
            if (node->getKey() > temp->getKey()) { // if pair is greater go right
                if (temp->getRight() == NULL) {
                    break;
                }
                temp = temp->getRight();
            }
            else if (node->getKey() < temp->getKey()) { // else, if pair is less than go left
                if (temp->getLeft() == NULL) {
                    break;
                }
                temp = temp->getLeft();
            }
            // never will be a condition where it is equal (we check duplicate case)
        }
        node->setParent(temp);
        // Node<Key, Value> *Node1 = new Node<Key, Value> (node->getKey(), node->getValue(), temp); // We declare this new node here because now we found parent
        // Here, temp will be a leaf node -> next step, is to check less than or greater and insert new node
        if (node->getKey() > temp->getKey()) { // greater than
            temp->setRight(node);
        }
        else { // less than
            temp->setLeft(node);
        }
        return node; // Returns pointer to node
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }

    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif

// NOTE TO SELF (DONT TOUCH NO BUGS, works)