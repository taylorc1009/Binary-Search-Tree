BinarySearchTree:
	cl /c test.cpp BinarySearchTree.cpp
	lib BinarySearchTree.obj
	link test.obj BinarySearchTree.lib
	cl /c ReadTextFile.cpp BinarySearchTree.cpp
	lib BinarySearchTree.obj
	link ReadTextFile.obj BinarySearchTree.lib
	test
	ReadTextFile single_words_test.txt
	ReadTextFile sentences_test.txt

test:
	cl /c test.cpp BinarySearchTree.cpp
	lib BinarySearchTree.obj
	link test.obj BinarySearchTree.lib
	test
	
count:
	cl /c ReadTextFile.cpp BinarySearchTree.cpp
	lib BinarySearchTree.obj
	link ReadTextFile.obj BinarySearchTree.lib
	ReadTextFile single_words_test.txt
	ReadTextFile sentences_test.txt
	
clean:
	del *.obj
	del *.exe
	del *.lib