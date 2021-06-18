#include <iostream>
#include "BinaryTree.hpp"

int main(void){
		Node root(10);
		Node child_left(5);
		Node child_right(20);
		root.left = &child_left;
		root.right = &child_right;

		std::cout << root.value << " " << root.left->value << " " << root.right->value << std::endl;
}
