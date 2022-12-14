#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffman.h"
using namespace std;

//void priorityQueueExapmple();



int LettersCount(string text, vector<letter*>*);
void bincode(vector<letter*>, string);


int main()
{
	int choice;
	int size = 0;
	string text = "", temptext = "";
	string inputname, outputname;
	vector<letter*> table;
	string kidud[256];
	string binaryCode;
	stringstream strStream;
	double x;
	int codeLen, BT1, BT2 = 0;
	HuffmanTree* tree = new HuffmanTree();
	HuffmanTree* tree2 = new HuffmanTree();

	int n;
	string latrsDcoder;
	string encodedStructure;
	string encodedText;

	//system("color 9f");
	cout << " enter 1 to encode a text\n";
	cout << "enter 2 to decode a text\n";
	cout << "enter 3 to exit\n";
	do
	{

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "enter the original text" << endl;
			cin >> text;
			int NumOfLetters = LettersCount(text, &table);
			cout << "The encoded string is:" << endl;
			cout << NumOfLetters << endl;
			tree->buildTree(table);
			tree->print();
			cout << endl;
			tree->TreeCode();
			cout << endl;
			tree->To_put_code_in_vec_leter(&table);
			bincode(table, text);
			cout << endl;


			table.clear();
		}
		break;

		case 2:
		{
			cout << "enter n ";
			cout << "enter the letters ";
			cout << "enter the encoded structure ";
			cout << "enter the encoded text ";

			cin >> n;
			cin >> latrsDcoder;
			string latrsDcoder2 = latrsDcoder;


			cin >> encodedStructure;
			cin >> encodedText;
			string* leters = &latrsDcoder;
			string* EncodedStructure = &encodedStructure;

			//tree2->buildTree2(EncodedStructure, leters);




			/* for (vector<letter*>::iterator it = table.begin(); it!= table.end() ; it ++)
			 {
				 cout << (*it)->ltr<< " ";
				 cout << (*it)->binCode << endl;
			 }*/
			tree->root = new HNode();
			tree->myFun(latrsDcoder, encodedStructure, tree->root, 0);
			tree2->bulidcoodinLeters(&table, latrsDcoder2);
			cout << "The decoded string is: ";
			//tree->myFun2(encodedText, tree->root, 0);
			tree2->print2(encodedText, table, n);
			//table.clear();
			cout << endl;


		}
		break;


		}

	} while (choice != 3);
}

int LettersCount(string text, vector<letter*>* Leters) //to put in vector 
{
	int temp[256] = { 0 };
	int counter = 0;
	for (int i = 0; i < text.length(); i++)
	{
		temp[(int)text[i]] ++;
	}

	for (int i = 0; i < 256; i++)
	{
		if (temp[i] > 0)
		{

			int x = temp[i];
			char temp = (char)i;
			string tempp = "";
			tempp += temp;
			letter* current = new letter(tempp, x);

			Leters->push_back(current);
			counter++;
		}
	}
	return counter;
}
void bincode(vector<letter*> table, string text)//to string binCode that text
{
	for (int i = 0; i < text.size(); i++)
	{
		for (vector<letter*>::iterator it = table.begin(); it != table.end(); it++)
		{

			string temp = "";
			temp += text[i];
			if (temp == (*it)->ltr)
			{
				cout << (*it)->binCode;
			}
		}
	}
}
