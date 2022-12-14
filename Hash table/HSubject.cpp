#include "HSubject.h"
#include<iostream>
#include"AbstrHashTable.h"
#include "Item.h"
#include<string>
using namespace std;
int HSubject::h1(string str)					// first hush func
{
	int i = stringToNum(str) % table_size;
	return i;
}
int HSubject::h2(string str)					// second huah func
{
	int i = stringToNum(str) % table_size;
	return i + 3;
}
void HSubject::printS(string subject)			// print all titles of the subject
{
	int i = hash_search(subject);
	if (i != -1)
		printList(table[i].data);
	else
	{
		cout << "ERROR" << endl;
	}

}

void HSubject::addSubjectAndTitle(string subject, string title)		// add titel to exsist subject
{																	// if the subject already exsist
	int i = this->hash_search(subject);								// added the titel to it
	if (i == -1)
	{
		list<string> new_titel;
		new_titel.push_front(title);
		Item< list<string>, string> newItem(new_titel, subject, full);
		hash_insert(newItem);
	}
	else
	{
		table[i].data.push_front(title);
	}
}



void HSubject::printN(string subject, int n)						// print N first apearence of the choosen subject
{
	int i = hash_search(subject);
	if (i != -1)
	{
		int j = 0;
		for (list<string>::iterator it = table[i].data.begin(); it != table[i].data.end() && j < n; j++, it++)
			cout << *it << endl;
	}
	else
	{
		cout << "ERROR" << endl;											// if subject dos not exsist print "ERROR"
	}

}


void HSubject::startNewTable()										// intial  the table to its start position
{
	for (int i = 0; i < table_size; i++)
	{
		list<string>::iterator it1, it2;
		it1 = table[i].data.begin();
		it2 = table[i].data.end();
		table[i].data.erase(it1, it2);
		table[i].key = '\0';
		table[i].flag = deleted;
	}

}


void HSubject::print()												// print all subject and asosiated titels
{
	for (int i = 0; i < table_size; i++)
	{
		if (table[i].flag == full)
		{
			cout << table[i].key << ": ";
			list<string>::iterator it = table[i].data.begin();
			for (it; it != table[i].data.end(); it++)
			{
				cout << *it << " ";
			}
			cout << endl;
		}

	}
}





void HSubject::printList(list<string> toPrint)						// func that get list of string and print all the links
{
	for (list<string>::iterator i = toPrint.begin(); i != toPrint.end(); ++i)
		cout << *i << " ";
	cout << endl;
}
int HSubject::stringToNum(string str)
{
	int sum = 0;
	for (int i = 0; i < str.length(); i++)
	{
		sum += str.at(i) + 'a';

	}
	return sum;
}
