#include "treeList.h"
#include"Tree.h"
#include <iostream>
#include <list>
#include <string>
#include"Node.h"

using namespace std;
list<Tree>::iterator it1;
treeList::treeList(const treeList& t)// copy ctor
{
	this->trees = t.trees;
}

treeList::~treeList()//dtor
{
	for (it1 = trees.begin(); it1 != trees.end(); it1++)//go over all trees
	{
		Tree* n = &(*it1);
		n->clear(n->getRoot());//dekete the tree
	}
}
void treeList::addNewTree(string title)//sending to a difrint function that adds a new tree
{
	Tree* p = new Tree();
	(*p).addNewTree(title);//add a new tree with this title
	trees.push_front(*p);//move the new tree to be the first in the list
}

Tree* treeList::findTree(string String)//findes a certaun tree
{
	for (it1 = trees.begin(); it1 != trees.end(); it1++)
	{
		Tree* p;
		p = &(*it1);
		if (p->search(String))////if that's the tree
			return p;

	}
	return NULL;// there isn't such a tree
}

void treeList::searchAndPrint(string val)// Finds all the appropriate responses from all the trees and prints them and all their descendants
{
	bool check = false;
	for (it1 = trees.begin(); it1 != trees.end(); it1++)
	{
		Tree* n = &(*it1);
		if (n->search(val))//If the content appears in the tree
		{
			cout << endl;
			n->printPart(val);//print the content and all of its descendants
			n->trackPrinting(val);// Print the route from the content to the tree root
			check = true;
		}
	}
	if (!check)//there isn't such a string
		cout << "ERROR";
}

bool treeList::addResponse(string title, string father, string son)//Adds a response to an existing tree
{
	Tree* p = findTree(title);//find the correct tree
	if (!p)                   // there isn't such a tree
		return false;
	return p->addResponse(father, son);//add the son to the father
}

bool treeList::delResponse(string title, string val)//Deletes a comment from a particular tree
{
	Tree* p = findTree(title);//find the correct tree
	if (!p)                    // there isn't such a tree
		return false;
	if (title == val)          //we want to dekete a whole tree
	{
		p->clear(p->getRoot());//Delete the contents of the tree
		for (it1 = trees.begin(); it1 != trees.end(); it1++)
		{
			Tree* q = &(*it1);
			if (q == p)
			{
				trees.erase(it1);//Erase the tree itself
				return true;
			}
		}
	}
	return p->delResponse(val);// delete the respons and all his descendants
}

void treeList::printAllTrees()//Prints all the trees with all the responses
{
	int counter = 0;
	for (it1 = trees.begin(); it1 != trees.end(); it1++)
	{

		counter++;
		Tree* n = &(*it1);
		cout << "Tree #" << counter << endl;
		n->print();//print the tree
		cout << endl;
	}
}

void treeList::printSubTree(string title, string val)// Prints a particular response and all of its descendants and the rout to the root
{
	if (findTree(title))//we found the tree
	{
		Tree* n = findTree(title);
		if (title == val)// if the response is the title
		{
			cout << endl;
			n->printPart(val);//print the whole tree
			return;
		}
		if (n->search(val))//we found the response
		{
			cout << endl;
			n->printPart(val);//print the content and all of its descendants
			n->trackPrinting(val);// Print the route from the content to the tree root
		}
	}
}