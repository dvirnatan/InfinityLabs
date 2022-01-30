#include <iostream>
#include <cstring>
#include "string.hpp"

ilrd::String::String(const char *s_)
{
	size_t len = strlen(s_);
	m_cstr = new (std::nothrow) char[len + 1];
	strcpy(m_cstr, s_);
}

ilrd::String::~String() {delete[] m_cstr; m_cstr = 0;}

ilrd::String::String(const String& other_)
{
	size_t len = strlen(other_.CStr());
	m_cstr = new (std::nothrow) char[len + 1];
	strcpy(m_cstr, other_.m_cstr);
}

ilrd::String& ilrd::String::operator=(const String& other_)
{
	delete [] m_cstr;
	size_t len = strlen(other_.m_cstr);
	m_cstr = new (std::nothrow) char[len + 1];
	memcpy(m_cstr, other_.m_cstr, len + 1);
	return *this;
}

size_t ilrd::String::Length() const
{
	return strlen(m_cstr);
}

char *ilrd::String::CStr() const
{
	return m_cstr;
}

int main()
{
	ilrd::String s1("hello");

	printf("%s\n", s1.ilrd::String::CStr());
	ilrd::String s2(s1);
	std::cout << s2.ilrd::String::CStr() << std::endl;

	ilrd::String s3("ok");
	std::cout << s3.ilrd::String::CStr() << std::endl;	
	s2 = s3;
	std::cout << s2.ilrd::String::CStr() << std::endl;	
	

	return 0;
}