// Driver Code 
#include "AVL-tree.h"
int main()
{
	AVL<int>  tree;
	tree.insert(50);
	tree.insert(49);
	tree.insert(48);
	tree.insert(47);
	tree.insert(46);
	tree.insert(45);
	tree.insert(51);
	tree.insert(52);
	tree.insert(53);
	tree.insert(54);
	tree.insert(55);
	tree.printTree();
	cout << endl;

	tree.remove(47);
	tree.printTree();
	cout << endl;

	tree.remove(48);
	tree.printTree();
	cout << endl;
}