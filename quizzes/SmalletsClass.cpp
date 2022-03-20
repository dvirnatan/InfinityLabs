#include <iostream>


class String
{
public:
String(char *c) : m_str(c) {}
char *Get() {return m_str;}

private:
char *m_str;
};
std::ostream& operator<<(std::ostream& os, const String& string) {return os << <const_cast>string.Get();} 

int main()
{	
	String s1 = "hello";

	//std::cout << s1 << std::endl;


	return 0;
}