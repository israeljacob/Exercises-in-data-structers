#pragma once
#include"AbstrHashTable.h"
#include <iostream>
#include "Item.h"
#include<string>
using namespace std;
class HSubject :public AbstrHashTable <list<string>, string>
{
public:
	HSubject(int length) : AbstrHashTable(length) {}
	~HSubject() {}

	int h1(string str);

	int h2(string str);

	void printS(string subject);
	void addSubjectAndTitle(string subject, string title);
	void printN(string subject, int n);
	void startNewTable();
	void print();

	static void printList(list<string> toPrint);

	static int stringToNum(string str);

};

