#pragma once
#include<vector>
#include <iostream>
#include "Item.h"
using namespace std;
static int nerest_priem_number(int number);
template <class T, class K>  class AbstrHashTable
{
public:
	int table_size = 0;												// initial length 
	Item<T, K>* table;												// field array of Item 
	AbstrHashTable(int length)										// constructor
	{
		this->table_size = nerest_priem_number(length);				// initial the table with the nearest prime number 
		table = new Item<T, K>[table_size];							// by calling func for this
		for (int i = 0; i < table_size; i++)
		{															// initial the stat to be empty
			table[i].flag = Empty;
		}
	}
	virtual ~AbstrHashTable()
	{																// destructor
		delete[]table;
	}
	virtual int  h1(K k) = 0;
	virtual int h2(K k) = 0;										// tow hush functions
	int hash_h(K k, int i)
	{																// hushing by "multyple hushing" methode
		return (h1(k) + i * h2(k)) % table_size;
	}

	int hash_search(K k)											// the search attribute 
	{
		int j;
		int i = 0;
		do
		{
			j = hash_h(k, i);
			if (table[j].key == k)									// if state= full return the index
				//  empty or deleted return -1
			{
				if (table[j].flag == deleted)
					return -1;
				return j;
			}
			i++;

		} while (i != table_size && table[j].flag != Empty);
		return -1;
	}

	void hash_insert(Item<T, K> newItem)							//  the insertion attribute 
	{																// get an item as parameter
																	// if the table isnt full
		int i = 0;													// searching for the first avalible place
		do
		{
			int j = hash_h(newItem.key, i);
			if (table[j].flag == Empty || table[j].flag == deleted)
			{
				table[j] = newItem;
				return;
			}
			i++;

		} while (i != table_size);
	}

	void remove(K k)												// the delete attribute
	{
		int i = hash_search(k);
		if (i == -1)
		{
			return;
		}
		table[i].flag = deleted;
	}


	void upgrade_item(int index)
	{
		cout << "Enter data  to upgrade" << endl;
		T new_content;
		cin >> new_content;
		table[index] = new Item<T, K>(new_content, table[index].key, table[index].flag);
	}

	void hash_print()
	{
		for (int i = 0; i < table_size; i++)
		{
			table[i].print();
		}
	}






};



// func that return the nearest prime number
static int nerest_priem_number(int number)
{
	int prime_num =-1;
	for (int i = number; i > 1; i--)
	{
		bool flag = 0;
		for (int j = i - 1; j > 1; j--)
		{
			if (i % j == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			prime_num = i;
			break;
		}
	}
	return prime_num;
}