// ------------------------------------------------ bintree.h --------------------------------------------------------
// Brent Stone CSS 343 Section C
// January 23rd, 2016
// January 29th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The bintree.cpp files does operations on the bintree object.  They include search, insert, build a tree
//			 from an array, build an array from a tree, get the height of a node, return if a tree is empty
//			 and destroys bintree objects.
// --------------------------------------------------------------------------------------------------------------------
// Assumptions - bintree objects are assumed to be less than 100 and all data entry is correct. #ifndef BINTREE_H
#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class BinTree
{
	//Overloaded <<
	friend ostream& operator<<(ostream &output, const BinTree &tree);

public:

	//Constructors and Destructors
	BinTree();													//Default Constructor
	~BinTree();													//Destructors
	BinTree(const BinTree &tree);				//copy constructor

	//Overloaded Operators
	BinTree& operator=(const BinTree& tree);	//assignment operator
	bool operator==(const BinTree &tree) const;	//==operator
	bool operator!=(const BinTree &tree) const;	//!=operator

	//Actions
	bool isEmpty()const;								//checks if empty
	void makeEmpty();										//empties tree
	void displaySideways() const;				//displays sideways
	bool insert(NodeData* nodeData);			//inserts Node
	bool retrieve(const NodeData &node, NodeData* &empNode); //gets node in tree
	int getHeight(const NodeData &node) const;	//returns height of node
	void bstreeToArray(NodeData* a[]);			//builds an array from bstree
	void arrayToBSTree(NodeData* a[]);			//builds a BSTree from an array

private:
struct  Node
{
	NodeData *data;
	Node *left;
	Node *right;
};
	Node* root;

//Utility Helper Functions
void sideways(Node*, int) const;					//Prints Sideways
void inOrderTraverse(Node* r,ostream& out) const;				//<< helper
bool recursiveInsert(Node *curr, NodeData* ins);	//Insert helper
void findNode(const NodeData& d, Node* &cur, Node* rt) const;//getHeight Helper, finds node
int getHeightHelper(Node* foundNode) const;				//also getHeightHelper
void copyTree(Node* node, Node *&nNode);			//Copyconstructor and assignment operator helper
bool areTreesEqaul(Node* t1, Node *t2) const;		//== operator helper
void clearTree(Node *&rt);							//Make empty helper
void addToArray(NodeData* arr[], Node *cur, int& index);	//bstree to array helper
void addToTree(NodeData* arr[], Node * cur, int low, int high); //arry to bstree helper

};


#endif
