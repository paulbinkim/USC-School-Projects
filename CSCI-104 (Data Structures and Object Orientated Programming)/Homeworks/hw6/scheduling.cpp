// Write a program to schedule exam time slots so that no students have two exams at the
// Same time (recursion/backtracking.)

// Input file (passed in command line), has three parameters on the first line.
// (# of exams, # of students. # of time slots)
// Input has name, white space, and classes

// Output is an assignment of classes to the integers between 1 and the
// number of timeslots (one class per line)

// If no solution, output No valid solution.

// Maintain a map of each class to its timeslot, using AVL implementation.
// Use try and catch appropriately.

// Make executable called scheduling.

#include "avlbst.h"
#include "bst.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>

using namespace std;

int main() {

    // BinarySearchTree<int, int> BST;
    // BST.insert(pair<int,int>(33,20));
    // BST.insert(pair<int,int>(27,50));
    // BST.insert(pair<int,int>(9,10));
    // BST.insert(pair<int,int>(2,45));
    // BST.insert(pair<int,int>(17,45));
    // BST.insert(pair<int,int>(40,45));
    // BST.insert(pair<int,int>(8,45));
    // BST.insert(pair<int,int>(21,45));
    // BST.insert(pair<int,int>(36,45));
    // BST.insert(pair<int,int>(52,45));
    // BST.insert(pair<int,int>(38,45));
    // BST.remove(33);
    // BST.remove(9);
    // BST.remove(2);
    // BST.insert(pair<int,int>(27,45));
    // BST.remove(17);
    // BST.remove(69);
    // // BST.remove(45);
    // // BST.remove(18);
    // // BST.remove(22);
    // // BST.remove(32);
    // // BST.remove(31);
    // BST.print();
    // cout << BST.isBalanced() << endl;

    AVLTree<int, int> AVL1;
    // AVL1.insert(pair<int,int>(10,20));
    // AVL1.insert(pair<int,int>(20,10));
    // AVL1.insert(pair<int,int>(30,40));
    // AVL1.insert(pair<int,int>(15,10));
    // AVL1.insert(pair<int,int>(25,10));
    // AVL1.insert(pair<int,int>(12,10));
    // AVL1.insert(pair<int,int>(2,10));
    // AVL1.insert(pair<int,int>(1,10));
    // AVL1.insert(pair<int,int>(17,10));
    // AVL1.insert(pair<int,int>(17,10));
    // AVL1.remove(10);
    // AVL1.remove(17);
    // AVL1.remove(15);
    // AVL1.remove(12);
    // AVL1.remove(2);
    // AVL1.remove(1);
    // AVL1.remove(10);
    AVL1.insert(pair<int,int>(10,20));
    AVL1.insert(pair<int,int>(10,20));

    AVL1.print();
    
    return 0;
}