#pragma once
#include <list>
#include<iostream>
#include<iterator>
#include<string>
#include"Node.h"
using namespace std;

class Tree
{
private:
	Node* root;
public:
	Tree() { root = NULL; }//default ctor
	Tree(const Tree*& t);// copy ctor
	~Tree();            // dtor
	Node* getRoot() { return root; }// get function
	void clear(Node*);             //Deletes certain content and all its descendants
	void addNewTree(string); // addes a new tree (if it exists, delefes all responses)
	Node* search(string);            // finds a content
	Node* helpSearch(string, Node*);  // a help function for finding
	bool addResponse(string, string);//addes a respons on a certain tree
	bool delResponse(string);    // deletes a respons on a certain tree and all his descendants
	void print();                       // prints all the contens in the tree
	void helpPrint(Node*, int);// a help function for printing
	Node* father(string);       // returns the father of a Node
	Node* helpFather(string, Node*); // a help function for returning the father
	void trackPrinting(string);//Prints the route from the current response to the tree root
	void printPart(string);// Prints a particular response and all of its descendants


};

