
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <string>
#include <iostream>

// forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

// treeNode class
template <class DataType>
class treeNode
{

    friend class binarySearchTree<DataType>;

private:
    // holds value of current node
    DataType value;
    // tree node objects holding the left and right nodes of the current node
    treeNode* leftNode;
    treeNode* rightNode;

public:
    // default constructor
    treeNode()
	{
    	leftNode = nullptr;
    	rightNode = nullptr;
	}
    // constructor
    treeNode(DataType newValue)
    {
    	value = newValue;
    	leftNode = nullptr;
    	rightNode = nullptr;
    }
    // functions to access the current node's right and left nodes
    treeNode* getLeft()
    {
    	return leftNode;
    }

    treeNode* getRight()
    {
    	return rightNode;
    }
    // functions to change the left and right node pointers
    void changeLeft(treeNode* newLeft)
    {
    	leftNode = new treeNode<DataType> (newLeft->getValue());
    }
    void changeRight(treeNode* newRight)
    {
    	rightNode = new treeNode<DataType> (newRight->getValue());
    }
    // function to change the value of the current node
    void changeValue(treeNode* newValue)
    {
    	value = newValue->getValue();

    }
    // returns the value of the current node
    DataType getValue()
    {
    	return value;
    }
    // returns pointer to the value of the current node
    DataType* getValuePointer()
    {
    	return &value;
    }
};

// binarySearchTree class
template <class DataType>
class binarySearchTree
{

private:
	// treeNode object holding the root of the tree
	treeNode<DataType>* root;
	// integer holding the size of the tree
	int sizeTree;
	// returns the node if found and the node before where it should go otherwise
	treeNode<DataType>* find(const DataType &searchItem);
	void changeRoot(DataType newRoot)
	{
		root = new treeNode<DataType> (newRoot);
	}
	//gets the root
	treeNode<DataType>* getRoot() const
	{
		return root;
	}
	// prints binary tree in order using recursion
	void printInOrder(treeNode<DataType>* currentNode) const;
	// overloading printInOrder function which prints binary tree in order using recursion to out
	void printInOrder(treeNode<DataType>* currentNode, std::ostream &out) const;
	// uses recursion to perform an in order traversal and calling the itemFound function for every item found
	void inOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const;
	// helper function to delete all the entries of the binary search tree being copied into
	void deleteAll(treeNode<DataType>* currentNode);
	// assignment operator helper function
	void assignmentHelper(treeNode<DataType>* currentFromNode);
	// erase helper function which actually deletes item
	void deleteIt(treeNode<DataType>* nodePtr);
	// uses recursion to perform a pre order traversal and calling the itemFound function for every item found
	void preOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const;
	// uses recursion to perform an out order traversal and calling the itemFound function for every item found
	void outOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const;
	// erase helper function
	void eraseHelper(treeNode<DataType>* currentNode, const DataType &deleteItem);
public:
	// default constructor
	binarySearchTree()
	{
		root = nullptr;
		sizeTree = 0;
	}
	// destructor
	virtual ~binarySearchTree()
	{
		deleteAll(root);
	}
	// copy constructor using preorder traversal
	binarySearchTree(const binarySearchTree<DataType> &from);
	// return true if the binary tree is empty
	bool empty() const
	{
		return sizeTree==0;
	}
	// Returns the number of items in the binary tree
	std::size_t size() const
	{
		return sizeTree;
	}
	// Display the contents of the binary tree in order by key
	void print() const;
	// Display the contents of the binary tree for debugging purposes
	void debug(std::ostream &out) const;
	// returns true if item is found and false otherwise
	bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
	// remove the specified item from the binary tree if found in the tree
	bool erase(const DataType &deleteItem);
	// Insert the item into the binary tree
	void insert(const DataType &newItem);
	// insert item into tree and if it already exists call dulpicateItemFound function
	void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
	// inorder traversal of the binary tree
	void traverse(void (*itemFound)(const DataType& foundItem)) const;
	//assignment operator using preorder traversal
	binarySearchTree<DataType> operator=(const binarySearchTree<DataType> &from);
	// Display the contents of the binary tree to out
	void print(std::ostream &out) const;
	// traverse preorder
	void traversePreOrder(void (*itemFound)(const DataType& foundItem)) const;
	// traverse outorder
	void traverseOutOrder(void (*itemFound)(const DataType& foundItem)) const;
};

template<class DataType>
// copy constructor using preorder traversal
binarySearchTree<DataType>::binarySearchTree(const binarySearchTree<DataType> &from)
{
	sizeTree=0;
	root = nullptr;
	// calling helper function which uses preorder traversal and recursion
	assignmentHelper(from.getRoot());

}
template<class DataType>
// returns the node if found and the node before where it should go otherwise
treeNode<DataType>* binarySearchTree<DataType>::find(const DataType &searchItem)
{
	// the first node to check is the root
	treeNode<DataType>* tempNode = root;
	// use helper function to find the position of the item if found or the node before where it should go
	treeNode<DataType>* currentNode;
	// use a while loop to search through the binary tree to see if the searchItem exists
	while(tempNode!=nullptr)
	{
		currentNode = tempNode;
		// if item is found return the node
		if(currentNode->getValue()==searchItem)
		{
			return currentNode;
		}
		// if the search item is smaller than the current node, look at the left child node
		else if(searchItem<currentNode->getValue())
		{
			tempNode = currentNode->getLeft();
		}
		// if search item is bigger than the current node, look at the right child node
		else
		{
			tempNode = currentNode->getRight();
		}
	}
	// return the node before where it should go if not found

	return currentNode;
}

template<class DataType>
// Insert the item into the binary tree
void binarySearchTree<DataType>::insert(const DataType &newItem)
{
	// make a tree node object for the new item
	treeNode<DataType>* newNode= new treeNode<DataType> (newItem);
	if(empty())
	{
		changeRoot(newItem);
		sizeTree++;
	}
	else
	{
		// use helper function to find the position of the item if found or the node before where it should go
		treeNode<DataType>* currentNode = find(newItem);
		// if node already exists, replace it
		if(currentNode->getValue()==newItem)
		{
			currentNode->changeValue(newNode);
		}
		// if the found node is larger than the new item, the new item should be the left child
		else if(newItem < currentNode->getValue())
		{
			currentNode->changeLeft(newNode);
			sizeTree++;
		}
		// if the found node is smaller than the new item, the new item should be the right child
		else
		{
			currentNode->changeRight(newNode);
			sizeTree++;

		}
	}
	// delete the new node
	delete newNode;

}

template<class DataType>
// prints binary tree in order using recursion
void binarySearchTree<DataType>::printInOrder(treeNode<DataType>* currentNode) const
{
	// if the current node is nullptr, return
	if(currentNode==nullptr)
		return;
	// recursively call left child nodes
	printInOrder((*currentNode).getLeft());
	// start printing left child nodes once you reach a nullptr node
	std::cout << (*currentNode).getValue() << std::endl;
	// recursively call right child nodes
	printInOrder((*currentNode).getRight());
}

template<class DataType>
// Display the contents of the binary tree in order by key
void binarySearchTree<DataType>::print() const
{
	// calling the print in order helper function starting from the root
	printInOrder(root);
}

template<class DataType>
// Display the contents of the binary tree for debugging purposes
void binarySearchTree<DataType>::debug(std::ostream &out) const
{
	// calling the print in order helper function starting from the root and printing to out
	printInOrder(root, out);
}

template<class DataType>
// Display the contents of the binary tree to out
void binarySearchTree<DataType>::print(std::ostream &out) const
{
	// calling the print in order helper function starting from the root and printing to out
	printInOrder(root, out);
}

template<class DataType>
// returns true if item is found and false otherwise
bool binarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType&))
{
	// the first node to check is the root
	treeNode<DataType>* currentNode = root;
	// use a while loop to search through the binary tree to see if the searchItem exists
	while(currentNode!=nullptr)
	{
		// if item is found call the passed function and return true
		if((*currentNode).getValue()==searchItem)
		{
			foundNode((*currentNode).getValue());
			return true;
		}
		// if the search item is smaller than the current node, look at the left child node
		else if(searchItem<(*currentNode).getValue())
		{
			currentNode = (*currentNode).getLeft();
		}
		// if search item is bigger than the current node, look at the right child node
		else
		{
			currentNode = (*currentNode).getRight();
		}
	}
	// return false if not found
	return false;
}

template<class DataType>
// remove the specified item from the binary tree if found in the tree
bool binarySearchTree<DataType>::erase(const DataType &deleteItem)
{
	// the first node to check is the root
	treeNode<DataType>* currentNode = root;
	// use a while loop to search through the binary tree to see if the searchItem exists
	while(currentNode!=nullptr)
	{
		// if item is found delete the node and reconstruct the tree accordingly
		if((*currentNode).getValue()==deleteItem)
		{
			eraseHelper(root, deleteItem);
			return true;
		}
		// if the search item is smaller than the current node, look at the left child node
		else if(deleteItem<(*currentNode).getValue())
		{
			currentNode = (*currentNode).getLeft();
		}
		// if search item is bigger than the current node, look at the right child node
		else
		{
			currentNode = (*currentNode).getRight();
		}
	}
	// return false if not found
	return false;
}

template<class DataType>
// insert item into tree and if it already exists call dulpicateItemFound function
void binarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
{
	treeNode<DataType>* newNode = new treeNode<DataType> (newItem);
	// use helper function to find the position of the item if found or the node before where it should go
	treeNode<DataType>* currentNode = find(newItem);
	if(empty())
	{
		changeRoot(newItem);
		sizeTree++;
	}
	else
	{
		// if node already exists, replace it
		if(currentNode->getValue()==newItem)
		{
			DataType* currentData = currentNode->getValuePointer();
			duplicateItemFound(*currentData, newItem);
		}
		// if the found node is larger than the new item, the new item should be the left child
		else if(newItem < currentNode->getValue())
		{
			currentNode->changeLeft(newNode);
			sizeTree++;
		}
		// if the found node is smaller than the new item, the new item should be the right child
		else
		{
			currentNode->changeRight(newNode);
			sizeTree++;
		}
	}
	delete newNode;
}

template<class DataType>
// overloading printInOrder function which prints binary tree in order using recursion to out
void binarySearchTree<DataType>::printInOrder(treeNode<DataType>* currentNode, std::ostream &out) const
{
	// if the current node is nullptr, return
	if(currentNode==nullptr)
		return;
	// recursively call left child nodes
	printInOrder((*currentNode).getLeft(), out);
	// start printing left child nodes once you reach a nullptr node
	out << (*currentNode).getValue() << std::endl;
	// recursively call right child nodes
	printInOrder((*currentNode).getRight(), out);
}

template<class DataType>
// uses recursion to perform an in order traversal and calling the itemFound function for every item found
void binarySearchTree<DataType>::inOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const
{
	// if the current node is nullptr, return
	if(currentNode==nullptr)
		return;
	// recursively call left child nodes
	inOrderTraversal((*currentNode).getLeft(), itemFound);
	// calling item found for every item found
	itemFound((*currentNode).getValue());
	// recursively call right child nodes
	inOrderTraversal((*currentNode).getRight(), itemFound);
}

template<class DataType>
// uses recursion to perform a pre order traversal and calling the itemFound function for every item found
void binarySearchTree<DataType>::preOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const
{
	// if the current node is nullptr, return
	if(currentNode==nullptr)
		return;
	// calling item found for every item found
	itemFound((*currentNode).getValue());
	// recursively call left child nodes
	preOrderTraversal((*currentNode).getLeft(), itemFound);
	// recursively call right child nodes
	preOrderTraversal((*currentNode).getRight(), itemFound);
}

template<class DataType>
// uses recursion to perform an out order traversal and calling the itemFound function for every item found
void binarySearchTree<DataType>::outOrderTraversal(treeNode<DataType>* currentNode, void (*itemFound)(const DataType& foundItem)) const
{
	// if the current node is nullptr, return
	if(currentNode==nullptr)
		return;
	// recursively call right child nodes
	outOrderTraversal((*currentNode).getRight(), itemFound);
	// calling item found for every item found
	itemFound((*currentNode).getValue());
	// recursively call left child nodes
	outOrderTraversal((*currentNode).getLeft(), itemFound);
}

template<class DataType>
// inorder traversal of the binary tree
void binarySearchTree<DataType>::traverse(void (*itemFound)(const DataType& foundItem)) const
{
	// calling helper function which uses recursion for an in order traversal
	inOrderTraversal(root, itemFound);
}

template<class DataType>

// traverse preorder
void binarySearchTree<DataType>::traversePreOrder(void (*itemFound)(const DataType& foundItem)) const
{
	// calling helper function which uses recursion for a pre order traversal
	preOrderTraversal(root, itemFound);
}

template<class DataType>
// traverse outorder
void binarySearchTree<DataType>::traverseOutOrder(void (*itemFound)(const DataType& foundItem)) const
{
	// calling helper function which uses recursion for an out order traversal
	outOrderTraversal(root, itemFound);
}

//assignment operator using preorder traversal
template <typename DataType>
binarySearchTree<DataType> binarySearchTree<DataType>::operator=(const binarySearchTree<DataType> &from)
{
	// if it's the same tree just return the address
	if(this==&from)
	{
		return *this;
	}
	else
	{
		// if not the same tree, delete all items from the tree beign copied into and copy everything using preorder traversal and recursion
		// calling helper functions to delete and copy
		deleteAll(root);
		assignmentHelper(from.getRoot());
	}
	return *this;
}

// assigment operator helper function using preorder traversal
template <typename DataType>
void binarySearchTree<DataType>::assignmentHelper(treeNode<DataType>* currentFromNode)
{
	// using preorder traversal and recursion to copy all the entries
	if(currentFromNode==nullptr)
	{
		return;
	}
	insert(currentFromNode->getValue());
	assignmentHelper(currentFromNode->getLeft());
	assignmentHelper(currentFromNode->getRight());

}

// deleting all the entries from the binary search tree being copied into
template <typename DataType>
void binarySearchTree<DataType>::deleteAll(treeNode<DataType>* currentNode)
{
	// using recursion to delete all the entries
	if(currentNode==nullptr)
	{
		return;
	}
	deleteAll(currentNode->getLeft());
	deleteAll(currentNode->getRight());
	// erasing each entry
	//erase(currentNode->getValue());

	delete currentNode;
	sizeTree--;
}

// erase helper function
template <typename DataType>
void binarySearchTree<DataType>::eraseHelper(treeNode<DataType>* currentNode, const DataType &deleteItem)
{
	// using recursion to delete all the entries
	if(currentNode==nullptr)
	{
		return;
	}
	deleteAll(currentNode->getLeft());
	deleteAll(currentNode->getRight());
	// erasing each entry
	//erase(currentNode->getValue());
	if(deleteItem==currentNode->getValue())
	{
		delete currentNode;
		sizeTree--;
	}
}

// delete all helper function
template <typename DataType>
void binarySearchTree<DataType>::deleteIt(treeNode<DataType>* nodePtr)
{
	treeNode<DataType>* tempNode = nullptr;

	// reattach left child if right child is nullptr
	if(nodePtr->getRight() ==nullptr)
	{
		tempNode =nodePtr;
		nodePtr = nodePtr ->getLeft();
		delete tempNode;
	}
	// if the node has 2 children
	else
	{
		// move one node right and go to the left most node
		tempNode = nodePtr -> getRight();
		while(tempNode->getLeft())
		{
			tempNode = tempNode->getLeft();
		}
		// reattach left subtree
		tempNode->changeLeft(nodePtr->getLeft());
		tempNode = nodePtr;
		// reattach right subtree
		nodePtr = nodePtr->getRight();
		delete tempNode;
		sizeTree--;
	}
}
#endif /* BINARYSEARCHTREE_H_ */
