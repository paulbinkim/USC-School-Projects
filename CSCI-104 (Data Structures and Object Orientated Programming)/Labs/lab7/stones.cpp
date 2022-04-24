#include "stones.h"
#include <queue> // to use std::priority_queue
#include <algorithm>
#include <iostream>
using namespace std;

// Here we are choosing the two heaviest rocks and smashing them together.
int lastStoneWeight(vector<int>& stones) {
    
    if (stones.size() == 1) {
        return stones.front();
    }
    else if(stones.size() == 0) {
        return 0;
    }

    make_heap(stones.begin(), stones.end());

    while (stones.size() > 1) {

        int value1 = stones.front();
        pop_heap(stones.begin(), stones.end());
        stones.pop_back();

        int value2 = stones.front();
        pop_heap(stones.begin(), stones.end());
        stones.pop_back();

        if (value1 > value2) {
            int value3 = value1 - value2;
            stones.push_back(value3);
            push_heap(stones.begin(), stones.end());
        }
    }

    if (stones.size() == 1) {
        return stones.front();
    }
    else if(stones.size() == 0) {
        return 0;
    }

    return 0;
}
