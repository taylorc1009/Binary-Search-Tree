/*
Taylor Courtney
40398643
*/

#include "BinarySearchTree.h"
#include "Node.h"
#include <string.h>

using namespace std;

// **Constructors **
BinarySearchTree::BinarySearchTree()
{
	//Remains empty as an empty node is already equal to 'nullptr'
}

BinarySearchTree::BinarySearchTree(std::string word)
{
	//Creates a new root node of a new tree
	root = new Node;
	//Enters into the new node the word passed in with the parameter 'word'
	root->word = word;
}

void copyTree(const Node *rhs, Node **node) //Takes the direct memory location of the node passed in order to modify the values stored there
{
	//If the next node of the tree being copied from is not equal to 'nullptr'
	if (rhs != nullptr) 
	{
		*node = new Node; //Follows the address we passed (using *) to access the actual values stored in there
		(*node)->word = rhs->word;
		//Calls the "copyTree" fuction recursively on the left and right nodes until there is nothing left to copy (i.e. the next node equals 'nullptr')
		copyTree(rhs->left, &(*node)->left);   //Passes the direct memory location of either the left or right node
		copyTree(rhs->right, &(*node)->right); //We need to go to the value in the node here to in order to get the memory locations stored in left/right
	}
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs)
{
	//Starts copying from the old to the new tree starting at the root node of each
	copyTree(rhs.root, &root); //Again passes memory address of this trees root node to allow us to follow it and modify the values stored is the address
}

BinarySearchTree::BinarySearchTree(const std::vector<std::string> &words)
{
	//Iterates for each word in the vector 'words' using its size
	for (int i = 0; i <= words.size() - 1; i++)
		//Uses the "insert" method to add each word from the vector array to the tree
		this->insert(words[i]);
}

void destroyHelper(Node **node)
{
	//Stops of the node equals 'nullptr', otherwise we would have an infinite recursion
	if (*node != nullptr) {
		//Destroys the branches of each node before destroying itself
		destroyHelper(&(*node)->left);  //
		destroyHelper(&(*node)->right); //Again passes memory address of either the left or right node to allow us to follow it
		delete *node;
	}
}

BinarySearchTree::~BinarySearchTree()
{
	//Starts deleting the tree from the root node
	destroyHelper(&root); //Passes the memory address of the root node of this tree so all nodes can be deleted correctly
}

// **Methods**
bool existsHelper(std::string word, Node *node)
{
	//Continues the check if the node is not empty
	if (node != nullptr) {
		//If the search criteria is less than the word in the current node it will be on the left
		if (word < node->word)
			return existsHelper(word, node->left);
		//And if the search criteria is greater than, it will be on the right
		else if (word > node->word)
			return existsHelper(word, node->right);
		//If it is not greater than, less than and the current node does not equal 'nullptr' that means it is equal to, therefore we have found the word
		else
			return true;
	}
	else
		return false;
}

bool BinarySearchTree::exists(std::string word) const
{
	//Searches the tree for the word stored in 'word' starting from the root node of the tree
	return existsHelper(word, root);
}

void insertHelper(std::string word, Node **node)
{
	//If the current node is not initialised as an actual node, we will set it up with the word we want to insert to the tree
	if (*node == nullptr) {
		*node = new Node;
		(*node)->word = word; //Goes straight to the value in node->word to modify it using its memory address
	}
	//If it doesn't equal 'nullptr' then the current node is occupied, so we must move to the next
	else {
		//If the word we want to enter is less than the word in the current node then we move to the left branch
		if (word < (*node)->word)
			insertHelper(word, &(*node)->left); //Again passes the memory address in the left node to the next occurance so we can follow it
		//And if it's greater than, we move to the right
		else if (word > (*node)->word)
			insertHelper(word, &(*node)->right); //Passes the memory address stored in the right node to the next occurance
	}
}

void BinarySearchTree::insert(std::string word)
{
	//Checks if the word to enter already exists in the tree or not before trying to insert it
	if (!this->exists(word))
		//Searches for an empty node to enter the word stored in 'word', starting at the root node
		insertHelper(word, &root); //Passes the memory address of the root node so we can access the values stores there
}

string inorderHelper(Node *node)
{
	//If node equals 'nullptr', it is either an empty tree or the end of the tree
	if (node != nullptr)
		//Returns each word in the tree as a string, in alphabetical order
		return inorderHelper(node->left) + node->word + " " + inorderHelper(node->right);
	//So if it's empty we return a blank string
	else
		return "";
}

std::string BinarySearchTree::inorder() const
{
	//Gets a string of the words in the tree in order, starting from the root node
	string str = inorderHelper(root);
	//If the string contains more than 1 word it will have an extra space on the end of it, we will therefore have to remove it
	if (str.length() > 1)
			str.pop_back();
	return str;
}

string preorderHelper(Node *node)
{
	if (node != nullptr)
		//Also returns the words in a string but in preorder fashion (top to bottom left to bottom right)
		return node->word + " " + preorderHelper(node->left) + preorderHelper(node->right);
	else
		return "";
}

std::string BinarySearchTree::preorder() const
{
	//Also starts at the root not and pops the extra space off the end of the stack of strings, if need be
	string str = preorderHelper(root);
	if (str.length() > 1)
		str.pop_back();
	return str;
}

string postorderHelper(Node *node)
{
	if (node != nullptr)
		//Again returns the words in a string but in post order (bottom left to top, then bottom right to top) this time
		return postorderHelper(node->left) + postorderHelper(node->right) + node->word + " ";
	else
		return "";
}

std::string BinarySearchTree::postorder() const
{
	//And starts at the root and pops the extra space
	string str = postorderHelper(root);
	if (str.length() > 1)
		str.pop_back();
	return str;
}

void incrementCounterHelper(Node **node, std::string word)
{
	//Searches for the counter of the word to increment - uses the same search format to find it; less than to the left, greater than to the right
	if (word < (*node)->word)
		incrementCounterHelper(&(*node)->left, word);
	else if (word > (*node)->word)
		incrementCounterHelper(&(*node)->right, word);
	//Otherwise the word has been found if the node does not equal 'nullptr'
	else if (*node != nullptr)
		(*node)->counter++;
}

///Part B VVV

void BinarySearchTree::incrementWordCounter(std::string word)
{
	//Searches for the counter to increment again starting from the root node
	incrementCounterHelper(&root, word);
}

std::string buildOutputHelper(Node *node)
{
	//Builds the line to be outputted in the format "(word): (counter)\n(word): (counter)\n..."
	if (node != nullptr)
		//Converts the word counter to a string in order for it to be displayed
		return node->word + ": " + to_string(node->counter) + "\n" + buildOutputHelper(node->left) + buildOutputHelper(node->right);
	else
		return "";
}

std::string BinarySearchTree::buildOutput()
{
	//Starts gathering the data to be outputted from the binary search tree
	return buildOutputHelper(root);
}

/// Part B ^^^

// **Operator overloads**
BinarySearchTree& BinarySearchTree::operator+(std::string word)
{
	//Inserts the word on the right of the + operator in to the tree on the left of it
	this->insert(word);
	//Returns the tree with the new word inserted
	return *this;
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &rhs)
{
	//Checks whether or not we are copying to the same tree, as in such a case we would end up deleting the tree and having no values to work with
	if (this != &rhs) {
		//Deletes every value in the tree to be copied to
		destroyHelper(&(this)->root);
		//Copies the values from the old tree to the tree we just emptied
		copyTree(rhs.root, &root);
	}
	//Returns the new tree we just copied to
	return *this;
}

/*
test:
	cl test.cpp BinarySearchTree.cpp
	cl ReadTextFile.cpp BinarySearchTree.cpp
	test
	ReadTextFile single_words_test.txt
	ReadTextFile sentences_test.txt

test:
	cl /c test.cpp BinarySearchTree.cpp
	lib BinarySearchTree.obj
	link BinarySearchTree.obj BinarySearchTree.lib
*/