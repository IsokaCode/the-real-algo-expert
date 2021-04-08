//#ifndef BST
//#define BST
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <vector>
//using namespace std;
//Lab 2

// Core Task 1
class BST

{

  public:
    BST(); //= default;

    BST(const BST& original); // A copy constructor (a constructor) that has (a constant reference to) another object of the same class as a parameter.
	  BST(BST&& original);
    ~BST();
    // manual copy assignment operators
    BST& operator=(const BST& original); // when an existing object is being overwritten using the assignment operator (e.g. 't1 = t2').
	  BST& operator=(BST&& original); // Move operator - gets used whenever the compiler knows that the original object will not be used again or the user explicitly calls 'std::move()' on an object


    using KeyType = int;
    using ItemType = std::string;
   // int Node(KeyType, ItemType);

    ItemType* lookup(KeyType);
    void insert(KeyType, ItemType);
    void remove(KeyType);
    void displayEntries();
    void displayTree();

  private:
    struct Node;
    //Node* root;
    void addNodeInteral(KeyType,ItemType, Node*& current);
    void displayInOrder(Node* current);
    void displayTreeRec(Node* current, int level);
    void removeRec(KeyType, Node* current);
    Node* detachMinimumNode(Node* &);
    static void deepDelete(Node*& current);
    static Node* deepCopy(Node* current);
    static Node* leaf();
    static bool isLeaf(Node*);
    Node* root = leaf();
    ItemType* lookupRec(KeyType,Node*);
    //BST() = default;
  
};
//#endif //BST
