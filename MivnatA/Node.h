#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;
class Node
{
public:
	string content;
	list <Node> responses;
	Node() { content = "0"; }//default ctor

	//ctor
	Node(string content, list <Node> responses) { this->content = content; this->responses = responses; }

	~Node() { responses.clear(); }//dtor
};