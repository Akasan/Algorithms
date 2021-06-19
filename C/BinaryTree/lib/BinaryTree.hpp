#pragma once
#include <iostream>
#include <vector>

struct Node{
public:
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int value;
    Node(int);
    void setLeft(Node*);
    void setRight(Node*);
};


Node make_graph_simple(std::vector<int>);
void print_left_right(Node);
