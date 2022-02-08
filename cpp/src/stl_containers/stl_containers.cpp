/**************************************
Author: Dvir Natan
Reviewer: 
Status: 
Date:
***************************************/
#include <iostream>
#include <iterator>
#include <map>
#include <list>

int Histo(void)
{
	using namespace std;
	map<string, int> map_c;
	map<string, int>::iterator iter;
	list<map<string, int>::iterator> list_c;
	pair<map<string, int>::iterator, bool> ret_insert;
	string str;
	static const int One = 1;

	while (getline(cin, str) && str != ".")
	{
		ret_insert = map_c.insert(pair<string, int>(str, One));
		if(ret_insert.second == true)
		{
			list_c.push_back(ret_insert.first);
		}
		else
		{
			++(*ret_insert.first).second;
		}
	 }

	list<map<string, int>::iterator>::iterator list_iter;
	cout << "Histogram:" << endl;
	for(list_iter = list_c.begin(); list_iter != list_c.end(); ++list_iter)
	{
		cout << (**list_iter).first;
		if((**list_iter).second > One)
		{	
			cout << " * " << (**list_iter).second;
		}
		cout << endl;
	}

	return 0;
}
