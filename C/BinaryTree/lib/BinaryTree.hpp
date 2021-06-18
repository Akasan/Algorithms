#pragma once

struct Node{
public:
		struct Node* parent;
		struct Node* left;
		struct Node* right;
		int value;
		Node(int);
};
