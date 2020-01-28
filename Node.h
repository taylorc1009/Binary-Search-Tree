/*
Taylor Courtney
40398643
*/

#pragma once

#include <string>

// Node of a tree, stores a word
struct Node
{
    // Word stored in this node of the tree
    std::string word = "";
	//Part B - Holds the amount of occurances of this word
	int counter = 1;
    // The left branch of the tree
    Node *left = nullptr;
    // The right branch of the tree
    Node *right = nullptr;
};
