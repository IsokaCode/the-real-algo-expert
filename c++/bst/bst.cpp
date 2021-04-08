#include <iostream>
//#include <ostream>
#include <string>
#include "bst.h"


// Core Task 1
struct BST::Node
{
  KeyType key;
  ItemType item;
  Node* leftChild;
  Node* rightChild;
  Node(KeyType k, ItemType i)  //constructor 
  {
      key = k;
      item = i;
      leftChild = nullptr;
      rightChild = nullptr;
  };

};

// Node(KeyType key, ItemType item)
// {
//   key = key;
//   item = item;
//   leftChild = nullptr;
//   rightChild = nullptr;

// }


BST::Node* BST::leaf()
{
  return nullptr ;
}

bool BST::isLeaf(Node* n)
{
  return (n == nullptr);
}

BST::BST() // constructor
{
  root = nullptr;
}

// IMPORTANT - deep deletes and shallow copies are dangerous
BST::~BST() // deconstructor - deletes all nodes in the tree
{
	deepDelete(root);
}
// Deep manual copy constructor
BST::BST(const BST& original) // A copy constructor (a constructor) that has (a constant reference to) another object of the same class as a parameter.
{
	root = deepCopy(original.root);
}
// when an existing object is being overwritten using the assignment operator (e.g. 't1 = t2').
BST& BST::operator=(const BST& original) // copy operator
{
	if (this == &original)
		return *this;

	deepDelete(root);
	root = deepCopy(original.root);

	return *this;
}

BST& BST::operator=(BST&& original) // Move operator - gets used whenever the compiler knows that the original object will not be used again or the user explicitly calls 'std::move()' on an object
{
  if (this == &original)
		return *this;

	deepDelete(root);
	root = original.root;
	original.root = nullptr;

	return *this;
}

// iterative check
/* BST::ItemType* BST::lookup(KeyType soughtKey)
{
  // descend tree 
  // check each node until it finds sought key
  // when sought key is found, return a pointer to the corresponding item
  // if the key is not found then return a null pointer
  // while current node != to nullptr or sought key
  //track current position by introducing a pointer varible to point to 'current' node
  Node* current = root;

	while (!BST::isLeaf(current))
	{
		if (current->key == soughtKey)
			return &current->item;

		if (soughtKey < current->key)
			current = current->leftChild;
		else
			current = current->rightChild;
	}

	if (!BST::isLeaf(current))
		return &current->item;

	return nullptr;

} */

//recursive check
BST::ItemType* BST::lookup(KeyType soughtKey) // wrapper function
{

  lookupRec(soughtKey, root);
  

  return nullptr;
}

BST::ItemType* BST::lookupRec(KeyType soughtKey, Node* current) // worker function
{
    
    if (BST::isLeaf(current))
    {
      return nullptr;
    }

    else
    {
      if (soughtKey < current->key)
        lookupRec(soughtKey,current->leftChild);


      else if (soughtKey > current->key)
        lookupRec(soughtKey, current->rightChild);
      	
      else if (current->key == soughtKey)
			  return &current->item;
    }
   return nullptr; 
}

//adding a Node to the tree
void BST::insert(KeyType key, ItemType item) //wrapper function
{
  addNodeInteral(key, item, root);
}
 
void BST::addNodeInteral(KeyType key,ItemType item, Node*& current) //worker function
{
  if(isLeaf(current))
  {
    Node* newNode = new Node(key, item); // Node constructor for new instance of node
    current = newNode;
  }
  else if (key < current->key)
  {
    if(current->leftChild != nullptr)
    {
      addNodeInteral(key, item, current->leftChild);
    }
    else
    {
      current->leftChild = new Node(key,item);
    }
  }
  else if (key > current->key)
  {
    if(current->rightChild != nullptr)
    {
      addNodeInteral(key, item, current->rightChild);
    }
    else
    {
      current->rightChild = new Node(key,item);
    }
  }
  else
  {
    std::cout << " The key " << key << " has already been added to the tree\n";
  }
  // debugging implementation
/*   else if (key == current->key) {
		current->item = item;
	}
	else if (key < current->key) {
		addNodeInteral(key, item, current->leftChild);
	}
	else if (key > current->key) {
		addNodeInteral(key, item, current->rightChild);
	}  */
}

//print dictionairy enteries inorder
void BST::displayEntries() //wrapper function
{
  displayInOrder(root);
}

void BST::displayInOrder(Node* current) //worker function
{
  if (isLeaf(current))
		return;

	displayInOrder(current->leftChild);

	std::cout << current->key << " " << current->item << std::endl;

	displayInOrder(current->rightChild);
  // if(root != nullptr)
  // {
  //   if(current->leftChild != nullptr)
  //   {
  //     displayInOrder(current->leftChild);
  //   }
  //   std::cout << current->key << " " << current->item<< std::endl;
  //   if(current->rightChild != nullptr)
  //   {
  //     displayInOrder(current->rightChild);
  //   }
  // }
  // else
  // {
  //   std::cout << "The tree is empty\n";
  // }
}

//display tree structure 
void BST::displayTree()
{
  displayTreeRec(root, 0);

}
void BST::displayTreeRec(Node* current, int level)
{
  std::string tabs(level, '\t');

  if (isLeaf(current)) {
		std::cout << tabs << "LEAF" << std::endl;
	}
	else {
		std::cout << tabs << current->key << " " << current->item << std::endl;

		displayTreeRec(current->leftChild, level + 1);
		displayTreeRec(current->rightChild, level + 1);
	}

}


// remove node from tree
void BST::remove(KeyType key)
{
  removeRec(key, root);
}

void BST::removeRec(KeyType key, Node* current)
{
  if (key < current->key) 
  {
		removeRec(key, current->leftChild);
	}
	else if (key > current->key) 
  {
		removeRec(key, current->rightChild);
	}
	else 
  {
		if (isLeaf(current->leftChild) && isLeaf(current->rightChild)) // removes node when both children are leaves
		{
			delete current;
			current = nullptr;
		}
    // to handle the case when the node to be removed has an internal node as one child (and a leaf as the other)
		else if (isLeaf(current->leftChild)) 
    {
			Node* toRemove = current;
			current = current->rightChild;
			delete toRemove;
		}
		else if (isLeaf(current->rightChild))
		{
			Node* toRemove = current;
			current = current->leftChild;
			delete toRemove;
		}
    // to handle the case when the node to be removed has two internal nodes as children.
		else
		{
			Node* minimumNode = detachMinimumNode(current->rightChild); // call worker function
			minimumNode->rightChild = current->rightChild;
			minimumNode->leftChild = current->leftChild;
			Node* toRemove = current;
			current = minimumNode;
			delete toRemove;
		}
	}

}

// detach minimum node from the tree
BST::Node* BST::detachMinimumNode(Node* &current)
{
	Node* root = current;
	while (!isLeaf(current->leftChild))
	{
		root = current;
		current = current->leftChild;
	}

	root->leftChild = current->rightChild;

	return current;
}

// performs traversal, applying the 'delete' operator to each node in the tree.
void BST::deepDelete(Node*& current)
{
	if (isLeaf(current))
		return;

	deepDelete(current->leftChild);
	deepDelete(current->rightChild);

	delete current;
	current = nullptr;
}

// performs traversal, copies all the nodes of the tree recursively
BST::Node* BST::deepCopy(Node* current)
{
	if (isLeaf(current))
		return nullptr;

	Node* newNode = new Node(current->key, current->item);
	newNode->leftChild = deepCopy(current->leftChild);
	newNode->rightChild = deepCopy(current->rightChild);

	return newNode;
}


//for testing
/*int main()
{
  BST bst;

  
  bst.insert(2, "apple");
  bst.insert(5, "app");
  bst.insert(4, "ape");
  bst.insert(3, "pple");
  bst.displayEntries();
  bst.displayTree();
  //std::cout << mytree.displayEntries() << std::endl;
  return 0;
} */
