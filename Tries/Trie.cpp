#include "Trie.h"
#include<iostream>
#include<string>

using namespace std;

//ASCII code of small a
const int   a = 97;


//adds a word to the stock
void Trie::insert(string str)
{
	// start from the root
	TrieNode* temp = root;
	int i;
	//Runs as the number of letters in the string, unless it breaks
	for (i = 0; i < str.length(); i++)
	{
		//if the letter doesn't exist we need to create a new node
		if (!temp->children[str[i] - a])
		{
			break;
		}
		else
			temp = temp->children[str[i] - a];//check the next letter
	}
	// Runs from the first letter that not exists till the end of the word
	for (int j = i; j < str.length(); j++)
	{
		//update the new node
		temp->children[str[j] - a] = new TrieNode();
		temp->children[str[j] - a]->father = temp;
		temp->countChildren++;
		//go on
		temp = temp->children[str[j] - a];
	}
	//the last letter is an end of the word
	temp->isEndWord = true;
}

//deletes a word to the stock
bool Trie::del(string str)
{
	//start from the root
	TrieNode* temp = root;
	//check every letter in str
	for (int i = 0; i < str.length(); i++)
	{
		//if the letter doesn't exist
		if (!temp->children[str[i] - a])
			return false;
		//if it exists go over to the next letter
		else
			temp = temp->children[str[i] - a];
	}
	//if it's not an end of a word so str doesn't exist
	if (!temp->isEndWord)
		return false;
	//if str exists and there is a continuation to a bigger word
	else if (temp->countChildren)
	{
		// don't delete any letter just indicate that here is not an end of a word
		temp->isEndWord = false;
		return true;
	}
	//if str exists and there isn't a continuation to a bigger word
	else
	{
		//delete the letters till you get a diffrent end
		recursionDelete(root->children[str[0] - a], str);
		return true;
	}
}

//deletes letters if they are unnecessary
void Trie::recursionDelete(TrieNode* node, string str)
{
	//if str contains more then 1 letter.
	if (str.length() > 1)
	{
		char save = str[0];
		str.erase(0, 1);
		//send str except from the first letter to our function (by recurtion).
		recursionDelete(node->children[str[0] - a], str);
		//if the node has children thet we did dekete or if the node is an end of an other word.
		if (node->countChildren || node->isEndWord)
			//so stop deletting.
			return;
		else
		{
			// delete the note.
			node->father->children[save - a] = NULL;
			node->father->countChildren--;
		}
	}
	// if str contains just the last note from the original str.
	else
	{
		// delete the note.
		node->father->children[str[0] - a] = NULL;
		node->father->countChildren--;
	}
}


//searches if a node exist in the stock
bool Trie::search(string str)
{
	//start from the root
	TrieNode* temp = root;
	//check every letter in str
	for (int i = 0; i < str.length(); i++)
	{
		temp = temp->children[str[i] - a];
		//if the letter doesn't exist
		if (!temp)
			return false;
	}
	//if str exists
	if (temp->isEndWord)
		return true;
	//if it's not an end of a word so str doesn't exist
	else
		return false;
}

// returns the node of the last letter in the word
Trie::TrieNode* Trie::findNode(string str)
{
	//start from the root
	TrieNode* temp = root;
	//check every letter in str
	for (int i = 0; i < str.length(); i++)
	{
		if (temp->children[str[i] - a])
			temp = temp->children[str[i] - a];
		//if the letter dosn't exist so str too.
		else
			return NULL;
	}
	// return the node of the last letter in str
	return temp;
}


// prints all the words that starts with...
bool Trie::printAutoSuggestions(string str)
{
	TrieNode* node = findNode(str);
	if (!node)
		return false;
	//send the last letter in str to search the words that continuing it.
	printByRecursion(node, str, 0);
	return true;
}


// helps the function printAutoSuggestions
void Trie::printByRecursion(TrieNode* node, string str, int counter)
{
	//if we got to an end of a word and we didn't print it yet.
	if (node->isEndWord && !counter)
	{
		//print
		cout << str << endl;
		//indicate that it was printed.
		counter++;
		//send to print bigger words that starts with the word that was printed.
		printByRecursion(node, str, counter);
	}
	else
	{
		//if we got to an end of a word and we did print it already.
		if (node->isEndWord && counter)
			//go on and indicate that the next word wasn't printed yet.
			counter--;
		for (int i = 0; i < ALPHABET; i++)
		{
			//if there is a child
			if (node->children[i])
			{
				char add = ('a' + i);
				//send str + the added note to our function (by recurtion).
				printByRecursion(node->children[i], (str + add), counter);
			}
		}
	}
}
