#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


#include <iostream>
#include "list_funcs.h"
template <class Key, class Value>
class StendhalNode {
public:
	StendhalNode() {
	}
	StendhalNode(Key key, Value val) {
		this->key = key;
		this->val = val;
	}
	~StendhalNode() {
		
	}

	Key getKey() {
		return key;
	}

	Value getValue() {
		return val;
	}

	bool isBlack() {
		return black;
	}

	template <class Key, class Value>
	friend std::ostream& operator<<(std::ostream& stream, StendhalNode<Key, Value>& node) {
		stream << "Key: " << node.key << ", Value: " << node.val;
		if (node.black)
			stream << ", Color: black\n";
		else
			stream << ", Color: red\n";

		return stream;
	}

private:
	template <class Key, class Value> friend class StendhalTree;
	

	Key key;
	Value val;
	StendhalNode<Key, Value> *left = nullptr;
	StendhalNode<Key, Value> *right = nullptr;
	StendhalNode<Key, Value> *parent = nullptr;
	bool black = false;	//new node is red, the root is black
	bool isDummy = false; //for correct removing
	bool isLeft() {
		if (!parent)
			return false;

		if (parent->left == this)
			return true;
		else
			return false;
	}

	bool isRight() {
		if (!parent)
			return false;

		if (parent->right == this)
			return true;
		else
			return false;
	}
	StendhalNode<Key, Value> *uncle() {
		StendhalNode<Key, Value> *node = grandpa();

		//no grandpa - no uncle
		if (!node)
			return nullptr;

		if (node->left == parent)
			return node->right;
		else
			return node->left;
	}
	StendhalNode<Key, Value> *grandpa() {
		//no parent(root) no grandpa
		if (!parent)
			return nullptr;

		return parent->parent;
	}

	
};
template <class Key, class Value>
class StendhalTree {
private:
	StendhalNode<Key, Value> *root = nullptr;
	


	void rotateLeft(StendhalNode<Key, Value> *node) {

		StendhalNode<Key, Value> *pivot = node->right;

		pivot->parent = node->parent; 
		if (node->parent != nullptr) {
			if (node->isLeft()) //re-attaching rotating part
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		}
		else
			root = pivot;
		node->right = pivot->left;
		if (pivot->left != nullptr)
			pivot->left->parent = node;

		node->parent = pivot;
		pivot->left = node;
	}
	void rotateRight(StendhalNode<Key, Value> *node) {

		StendhalNode<Key, Value> *pivot = node->left;

		pivot->parent = node->parent; 
		if (node->parent != nullptr) {
			if (node->isLeft())  //re-attaching rotating part
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		}
		else
			root = pivot;
		node->left = pivot->right;
		if (pivot->right != nullptr)
			pivot->right->parent = node;

		node->parent = pivot;
		pivot->right = node;
	}

	void Inorder_DeletingDummies(StendhalNode<Key, Value> *node)
	{
		if (node != nullptr)
		{
			Inorder_DeletingDummies(node->left);
			
			Inorder_DeletingDummies(node->right);
			if (node->isDummy) {
				if (node->isLeft())
					node->parent->left = nullptr;
				else 
					node->parent->right = nullptr;

				delete node;
				node = nullptr;
			}
		}

	}

	//fix the tree after we add a new node
	//used in insert
	void fixTreeAfterInsert(StendhalNode<Key, Value> *node) {
		StendhalNode<Key, Value> *grandpa = nullptr, *uncle = nullptr;

		
		//don'n fix if its root or if parent is black
		while (node != root && node->parent != nullptr && !node->parent->black) {
			//the fresh added node is red
			grandpa = node->grandpa();
			uncle = node->uncle();

			if (grandpa== nullptr)
				return;
			

			//if uncle color is black, perform a rotation to make child and parent on one side
			//then perfom a rotation again

			//if no uncle is like uncle is black
			if (uncle==nullptr || uncle->black) {
				if (node->parent->isRight() && node->isLeft()) {
					rotateRight(node->parent);
					node = node->right;
				}
				else if (node->parent->isLeft() && node->isRight()) {
					rotateLeft(node->parent);
					node = node->left;
				}

				node->parent->black = true;
				grandpa->black = false;
				//then doing rotation on grandpa
				if (node->parent->isRight())
					rotateLeft(grandpa);
				else
					rotateRight(grandpa);
			}
			//if uncle color is red, paint parent black, grandpa red, uncle black, and start checking 
			//from grandpa
			else if (!uncle->black) {
				node->parent->black = true;
				grandpa->black = false;
				uncle->black = true;
			}

			node = grandpa;
		}

		root->black = true;
	}

	void fixTreeAfterRemove(StendhalNode<Key, Value> *node) {
		while (node != root && node->black) {
			if (node->isLeft()) {
				StendhalNode<Key, Value> *bro = node->parent->right;
				bool broleftcolor; //using bufering variables of children color to avoid memory access issues
				bool brorightcolor;
				if (bro->left == nullptr)
					broleftcolor = true;
				else
					broleftcolor = bro->left->isBlack();

				if (bro->right == nullptr)
					brorightcolor = true;
				else
					brorightcolor = bro->right->isBlack();

				if ((bro != nullptr) && (!bro->black)) { //case: red brother with black kids
					bro->black = true;
					node->parent->black = false;
					rotateLeft(node->parent);
					bro = node->parent->right;
				}
				//case: black brother with black children - or NIL brother
				else if ((bro==nullptr) || (broleftcolor && brorightcolor)) {
					bro->black = false;
					node = node->parent;
				}
				else {
					if (brorightcolor) { //case: black brother with black right child
						bro->left->black = true;
						bro->black = false;
						rotateRight(bro);
						bro = node->parent->right;
					}
					
						bro->black = node->parent->black;
							node->parent->black = true;
							bro->right->black = true;
							rotateLeft(node->parent);
							node = root;
				
				}
			}
			else {
				StendhalNode<Key, Value> *bro = node->parent->left;
				bool broleftcolor; //using bufering variables of children color to avoid memory access issues
				bool brorightcolor;
				if (bro->left == nullptr)
					broleftcolor = true;
				else
					broleftcolor = bro->left->isBlack();

				if (bro->right == nullptr)
					brorightcolor = true;
				else
					brorightcolor = bro->right->isBlack();
				if ((bro != nullptr) && (!bro->black)) {//case: red brother with black kids
					bro->black = true;
					node->parent->black = false;
					rotateRight(node->parent);
					bro = node->parent->left;
				}
				//case: black brother with black children - or NIL brother
				if ((bro == nullptr) || (broleftcolor && brorightcolor)) {
					bro->black = false;
					node = node->parent;
				}
				else {
					if (broleftcolor) { //case: black brother with black right child
						bro->right->black = true;
						bro->black = false;
						rotateLeft(bro);
						bro = node->parent->left;
					}
					
						bro->black = node->parent->black;
						node->parent->black = true;
						bro->left->black = true;
						rotateRight(node->parent);
						node = root;
					
				}
			}
		}
		node->black = true;
		Inorder_DeletingDummies(root);
	}

	void printFromNode(StendhalNode<Key, Value> *node, size_t level, bool left_or_right) {
		if (node != nullptr) {
			printFromNode(node->left, level + 3, true);

			bool strokes = false;

			for (size_t i = 0; i < level; ++i) {
				if (i + 2 == level) {
					strokes = true;
				}

				if (strokes) {
					std::cout << "---";
				}
				else {
					std::cout << "   ";
				}
			}


			if (left_or_right && node != root) {
				std::cout << "L, ";

			}
			else if (node != root) {
				std::cout << "R, ";
			}

			if (node->black) {
				std::cout << "Blk:";
			}
			else {
				std::cout << "Red:";
			}

			std::cout << node->key << ", " << node->val << std::endl;
			printFromNode(node->right, level + 3, false);
		}
	}

	//recursive delete all the tree
	void recuirsiveClear(StendhalNode<Key, Value> *node) {
		if (node==nullptr)
			return;

		recuirsiveClear(node->left);
		recuirsiveClear(node->right);

		delete node;
		node = nullptr;

		root = nullptr;
	}

	//to fill the list of keys
	void recuirsiveKeys(StendhalNode<Key, Value> *node, List<Key> *list) {
		if (node == nullptr)
			return;
		list->push_back(node->key);
		//std::cout << node->key<<" ";
		recuirsiveKeys(node->left, list);
		recuirsiveKeys(node->right, list);
	}

	//to fill the list of values
	void recuirsiveValues(StendhalNode<Key, Value> *node, List<Value> *list) {
		if (node==nullptr)
			return;
		list->push_back(node->val);
		recuirsiveValues(node->left, list);
		recuirsiveValues(node->right, list);
	}
	//to fill the list of colors
	void recuirsiveColors(StendhalNode<Key, Value> *node, List<bool> *list) {
		if (node == nullptr)
			return;
		list->push_back(node->isBlack());
		recuirsiveColors(node->left, list);
		recuirsiveColors(node->right, list);
	}
public:
	StendhalTree() {

	}

	~StendhalTree() {
		clear();
	}

	

	
	template <class Key, class Value>
	friend std::ostream& operator<<(std::ostream& stream, StendhalTree<Key, Value>& tree) {
		StendhalNode<Key, Value> *node = tree.root;
		if (!node) {
			std::cout << "An empty tree.\n";
			return stream;
		}

		tree.printFromNode(tree.root, 0, true);
		return stream;
	}

	void insert(Key key, Value val) {
		//adding the first elem is easy
		if (root==nullptr) {
			root = new StendhalNode<Key, Value>(key, val);
			root->black = true;
			return;
		}
		StendhalNode<Key, Value> *node = root;
		bool found = false;

		while (!found) {
			if (key > node->key) {
				if (node->right)
					node = node->right;
				else
					found = true;
			}
			else if (key < node->key) {
				if (node->left)
					node = node->left;
				else
					found = true;
			}
			else if (key == node->key)//2 equal keys can't exist in one tree
			{
				std::cout << "There is already such key\n";
				return;
			}
				
		}

		StendhalNode<Key, Value> *newNode = new StendhalNode<Key, Value>(key, val);
		if (key > node->key)
			node->right = newNode;
		else
			node->left = newNode;

		newNode->parent = node;

		fixTreeAfterInsert(newNode);
	}

	StendhalNode<Key, Value> *find(Key key) {
		StendhalNode<Key, Value> *node = root;
		bool found = false;
		if (root == nullptr) {
			return nullptr;
		}
		while (!found) {
			if (key > node->key) {
				if (node->right)
					node = node->right;
				else
					return nullptr;
			}
			else if (key < node->key) {
				if (node->left)
					node = node->left;
				else
					return nullptr;
			}
			else if (key == node->key)
				found = true;
		}

		return node;
	}
	
	void remove(Key key) {
		StendhalNode<Key, Value> *deleting = find(key);
		StendhalNode<Key, Value> *fixNode = nullptr;

		//if node to remove wasn't found - return
		if (deleting==nullptr) {
			return;
		}

		bool blackDeleted = deleting->black;

		//if no children simply delete the node
		if (deleting->left==nullptr && deleting->right == nullptr) {
			deleting->isDummy = true;
			fixNode = deleting;
			if (deleting->isLeft())
				deleting->parent->left = fixNode;
			else if (deleting->isRight())
				deleting->parent->right = fixNode;
			
			//delete deleting;
		
			deleting = nullptr;

			//if root was deleted
			if (root == nullptr) {
				return;
			}
		}

		//only right child
		else if (deleting->left == nullptr && deleting->right != nullptr) {
			if (deleting->isLeft())
				deleting->parent->left = deleting->right;
			else if (deleting->isRight())
				deleting->parent->right = deleting->right;

			deleting->right->parent = deleting->parent;

			fixNode = deleting->right;
			delete deleting;
			deleting = nullptr;

			if (root == nullptr) {
				root = fixNode;
			}
		}

		//only left child
		else if (deleting->left!= nullptr && deleting->right == nullptr) {
			if (deleting->isLeft())
				deleting->parent->left = deleting->left;
			else if (deleting->isRight())
				deleting->parent->right = deleting->left;

			deleting->left->parent = deleting->parent;

			fixNode = deleting->left;
			delete deleting;
			deleting = nullptr;

			if (root == nullptr) {
				root = fixNode;
			}
		}

		//both children
		else if (deleting->left != nullptr && deleting->right != nullptr) {
			auto *nextToRemove = deleting->right;

			while (nextToRemove->left)
				nextToRemove = nextToRemove->left;

			deleting->key = nextToRemove->key;
			deleting->val = nextToRemove->val;
			//if minimal node placed in right subtree
			if (nextToRemove->isLeft()) {
				if (nextToRemove->right == nullptr) {
					nextToRemove->isDummy = true;
					fixNode = nextToRemove;
				}
				else {
					nextToRemove->parent->left = nextToRemove->right;
					fixNode = nextToRemove->right;
				}
			}
			//if minimal node is child of new deleting node
			else if (nextToRemove->isRight()) {
				//if there is no right child of deleting - make it dummy
				if (nextToRemove->right == nullptr) {
					nextToRemove->isDummy = true;
					fixNode = nextToRemove;
				}
				else {
					nextToRemove->parent->right = nextToRemove->right;
					fixNode = nextToRemove->right;
				}
			}
			

			if (nextToRemove->black)
				blackDeleted = true;
			else
				blackDeleted = false;
			
			//delete nextToRemove;
			nextToRemove = nullptr;
		}

		root->black = true;

		//no need to balance if red was deleted
		if (blackDeleted && fixNode!=nullptr)
			fixTreeAfterRemove(fixNode);
		Inorder_DeletingDummies(root);
	}

	void clear() {
		recuirsiveClear(root);
	}

	List<Key> *get_keys() {
		StendhalNode <Key, Value> *node= root;
		List<Key> *list = new List<Key>();	
		recuirsiveKeys(node, list);
		return list;
	}

	List<Value> *get_values() {
		StendhalNode <Key, Value> *node = root;
		List<Value> *list = new List<Value>();
		recuirsiveValues(node, list);
		return list;
	}
	List<bool> *get_colors() {
		StendhalNode <Key, Value> *node = root;
		List<bool> *list = new List<bool>();
		recuirsiveColors(node, list);
		return list;
	}
};


#endif