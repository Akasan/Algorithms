#pragma once
#include <iostream>
#include <vector>

struct Node{
public:
    struct Node* parent = NULL;
    struct Node* left = NULL;
    struct Node* right = NULL;
    int value;
    Node(int);
    void setParent(Node*);
    void setLeft(Node*);
    void setRight(Node*);
    bool existParent();
    bool existLeft();
    bool existRight();
};


Node make_graph_simple(std::vector<int>);
void print_left_right(Node);
