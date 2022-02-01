#include "complex.hpp"
#include <iostream>

namespace ilrd
{
	Complex::Complex(double real_, double imaginary_) : m_real(real_), m_imaginary(imaginary_)
	{
		// empty
	}

	Complex::Complex(const Complex& other_) : m_real(other_.m_real), m_imaginary(other_.m_imaginary)
	{
		// empty
	}

	Complex::~Complex()
	{
		// empty
	}
	
	Complex& Complex::operator=(const Complex& other_)
	{
		m_real = other_.m_real;
		m_imaginary = other_.m_imaginary;
		return *this;
	}

	const Complex& Complex::operator+=(const Complex& other_)
	{
		m_real += other_.m_real;
		m_imaginary += other_.m_imaginary;
		return *this;
	}

	const Complex& Complex::operator-=(const Complex& other_)
	{
		m_real -= other_.m_real;
		m_imaginary -= other_.m_imaginary;
		return *this;	
	}

	// 	const Complex& Complex::operator*=(const Complex& other_) {}
	//	const Complex& Complex::operator/=(const Complex& other_) {}

	void Complex::SetReal(double real_)
	{
		m_real = real_;
	}

	void Complex::SetImaginary(double imaginary_)
	{
		m_imaginary = imaginary_;
	}

	double Complex::GetReal() const
	{
		return m_real;
	}

	double Complex::GetImaginary() const
	{
		return m_imaginary;
	}

	std::ostream& operator<<(std::ostream& os_, const Complex& complex_)	
	{
		return os_ << "(" << complex_.GetReal() <<" + " << complex_.GetImaginary() << "i"
		<< ")" << std::endl;
	}

	std::istream& operator>>(std::istream& is_, Complex& complex_)
	{
		double real;
		double imaginary;

		is_ >> real >> imaginary;

		complex_.SetReal(real);
		complex_.SetImaginary(imaginary);

		return is_;
	}

	bool operator==(const Complex& lhs_, const Complex& rhs_)
	{
		return (lhs_.GetReal() == rhs_.GetReal() && lhs_.GetImaginary() == rhs_.GetImaginary());
	}

	bool operator!=(const Complex& lhs_, const Complex& rhs_)	
	{
		return (!(lhs_ == rhs_));
	}

	const Complex operator+(const Complex& lhs_, const Complex& rhs_)
	{
		Complex ret(lhs_.GetReal() + rhs_.GetReal(), lhs_.GetImaginary() + rhs_.GetImaginary());
		return ret;
	}

	const Complex operator-(const Complex& lhs_, const Complex& rhs_)
	{
		Complex ret(lhs_.GetReal() - rhs_.GetReal(), lhs_.GetImaginary() - rhs_.GetImaginary());
		return ret;
	}

}// namespace ilrd