// ------------------------------------------------ bintree.cpp --------------------------------------------------------
// Brent Stone CSS 343 Section C
// January 23rd, 2016
// January 29th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The bintree.cpp files does operations on the bintree object.  They include search, insert, build a tree
//			 from an array, build an array from a tree, get the height of a node, return if a tree is empty
//			 and destroys bintree objects.
// --------------------------------------------------------------------------------------------------------------------
// Assumptions - bintree objects are assumed to be less than 100 and all data entry is correct.
// --------------------------------------------------------------------------------------------------------------------
#include "bintree.h"
#include <algorithm>

// --------------------- operator<< -----------------------------
// Overloaded<<: Calls inOrderTraverse() to print tree inOrder
// Preconditions: bintree object
// Postconditions: bintree object displayed
// --------------------------------------------------------------
ostream& operator<<(ostream& output, const BinTree& t)
{
	t.inOrderTraverse(t.root, output);
	output << endl;
	return output;
}

// --------------------- inOrderTraverse ------------------------
// In Order Traverse: print tree inOrder
// Preconditions: bintree object
// Postconditions: bintree object displayed
// --------------------------------------------------------------
void BinTree::inOrderTraverse(Node * r, ostream& out) const
{
	if (r != NULL)
	{
		inOrderTraverse(r->left, out); //left first for inorder
		out << *(r->data) << " ";
		inOrderTraverse(r->right, out);
	}
}


//------------------------- BinTree() ----------------------------
// Default constructor: Creates a binTree object
// Preconditions: None
// Postconditions: BinTree object created.
// ---------------------------------------------------------------
BinTree::BinTree()
{
	this->root = NULL;
}

//------------------------- ~BinTree() ----------------------------
// Destructor: Deletes a bintree object, calls make empty()
// Preconditions: bintree object
// Postconditions: bintree deleted
// ----------------------------------------------------------------
BinTree::~BinTree()
{
	this->makeEmpty();
}

//------------------------- BinTree() --------------------------------
// Copy constructor: Creates a bintree object and performs a deep
//					 copy calls on copyTree to perform deep copy
// Preconditions: None
// Postconditions: BinTree object created and copied
// --------------------------------------------------------------------
BinTree::BinTree(const BinTree &tree)
{
	copyTree(tree.root,this->root);
}

//------------------------- operator= ----------------------------------
// Assignment Operator=: Copies the bintree object to a another bintree
//						 object. If the objects are not equal, the
//						 operator clears the bintree object first.
// Preconditions: Bintree object is initilized and created
// Postconditions: Bintree object is copied
// ---------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& rhs)
{
	if (*this == rhs)				//if equal return
	{
		return *this;
	}
	else
	{
		this->makeEmpty();				//first makes empty
		copyTree(rhs.root, this->root); //then calls on copyTree
		return *this;
	}
}

//------------------------- copyTree ---------------------------------------
// CopyTree: Helper function for the assignemnet operator, copies a bintree
//			 object recursively/
// Preconditions: Bintree object is initilized and created
// Postconditions: Bintree object is copied
// --------------------------------------------------------------------------
void BinTree::copyTree(Node * node, Node *& nNode)
{
	if (node != NULL)					//preoder traversal;
	{
		nNode = new Node;				//new node
		NodeData *insert = new NodeData(*(node->data));  //new node data,that copies to insert(temp)
		nNode->data = insert;					//copies nNode data from insert
		copyTree(node->left, nNode->left);      //recursive, left
		copyTree(node->right, nNode->right);	//recursive, right
	}
	else
	{
		nNode = NULL;							//empty
	}
}


//------------------------- operator== -------------------------------------
// Overloaded== :  Checks if two binTtree objects are equal. Calls
//				   areTreesEqual() helper function
// Preconditions: None
// Postconditions: returns result from areTreesEqual
// -------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &tree) const
{
	return areTreesEqaul(this->root, tree.root);
}

//------------------------- operator!= -------------------------------------
// Overloaded!= : Checks if two bintree objects are not equal.
//				  Calls the areTreesEqual() helper function
// Preconditions: None
// Postconditions: returns result from !areTreesEqual
// -------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &tree) const
{
	return !(areTreesEqaul(this->root, tree.root));
}

//------------------------- areTreesEqual ----------------------------------
// areTreesEqual= : Checks if two bintree objects are equal.
//				    Helper fucntion for == & !=
// Preconditions: 2 bintree objects
// Postconditions: returns result from !areTreesEqual
// -------------------------------------------------------------------------
bool BinTree::areTreesEqaul(Node *t1, Node *t2) const
{
	if (t1 == NULL && t2 == NULL)		//this case checks if both trees are null
	{
		return true;
	}
	else if (t1 == NULL || t2 == NULL)	//checks if one Node is Null and the other is not
	{
		return false;
	}
	else if (*(t1->data) == *(t2->data) && t1->left == NULL && t2->left == NULL && t1->right == NULL && t2->right == NULL) //Speical Case where node data is equal but nodes have no children
	{
		return true;
	}
	return(*(t1->data) == *(t2->data) && areTreesEqaul(t1->left, t2->left) && areTreesEqaul(t1->right, t2->right)); //recursively moves throughout the tree and checks data

}

//------------------------- retrieve ----------------------------------------
// retrieve : Checks if the data is found within a bintree object.
//			  Non-recursive function that checks for nodedata.
// Preconditions: a tree that is be initilized with nodeData
// Postconditions: returns if data is found within object
// --------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &d, NodeData* &dFind)
{
	Node *current = root;
	bool search = false;

	if (current == NULL)		//root is empty thus tree is empty
	{
		dFind == NULL;
		return false;
	}

	while (!search)									//while loop
	{
		if (current != NULL && d == *(current->data))	//if data is found
		{
			search = true;							//bool search variable = true
			dFind = current->data;					//point to the data
			return search;							//return true
		}
		else if(current != NULL && d < *(current->data))
		{
			current = current->left;				//data is less than, so move left
		}
		else if (current != NULL && d > *(current->data))
		{
			current = current->right;			//data is greater than, so move right
		}
		else
		{
			return false;						//not found
		}
	}
}

// --------------------- getHeight ----------------------------------------
// GetHeight: Returns the height of a given node in bintree object
//			  uses 2 helper functions, findNode and getHeightHeleper.
// Preconditions: NodeData data that will be searched
// Postconditions: returns the height of the node in a bintree ojbect
// -----------------------------------------------------------------------
int BinTree::getHeight(const NodeData &d) const
{
	if (root == NULL)			//root is null, tree empty, return 0
	{
		return 0;
	}
	Node *found = NULL;			//node pointer to look for the node
	findNode(d, found, root);	//seach for node
	return getHeightHelper(found);	//return hight if found
}

// --------------------- findNode ---------------------------------------
// findNode: recursively searches for node within bintree object
// Preconditions: NodeData data, Node pointer to point to found node
//				  and starting root node.
// Postconditions: if found points to the location of the node
// ----------------------------------------------------------------------
void BinTree::findNode(const NodeData& d, Node* &cur, Node* rt) const
{
	if(rt != NULL)
	{
		findNode(d, cur, rt->left);		//left
		if (*rt->data == d)				//if found set to current pointer
		{
			cur = rt;
		}
		findNode(d, cur, rt->right);	//right
	}
}

// --------------------- getHeightHelper --------------------------------
// GetHightHelper: recursively searches for node within bintree object
// Preconditions: Node pointer
// Postconditions: retunrs location of found node.
// ----------------------------------------------------------------------
int BinTree::getHeightHelper(Node* foundNode) const
{
	if (foundNode == NULL)	//leafnode
	{
		return 0;
	}
	else
	{
		return 1 + max(getHeightHelper(foundNode->left), getHeightHelper(foundNode->right)); //returns the height
	}
}


// --------------------- bstreeToArray -------------------------------
// bstreeToArray: copies all data from bintree data to an array
//				  call addToArray() helper function and empties tree
// Preconditions: Nodedata pointer to array
// Postconditions: transfers data to array
// --------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arr[])
{
	int index = 0;								//index
	addToArray(arr, root, index);	//helper
	this->makeEmpty();
}

// --------------------- addToArray ---------------------------------
// Add To Array: Helper function that takes nodes and places
// Preconditions: bintree object
// Postconditions: reutrns position in array to place data
// ------------------------------------------------------------------
void BinTree::addToArray(NodeData* arr[], Node *cur, int& index)
{
    if (cur != NULL)
    {
        addToArray(arr, cur->left, index);	//left
        NodeData* insert = new NodeData(*cur->data); //new NodeData insert
        arr[index] = insert;								//insert into arry using index
        index++;														//increment index
        addToArray(arr, cur->right, index); //right
    }

}

// --------------------- arrayToBSTree -------------------------------
// Array to BSTree: copies all data from an array and builds a
//					balanced bintree object.  Calls addToTree() to help
//					build the tree
// Preconditions: arry filled wit nodeData objecs
// Postconditions: builds balanced bstree
// -------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[])
{
	this->makeEmpty();			//clears current bintree object
	int count = 0;

	for (int i = 0 ; i < 100; i++) //checks how many indexes are being used
	{
		if (arr[i] != NULL)
		{
			count++;
		}
		else
		{
			arr[i] = NULL;			//sets the non used ones to null
		}
	}

	addToTree(arr, root, 0, count-1); //call helper function
}

// --------------------- addToTree ----------------------------------
// Add To Tree: function that builds a balanced bstree object
//				recursively. Helper function for arrayToBSTree
// Preconditions: arry filled wit nodeData objecs
// Postconditions: builds balanced bstree
// ------------------------------------------------------------------
void BinTree::addToTree(NodeData* arr[], Node * cur, int low, int high)
{
	if (low > high)		//end of array
	{
		cur = NULL;
	}
	else
	{
		int mid = (high + low) / 2;		//using formual to find midpoint
		NodeData *temp;					//Nodedata pointer
		temp = arr[mid];				//pointer = data
		arr[mid] = NULL;				//array = NULL
		insert(temp);					//call insert

		addToTree(arr, cur, low, mid - 1);		//recursively call left side of index
		addToTree(arr, cur, mid + 1, high);		//recursively call right side of index
	}
}

//------------------------- isEmpty -----------------------------------
// Is Empty: checks if bintree object is empty
// Preconditions: None
// Postconditions: nothing changes
// --------------------------------------------------------------------
bool BinTree::isEmpty()const
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//------------------------- makeEmpty ---------------------------------
// Make Empty: Clears the BinTre object, calls clearTree helper function
// Preconditions: bintree object
// Postconditions: clears bintreee object
// --------------------------------------------------------------------
void BinTree::makeEmpty()
{
	clearTree(this->root);
}

//------------------------- clearTree ---------------------------------
// Clear Tree: Clears Tree, helper function of makeEmpty
// Preconditions: bintree object
// Postconditions: clears bintreee object
// --------------------------------------------------------------------
void BinTree::clearTree(Node *&rt)
{
	if (rt != NULL)
	{
		clearTree(rt->left);		//left
		clearTree(rt->right);		//right
		delete rt->data;			//delete NodeData
		rt->data = NULL;			//NodeData set To NULL
		delete rt;					//Delete node pointer
		rt = NULL;					//set to Null
	}
	else
	{
		rt = NULL;					//sets root to null
	}
}

//------------------------- insert ----------------------------------------
// Insert:  inserts node with Nodedata into bintree object.
//			Calls recursiveInsert()
// Preconditions: None
// Postconditions: adds node to bintree
// ------------------------------------------------------------------------
bool BinTree::insert(NodeData* nodeData)
{
	if (root == NULL)
	{
		root = new Node;		//creates new node for root
		root->data = nodeData;	//copies data
		root->left = NULL;		//left child is NULL
		root->right = NULL;		//right child is NULL
		return true;			//insert successful
	}
	else
	{
		Node *current = root;				//pointer to traverse
		recursiveInsert(root, nodeData);	//call function
	}
}

//------------------------- recursiveInsert ---------------------------------
// Recursive Insert:  inserts node with Nodedata into bintree object.
// Preconditions: None
// Postconditions: adds node to bintree
// --------------------------------------------------------------------------
bool BinTree::recursiveInsert(Node* curr, NodeData *ins)
{
	if (*(ins) < *(curr->data))			//if nodedata is less than current pointer
	{
		if (curr->left == NULL)			//if left is null, insert new node
		{
			Node *insert = new Node;	//new node
			insert->data = ins;			//insert data
			insert->left = NULL;		//left child NULL
			insert->right = NULL;		//right child NULL
			curr->left = insert;		//point current node to new node
			return true;
		}
		else
		{
			recursiveInsert(curr->left, ins); //if not null keep searching for insertion point
		}
	}
	else if (*(ins) > *(curr->data))	//if node data is greater than current pointer
	{
		if (curr->right == NULL)		//if right is null insert new node
		{
			Node *insert = new Node;	//new node
			insert->data = ins;			//copy data
			insert->left = NULL;		//left child null
			insert->right = NULL;		//right child null
			curr->right = insert;		//point current ndoe to new node
			return true;
		}
		else
		{
			recursiveInsert(curr->right, ins);	//if not null keep searching for insertion point
		}
	}
	else
	{
		return false;	//return false, if there is duplicates
	}
}

//------------------------- displaySideways -------------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-------------------------------------------------------------------------------
void BinTree::displaySideways() const {
	sideways(root, 0);
}


//---------------------------- Sideways -----------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-------------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
