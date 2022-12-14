#include"Tree.h"
#include <iostream>
#include <list>
#include <string>
#include"Node.h"

using namespace std;
Tree::Tree(const Tree*& t)// copy ctor
{
	this->root->content = t->root->content;
	this->root->responses = t->root->responses;
}
Tree::~Tree()//dtor
{
	if (root)
		delete root;
	root = NULL;

}


void Tree::clear(Node* p)//Deletes certain content and all its descendants
{
	p->responses.clear();//Erase all the offspring
	p->content.clear();//Delete the content
}

void Tree::addNewTree(string title)// addes a new tree (if it exists, delefes all responses)
{
	if (!search(title))//if there isn't a discussion that has that title
	{
		Node* n = new Node;// a new root
		n->content = title;
		root = n;
	}
	else
		search(title)->responses.clear();//Delete all comments except the title
}

Node* Tree::search(string val)// finds a content
{
	return helpSearch(val, root);
}

Node* Tree::helpSearch(string String, Node* p)// a help function for finding
{
	if (p)//if the node containing something
	{
		if (p->content == String)//we found
			return p;
		int i;
		if (p->responses.size())//If he has offspring
		{
			list<Node>::iterator it2;
			// go over all the nodes besides the last (if it will go till the kast and then it2++ the program will get stuck)
			for (it2 = p->responses.begin(), i = 0; it2 != p->responses.end(), i < p->responses.size() - 1; it2++, i++)
			{
				Node* q = &(*it2);
				if (q->content == String)//we found
					return q;
				if (q->responses.size())//If he has offspring
					if (helpSearch(String, q))
						return helpSearch(String, q);
			}
			//check the kast node in the list
			Node* q = &(*it2);
			if (q->content == String)//we found
				return q;
			if (q->responses.size())//If he has offspring
				if (helpSearch(String, q))
					return helpSearch(String, q);
		}
	}
	return NULL;//we didn't find
}

bool Tree::addResponse(string father, string son)//addes a respons on a certain tree
{
	Node* p = new Node;
	p->content = son;
	if (!search(father))// we don't have what to add on
		return false;
	else
	{
		(search(father)->responses).insert(search(father)->responses.end(), *p);// add the son on the father
		return true;// we did it
	}

}

bool Tree::delResponse(string val)// deletes a respons on a certain tree and all his descendants
{
	if (search(val))// if the respons exists
	{
		list<Node>::iterator it2;

		Node* p = father(val);
		for (it2 = p->responses.begin(); it2 != p->responses.end(); it2++)
		{
			Node* q = &(*it2);
			if (q->content == val)//if q is the son
			{
				father(val)->responses.erase(it2);// delete the son
				return true;
			}
		}
	}
	return false;// if the respons dosn't exists
}

void Tree::print()// prints all the contens in the tree
{
	helpPrint(root, 0);//sends to helpPrint
}

void Tree::helpPrint(Node* p, int spaces = 0)// a help function for printing
{
	if (p)//if the node is containing something
	{
		list<Node>::iterator it2;

		for (int i = 0; i < spaces; i++)
			cout << " ";
		if (p->content != "0")//if the node is containing something
		{
			cout << p->content << endl;//print the content
			if (p->responses.size())//If he has offspring
			{
				int i;
				// go over all the nodes besides the last (if it will go till the kast and then it2++ the program will get stuck)
				for (it2 = p->responses.begin(), i = 0; it2 != p->responses.end(), i < p->responses.size() - 1; it2++, i++)
				{
					Node* q = &(*it2);
					if (q->responses.size())//If he has offspring
					{
						helpPrint(q, spaces + 3);//send the son to the printing function
					}
					else
					{
						for (int i = 0; i < spaces; i++)
							cout << " ";
						cout << q->content << endl;//print the content
					}
				}
				Node* q = &(*it2);
				if (q->responses.size())//If he has offspring
				{
					helpPrint(q, spaces + 3);//send the son to the printing function
				}
				else
				{
					for (int i = 0; i < spaces + 3; i++)
						cout << " ";
					cout << q->content << endl;//print the content
				}

			}

		}
	}
}

Node* Tree::father(string val)// returns the father of a Node
{
	return helpFather(val, root);//sends to helpFather
}

Node* Tree::helpFather(string String, Node* p)// a help function for returning the father
{
	if (p->responses.size())//If he has offspring
	{
		int i;
		list<Node>::iterator it2;
		// go over all the nodes besides the last (if it will go till the kast and then it2++ the program will get stuck)
		for (it2 = (*p).responses.begin(), i = 0; it2 != (*p).responses.end(), i < p->responses.size() - 1; it2++, i++)
		{
			Node* q = &(*it2);
			if (q->content == String)//we found
				return p;
			if (q->responses.size())//If he has offspring
				return helpFather(String, q);//Send the son to search
		}
		Node* q = &(*it2);
		if (q->content == String)//we found
			return p;
		if (q->responses.size())//If he has offspring
			return helpFather(String, q);//Send the son to search
	}
	return NULL;//we didn't found
}

void Tree::trackPrinting(string val)//Prints the route from the current response to the tree root
{
	Node* p = search(val);
	cout << val;
	if (p != root)//while we didn't get to the top
	{
		cout << "=>";
		trackPrinting(father(val)->content);//send the father for printing
	}
}

void Tree::printPart(string val)// Prints a particular response and all of its descendants
{
	if (search(val))//if the reponse exists
		helpPrint(search(val));// print from the response and down
}