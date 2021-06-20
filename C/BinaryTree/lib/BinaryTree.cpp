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
    node->parent = this;
    node->depth = this->depth + 1;
}

void Node::setRight(Node* node){
    this->right = node;
    node->parent = this;
    node->depth = this->depth + 1;
}

void Node::setParent(Node* node){
    this->parent = node;
    node->parent = this;
    node->depth = this->depth + 1;
}

bool Node::existParent(){
    if(this->parent == NULL) return false;
    else return true;
}

bool Node::existLeft(){
    if(this->left == NULL) return false;
    else return true;
}

bool Node::existRight(){
    if(this->right == NULL) return false;
    else return true;
}

Node make_graph_simple(std::vector<int> array){
    Node root(array[0]);
    Node* currentNode = NULL;
    
    for(int i=1; i<array.size(); i++){
        currentNode = &root;
    
        while(true){
            if(array[i] < currentNode->value){
                if(currentNode->existLeft()){
                    std::cout << "\tgo to next left" << std::endl;
                    currentNode = currentNode->left;
                    continue;
                }
                else{
                    std::cout << "\tset to left" << std::endl;
                    currentNode->setLeft(new Node(array[i]));
                    break;
                }
            }
            else{
                if(currentNode->existRight()){
                    std::cout << "\tgo to next right" << std::endl;
                    currentNode = currentNode->right;
                    continue;
                }
                else{
                    std::cout << "\tset to right" << std::endl;
                    currentNode->setRight(new Node(array[i]));
                    break;
                }
            }
        }
        std::cout << "===============================================================" << std::endl;
    }
    return root;
}


void print_left_right(Node node){
    std::cout << "VALUE: " << node.value << " ";
    if(node.existLeft()){
        std::cout << "LEFT: " << node.left->value << " ";
    }
    if(node.existRight()){
        std::cout << "RIGHT: " << node.right->value << "";
    }
    std::cout << std::endl;
}

