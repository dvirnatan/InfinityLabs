#include <iostream>
#include "BitArray.hpp"

using ilrd::BitArray;
using std::cout;
using std::endl;

int main()
{
	BitArray<9> b1, b2, b3;

	b1.Set(1, 1);
	b1[1] = true;
	b2 = b1;
	b2[2] = true;
	b3 = b2;
	b3[3] = true;

	cout << b1.ToString() << endl;
	cout << b3.ToString() << endl;
	b3[8] = b1[1];
	cout << b3.ToString() << endl;

	b1.Set(true);
	cout << b1.ToString() <<": " <<  b1.Count() << endl;
	b2 = b1;
	b2.Flip(8);
	cout << b1.ToString() <<" == " <<  b2.ToString() << endl;
	if( b1 == b2)
	{
		cout << "Yes" << endl;
	}
	

	// b3[9] = true;
	// cout << b3.ToString() << endl;
	
	// cout << " b1: "<< b1[1] << " b2: " << b2[2] << " b3: " << b3[3] << endl;
	// cout << b2.ToString() << endl;

	// cout << b3.Count() << endl;
	// cout << b2.Count() << endl;
	// cout << b1.Count() << endl;
	// b1.Set(true);
	// cout << b1.Count() << endl;
	// b1.Flip();
	// cout << b1.Count() << endl;



	
	return 0;
}