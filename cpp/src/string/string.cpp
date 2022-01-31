/**************************************
Author: Dvir Natan
Reviewer: Mickey Grab
Status: Aprroved
Date: 13.1.2022
***************************************/
#include <ostream> // output stream
#include <cstring> //strcmp , memecpy
#include "string.hpp"

static char *StrDup(const char* s)
{
	size_t len = strlen(s);
	char *m_cstr_ = new char[len + 1];
	memcpy(m_cstr_, s, len + 1);
	return m_cstr_;
}

namespace ilrd
{
String::String(const char *s_) : m_cstr(StrDup(s_))
{
	// empty;
}

String::~String()
{
	delete[] m_cstr; m_cstr = 0;
}

String::String(const String& other_) : m_cstr(StrDup(other_.Cstr()))
{
	// empty;
}

String& String::operator=(const String& other_)
{
	delete [] m_cstr;
	m_cstr = StrDup(other_.Cstr());
	return *this;
}

std::ostream& operator<<(std::ostream& os_, const ilrd::String& string_)
{
	return os_ << string_.Cstr();
}

bool operator==(const String& one_, const String& other_)
{
	return strcmp(one_.Cstr(), other_.Cstr()) == 0;
}

bool operator<(const String& one_, const String& other_)
{
	return (strcmp(one_.Cstr(), other_.Cstr()) < 0);
}

bool operator>(const String& one_, const String& other_)
{
	return (strcmp(one_.Cstr(), other_.Cstr()) > 0);
}

size_t String::Length() const
{
	return strlen(m_cstr);
}

const char *String::Cstr() const
{
	return m_cstr;
}

}// namespace ilrd
// _____________________EOF____________________