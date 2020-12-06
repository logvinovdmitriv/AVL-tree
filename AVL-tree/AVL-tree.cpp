#include <iostream>
#include "AVL-tree.h"
int main()
{
	AVL<int> tree;
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(7);

	tree.printTree();
	return 0;
};

