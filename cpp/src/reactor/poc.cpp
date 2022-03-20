#include <map>
#include <iostream>

using std::cout;
using std:: endl;
using std::map;

int main()
{
	map<int, std::string> m;
	m.insert(std::pair<int, std::string>(1, "one"));
	m.insert(std::pair<int, std::string>(3, "three"));
	m.insert(std::pair<int, std::string>(0, "zero"));
	m.insert(std::pair<int, std::string>(4, "four"));

	// int num = 3;
	for(auto it : m)
	{
		it.second.append("*");
		cout << it.second << endl;
	}

	int array[4] = {1,3,0,4};
	int ii = 0;
	for(auto &i : array)
	{
		i += 1;
		cout << i << "\t";
		cout << array[ii] << endl;
		ii += 1;
	}

}