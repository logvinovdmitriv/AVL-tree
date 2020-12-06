#pragma once
#include <iostream>

using namespace std;

template <typename T>
class AVL
{
private:
	class Node
	{
	public:

		T data = T();
		Node* pLeft = nullptr;
		Node* pRight = nullptr;
		int height =NULL;
	};
	
	Node* Root = nullptr;
	int size = NULL;
	void insertNode(Node* current, Node* nodeForInsert);
	bool isExistNode(Node* current, T& data);
	void printNode(Node* current);
	void removeNode(Node* current, T& data);
	void removeLeafs(Node* current);

	static int Max(int a, int b);
	static int getHeight(Node* current);
	static int getBalance(Node* current);
	
	Node* leftRotate(Node* x)
	{
		Node* y = x->pRight;
		Node* T2 = y->pLeft;

		// Perform rotation  
		y->pLeft = x;
		x->pRight = T2;

		// Update heights  
		x->height = max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;
		y->height = max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;

		// Return new root  
		return y;
	}

	Node* rightRotate(Node* y)
	{
		Node* x = y->pLeft;
		Node* T2 = x->pRight;

		// Perform rotation  
		x->pRight = y;
		y->pLeft = T2;

		// Update heights  
		y->height = max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;
		x->height = max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;

		// Return new root  
		return x;
	}

public:
	bool isExist(T data);
	void insert(T data);
	void remove(T data);
	void printTree();
	void clear();
	int Size();
	~AVL();
};

template<typename T>
inline AVL<T>::~AVL()
{
	clear();
}

template<typename T>
inline void AVL<T>::printTree()
{
	if (size > 0)
	{
		printNode(Root);
	}
	else
	{
		cout << "Tree is empty" << endl;
	}

}

template<typename T>
inline void AVL<T>::clear()
{
	removeLeafs(Root);
	Root = nullptr;
}

template<typename T>
inline int AVL<T>::Size()
{
	return size;
}

template<typename T>
inline void AVL<T>::removeLeafs(Node* current)
{
	if (current == nullptr) return;

	/* first delete both subtrees */
	removeLeafs(current->pLeft);
	removeLeafs(current->pRight);

	/* then delete the node */
//	cout << "\n Deleting node: " << current->data;
	delete current;
	size--;
}

template<typename T>
inline int AVL<T>::Max(int a, int b)
{
	return ((a > b) ? a : b);
}

template<typename T>
inline int AVL<T>::getHeight(Node* current)
{
	if (current == nullptr)
		return 0;
	return current->height;
}

template<typename T>
inline int AVL<T>::getBalance(Node* current)
{
	if (current == nullptr)
		return 0;
	return (getHeight(current->pLeft) - getHeight(current->pRight));
}

template<typename T>
inline void AVL<T>::printNode(Node* current)
{
	if (current != nullptr)
	{
		cout << current->data << "\t";
		printNode(current->pLeft);
		printNode(current->pRight);

	};
}
template<typename T>
inline void AVL<T>::remove(T data)
{
	removeNode(Root, data);
}

template<typename T>
inline void AVL<T>::removeNode(Node* current, T& data)
{
	if (Root->data == data)
	{
		auto oldRoot = Root;
		Root = Root->pLeft;
		insertNode(Root, oldRoot->pRight);
		delete oldRoot;
		size--;
		current = Root;
		return;
	};
	if (current->pLeft != nullptr)
	{
		if (current->pLeft->data == data)
		{
			auto forDelete = current->pLeft;
			if (forDelete->pLeft != nullptr)
			{
				insertNode(Root, forDelete->pLeft);
			};
			if (forDelete->pRight != nullptr)
			{
				insertNode(Root, forDelete->pRight);
			}
			delete forDelete;
			size--;
			current->pLeft = nullptr;
			return;

		};
	}

	if (current->pRight != nullptr)
	{
		if (current->pRight->data == data)
		{
			auto forDelete = current->pRight;
			if (forDelete->pLeft != nullptr)
			{
				insertNode(Root, forDelete->pLeft);
			};
			if (forDelete->pRight != nullptr)
			{
				insertNode(Root, forDelete->pRight);
			}
			delete forDelete;
			size--;
			current->pRight = nullptr;
			return;
		};
	}
	if (current->data > data)
	{
		removeNode(current->pLeft, data);
	};
	if (current->data < data)
	{
		removeNode(current->pRight, data);
	};
}

template<typename T>
inline void AVL<T>::insert(T data)
{
	Node* nodeForInsert = new Node;
	nodeForInsert->data = data;
	auto current = Root;
	if (Root == nullptr)
	{
		Root = nodeForInsert;
	}
	insertNode(current, nodeForInsert);
	nodeForInsert->height = 1 + Max(getHeight(nodeForInsert->pLeft), getHeight(nodeForInsert->pRight));
	size++;

	//balance = pLeft->height-pRight->Height
	int balance = getBalance(nodeForInsert);

//если не сбалансированно !(-1<balance<1)
	  // Left Left Case  
	if ((balance > 1) && (nodeForInsert->data < nodeForInsert->pLeft->data))
		nodeForInsert = rightRotate(nodeForInsert);

	// Right Right Case  
	if ((balance < -1) && (nodeForInsert->data >nodeForInsert->pRight->data))
		nodeForInsert =  leftRotate(nodeForInsert);

	// Left Right Case  
	if ((balance > 1) && (nodeForInsert->data > nodeForInsert->pLeft->data))
	{
		nodeForInsert->pLeft = leftRotate(nodeForInsert->pLeft);
		nodeForInsert = rightRotate(nodeForInsert);
	}

	// Right Left Case  
	if ((balance < -1) && (nodeForInsert->data < nodeForInsert->pRight->data))
	{
		nodeForInsert->pRight = rightRotate(nodeForInsert->pRight);
		nodeForInsert = leftRotate(nodeForInsert);
	}


}

template<typename T>
inline void AVL<T>::insertNode(Node* current, Node* nodeForInsert)
{
	if (current == nullptr)
	{
		current = nodeForInsert;
	};

	if (nodeForInsert != nullptr)
	{
		if (nodeForInsert->data < current->data)
		{
			if (current->pLeft == nullptr)
			{
				current->pLeft = nodeForInsert;
			}
			else
			{
				insertNode(current->pLeft, nodeForInsert);
			}

		};
		if (nodeForInsert->data > current->data)
		{
			if (current->pRight == nullptr)
			{
				current->pRight = nodeForInsert;
			}
			else
			{
				insertNode(current->pRight, nodeForInsert);
			}

		};

		if (nodeForInsert->data == current->data)
		{
			current->data = nodeForInsert->data;
		};

	};

}


template<typename T>
inline bool AVL<T>::isExist(T data)
{
	return isExistNode(Root, data);
};

template<typename T>
inline bool AVL<T>::isExistNode(Node* current, T& data)
{
	if (current->data == data)
	{
		return true;
	};
	isExistNode(current->pLeft, data);
	isExistNode(current->pRight, data);
	return false;
};
