// Driver Code 
#include "AVL-tree.h"
int main()
{
	AVL<int>  tree;
	tree.insert(7);
	tree.insert(4);
	tree.insert(5);
	tree.insert(3);
	tree.insert(1);
	tree.insert(100);
	tree.insert(200);
	tree.insert(300);


	tree.printTree();
	cout << endl;
	tree.remove(4);
	tree.printTree();
	cout << endl;
	tree.remove(100);
	tree.printTree();
	cout << endl;
}