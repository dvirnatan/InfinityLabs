#include <iostream>
#include <cstring>
#include "string.hpp"

static char *StrDup(const char* s)
{
	size_t len = strlen(s);
	char *m_cstr_ = new (std::nothrow) char[len + 1];
	memcpy(m_cstr_, s, len + 1);
	return m_cstr_;
}

ilrd::String::String(const char *s_)
{
	m_cstr = StrDup(s_);
}

ilrd::String::~String() {delete[] m_cstr; m_cstr = 0;}

ilrd::String::String(const String& other_)
{
	m_cstr = StrDup(other_.Cstr());
}

ilrd::String& ilrd::String::operator=(const String& other_)
{
	delete [] m_cstr;
	m_cstr = StrDup(other_.Cstr());
	return *this;
}

std::ostream& operator<<(std::ostream& os_, const ilrd::String& string_)
{
	return os_ << string_.Cstr();
}

bool ilrd::operator==(const ilrd::String& one_, const ilrd::String& other_)
{
	return strcmp(one_.Cstr(), other_.Cstr());
}

bool ilrd::operator<(const ilrd::String& one_, const ilrd::String& other_)
{
	return (strcmp(one_.Cstr(), other_.Cstr()) < 0);
}

bool ilrd::operator>(const ilrd::String& one_, const ilrd::String& other_)
{
	return (strcmp(one_.Cstr(), other_.Cstr()) > 0);
}

size_t ilrd::String::Length() const
{
	return strlen(m_cstr);
}

const char *ilrd::String::Cstr() const
{
	return m_cstr;
}

int main()
{
	ilrd::String s1("hello");

	printf("%s\n", s1.ilrd::String::Cstr());
	ilrd::String s2(s1);
	std::cout << s2.ilrd::String::Cstr() << std::endl;

	ilrd::String s3("ok");
	std::cout << s3.ilrd::String::Cstr() << std::endl;	
	s2 = s3;
	std::cout << s2.ilrd::String::Cstr() << std::endl;
	std::cout << (s1 == s3) << std::endl;	
	
	return 0;
}