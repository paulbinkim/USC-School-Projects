// Paul Kim, pbkim@usc.edu

// Including Libraries for Functionality
#include "MinHeap.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;  // Piazza said this is allowed

struct Node {  // Creating a Node Struct
    string Word;
    vector<Node*> Neighbors;  // Neighboring Nodes
    int Huerisitc;            // H Value
    int Distance;             // G Value
    int Priotity;             // F
    bool visited;             // Boolean used for A*
    bool explored;             
};

int helperHueristic(string s1, string s2);  // Helper Function (Hueristic) Prototype that calculates H value
void BuildGraph(
        string s1,
        string s2,
        set<string> set,
        vector<string> bank,
        map<string, Node*> searcher);                               // Helper Function (Build Graph) Prototype
void Dijkstras(map<string, Node*> searcher, string s1, string s2);  // Dijkstras Algorithm (A* Search) Prototype

int main(int argc, char* argv[]) {
    int numWords = 0;              // Counts number of words in txt file
    set<string> wordBank1;         // Creating a set, used to hold words in txt file
    vector<string> Word;           // Storage for Words
    map<string, Node*> NodeValue;  // Used to hold Node Struct of a string

    string temp;  // String variable used to temporarily hold variables

    if (argc != 4) {  // Must be 3 arguments, excluding ./Program (4 total)
        throw exception();
    }

    string startStr = argv[1];                                   // Start String
    for (long unsigned int i = 0; i < startStr.length(); i++) {  // Loop used to capitalize string
        startStr[i] = toupper(startStr[i]);
    }

    string targetStr = argv[2];                                   // Target String
    for (long unsigned int i = 0; i < targetStr.length(); i++) {  // Loop used to capitalize string
        targetStr[i] = toupper(targetStr[i]);
    }

    if (startStr.length() != targetStr.length()) {  // If input string and target string are not the same length
        throw exception();
    }

    if (startStr.compare(targetStr) == 0) {  // If input string and target string are the same string
        cout << 0 << endl;
        cout << 0 << endl;
    }

    ifstream myfile;  // Opening txt.file
    myfile.open(argv[3]);

    if (!myfile) {  // Error Checking if file doesn't open
        throw exception();
    }

    myfile >> numWords;  // Inputs number of words in file, denoted by first line of file

    // Enter a list of all words into set
    for (int i = 0; i < numWords; i++) {
        myfile >> temp;  // Parse "string" lines one by one

        for (long unsigned int i = 0; i < temp.length(); i++) {  // Loop used to capitalize string
            temp[i] = toupper(temp[i]);
        }

        wordBank1.insert(temp);  // Insert string into set (Used later to see if word exists)
        Word.push_back(temp);    // Vector that holds all the words

        Node* WordNode = new Node();  // Dynamic Memory
        WordNode->Word = temp;
        WordNode->Huerisitc = helperHueristic(temp, targetStr);
        WordNode->Distance = 0;
        WordNode->visited = false;

        NodeValue.insert(make_pair(temp, WordNode));  // Inserting Intital Strings into Map
    }

    BuildGraph(startStr, targetStr, wordBank1, Word, NodeValue);  // Builds Graph (Adjacency List)
    Dijkstras(NodeValue, startStr, targetStr);                    // Calls Dijkstras (A* Search)
}
void Dijkstras(
        map<string, Node*> NodeValue, string Input, string Target) {  // Reference to Lecture Notes (Searching Graph)
    int expansions = 0;

    MinHeap<string> pq(2);  // Priority Queue in MinHeap.h

    map<string, Node*>::iterator it;
    it = NodeValue.find(Input);

    int h = it->second->Huerisitc;
    int n = Input.length();          // Should be the same size
    int priority = h * (n + 1) + h;  // Priority Formula given by Prompt

    pq.add(it->first, priority);

    while (!pq.isEmpty()) {  // Main While Loop
        string current = pq.peek();
        map<string, Node*>::iterator it;
        it = NodeValue.find(current);  // V
        pq.remove();

        if (it->second->explored)
            continue;

        if (current != Target) {
            expansions++;  // Counts Expansions
        } else {           // Exit (Base Case) Condition
            break;
        }

        it->second->explored = true;

        for (long unsigned int i = 0; i < it->second->Neighbors.size(); i++) {  // For all nodes out going edges from V

            if (it->second->Neighbors[i]->visited == false
                || it->second->Neighbors[i]->Distance > it->second->Distance + 1) {
                it->second->Neighbors[i]->Distance = it->second->Distance + 1;  // G iterator happens here
                int h = it->second->Neighbors[i]->Huerisitc;
                int n = Input.length();  // Should be the same size
                int f = h + it->second->Neighbors[i]->Distance;
                int priority = f * (n + 1) + h;  // Priority Formula given by Prompt

                pq.add(it->second->Neighbors[i]->Word, priority); // Add to PQ
                it->second->Neighbors[i]->visited = true;
            }
        }
    }

    it = NodeValue.find(Target);  // V

    cout << it->second->Distance << endl; // Output statements
    cout << expansions << endl;
}

// Helper function to build graph
void BuildGraph(
        string Input,
        string Target,
        set<string> wordBank,
        vector<string> Word,
        map<string, Node*> NodeValue) {  // Build Graph (Adjacency List Helper)
    Node* WordNode;                      // Create Node

    for (long unsigned int i = 0; i < wordBank.size(); i++) {
        WordNode = new Node();
        WordNode->Word = Input;
        WordNode->Distance = 0;
        WordNode->visited = false;
        WordNode->Huerisitc = helperHueristic(Input, Target);

        for (long unsigned int j = 0; j < Word[i].length(); j++) {

            string temp1 = Word[i];  // Modified
            string temp2 = Word[i];  // Non-Modified

            for (int k = 65; k <= 90; k++) {
                temp1[j] = k;
                if (temp1.compare(temp2) == 0) {  // ERROR CHECK IF ORIGINAL
                    continue;                     // Skip if repeated
                }
                // Prompt ("Word file will not contain duplicates")
                else if (wordBank.count(temp1)) {  // Checks if word exist in set
                    map<string, Node*>::iterator it;
                    it = NodeValue.find(temp2);

                    it->second->Neighbors.push_back(NodeValue.find(temp1)->second);
                }
            }
        }
    }
}

int helperHueristic(string Input, string Target) {  // Helper Function that Calculates H
    int Heuristic = 0;
    if (Input.length() != Target.length()) {
        return 999999;  // Random Variable
    } else {
        for (long unsigned int i = 0; i < Input.length();
             i++) {  // Counts the number letters which do not match the letter
            if (Input[i] != Target[i]) {
                Heuristic++;
            }
        }
        return Heuristic;
    }
}