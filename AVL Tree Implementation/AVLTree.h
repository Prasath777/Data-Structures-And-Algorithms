#pragma once
#include <iostream>
#include<string>
#include <vector>
#include<algorithm>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::max;
#include <stdexcept>

// AVL Node Class
template<class K, class V>
class AVLTreeNode {
public:
	K key;
	V value;
	AVLTreeNode<K,V>* left;
	AVLTreeNode<K,V>* right;
	AVLTreeNode<K,V>* parent;
	unsigned height;
	AVLTreeNode();
	AVLTreeNode(const K& keyv,const V& val,const unsigned& ht, AVLTreeNode<K,V>* par);
	// Should have attributes named:
	// parent - pointer to parent
	// left - pointer to left child
	// right - pointer to right child
	// key - node's key
	// value - node's value
	// height - node's height

	// Constructors ...
};

//Default Constructor
template<class K, class V>
AVLTreeNode<K,V>::AVLTreeNode(){
	value=0;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	height = -1;
}

//Constructor(Intializing)
template<class K, class V>
AVLTreeNode<K,V>::AVLTreeNode(const K& keyv,const V& val, const unsigned& ht, AVLTreeNode<K,V>* par){
	key = keyv;
	value=val;
	left = nullptr;
	right = nullptr;
	parent = par;
	height = ht;
}
// AVL Tree class
template<class K, class V>
class AVLTree
{
private:
	// Tree attributes go here
	// Your tree MUST have a root node named root
    AVLTreeNode<K,V>* root;
	unsigned int treeSize; //to record the number of nodes in the tree
	void deleteTree(AVLTreeNode<K,V>* root);
	AVLTreeNode<K,V>* copyTree(AVLTreeNode<K,V>* root);
	AVLTreeNode<K,V>* predecessorHelper(AVLTreeNode<K,V>* node);
	void inOrderTraversal1(AVLTreeNode<K,V>* root, vector<K> &v) const;
	void inOrderTraversal2(AVLTreeNode<K,V>* root, vector<V> &v) const;
	int maxHeight(AVLTreeNode<K,V>* nodeA,AVLTreeNode<K,V>* nodeB );
	int height(AVLTreeNode<K,V>* node);
	void adjustHeight(AVLTreeNode<K,V>* node);
	AVLTreeNode<K,V>* leftRotate(AVLTreeNode<K,V>* pivot);
	AVLTreeNode<K,V>* rightRotate(AVLTreeNode<K,V>* pivot);
	void reBalanceInsert(AVLTreeNode<K,V>* insertedNode, AVLTreeNode<K,V>* nodeParent);
	void reBalanceRemove(AVLTreeNode<K,V>* nodeParent);
	int findBalanceFactor(AVLTreeNode<K,V>* node);

public:
	AVLTree<K,V>();
	AVLTree<K,V>(const AVLTree<K,V>& tree);
	AVLTree<K,V>& operator=(const AVLTree<K,V>& tree);
	~AVLTree<K,V>();
	bool insert(const K& key, const V& value);
	bool remove(const K& key);
	V search(const K& key) const;
	vector<V> values() const;
	vector<K> keys() const;
	unsigned int size() const;
	void* getRoot() const { return root; }; // DO NOT REMOVE
};

// AVL Tree Methods go here
//Default Constructor
template<class K, class V>
AVLTree<K,V>::AVLTree(){
	//intializing the private variables
	root = nullptr;
	treeSize = 0;
}
//Copy Constructor
template<class K, class V> 
AVLTree<K,V>::AVLTree(const AVLTree<K,V>& tree){
		root = copyTree(tree.root); //calling helper function to make a deep copy
}

//Overloaded Assignment operator
template<class K, class V>
AVLTree<K,V>& AVLTree<K,V>::operator=(const AVLTree<K,V>& tree){
	if(this == &tree){//if LHS == RHS, don't swap
		return *this;
	}
	//otherwise delete the original tree and copy the passed tree
	deleteTree(root);
	root = copyTree(tree.root);
	return *this;
}

//Destructor
template<class K, class V>
AVLTree<K,V>::~AVLTree(){
	deleteTree(root);// calling the helper to delete the tree
}

//insert a node into the tree
template<class K, class V>
bool AVLTree<K,V>::insert(const K& key,const V& value){
	//if the root is null, then we create our first node and make it as the root
	if(root == nullptr){
		root = new AVLTreeNode<K,V>(key,value,0,nullptr);
		treeSize = 1; //this is the first node in the tree
		return true;
	}
	AVLTreeNode<K,V>* current = root;
	AVLTreeNode<K,V>* parent = nullptr;
	bool insertLeft = false; //to check if the inserted node is a left child
	
	//loop to find the insertion location
	while(current != nullptr){
		//parent of the inserted node is kept track of 
		if(key > current->key){ 
			parent = current;
			current=current->right;//go right
			insertLeft = false;
		
		}
		else if(key < current->key){
			parent = current;
			current = current->left;//go left
			insertLeft = true;

		}
		else{ //if key == current->key, then the key is already present in the tree
			return false;
		}
	}
	//Node created to insert
	AVLTreeNode<K,V>* newNode= new AVLTreeNode<K,V>(key,value,0,parent);
	if(insertLeft){ // if the insert location is the left of the parent, we insert to the left of the parent
		parent->left = newNode;
	}
	else{ // otherwise we insert to the right
		parent->right = newNode;
	}
	adjustHeight(parent); //updating the heights if necessary
	reBalanceInsert(newNode, parent); // rebalance the tree if the tree is unbalanced
	treeSize++; //the number of nodes has increased
	return true;
}

template<class K, class V> 
bool AVLTree<K,V>::remove(const K& key){

	if(root == nullptr){ //if the tree is empty, then we cannot remove stuff
		return false;
	}
	bool isLeftChild = false; // variable to see if the node to be deleted is a left child
	AVLTreeNode<K,V>* current = root;
	AVLTreeNode<K,V>* parent = nullptr;
	while(current != nullptr){
		if(key > current->key){
			parent = current;
			current=current->right;
			isLeftChild = false;
		}
		else if(key < current->key){
			parent = current;
			current = current->left;
			isLeftChild = true;
		}
		else{ //if key == current->key, then the key to be removed has been found
			break;
		}
	}
	//if the the key is not in the tree
	if(current == nullptr){
		return false;
	}
	treeSize--;//the number of nodes will decrease as we're removing
	AVLTreeNode<K,V>* deleteNode = current;
	//removed node is a leaf node
	if(current->left == nullptr && current->right == nullptr){
		//if the node to be removed is not a root
		if(current != root){
			//if the node to be removed is a left child, then we set the parent's left to null
			if(isLeftChild){
				parent->left = nullptr;
			
			}
			//otherwise we just the parent's right to null
			else{
				parent->right = nullptr;
			
			}
		}
		//if it's a root, then we just have a single node in the whole tree
		else{
		
			root = nullptr;
		}
		//settting the pointer of the deleted node to null
		deleteNode->left =nullptr;
		deleteNode->right = nullptr;
		deleteNode->parent = nullptr;
		delete deleteNode; // deleting the node from the tree
		adjustHeight(parent); //updating the heights if necessary
		reBalanceRemove(parent);//rebalnce if the trree is unbalanced
		return true;
	}
	else if(current->left && current->right){
		
		AVLTreeNode<K,V>* predes = predecessorHelper(current);//finding the predecessor node
		
		AVLTreeNode<K,V>* predesparent = predes->parent;// predecessor's parent
		
		
		if(current->left == predes){ //if the predesccor is the deleted node's left child
			predes->parent = current->parent; //make deleted node's parent to be the predecessor parent 
			if(current->parent != nullptr){ // if we are deleting the root
				//make the predes as the child of the the deleted node's parent appropriately
				if(current->parent->left == current){
					current->parent->left = predes;
				}
				else{
					current->parent->right = predes;
				}
			}
			//the predecessor right child need to chnage
			predes->right = current->right;
			predes->right->parent = predes;	
		}
		//otherwise do the normal removal process
		else{
			//if the predecessor is a leaf node, just make the the predes parent's right child null
			if(predes->left == nullptr && predes->right == nullptr){
				predes->parent->right = nullptr;
			}
			//if the predecessor has a left child, make appropriate changes
			else{
				predes->parent->right=predes->left;
				predes->left->parent = predes->parent;
			
			}	
			//copy the contents of the deleted node to the predecessor so that the it replaces the deleted node
			predes->right = current->right;
			predes->right->parent = predes;
			predes->left = current->left;
			predes->left->parent = predes;
			predes->parent = parent;
			if(current->parent != nullptr){ //if the deleted node is not the roor
				if(current->parent->left == current){
					current->parent->left = predes;
				}
				else{
					current->parent->right = predes;
				}
			}
		}
		if(current == root){ //if the deleted node is the root, make the predecessor as the new root
			root = predes;
		}
		//setting the pointer of the deleted node to null
		deleteNode->parent = nullptr;
		deleteNode->right = nullptr;
		deleteNode->left = nullptr;
		if(predesparent->key != deleteNode->key){ //if the deleted node is not the predecessor's parent 
			//updating the heights if necessary and rebalance the tree if needed
			adjustHeight(predesparent);
			reBalanceRemove(predesparent);
		}
		else{ //of the predecessor's parent is deleted
			//updating the heights if necessary and rebalance the tree if needed
			adjustHeight(predes);
			reBalanceRemove(predes);
		}
		delete deleteNode; // deallocate the node in dynamic memory
		return true;
	}
	//if the removed node has one child
	else{
		// choose a child node
        AVLTreeNode<K,V>* child = (current->left)? current->left: current->right;
 
        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (current != root)
        {	
            if (current == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
			child->parent = parent;
        }
 
        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
			child->parent = nullptr;
        }
		//setting the pointer of the deleted node to null
		deleteNode->left =nullptr;
		deleteNode->right = nullptr;
		deleteNode->parent = nullptr;
        delete deleteNode; // deallocate the node in dynamic memory
		//updating the heights if necessary and rebalance the tree if needed
		adjustHeight(parent);
		reBalanceRemove(parent);
		return true;
	}
}

template<class K, class V>
//searches the key and returns the corresponding value
V AVLTree<K,V>::search(const K& key) const {
	//if the root is null, there's nothing to search
	if(root == nullptr){
		throw std::runtime_error("The tree is empty");
	}
	AVLTreeNode<K,V>* current = root;
	//Otherwise traverse the tree to search the key
	while(current != nullptr){
		if(key > current->key){
			current=current->right;
		}
		else if(key < current->key){
			current = current->left;
		}
		else{
			return current->value;
		}		
	}
	//throw an exception if the key is not in the tree
	throw std::runtime_error("Not Found");
}
//returns a vector containing values in key order
template<class K, class V>
vector<V> AVLTree<K,V>::values() const {
	vector<V> values;
	inOrderTraversal2(root, values); // helper to traverse the tree using pre-order and push values in the vector passed by reference

	return values;
}

//returns a vector containing keys in ascending order
template<class K, class V>
vector<K> AVLTree<K,V>::keys() const {
	vector<K> keys;
	inOrderTraversal1(root, keys); // helper to traverse the tree using pre-order and push values in the vector passed by reference
	return keys;
}

//returns the size of the tree/ number of nodes
template<class K, class V>
unsigned int AVLTree<K,V>::size() const {
	
	return treeSize; //return the size/ no of nodes in the tree
}

//deletes the whole tree when the root of the tree is passed
template<class K, class V>
void AVLTree<K,V>::deleteTree(AVLTreeNode<K,V>* node)
{	
	//the tree is traversed using post-order
    if (node) //the root shouldn't be null to start with
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
//makes a deep copy of the tree passed nad returns the root to that copied tree
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K,V>::copyTree(AVLTreeNode<K,V>* root){

	if(root == nullptr){ //if the root is null, there's nothing to copy
		return nullptr;
	}
	//creating a new node
	AVLTreeNode<K,V>* newNode = new AVLTreeNode<K,V>(root->key,root->value,root->height,root->parent);

	//traversing the tree using pre-order recursively
	newNode->left = copyTree(root->left);
	newNode->right = copyTree(root->right);

	return newNode;

}

//returns the predecessor of the node passed
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K,V>::predecessorHelper(AVLTreeNode<K,V>* node){
	AVLTreeNode<K,V>* predsor = node->left;// we are looking for the largest node in the left subtree 
	if(predsor->right == nullptr){ //if there's node right subtree for the node's child, then this is the predecessor
		return predsor;
	}

	//if there's a right subtree, then we traverse to rightmost node which will be our predecessor
	while(predsor->right){
		predsor = predsor->right;
	}
	return predsor;
}

//traverses the tree using in-order and stores the keys in the vector passed by reference
template<class K, class V>
void AVLTree<K,V>::inOrderTraversal1(AVLTreeNode<K,V>* root, vector<K> &v) const{
	if(root){
		inOrderTraversal1(root->left,v);
		v.push_back(root->key);
		inOrderTraversal1(root->right,v);
	}

}

//traverses the tree using in-order and stores the values in the vector passed by reference
template<class K, class V>
void AVLTree<K,V>::inOrderTraversal2(AVLTreeNode<K,V>* root, vector<V> &v) const{
	if(root){
		inOrderTraversal2(root->left,v);
		v.push_back(root->value);
		inOrderTraversal2(root->right,v);
	}


}

//returns the maximum height value of the two nodes passed
template<class K, class V>
int AVLTree<K,V>::maxHeight(AVLTreeNode<K,V>* left,AVLTreeNode<K,V>* right ){	
	if(left == nullptr && right == nullptr){ 
		return -1;
	}
	else if(left == nullptr){ //if the left is null, we return the right's height
		return right->height;
	}
	else if(right == nullptr){//if the right is null, we return the left's height
		return left->height;
	}
	else{ //if both are valid, then we return the maximum of the two heights
		return max(left->height, right->height);
	}
}

//returns the height of the passed node
template<class K, class V>
int AVLTree<K,V>::height(AVLTreeNode<K,V>* node)
{
    // base case: empty tree has a height of -1
    if (node == nullptr) {
        return -1;
    }
 
   return node->height;
}

//adjust the heights of the nodes from the passed node up to the root
template<class K, class V>
void AVLTree<K,V>::adjustHeight(AVLTreeNode<K,V>* node){

	while(node != nullptr){
		node->height = maxHeight(node->left, node->right) + 1; // calculating height
		// cout<<endl<<node->key<<" height has changed to "<<node->height;
		node = node->parent; //travelling up the tree
	}
}

//returns the balance factor of the passed node
template<class K, class V>
int AVLTree<K,V>::findBalanceFactor(AVLTreeNode<K,V>* node){
	if(node){
		return height(node->left) - height(node->right); // calculation of balance factor
	}
	return -1; // if the node passed is nul
}

//performs left rotation on the passed node
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K,V>::leftRotate(AVLTreeNode<K,V>* pivot){
	AVLTreeNode<K,V>* pivotChild =  pivot->right; //pivot's child
	AVLTreeNode<K,V>* pivotNewChild = pivotChild->left; // pivot's grandchild

	pivotChild->left = pivot;
	pivot->right = pivotNewChild;
	//sometimes the pivot might not have a left grandchild	
	if(pivotNewChild){
	pivotNewChild->parent = pivot;
	}
	//Perform the rotation
	if(pivot->parent){
		
		if(pivot->parent->right == pivot){
			pivot->parent->right = pivotChild;
		}
		else{
			pivot->parent->left = pivotChild;
		}
	}
	pivotChild->parent = pivot->parent;
	pivot->parent = pivotChild;
	//update heights
	adjustHeight(pivot);

	if(pivot == root){root = pivotChild;root->parent = nullptr;} //if the pivot was a root, the pivot's child becomes the root now
	return pivotChild; //return the root of the subtree

}

//performs left rotation on the passed node
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K,V>::rightRotate(AVLTreeNode<K,V>* pivot){
	AVLTreeNode<K,V>* pivotChild =  pivot->left; //pivot's child
	AVLTreeNode<K,V>* pivotNewChild = pivotChild->right; // pivot's grandchild

	pivotChild->right = pivot;
	pivot->left = pivotNewChild;
	//sometimes the pivot might not have a right grandchild	
	if(pivotNewChild){
		pivotNewChild->parent = pivot;
	}
	//perform the rotation
	if(pivot->parent){
		if(pivot->parent->right == pivot){
			pivot->parent->right = pivotChild;
		}
		else{
			pivot->parent->left = pivotChild;
		}
	}
	pivotChild->parent = pivot->parent;
	pivot->parent = pivotChild;
	// update heights
	adjustHeight(pivot);

	if(pivot == root){root = pivotChild;root->parent = nullptr;}  //if the pivot was a root, the pivot's child becomes the root now
	return pivotChild; //return the root of the subtree
}

//Balances the tree after insertion if needed
template<class K, class V>
void AVLTree<K,V>::reBalanceInsert(AVLTreeNode<K,V>* insertedNode, AVLTreeNode<K,V>* nodeParent){
	
	int balanceFactor; // variable to store the balance factor

	while(nodeParent != nullptr){	
	
		balanceFactor =  findBalanceFactor(nodeParent);
		
		//Left Left Case
		if(balanceFactor > 1  && insertedNode->key < nodeParent->left->key){

			rightRotate(nodeParent);
		}
		//Right Right Case
		else if(balanceFactor < -1  && insertedNode->key > nodeParent->right->key){
			
			leftRotate(nodeParent);
		
		}
		//	Left Right Case
		else if(balanceFactor > 1  && insertedNode->key > nodeParent->left->key){

			leftRotate(nodeParent->left);
			rightRotate(nodeParent);
		}
		// Right Left Case	
		else if(balanceFactor < -1  && insertedNode->key < nodeParent->right->key){
			
			rightRotate(nodeParent->right);
			leftRotate(nodeParent);
		}
		nodeParent = nodeParent->parent; //travel up the tree to the root
	}

}

//Balances the tree after removal if needed
template<class K, class V>
void AVLTree<K,V>::reBalanceRemove(AVLTreeNode<K,V>* nodeParent){
	int balanceFactor;
	
	while(nodeParent != nullptr){	
		
		balanceFactor =  findBalanceFactor(nodeParent);
	
		//Left Left	
		if(balanceFactor > 1  && findBalanceFactor(nodeParent->left) >= 0){
			
			rightRotate(nodeParent);
		}
		//Right Right
		else if(balanceFactor < -1  && findBalanceFactor(nodeParent->right) <= 0){
			
			leftRotate(nodeParent);
		}
		//	Left Right
		else if(balanceFactor > 1  && findBalanceFactor(nodeParent->left) < 0){

			leftRotate(nodeParent->left);
			rightRotate(nodeParent);
			
		}
		// Right Left
		else if(balanceFactor < -1  && findBalanceFactor(nodeParent->right) > 0){
			
			rightRotate(nodeParent->right);
			leftRotate(nodeParent);
		}
		nodeParent = nodeParent->parent; //travel up the tree to the root
	}
}
