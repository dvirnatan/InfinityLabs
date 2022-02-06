#include <iostream>
#include <cstdio>
#include <cstring> // strlen memcopy
#include "RCString.hpp"


static char *StrDup(const char* s)
{
	size_t len = strlen(s);
	char *m_cstr_ = new char[len + 1];
	memcpy(m_cstr_, s, len + 1);
	return m_cstr_;
}

namespace ilrd
{
class RefCuntStr
{
public:
	RefCuntStr(const char *s_) : m_cstr(StrDup(s_)), m_cntr(1) {};
	~RefCuntStr() {delete[] m_cstr; m_cstr = 0;};

    const char *m_cstr;
    size_t m_cntr;
};

RCString::RCString(const char *s_) throw(std::bad_alloc) : m_rcstr(new RefCuntStr(s_))
{
	//empty;
}

RCString::~RCString()noexcept
{
	--m_rcstr->m_cntr;
	if(m_rcstr->m_cntr < 1) 
	{
		delete m_rcstr;
	}
}

RCString::RCString(const RCString& other_)noexcept : m_rcstr(other_.m_rcstr)
{
	++m_rcstr->m_cntr;
}

RCString& RCString::operator=(const RCString& other_) noexcept
{
	++(other_.m_rcstr->m_cntr);
	this->~RCString();
	this->m_rcstr = other_.m_rcstr;
	return const_cast<RCString&>(other_);
}

const char *RCString::CStr() const noexcept
{
	return this->m_rcstr->m_cstr;
}

size_t RCString::Length() const noexcept
{
	return strlen(this->m_rcstr->m_cstr);
}

std::ostream& operator<<(std::ostream& os_, const RCString& string_) throw(std::ios_base::failure)
{
	return os_ << string_.CStr();
}

std::istream& operator>>(std::istream& is_, RCString& string_)throw(std::ios_base::failure)
{
	char buffer[BUFSIZ];
	is_ >> buffer;
	string_ = buffer;

	return is_;
}

bool operator==(const RCString& lhs_, const RCString& rhs_) noexcept
{
	return strcmp(lhs_.CStr(), rhs_.CStr()) == 0;
}

bool operator!=(const RCString& lhs_, const RCString& rhs_) noexcept
{
	return !(lhs_ == rhs_);
}

bool operator<(const RCString& lhs_, const RCString& rhs_) noexcept
{
	return strcmp(lhs_.CStr(), rhs_.CStr()) < 0;
}

bool operator>(const RCString& lhs_, const RCString& rhs_) noexcept
{
	return strcmp(lhs_.CStr(), rhs_.CStr()) > 0;
}

char RCString::operator[](size_t indx) const noexcept
{
	return this->m_rcstr->m_cstr[indx];
}

char& RCString::operator[](size_t indx) throw(std::bad_alloc)
{
	*this = m_rcstr->m_cstr;
	return const_cast<char&>(m_rcstr->m_cstr[indx]);
}

}// namespace ilrd