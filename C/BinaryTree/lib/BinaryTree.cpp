#include"BinaryTree.hpp"
#include<iostream>
#include<vector>
#include<algorithm>

Node::Node(int value)
{
	this->value = value;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}

void Node::setLeft(Node* node){
 	this->left = node;
}

void Node::setRight(Node* node){
   	this->right = node;
}


Node make_graph_simple(std::vector<int> array){
   	Node root(array[0]);
   	Node* currentNode = NULL;

   	for(int i=1; i<array.size(); i++){
 	   	currentNode = &root;

   	   	while(true){
   	   	   	if(array[i] < currentNode->value){
   	   	   	   	if(currentNode->left == NULL){
   	   	   	   	   	std::cout << "\tset to left" << std::endl;
   	   	   	   	   	currentNode->setLeft(new Node(array[i]));
   	   	   	   	   	break;
   	   	   	   	}
   	   	   	   	else{
   	   	   	   	   	std::cout << "\tgo to next left" << std::endl;
   	   	   	   	   	currentNode = currentNode->left;
   	   	   	   	   	continue;
   	   	   	   	}
            }
   	   	   	else{
   	   	   	   	if(currentNode->right == NULL){
   	   	   	   	   	std::cout << "\tset to right" << std::endl;
   	   	   	   	   	currentNode->setRight(new Node(array[i]));
   	   	   	   	   	break;
   	   	   	   	}
   	   	   	   	else{
   	   	   	   	   	std::cout << "\tgo to next right" << std::endl;
   	   	   	   	   	currentNode = currentNode->right;
   	   	   	   	   	continue;
   	   	   	   	}
            }
   	   	}
   	   	std::cout << "===============================================================" << std::endl;
   	}
   	return root;
}


void print_left_right(Node node){
   	std::cout << "VALUE: " << node.value << " ";
   	if(node.left != NULL){
   	   	std::cout << "LEFT: " << node.left->value << " ";
   	}
   	if(node.right != NULL){
  	   	std::cout << "RIGHT: " << node.right->value << "";
   	}
   	std::cout << std::endl;
}

