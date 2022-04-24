#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

int height(Node* node) {
	if (node == NULL) {
		return 0;
	}

	return 1 + max(height(node->left),height(node->right));
}

int rangeSum(Node *root, int L, int R) {
	
	//Base case - called on a null node -> return 0!
	int sum = 0;

	if (root == NULL) {
		return 0;
	}	

	if (root->key >= L && root->key <= R) {
		sum += root->key;
	}
	
	sum += rangeSum(root->left, L, R);
	sum += rangeSum(root->right, L, R);
	
	return sum;
	
	//Otherwise get the value of the left and right trees under you (recursive call)
	//Sum em
	//Should add node->key to the sum?
	//Return the sum!
}
    
bool isBalanced(Node *root) {
	int left;
	int right;

	if (root == NULL) {
		return true;
	}

	left = height(root->left);
	right = height(root->right);

	if (abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
		return true;
	}
	return 0;
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!

	//Check if there are subtrees under us
	//Are they balanced?

	//If all nodes are balanced return true!
}


/*

Given a binary tree, return the level order traversal of its nodes' values. (i.e. from left to right, level by level).


If you're given this binary tree as input:

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/
vector<vector<int>> levelOrder(Node* root) {
	vector<vector<int>> results;
    if (root == NULL) {
		return results;
	}
	queue<Node*> queue1;
	queue1.push(root);
	while (!queue1.empty()) {
		vector<int> level;
		int size = queue1.size();
		for (int i = 0; i < size; i++) {
			Node* current = queue1.front();
			queue1.pop();
			level.push_back(current->key);
			if (current->left) {
				queue1.push(current->left);
			}
			if (current->right) {
				queue1.push(current->right);
			}
		}
		results.push_back(level);
	}
	return results;
}