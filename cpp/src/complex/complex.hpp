//  Complex.hpp

#ifndef ILRD_RD111_COMPLEX_HPP
#define ILRD_RD111_COMPLEX_HPP

#include <iosfwd> // i/o stream

namespace ilrd
{
class Complex
{
public:
    Complex(double real_ = 0, double imaginary_ = 0);// non explicit by design
    Complex(const Complex& other_);
    ~Complex();
    Complex& operator=(const Complex& other_);
    const Complex& operator+=(const Complex& other_);
    const Complex& operator-=(const Complex& other_);
    const Complex& operator*=(const Complex& other_);
    const Complex& operator/=(const Complex& other_);
    
    void SetReal(double real_);
    void SetImaginary(double imaginary_);
    double GetReal() const;
    double GetImaginary() const;

private:
    double m_real;
    double m_imaginary;
};

std::ostream& operator<<(std::ostream& os_, const Complex& complex_);
std::istream& operator>>(std::istream& is_, Complex& complex_);
bool operator==(const Complex& lhs_, const Complex& rhs_);
bool operator!=(const Complex& lhs_, const Complex& rhs_);
const Complex operator+(const Complex& lhs_, const Complex& rhs_);
const Complex operator-(const Complex& lhs_, const Complex& rhs_);
const Complex operator*(const Complex& lhs_, const Complex& rhs_);
const Complex operator/(const Complex& lhs_, const Complex& rhs_);
} // namespace ilrd

#endif // ILRD_RD111_COMPLEX_HPP