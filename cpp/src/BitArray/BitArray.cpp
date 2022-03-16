/**********************************/
/*			BitArray			  */
/*	Author: Dvir Natan 			  */
/*	Reviwer: OrShoham			  */
/*	Date: 03/03/2022	          */
/*	Status: Fixing                */		  
/**********************************/

#include "BitArray.hpp"

static const size_t NumOfEntriesInLut = 256;

namespace ilrd
{
	static unsigned char CountBits(unsigned char val);
	unsigned char LUT::m_lut[NumOfEntriesInLut];
    bool LUT::is_init;

	LUT::LUT()
	{
		if(!is_init)
		{
			InitLut();
			is_init = true;
		}
	}

	unsigned char LUT::operator()(unsigned char byte)
	{
		return m_lut[byte];
	}

	void LUT::InitLut()
	{
		for(size_t i = 0; i < NumOfEntriesInLut; ++i)
		{
			m_lut[i] = CountBits(i);
		}
	}

static unsigned char CountBits(unsigned char val)
{
    size_t counter = 0;
    while(val)
    {
        ++counter;
        val &= (val - 1);
    }
    return counter;
}


} // namespace ilrd

