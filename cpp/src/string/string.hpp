#include <iostream>
#include <cstddef>

#ifndef ILRD_RD11_STRING_HPP
#define ILRD_RD11_STRING_HPP

namespace ilrd
{
class String
{
public:
    String(const char *s_ = "");
    String(const String& other_);
    ~String();
    String& operator=(const String& other_);
    size_t Length() const;
    const char *Cstr() const;

private:
    char *m_cstr;
};

std::ostream& operator<<(std::ostream& os_, const String& string_);
bool operator==(const String& one_, const String& other_);
bool operator<(const String& one_, const String& other_);
bool operator>(const String& one_, const String& other_);

} //namespace ilrd

#endif
