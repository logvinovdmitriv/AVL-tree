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
	Node* insertNode(Node* current, T data)
	{
		/* 1. Perform the normal BST insertion */
		if (current == nullptr)
			return(newNode(data));

		if (data < current->data)
			current->pLeft = insertNode(current->pLeft, data);
		else if (data > current->data)
			current->pRight = insertNode(current->pRight, data);
		else // Equal keys are not allowed in BST  
			return current;

		/* 2. Update getHeight of this ancestor current */
		current->height = 1 + max(getHeight(current->pLeft),
			getHeight(current->pRight));

		/* 3. Get the balance factor of this ancestor
			current to check whether this current became
			unbalanced */
		int balance = getBalance(current);

		// If this current becomes unbalanced, then  
		// there are 4 cases  

		// Left Left Case  
		if (balance > 1 && data < current->pLeft->data)
			return rightRotate(current);

		// Right Right Case  
		if (balance < -1 && data > current->pRight->data)
			return leftRotate(current);

		// Left Right Case  
		if (balance > 1 && data > current->pLeft->data)
		{
			current->pLeft = leftRotate(current->pLeft);
			return rightRotate(current);
		}

		// Right Left Case  
		if (balance < -1 && data < current->pRight->data)
		{
			current->pRight = rightRotate(current->pRight);
			return leftRotate(current);
		}

		/* return the (unchanged) current pointer */
		return current;
	}
	bool isExistNode(Node* current, T& data);
	void printNode(Node* current);
	void removeNode(Node* current, T& data);
	void removeLeafs(Node* current);
	void InsertLeftAndRightBranch(Node* current);

	static int Max(int a, int b);
	static int getHeight(Node* current);
	static int getBalance(Node* current);
	
	Node* leftRotate(Node* x)
	{
		if (x != nullptr)
		{
			Node* y = x->pRight;
			Node* T2 = nullptr;
			if (y != nullptr)
			{
				T2 = y->pLeft;

				// Perform rotation  
				y->pLeft = x;
				x->pRight = T2;

				// Update heights  
				x->height = Max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;
				y->height = Max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;

				// Return new root  
				return y;
			};

		}
		
	}

	Node* rightRotate(Node* y)
	{
		if (y != nullptr)
		{
			Node* x = y->pLeft;
			Node* T2 = nullptr;
			if (x != nullptr)
			{
				T2 = x->pRight;
				// Perform rotation 
				x->pRight = y;
				y->pLeft = T2;

				// Update heights  
				y->height = Max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;
				x->height = Max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;

				// Return new root  
				return x;
			};
			
		}
		
	}

	Node* newNode(T data)
	{
		Node* node = new Node();
		node->data = data;
		node->pLeft = nullptr;
		node->pRight = nullptr;
		node->height = 1; // new node is initially 
						// added at leaf 
		if (Root == nullptr)
		{
			Root = node;
		}
		return(node);
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
	if (Root == nullptr)
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		printNode(Root);
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
inline void AVL<T>::remove(T data)
{
	removeNode(Root, data);
}









template<typename T>
inline void AVL<T>::removeNode(Node* current, T& data)
{
	if (current != nullptr)
	{
		if (current->data == data && Root == current)
		{
			auto forDelete = current;
			Root = nullptr;
			if (forDelete->pLeft != nullptr)
			{
				InsertLeftAndRightBranch(forDelete->pLeft);
			};
			if (forDelete->pRight != nullptr)
			{
				InsertLeftAndRightBranch(forDelete->pRight);
			};
		};
		if (current->pLeft != nullptr)
		{
			if (current->pLeft->data == data)
			{
				auto forDelete = current->pLeft;
				current->pLeft = nullptr;
				if (forDelete->pLeft != nullptr)
				{
					InsertLeftAndRightBranch(forDelete->pLeft);
				};
				if (forDelete->pRight != nullptr)
				{
					InsertLeftAndRightBranch(forDelete->pRight);
				};
				return;
			};
		};

		if (current->pRight != nullptr)
		{
			if (current->pRight->data == data)
			{
				auto forDelete = current->pRight;
				current->pRight = nullptr;
				if (forDelete->pLeft != nullptr)
				{
					InsertLeftAndRightBranch(forDelete->pLeft);
				};
				if (forDelete->pRight != nullptr)
				{
					InsertLeftAndRightBranch(forDelete->pRight);
				};

				return;
			};
		};
		
		if (current->data > data)
		{
			removeNode(current->pLeft, data);
			return;
		};
		if (current->data < data)
		{
			removeNode(current->pRight, data);
			return;
		};
	}
	
	return;
}


template<typename T>
inline void AVL<T>::InsertLeftAndRightBranch(Node* current)
{
	if (current->pLeft != nullptr)
	{
		InsertLeftAndRightBranch(current->pLeft);
		
	};
	if (current->pRight != nullptr)
	{
		InsertLeftAndRightBranch(current->pRight);
		
	};
	if (current != nullptr)
	{
		insert(current->data);
	}
	
	return;
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
		cout <<"current = "<< current->data << endl;
		printNode(current->pLeft);
		printNode(current->pRight);

	};
}


template<typename T>
inline void AVL<T>::insert(T data)
{
	Root = insertNode(Root, data);
};



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

