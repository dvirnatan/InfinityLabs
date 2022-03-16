/**********************************/
/*			BitArray			  */
/*	Author: Dvir Natan 			  */
/*	Reviwer: OrShoham			  */
/*	Date: 03/03/2022	          */
/*	Status: Fixing                */		  
/**********************************/


#ifndef __BIT_ARRAY_HPP
#define __BIT_ARRAY_HPP

#include <cstddef> // size_t
#include <string>
#include <algorithm>// for each
#include <stdexcept>// std::invalid_agument

namespace ilrd
{

static const unsigned char NumOfBits = 8;

template <size_t size>
class BitArray
{
public:
    explicit BitArray();
    ~BitArray();
    BitArray(const BitArray& other);
    const BitArray& operator=(const BitArray& other);

private:
    class Bit;
public:
    Bit operator[](size_t indx);
    bool operator[](size_t indx) const;

    const BitArray& operator|=(const BitArray& other);
    const BitArray& operator&=(const BitArray& other);
    const BitArray& operator^=(const BitArray& other);
    const BitArray& operator>>=(size_t n); //advanced
    const BitArray& operator<<=(size_t n); //advanced

    const BitArray& Set(bool val, size_t indx);
    const BitArray& Set(bool val);
    const BitArray& Flip(size_t indx);
    const BitArray& Flip();

    bool Get(size_t indx) const;
    size_t Count() const;
    std::string ToString() const;

private:
    unsigned char array[size / NumOfBits + !!(size % NumOfBits)];
	void ThrowException(size_t indx) const;
};

template <size_t size>
bool operator==(const BitArray<size>& lhs, const BitArray<size>& rhs);
template <size_t size>
bool operator!=(const BitArray<size>& lhs, const BitArray<size>& rhs);

template <size_t size>
const BitArray<size> operator|(const BitArray<size>& lhs, const BitArray<size>& rhs);
template <size_t size>
const BitArray<size> operator&(const BitArray<size>& lhs, const BitArray<size>& rhs);
template <size_t size>
const BitArray<size> operator^(const BitArray<size>& lhs, const BitArray<size>& rhs);


template <size_t size>
class BitArray<size>::Bit
{
public:
    explicit Bit(BitArray& bitArray, size_t indx);
    ~Bit();
    Bit(const Bit& other);
    const BitArray::Bit& operator=(bool b);
    const BitArray::Bit& operator=(const Bit& other);
    operator bool() const;

private:
    BitArray& m_bitArray;
    const size_t m_indx;
};

// implementation
template <size_t size>
BitArray<size>::BitArray() 
{
	Set(false);
}
template <size_t size>
BitArray<size>::~BitArray() 
{
	// Empty
}

template <size_t size>
BitArray<size>::BitArray(const BitArray& other) 
{
	std::copy(other.array, other.array + sizeof(other.array), array);
}

template <size_t size>
const BitArray<size>& BitArray<size>::operator=(const BitArray& other)
{
	std::copy(other.array, other.array + sizeof(other.array), array);
	return *this;
}

template <size_t size>
typename BitArray<size>::Bit BitArray<size>::operator[](size_t indx)
{
	ThrowException(indx);

	return Bit(*this, indx);
} 

template <size_t size>
bool BitArray<size>::operator[](size_t indx) const
{
	ThrowException(indx);

	return Get(indx);
} 

template <size_t size>
const BitArray<size>& BitArray<size>::operator|=(const BitArray& other)
{
	std::transform(other.array, other.array + sizeof(other.array), 
												array, array, std::bit_or<unsigned char>());
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::operator&=(const BitArray& other)
{
	std::transform(other.array, other.array + sizeof(other.array), 
												array, array, std::bit_and<unsigned char>());
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::operator^=(const BitArray& other)
{
	std::transform(other.array, other.array + sizeof(other.array), 
												array, array, std::bit_xor<unsigned char>());
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::Set(bool val, size_t indx)
{
	ThrowException(indx);

	if(val == true)
	{
		array[indx/NumOfBits] |=  (1 << (indx % NumOfBits));
	}
	else
	{
		array[indx/NumOfBits] &=  ~(1 << (indx % NumOfBits));
	}
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::Set(bool val)
{
	std::fill(array, array + sizeof(array), 0 - val);
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::Flip(size_t indx)
{
	ThrowException(indx);

	Set(!(Get(indx)), indx);
	return *this;
}

template <size_t size>
const BitArray<size>& BitArray<size>::Flip()
{
	std::transform(array, array + sizeof(array), array, std::bit_not());
	return *this;
}

template <size_t size>
bool BitArray<size>::Get(size_t indx) const 
{
	ThrowException(indx);

	return ((array[indx / NumOfBits] >> (indx % NumOfBits)) & 1);
}

template <size_t size>
std::string BitArray<size>::ToString() const
{
	std::string temp;
	for(size_t i = 0; i < size; ++i)
	{
		temp += Get(i) + '0';
	}
	return temp;
}

template <size_t size>
bool operator==(const BitArray<size>& lhs, const BitArray<size>& rhs)
{
	for(size_t i = 0; i < size; ++i)
	{
		if(lhs.Get(i) != rhs.Get(i))
		{
			return false;
		}
	}
	return true;
}

template <size_t size>
bool operator!=(const BitArray<size>& lhs, const BitArray<size>& rhs)
{
	return !(lhs == rhs);
}

template<size_t size>
const BitArray<size> operator|(const BitArray<size>& lhs, const BitArray<size>& rhs)
{
	BitArray<size> ret(lhs);
	return (ret |= rhs);
} 

template<size_t size>
const BitArray<size> operator&(const BitArray<size>& lhs, const BitArray<size>& rhs)
{
	BitArray<size> ret(lhs);
	return (ret &= rhs);
} 

template<size_t size>
const BitArray<size> operator^(const BitArray<size>& lhs, const BitArray<size>& rhs)
{
	BitArray<size> ret(lhs);
	return (ret ^= rhs);
} 

template <size_t size>
BitArray<size>::Bit::Bit(BitArray& bitArray, size_t indx)
 : m_bitArray(bitArray), m_indx(indx)
{
	// Empty
}

template <size_t size>
BitArray<size>::Bit::~Bit()
{
	// Empty
}

template <size_t size>
BitArray<size>::Bit::Bit(const Bit& other) : m_bitArray(other.m), m_indx(other.m_indx)
{
	// Empty
}

template <size_t size>
const typename BitArray<size>::Bit&  BitArray<size>::Bit::operator=(bool b)
{
	m_bitArray.Set(b, m_indx);
	return *this;
}

template <size_t size>
const typename BitArray<size>::Bit&  BitArray<size>::Bit::operator=(const Bit& other)
{
	m_bitArray.Set(other.m_bitArray.Get(other.m_indx), m_indx);
	return *this;
}

template <size_t size>
BitArray<size>::Bit::operator bool() const
{
	return m_bitArray.Get(m_indx);
}

class LUT
{
public:
	LUT();
    static void InitLut();
    unsigned char operator() (unsigned char byte);

private:
    static unsigned char m_lut[256];
    static bool is_init;
};
 
template <size_t size>
size_t BitArray<size>::Count() const
{
    static LUT lut;
    BitArray<size> temp(*this);

    temp.array[sizeof(temp.array) -1] <<= (sizeof(temp.array) * NumOfBits) - size;

    size_t counter = 0;
    for(size_t i = 0; i < sizeof(temp.array); ++i)
    {
         counter += lut(temp.array[i]);
    }

    return counter;
}

template<size_t size>
void BitArray<size>::ThrowException(size_t indx) const
{
	if(size <= indx)
	{
		throw std::invalid_argument("index is out of range");
	}
}


} // namespace ilrd

#endif // __BIT_ARRAY_HPP