#pragma once
#include"Tree.h"
#include <iostream>
#include <list>
#include <string>
#include"Node.h"

using namespace std;
class treeList
{
private:
	list <Tree> trees;

public:
	treeList() {  }//default ctor
	treeList(const treeList&);// copy ctor
	~treeList();             //dtor
	void addNewTree(string);//sending to a difrint function that adds a new tree
	Tree* findTree(string);//findes a certaun tree
	void searchAndPrint(string);// Finds all the appropriate responses from all the trees and prints them and all their descendants
	bool addResponse(string, string, string);//Adds a response to an existing tree
	bool delResponse(string, string);//Deletes a comment from a particular tree
	void printAllTrees();//Prints all the trees with all the responses
	void printSubTree(string, string);// Prints a particular response and all of its descendants and the rout to the root
};

