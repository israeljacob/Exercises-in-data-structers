#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
using namespace std;
class boolandLTeter
{
public:
	bool falg;
	string x;
	boolandLTeter() {};
	boolandLTeter(bool fla, string y) { falg = fla, x = y; }
};
class letter
{
public:
	string ltr;
	int  frq;
	string binCode;
	letter()
	{
		ltr = "";
		frq = 0;
		binCode = " ";
	}
	letter(string Ltr, string code) :ltr(Ltr), binCode(code) {};
	letter(string _ltr, int _freq) : ltr(_ltr), frq(_freq)
	{
		binCode = "";
	}

	letter(letter& other)
	{
		this->frq = other.frq;
		this->ltr = other.ltr;
	}

};
//a node of a leaf or a node of a subtree.
class HNode
{
public:
	string ltr;
	int frq;
	HNode* left;
	HNode* right;
	HNode* fazer;
	string cood;
	friend class compareNode;
	HNode() {}
	HNode(string s, int n) : ltr(s), frq(n) { left = NULL, right = NULL; }
};
class compareNode
{
public:
	HNode* n;
	bool operator()(HNode* const& n1, HNode* const& n2)
	{
		return(n1->frq > n2->frq);
	}
};
class HuffmanTree
{
public:
	HNode* root;

	void buildTree2(string* destrcture, string* orderTreeLetr)
	{
		this->root = NULL;
		root = new HNode();
		BuildTree2(destrcture, orderTreeLetr, root);
	}

	void BuildTree2(string* destrcture, string* orderTreeLetr, HNode* node)
	{
		if ((*destrcture)[0] == '0')
		{
			HNode* x = new HNode();
			HNode* y = new HNode();
			node->left = x;
			node->right = y;

			x->fazer = node;
			y->fazer = node;

			*destrcture = destrcture->substr(1);

			BuildTree2(destrcture, orderTreeLetr, node->left);
			BuildTree2(destrcture, orderTreeLetr, node->right);

		}

		else
		{
			if ((*destrcture)[0] == '1')
			{
				node->ltr = orderTreeLetr->substr(0, 1);

				*orderTreeLetr = orderTreeLetr->substr(1);

				*destrcture = destrcture->substr(1);


			}

		}

	}
	void bulidcoodinLeters(vector<letter*>* Leters, string leters)
	{

		for (int i = 0; i < leters.size(); i++)

		{

			string code = "";
			string x = "";
			x = leters[i];
			string temp = BulidcoodinLeters(code, x, root);
			//cout << temp << endl;
			letter* tempp = new letter(x, temp);
			Leters->push_back(tempp);
		}

	}
	string BulidcoodinLeters(string code, string letr, HNode* node)
	{
		if (node == NULL)
			return "";

		if (node->ltr == letr)
		{
			return code;
		}
		return BulidcoodinLeters(code + "0", letr, node->left) + BulidcoodinLeters(code + "1", letr, node->right);

	}

	void buildTree(vector<letter*> table)
	{
		this->root = NULL;
		priority_queue<HNode*, vector<HNode*>, compareNode> pQueue;

		for (vector<letter*>::iterator it = table.begin(); it != table.end(); it++)
		{
			HNode* temp = new HNode((*it)->ltr, (*it)->frq);

			pQueue.push(temp);
		}
		HNode* x = new HNode();
		HNode* y = new HNode();
		for (int t = 0; t < table.size() - 1; t++)
		{
			HNode* z = new HNode();
			x = pQueue.top();
			pQueue.pop();
			y = pQueue.top();
			pQueue.pop();
			/*if (x->frq == y->frq)
			{
				if ( x->ltr ==""||y->ltr=="")
				{
					HNode* temp = x;
					x = y;
					y = temp;

				}
			}*/
			bincood(x, 0);
			bincood(y, 1);
			z->left = x;
			z->right = y;
			z->frq = x->frq + y->frq;
			pQueue.push(z);
		}

		root = pQueue.top();
		pQueue.pop();
	}
	void To_put_code_in_vec_leter(vector<letter*>* Leters)
	{
		to_put_code_in_vec_leter(root, Leters);
	}

	void to_put_code_in_vec_leter(HNode* node, vector<letter*>* Leters)
	{
		if (node->left == NULL && node->right == NULL)

		{
			for (vector<letter*>::iterator it = Leters->begin(); it != Leters->end(); it++)
			{
				if ((*it)->ltr == node->ltr)
				{
					(*it)->binCode = node->cood;

				}
			}
			return;
		}
		if (node->left) to_put_code_in_vec_leter(node->left, Leters);
		if (node->right) to_put_code_in_vec_leter(node->right, Leters);


	}
	void bincood(HNode* node, int x)
	{
		if (node->left == NULL && node->right == NULL)
		{
			if (x == 0)
			{
				string temp = "0" + node->cood;
				node->cood = temp;
				//cout << node->ltr << " " << node->cood << endl;

			}
			if (x == 1)
			{
				string temp = "1" + node->cood;
				node->cood = temp;
				//cout << node->ltr << " " << node->cood << endl;

			}
		}
		if (node->left) bincood(node->left, x);
		if (node->right) bincood(node->right, x);
	}
	void print2(string encodedText, vector<letter*> vec, int n)

	{
		//cout << "1 ";
		vector<letter*>::iterator it;

		for (int i = 0; i < 1000 /*encodedText.size*/; i++)
		{
			//cout << encodedText.size();
			//if (encodedText.size() == 0)
			//{
			////	cout << " 3 ";
			//	return;
			//}
			int count = 0;
			bool flag = false;
			int chek = 0;
			vector<letter*>::iterator it;
			for (it = vec.begin(); it != vec.end(); it++)
			{
				int x = (*it)->binCode.size();
				for (int i = 0; i < x; i++)
				{
					if ((*it)->binCode[i] == encodedText[count])
					{
						count++;
						chek++;
						if (chek == x)
						{
							flag = true;
							break;
						}
					}
					else
					{
						count = 0;
						chek = 0;

						break;
					}
				}
				if (flag)
				{
					cout << (*it)->ltr;
					encodedText = encodedText.substr(x);
					count = 0;
					chek = 0;
					flag = false;
					break;

				}

			}


		}



	}

	void print()
	{

		TreeSortedString(root);


	}

	void TreeSortedString(HNode* node)
	{


		if (node->left == NULL && node->right == NULL)
			return;
		if (node->left) TreeSortedString(node->left);
		cout << node->left->ltr << "";

		if (node->right) TreeSortedString(node->right);
		cout << node->right->ltr << "";
	}
	void TreeCode()
	{
		TReeCode(root);

	}
	void TReeCode(HNode* root)
	{
		if (!root->left)
		{
			cout << "1";
			return;
		}
		cout << "0";
		if (root->left)TReeCode(root->left);
		if (root->right)TReeCode(root->right);

	}
	void printCode()
	{
		PrintCode(root);
	}
	void PrintCode(HNode* root)
	{
		if (root->left == NULL && root->right == NULL)
		{
			return;
		}

		if (root->left) { cout << "1";  PrintCode(root->left); }
		if (root->right) { cout << "0";  PrintCode(root->right); }
	}


	void myFun(string kk, string nn, HNode* n, int m)
	{
		if (kk.size())
		{
			if (nn[m] == '0')
			{
				n->left = new HNode();
				n->left->fazer = n;
				if (nn[m + 1] == '1')
				{
					n->left->ltr = kk[0];
					kk.erase(0, 1);
					myFun(kk, nn, n, m + 1);
				}
				else
				{
					myFun(kk, nn, n->left, m + 1);
				}
			}
			else
			{
				n->right = new HNode();
				n->right->fazer = n;
				if (nn[m + 1] == '1')
				{
					n->right->ltr = kk[0];
					kk.erase(0, 1);
					n = n->fazer;
					while (kk.size() && n->right)
						n = n->fazer;
					myFun(kk, nn, n, m + 1);
				}
				else
				{
					myFun(kk, nn, n->right, m + 1);
					//myFun(kk, nn, n, m + 1);
				}
			}
		}
	}

	void myFun2(string nn, HNode* n, int count)
	{
		if (nn.size())
		{
			if (nn[count] == '0')
			{
				if (n->left)
					myFun2(nn, n->left, ++count);
				else
				{
					cout << n->ltr;
					nn.erase(0, count);
					myFun2(nn, root, 0);
				}
			}
			else
			{
				if (n->right)
					myFun2(nn, n->right, ++count);
				else
				{
					cout << n->ltr;
					nn.erase(0, count);
					myFun2(nn, root, 0);
				}
			}
		}
		if (!nn.size())
			return;
	}
};