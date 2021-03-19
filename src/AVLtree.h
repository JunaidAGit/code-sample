//This code is from https://rosettacode.org/wiki/AVL_tree#C.2B.2B
// with some slight modifications and extra functions by Wyatt S Carpenter
// (marked where appropriate)
#include <iostream>
#include "ResizableArray.h"
//#include "Order.cpp"

namespace std {

/* AVL node */
template<class T>
class AVLnode {
public:
	//Element
	T key;

	//The balance of hte tree
	int balance;

	//Each node of the tree
	AVLnode *left, *right, *parent;

	//The components of each node
	AVLnode(T k, AVLnode *p) :
			key(k), balance(0), parent(p), left(NULL), right(NULL) {
	}

	//Deletion methods for the left and right nodes of a tree
	~AVLnode() {
		delete left;
		delete right;
	}
};

/* AVL tree */
template<class T>
class AVLtree {

//Public methods
public:
	AVLtree(void);
	~AVLtree(void);
	bool insert(T key);
	bool remove(T key); //Wyatt changed removeKey to this
	void printBalance();

	//Enumeration to get preorder, inorder, and postorder traversal
	enum Order {
		pre, in, post
	};
	ResizableArray<T> toResizableArray(Order order = Order::in); //Wyatt added this fn
	T* find(T key); //Wyatt added this
	int getItemCount();

//Private variables which contain all of the elements of the AVLtree
private:
	AVLnode<T> *root;

	AVLnode<T>* rotateLeft(AVLnode<T> *a);
	AVLnode<T>* rotateRight(AVLnode<T> *a);
	AVLnode<T>* rotateLeftThenRight(AVLnode<T> *n);
	AVLnode<T>* rotateRightThenLeft(AVLnode<T> *n);
	void rebalance(AVLnode<T> *n);
	int height(AVLnode<T> *n);
	void setBalance(AVLnode<T> *n);
	void printBalance(AVLnode<T> *n);
	void clearNode(AVLnode<T> *n);
	ResizableArray<T> RA; //Wyatt added this
	void populateRA(AVLnode<T> *node, Order order = in); //Wyatt added this fn
};

/* AVL class definition */
template<class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
	setBalance(n);

	//Checks the heights to see where to balance
	if (n->balance == -2) {
		if (height(n->left->left) >= height(n->left->right))
			n = rotateRight(n);
		else
			n = rotateLeftThenRight(n);
	} else if (n->balance == 2) {
		if (height(n->right->right) >= height(n->right->left))
			n = rotateLeft(n);
		else
			n = rotateRightThenLeft(n);
	}

	//Balancing
	if (n->parent != NULL) {
		rebalance(n->parent);
	} else {
		root = n;
	}
}

//Rotation for left
template<class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
	AVLnode<T> *b = a->right;
	b->parent = a->parent;
	a->right = b->left;

	//Checking for NULLs
	if (a->right != NULL)
		a->right->parent = a;

	//Setting what to rotate
	b->left = a;
	a->parent = b;

	//Rotation
	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		} else {
			b->parent->left = b;
		}
	}

	//Balancing
	setBalance(a);
	setBalance(b);
	return b;
}

//Rotation for right
template<class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
	AVLnode<T> *b = a->left;
	b->parent = a->parent;
	a->left = b->right;

	//Checking for NULLS
	if (a->left != NULL)
		a->left->parent = a;

	//Setting rotations
	b->right = a;
	a->parent = b;


	//Rotating
	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		} else {
			b->parent->left = b;
		}
	}

	//Balancing
	setBalance(a);
	setBalance(b);
	return b;
}

//rotation for Left then Right
template<class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

//Rotations for Right then Left
template<class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

//Returns the height of the tree
template<class T>
int AVLtree<T>::height(AVLnode<T> *n) {
	if (n == NULL)
		return -1;
	return 1 + std::max(height(n->left), height(n->right));
}

//Sets the balance of the tree
template<class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
	n->balance = height(n->right) - height(n->left);
}

//Prints balance
template<class T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
	if (n != NULL) {
		printBalance(n->left);
		std::cout << n->balance << " ";
		printBalance(n->right);
	}
}

//Creation method
template<class T>
AVLtree<T>::AVLtree(void) :
		root(NULL) {
}

//Deletion method
template<class T>
AVLtree<T>::~AVLtree(void) {
	delete root;
}

//Insertion method which encapsulates duplicate error checking
template<class T>
bool AVLtree<T>::insert(T key) {
	if (root == NULL) {
		root = new AVLnode<T>(key, NULL);
	} else {
		AVLnode<T> *n = root, *parent;

		//Iterates through and finds a place to insert
		while (true) {
			if (n->key == key) {

				n->key = key; //this line added by Wyatt to overwrite the node according to spec
				return true;            	//polarity reversed by Wyatt
			}
			parent = n;

			//Decides whether to go left or right
			bool goLeft = n->key > key;
			n = goLeft ? n->left : n->right;

			//Places it left or right
			if (n == NULL) {
				if (goLeft) {
					parent->left = new AVLnode<T>(key, parent);
				} else {
					parent->right = new AVLnode<T>(key, parent);
				}


				//Rebalances the tree
				rebalance(parent);
				break;
			}
		}
	}

	return false; //polarity reversed by Wyatt
}

//Method used to remove an element from the tree. Encapsulates
template<class T>
bool AVLtree<T>::remove(T delKey) { //Wyatt changed removeKey to this
	if (root == NULL) {
		return false; //Wyatt added this line
	}
	AVLnode<T> *n = root, *parent = root, *delNode = NULL, *child = root;

	//Checking for whether the tree hits a NULL
	while (child != NULL) {
		parent = n;
		n = child;
		child = delKey >= n->key ? n->right : n->left;
		if (delKey == n->key)
			delNode = n;
	}

	//If the deletion node is legitimate, traverses through and finds it
	if (delNode != NULL) {
		delNode->key = n->key;

		child = n->left != NULL ? n->left : n->right;

		//Removal
		if (root->key == delKey) {
			root = child;
		} else {
			if (parent->left == n) {
				parent->left = child;
			} else {
				parent->right = child;
			}

			//Rebalances after removal
			rebalance(parent);
		}
		return true; //Wyatt added this line
	} else {         //Wyatt added this clause
		return false;
	}
}

//Method used to obtain the balance of the tree
template<class T>
void AVLtree<T>::printBalance() {
	printBalance(root);
	std::cout << std::endl;
}

//Converts the AVLtree to a resizableArray
template<class T>
ResizableArray<T> AVLtree<T>::toResizableArray(Order order) {

	//Populates the resizableArray
	RA = ResizableArray<T>();
	populateRA(root, order);


	return RA;
}

//Helper method for the conversion. Populates the ResizableArray
template<class T>
void AVLtree<T>::populateRA(AVLnode<T> *node, Order order) {

	//Throws an error if the end of the tree is reached
	try {
		//Ends when the node reaches its send
		if (node == NULL) {
			return;
		}
	} catch (exception e) {
		cerr << "Error: Reached the end of the tree";
	}

	//If it is preorder, add to the resizableArray then go to the left node
	if (order == pre) {
		RA.add(node->key);
	}
	populateRA(node->left);

	//If it is inorder, add to the resizableArray then go to the right node
	if (order == in) {
		RA.add(node->key);
	}
	populateRA(node->right);

	//If it is postorder, add to the resizableArray then return
	if (order == post) {
		RA.add(node->key);
	}
	return;
}

//Method used to find objects in the tree
template<class T>
T* AVLtree<T>::find(T key) { //most of this logic was copied from remove
	if (root == NULL) {
		return NULL;
	}
	AVLnode<T> *n = root, *parent = root, *delNode = NULL, *child = root;

	//Iterates through
	while (child != NULL) {
		parent = n;
		n = child;
		child = key >= n->key ? n->right : n->left;
		if (key == n->key)
			return &(n->key);
	}
	return NULL;
}

//Method used to get the size of the tree
template<class T>
int AVLtree<T>::getItemCount() {
	return toResizableArray().length;
}
}/* namespace std */
