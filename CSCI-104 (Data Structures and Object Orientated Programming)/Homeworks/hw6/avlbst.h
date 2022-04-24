#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

// DO NOT USE NAMESPACE

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
    // Do nothing
}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* InsertHelper(AVLNode<Key, Value> *node);
    AVLNode<Key, Value>* RemoveHelper(AVLNode<Key, Value> *node);
    void rotateLeft(AVLNode<Key, Value> *node);
    void rotateRight(AVLNode<Key, Value> *node);
    void updateNodeHeight(AVLNode<Key, Value> *node);
    int findUnbalanced(AVLNode<Key, Value> *node);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // UPDATE HEIGHTS OF PARENTS ONCE YOU INSERT
    // Adds AVL Node into tree, calculates height (findUnbalanced function), and does appropriate rotations.
    
    AVLNode<Key, Value>* Node1 = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    AVLNode<Key, Value> *NodePosition = InsertHelper(Node1);

    if (NodePosition == NULL) { // If duplicate
        delete Node1;
        return;
    }

    updateNodeHeight(NodePosition); // Use pointer of newly inserted node and update it's height (will do this everytime a new node is in)

    // Now walk up the AVL node/tree

    AVLNode<Key, Value>* Parent = NodePosition->getParent(); // Insert Helper gives a pointer to the parent node of inserted value

    while (Parent != NULL) {
        // Want to keep updating node here
        updateNodeHeight(Parent);

        // Here we calculate the distance between the two children of the parent to check if unbalanced
        int heightDiff = findUnbalanced(Parent);

        // Boolean variables to check which rotation occurs (if right side is greater or if left side is greater)
        bool LeftRot = false;
        bool RightRot = false;
        bool ifchange = false;

        // These conditions will determine which rotation to do first
        // If heightDiff is negative, that means right child is greater 
        // If heightDiff is positive, that means left child is greater
        // These conditions are evidently what rotation we want to do last.
        
        if (heightDiff < -1) {
            LeftRot = true;
        }
        else if (heightDiff > 1) {
            RightRot = true;
        }
        else { // Case where balanced (height diff = 0)
            LeftRot = false;
            RightRot = false;
        }

        // If Left & Right Rot are false, no rotations will occur and jump up next parent

        // There will only be 4 cases (Zig Zig/ Zig Zag)
        if (LeftRot == true) {
            if (new_item.first > Parent->getRight()->getKey()) {
                rotateLeft(Parent);
                ifchange = true;
            }
            else {
                rotateRight(Parent->getRight()); 
                rotateLeft(Parent);
                ifchange = true;
            }
        }
        else if (RightRot == true) {
            if (new_item.first < Parent->getLeft()->getKey()) {
                rotateRight(Parent);
                ifchange = true;
            }
            else {
                rotateLeft(Parent->getLeft());
                rotateRight(Parent);
                ifchange = true;
            }
        }

        // We put a flag if a change/rotation has occured, because we don't want to check the parents directly after a change.
        // We want to "skip" two iterations if true
        if (ifchange == true) {
            Parent = Parent->getParent(); // Walk up
            ifchange = false;
        }
        Parent = Parent->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO (Same Implementation of BST Remove)
    AVLNode<Key, Value> *FindNode = static_cast<AVLNode<Key, Value>*>(this->internalFind(key)); // Find if key exists
    if (FindNode == NULL) {
        return;
    }
    AVLNode<Key, Value> *Parent = RemoveHelper(FindNode); // Here we return the pointer to parent

    updateNodeHeight(Parent);
    
    // Copy and Paste Conditions from insert
    while (Parent != NULL) {
        // Want to keep updating node here
        updateNodeHeight(Parent);

        // Here we calculate the distance between the two children of the parent to check if unbalanced
        int heightDiff = findUnbalanced(Parent);

        // We use the difference, rather getting direct height to not run into NULL errors (accessing height for NULLs)
        int leftHeightDiff = findUnbalanced(Parent->getLeft());
        int rightHeightDiff = findUnbalanced(Parent->getRight());

        // Boolean variables to check which rotation occurs (if right side is greater or if left side is greater)
        bool LeftRot = false;
        bool RightRot = false;
        bool ifchange = false;

        // These conditions will determine which rotation to do first
        // If heightDiff is negative, that means right child is greater 
        // If heightDiff is positive, that means left child is greater
        // These conditions are evidently what rotation we want to do last.
        
        if (heightDiff < -1) {
            LeftRot = true;
        }
        else if (heightDiff > 1) {
            RightRot = true;
        }
        else { // Case where balanced (height diff = 0)
            LeftRot = false;
            RightRot = false;
        }

        // If Left & Right Rot are false, no rotations will occur and jump up next parent

        // There will only be 4 cases (Zig Zig/ Zig Zag)
        if (LeftRot == true) {
            if (rightHeightDiff <= 0) { // Lecture notes (break ties) Zig Zig
                rotateLeft(Parent);
                ifchange = true;
            }
            else {
                rotateRight(Parent->getRight()); 
                rotateLeft(Parent);
                ifchange = true;
            }
        } 
        else if (RightRot == true) {
            if (leftHeightDiff >= 0) { // Lecture notes (break ties) Zig Zig
                rotateRight(Parent);
                ifchange = true;
            }
            else {
                rotateLeft(Parent->getLeft());
                rotateRight(Parent);
                ifchange = true;
            }
        }
        // We put a flag if a change/rotation has occured, because we don't want to check the parents directly after a change.
        // We want to "skip" two iterations
        if (ifchange == true) {
            Parent = Parent->getParent(); // Walk up
            ifchange = false;
        }
        Parent = Parent->getParent();
    }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::InsertHelper(AVLNode<Key, Value> *node) 
{
    // TODO (Complete) (Same as BST Insert Helper but now an AVL Node)
    // VALUE HAS NOTHING TO DO WITH ORGANIZATION OF TREE (MISINTERPRETED)
    AVLNode<Key, Value> *duplicateNode = static_cast<AVLNode<Key, Value>*>(this->internalFind(node->getKey())); // Find if key exists
    if (duplicateNode != NULL) { // Node already exists
        duplicateNode->setValue(node->getValue()); // just change value (prompt)
        return NULL;
    }
    else if (this->root_ == NULL){ // nothing exist in the tree
        this->root_ = node; // (Key, Value, Parent (should be NULL))
        return static_cast<AVLNode<Key, Value>*>(this->root_);
    }
    else {
        AVLNode<Key, Value> *temp = static_cast<AVLNode<Key, Value>*>(this->root_); // Always start at root
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
AVLNode<Key, Value>* AVLTree<Key, Value>::RemoveHelper(AVLNode<Key, Value> *node) 
{
    // Remove Helper that returns AVLNode, return the parent
    AVLNode<Key, Value> *FindNode = static_cast<AVLNode<Key, Value>*>(this->internalFind(node->getKey())); // Find if key exists

    if (FindNode == NULL) { // Element does not exist
        return NULL; // Return Nothing (if element does not exist)
    }
    else { // Element does exist
        // CHECK THE CONDITIONS 
        AVLNode<Key, Value> *temp = FindNode;

        if ((FindNode->getLeft() == NULL) && (FindNode->getRight() == NULL)) { // If leaf node
            // If leaf node, just remove and set appropriate parent pointers
            temp = temp->getParent(); // Temp is parent of node we are deleting
            // Make sure we don't delete other child of parent
            if (temp == NULL) { // THIS MEANS it is a Root
                this->root_ = NULL;
            }
            else if (temp->getLeft() == FindNode) {
                temp->setLeft(NULL);
            }
            else { // exhaustive
                temp->setRight(NULL);
            }
            delete FindNode;
            return temp; // WE ARE RETURN PARENT OF NODE WE ARE DELETING
        }        
        else if ((FindNode->getLeft() != NULL) && (FindNode->getRight() != NULL)) { // Node with double child
            // Find value, find successor, copy successor into deletion node, delete successer node, set successor parents

            // Find in-order Predecessor (prompt)
            // Swap the Predecessor into the node you are removing
            AVLNode<Key, Value> *Predecessor = static_cast<AVLNode<Key, Value>*>(this->predecessor(temp)); 
            nodeSwap(Predecessor, temp);

            // TA said to do this?
            updateNodeHeight(Predecessor);
            updateNodeHeight(temp);
            
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
                return temp; // WE ARE RETURN PARENT OF NODE WE ARE DELETING
            }
            else { // Single Child
                AVLNode<Key, Value> *Parent = FindNode->getParent();
                AVLNode<Key, Value> *RightChild = FindNode->getRight();
                AVLNode<Key, Value> *LeftChild = FindNode->getLeft();
                if (Parent == NULL) { // need to do things with root
                    if (FindNode->getLeft() != NULL) { 
                        LeftChild->setParent(NULL); // since now root.
                        this->root_ = LeftChild;
                        delete FindNode;
                        return NULL; // We deleted the ROOT
                    }
                    else { 
                        RightChild->setParent(NULL);
                        this->root_ = RightChild;
                        delete FindNode;
                        return NULL; // We deleted the Root
                    }
                }
                else {
                    if (Parent->getLeft() == FindNode) { // Node is to the left
                        if (FindNode->getLeft() != NULL) {
                            Parent->setLeft(LeftChild);
                            LeftChild->setParent(Parent);
                            delete FindNode;
                            return Parent;
                        }
                        else {
                            Parent->setLeft(RightChild);
                            RightChild->setParent(Parent);
                            delete FindNode;
                            return Parent;
                        }
                    }
                    else {  // Node is to the right
                        if (FindNode->getRight() != NULL) {
                            Parent->setRight(RightChild);
                            RightChild->setParent(Parent);
                            delete FindNode;
                            return Parent;
                        }
                        else {
                            Parent->setRight(LeftChild);
                            LeftChild->setParent(Parent);
                            delete FindNode;
                            return Parent;
                        }
                    }
                }
            }
        }
        else { // exhaustive conditon (Single child)
            // If node has single child, promote predecessor/successor
            AVLNode<Key, Value> *Parent = FindNode->getParent();
            AVLNode<Key, Value> *RightChild = FindNode->getRight();
            AVLNode<Key, Value> *LeftChild = FindNode->getLeft();

            if (Parent == NULL) { // need to do things with root
                if (LeftChild != NULL) { 
                    LeftChild->setParent(NULL); // since now root.
                    this->root_ = LeftChild;
                    delete FindNode;
                    return NULL;
                }
                else { 
                    RightChild->setParent(NULL);
                    this->root_ = RightChild;
                    delete FindNode;
                    return NULL;
                }
            }
            else {
                if (Parent->getLeft() == FindNode) { // Node is to the left
                    if (LeftChild != NULL) {
                        Parent->setLeft(LeftChild);
                        LeftChild->setParent(Parent);
                        delete FindNode;
                        return Parent;
                    }
                    else {
                        Parent->setLeft(RightChild);
                        RightChild->setParent(Parent);
                        delete FindNode;
                        return Parent;
                    }
                }
                else {  // Node is to the right
                    if (RightChild != NULL) {
                        Parent->setRight(RightChild);
                        RightChild->setParent(Parent);
                        delete FindNode;
                        return Parent;
                    }
                    else {
                        Parent->setRight(LeftChild);
                        LeftChild->setParent(Parent);
                        delete FindNode;
                        return Parent;
                    }
                }            
            }
        }
    }
}


template<class Key, class Value>
int AVLTree<Key, Value>::findUnbalanced(AVLNode<Key, Value> *node)
{
    // Update node height by climbing upwards of the tree
    int leftChildHeight = 0;
    int rightChildHeight = 0;

    AVLNode <Key, Value> *CurrentNode = node;  
    if (CurrentNode == NULL) {
        return 0; // Means that node doesn;t exist, no difference between heights
    }  

    if (CurrentNode->getLeft() != NULL) {
        leftChildHeight = CurrentNode->getLeft()->getHeight();
    }
    if (CurrentNode->getRight() != NULL) {
        rightChildHeight = CurrentNode->getRight()->getHeight();
    }
    // We pre-set leftChild and rightChild to 0 

    int difference = leftChildHeight-rightChildHeight; // RETURN THIS (WE CAN CALCULATE IF LEFT OR RIGHT)
    return difference;
    // SOLVE NULL PROBLEM
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *node) 
{
    //AVLNode<Key, Value> *Parent = node->getParent(); // The node we are rotating is the middle node in a RotateLeft Example
    // Assume "node" is the root node of the single rotation
    AVLNode<Key, Value> *z = node;
    AVLNode<Key,Value> *ParentofRootRotation = z->getParent(); // grandparent
    AVLNode<Key, Value> *y = node->getRight(); // right
    AVLNode<Key, Value> *t1 = y->getLeft();
    // AVLNode<Key, Value> *x = y->gecleartRight();

    if (z == this->root_) {
        this->root_ = y;
    }

    z->setParent(y);
    z->setRight(t1);

    y->setLeft(z);
    y->setParent(ParentofRootRotation); // Will be NULL if it has no parent

    if (t1 != NULL) {
        t1->setParent(z);
    }

    if (ParentofRootRotation != NULL) {
        if (ParentofRootRotation->getLeft() == z) {
            ParentofRootRotation->setLeft(y);
        }
        else {
            ParentofRootRotation->setRight(y);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *node)
{
    //AVLNode<Key, Value> *Parent = node->getParent(); // The node we are rotating is the middle node in a RotateLeft Example
    // Assume "node" is the root node of the single rotation
    AVLNode<Key, Value> *z = node;
    AVLNode<Key,Value> *ParentofRootRotation = z->getParent();
    AVLNode<Key, Value> *y = node->getLeft();
    AVLNode<Key, Value> *t2 = y->getRight();

    // AVLNode<Key, Value> *x = y->getLeft();

    if (z == this->root_) {
        this->root_ = y;
    }

    z->setParent(y);
    z->setLeft(t2);

    y->setRight(z);
    y->setParent(ParentofRootRotation); // Will be NULL if it has no parent

    if (t2 != NULL) {
        t2->setParent(z);
    }

    if (ParentofRootRotation != NULL) {
        if (ParentofRootRotation->getRight() == z) {
            ParentofRootRotation->setRight(y);
        }
        else {
            ParentofRootRotation->setLeft(y);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::updateNodeHeight(AVLNode<Key, Value> *node)
{
    // Update node height by climbing upwards of the tree
    int leftChildHeight = 0;
    int rightChildHeight = 0;

    AVLNode <Key, Value> *CurrentNode = node;    

    if (CurrentNode != NULL) {
        if (CurrentNode->getLeft() != NULL) {
            leftChildHeight = CurrentNode->getLeft()->getHeight();
        }
        if (CurrentNode->getRight() != NULL) {
            rightChildHeight = CurrentNode->getRight()->getHeight();
        }
        // We pre-set leftChild and rightChild to 0
        // We can add this statement so this function updates the height after each insertion
        CurrentNode->setHeight(std::max(leftChildHeight,rightChildHeight)+1); // Add one because we set inserted the child
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

#endif