#pragma once
#include<iostream>
#include<string>

using namespace std;
const int ALPHABET = 26;

class Trie
{
protected:
	class TrieNode
	{
	public:
		TrieNode* children[ALPHABET] = { 0 };
		TrieNode* father = NULL;
		bool isEndWord = false;
		int countChildren = 0;

		TrieNode() {}
	};
	TrieNode* root = new TrieNode();

public:
	Trie() {}//ctor-initialize root to be "root"

	//all functions
	void insert(string str);//adds a word to the stock
	bool del(string str);//deletes a word to the stock
	void recursionDelete(TrieNode*, string str); //deletes letters if they are unnecessary
	bool search(string str);//searches if a node exist in the stock
	TrieNode* findNode(string str); // returns the node of the last letter in the word
	bool printAutoSuggestions(string str); // prints all the words that starts with...
	void printByRecursion(TrieNode*, string, int);// helps the function printAutoSuggestions
};

