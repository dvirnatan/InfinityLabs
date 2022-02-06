#include <iostream>
#include <cstring>
#include "RCString.hpp"

void Test(bool state, size_t line)
{
    if (!state)
    {
        std::cout << "Error in line: " << line << std::endl;
    }
    
}

using ilrd::RCString;
using std::endl;

int main()
{
    RCString rs1;
    RCString rs2(rs1);
    Test(rs1 == rs2, __LINE__);
    RCString rs3 = "Dvir";
    Test(strcmp(rs3.CStr(), "Dvir") == 0, __LINE__);
    Test(rs3.Length() == 4, __LINE__);
    RCString rs4;
    std::cin >> rs4;
    rs1 = "Natan";
    rs4 = rs1; //Natan
    Test(rs4 == rs1, __LINE__);
    rs4 = rs4;
	std::cout << rs4 << endl;
	for(size_t i = 0; i < rs3.Length(); ++i)
	{
    	Test(rs1[i] == rs4[i], __LINE__);
	}
    Test(rs3 != rs2, __LINE__);
    rs2 = "aaaa";
	rs3 = "bbbb";
    Test(rs3 > rs2, __LINE__);
    rs1[0] = 'm';
    // try
    // {
    //     RCString rs6;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    
    // const RCString rs5("Kilo");
    // std::cout << rs3[0] << std::endl;
    // std::cout << rs5[0] << std::endl;
    // std::cout << rs1 << " " << rs2 << " " << rs3 << " " << rs4 << endl;

    return 0;
}