//  rcstring.hpp
#ifndef ILRD_RD111_RCSTRING_HPP
#define ILRD_RD111_RCSTRING_HPP

#if cplusplus <= 201103L 
#define noexcept throw()
#endif // #if cplusplus >= 201103L 

#include <ios> // ios_base::failure
#include <new> // bad_alloc
#include <iosfwd> //i/ostream

namespace ilrd
{
class RefCuntStr;

class RCString 
{
public:
    RCString(const char *s_ = "") throw(std::bad_alloc); // non explicit by design
    RCString(const RCString& other_) noexcept;
    ~RCString() noexcept;
    RCString& operator=(const RCString& other_) noexcept;
    
    size_t Length() const noexcept;
    const char *CStr() const noexcept;
    
    char operator[](size_t indx) const noexcept;
    char& operator[](size_t indx) throw(std::bad_alloc);
private:
    RefCuntStr *m_rcstr;
};

std::ostream& operator<<(std::ostream& os_, const RCString& string_) throw(std::ios_base::failure);
std::istream& operator>>(std::istream& is_, RCString& string_)throw(std::ios_base::failure);
bool operator==(const RCString& lhs_, const RCString& rhs_) noexcept;
bool operator!=(const RCString& lhs_, const RCString& rhs_) noexcept;
bool operator<(const RCString& lhs_, const RCString& rhs_) noexcept;
bool operator>(const RCString& lhs_, const RCString& rhs_) noexcept;
} // namespace ilrd

#endif // ILRD_RD111_RCSTRING_HPP