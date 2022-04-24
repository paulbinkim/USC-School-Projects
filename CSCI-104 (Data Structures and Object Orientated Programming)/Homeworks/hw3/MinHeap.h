// Including Useful Libraries for Functionality
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <map>
#include <utility>  // Used for PAIRS and SWAP
#include <vector>

// Templated Class
template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;  // TOP
                            /* returns the element with smallest priority.
                                  Break ties however you wish.
                                  Throws an exception if the heap is empty. */

    void remove();  // POP
                    /* removes the element with smallest priority.
                          Break ties however you wish.
                    Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

    void UpdatePriority(T item, int priority);
    // Used in Part 2 (A* Search, PIAZZA @994, encouraged by Professor Cote)

private:
    std::vector<std::pair<T, int>> heap1;  // Vector that holds pairs
    void trickledown(int pos);
    void bubbleup(int pos);
    int numChildren;
    std::map<T, int> Position; // Map used to keep track of position

    // whatever you need to naturally store things.
    // You may also add helper functions here.
};

template<class T>
MinHeap<T>::MinHeap(int d) {  // Constructor
    if (d < 2) {              // Doesn't do anything for D less than 2
        return;
    } else {
        numChildren = d;  // Setting numChildren to D
    }
}

template<class T>  // Deconstructor
MinHeap<T>::~MinHeap() {}

template<class T>
void MinHeap<T>::remove() {  // Removes element with smallest priority (top most node)
    if (heap1.size() == 0) {
        return;                      // There's nothing to remove.
    } else if (heap1.size() == 1) {  // When there is only the parent (topmost) node, just need to remove.
        heap1.pop_back();

    } else {
        std::swap(heap1[0], heap1[heap1.size() - 1]);  // Swap functions 
        std::swap(Position[heap1[0].first], Position[heap1.back().first]); // Swap map as well

        heap1.pop_back();
        trickledown(0);  // There is a new value at index 0 so we must trickledown
    }
}

template<class T>
void MinHeap<T>::trickledown(int pos) {                // Trickle Down function used in remove
    if (pos > ((heap1.size() - 2.0) / numChildren)) {  // Use float so we can get negatives when heap.size < 1
        return;
    }                                           // Recursive Base Case
    int smallestpos = (numChildren * pos) + 1;  // Initialize to left most child node
    for (int i = 1; i < numChildren + 1; i++) {
        int child = (numChildren * pos) + i;  // child is a position of the node below parent
        if (child < heap1.size()) {           // Condition to check if not accessing out of bounds
            if (heap1[child].second < heap1[smallestpos].second) {
                smallestpos = child;
            }
        }
    }
    if (heap1[smallestpos].second < heap1[pos].second) {  // if child is less than parent
        std::swap(heap1[smallestpos], heap1[pos]);

        // int temp = Position[heap1[smallestpos].first];
        // Position[heap1[smallestpos].first] = Position[heap1[pos].first];
        // Position[heap1[pos].first] = temp;

        std::swap(Position[heap1[smallestpos].first], Position[heap1[pos].first]);

        trickledown(smallestpos);
    } else if (heap1[smallestpos].second == heap1[pos].second) {
        if (heap1[pos].first > heap1[smallestpos].first) {
            std::swap(heap1[smallestpos], heap1[pos]);
            std::swap(Position[heap1[smallestpos].first], Position[heap1[pos].first]);
            trickledown(smallestpos);
        }
    }
}

template<class T>
void MinHeap<T>::add(T item, int priority) {  // Add function to add to Priority Queue
    heap1.push_back(std::make_pair(item, priority));
    Position.insert(std::make_pair(item, heap1.size() - 1));
    bubbleup(heap1.size() - 1);  // -1 here
}

template<class T>
void MinHeap<T>::bubbleup(int pos) {       // Bubble up function used in Add
    int parent = (pos - 1) / numChildren;  // Formula for D children
    if (pos == 0) {
        return;                                             // When there is only one element in the vector
    } else if (heap1[parent].second > heap1[pos].second) {  // We are creating a min heap
        std::swap(heap1[parent], heap1[pos]);
        std::swap(Position[heap1[parent].first], Position[heap1[pos].first]);

        bubbleup((pos - 1) / numChildren);  // Recursion
    } else if (heap1[parent].second == heap1[pos].second) {
        if (heap1[parent].first > heap1[pos].first) {
            std::swap(heap1[parent], heap1[pos]);
            std::swap(Position[heap1[parent].first], Position[heap1[pos].first]);
            bubbleup((pos - 1) / numChildren);  // Recursion
        }
    }
}

template<class T>
const T& MinHeap<T>::peek() const {  // Returns very-most top value of vector (min)
    if (heap1.size() == 0) {
        throw std::out_of_range("Heap is empty");  // Exceptions
    } else {
        return heap1[0].first;
    }
}

template<class T>
bool MinHeap<T>::isEmpty() {  // Checks if vector is empty or filled
    if (heap1.size() == 0) {
        return true;  // Yes, it is empty.
    } else {
        return false;  // No, it is not empty.
    }
}

template<class T>
void MinHeap<T>::UpdatePriority(T item, int priority) {  // Taken straight from Heaps Lecture Notes
    int location = Position[item];
    if (heap1[location].second
        < priority) {  // Means that the new update will assign a higher priority, therefore, will have to trickle down
        heap1[location].second = priority;
        trickledown(location);
    } else {  // Else, if priority is the same or lower
        heap1[location].second = priority;
        bubbleup(location);
    }
}