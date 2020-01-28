/*
Taylor Courtney
40398643
*/

#include "BinarySearchTree.h"
#include "Node.h"
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
	//Checks whether the user entered the correct amount of arguments needed, otherwise displays an error
	if (argc == 2) {
		//Opens the file the user entered
		ifstream file (argv[1]);
		//Checks whether or not the file the user entered was able to be opened, otherwise displays an error
		if (file.is_open()) {
			string word;
			BinarySearchTree *wordsInFile = new BinarySearchTree();
			//Iterates over each word in the file
			while (file >> word) {
				//Clean is set to 'false' as long as the last character stored in 'word' is not punctual
				bool clean = false;
				while (!clean) {
					//Detects whether or not the last character is alphabetical
					if (word.back() == ' ' || word.back() == '?' || word.back() == ',' || word.back() == '.')
						//Pops the last character off the stack 'word' if it's not alphabetical
						word.pop_back();
					else
						clean = true;
				}
				//Detects whether or not the current word already exists in the tree in order to increment its counter
				if (!wordsInFile->exists(word))
					wordsInFile->insert(word);
				else
					wordsInFile->incrementWordCounter(word);
			}
			//Displays each word and the amount of times they occur
			cout << wordsInFile->buildOutput();
			//Frees the memory the binary search tree is stored in
			delete wordsInFile;
		}
		else
			cout << "ERROR - No such file found in the current directory";
	}
	else
		cout << "ERROR - No file specified or invalid amount of arguments";
	return 0;
}