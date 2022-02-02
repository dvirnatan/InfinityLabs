#include "Ex15.h"
#include <iostream>

void MaxCalling()
{
	//std::cout << "Ex15_2 no type specified " << Max(0.5, 0.6) << std::endl;
	std::cout << "Ex15_2 <int> " << Max<char>(5, 6) << std::endl;
	//std::cout << Max<char>('a', 'b') << std::endl;
}
