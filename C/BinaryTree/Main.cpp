#include <vector>
#include <iostream>
#include "BinaryTree.hpp"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <random>


#define SIZE 5


int printNode(int cnt, Node node, int depth)
{
    for(int i=0; i<cnt; i++){
        std::cout << "-";
    }
    while(node.right != NULL){
        printNode(cnt+1, *node.right, depth);
        break;
    }
    for(int i=0; i<cnt; i++){
        std::cout << "-";
    }
    std::cout << node.value << std::endl;
    for(int i=0; i<cnt; i++){
        std::cout << "-";
    }
    while(node.left != NULL){
        printNode(cnt+1, *node.left, depth);
        break;
    }
    return depth +1;
}

int main(void){
	std::vector<int> array(SIZE);
	for(int i=0; i<array.size(); i++)array[i] = i+1;
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(array.begin(), array.end(), engine);

	Node root = make_graph_simple(array);
	printNode(0, root, 1);
}
