#include "ws6.h"

int main()
{
	unsigned int var1 = 3, var2 = 2;
	unsigned int var3 = 1;
	unsigned int var4 = 21;
	unsigned int var5 = 12;
	unsigned int var6 = 127;
	unsigned int var7 = 8;
	unsigned int var8 = 51;
	unsigned int var9 = 1;
	unsigned int var10 = 2;
	unsigned int var11 = 8;
	unsigned int var12 = 10;
	unsigned int var13 = 63;
	unsigned int var14 = 65;
	unsigned int var15 = 23452;
	float var16 = 3.14;
	
	long pow2;
	size_t check_pow2;
	unsigned int add_1;
	size_t pow2_loop;
	unsigned int arr[]={515,290,38,35,515};
	int bit6_and_bit2;
	int bit6_or_bit2;
	int miror_loop;
	unsigned char swap_bit3_bit5;
	unsigned char mirror;
	size_t bits_loop;
	int closet_smaller_num_16;
	size_t count_bits;
	
	
	pow2 =  Pow2(var1,var2);
	printf("%d * (2 ^ %d) = %ld\n",var1, var2, pow2);
	check_pow2 = IfPow2(var3);
	printf("check pow 2 of %u is %lu\n", var3, check_pow2);
	add_1 = AddOne(var4);
	printf("add_1 to %u is %u\n",var4, add_1);
	pow2_loop = IfPow2Loop(var5);
	printf("pow2 loop of %u is %lu\n", var5, pow2_loop);
	printf("The bits that have 3 bits are:\n");
	ThreeBitsOn(arr,5);
	bit6_and_bit2 = TwoAndSixAreOn(var6);
	printf("bit6&&bit2 of %u is = %d\n", var6, bit6_and_bit2);
	bit6_or_bit2= TwoOrSixAreOn(var7);
	printf("bit6||bit2 of %u is = %d\n", var7, bit6_or_bit2);
	swap_bit3_bit5 = SwapThreeAndFive(var8);
	printf("swap bit3 bit5 %u is %u\n", var8, swap_bit3_bit5);
	miror_loop = MirrorLoop(var9);
	printf("miror_loop of %u is %u\n",var9,miror_loop);
	mirror = Mirror(var10);
	printf("miror of %u is %u\n", var10, mirror);
	printf("Befor swap: a = %d, b = %d\n",var11,var12);
	Swap(&var11, &var12);
	printf("After swap: a = %d, b = %d\n",var11,var12);
	bits_loop = CountSetBitsLoop(var13);
	printf("bits_loop of %u is %lu\n",var13,bits_loop);
	closet_smaller_num_16 = SixTeen(var14);
	printf("closet_smaller_num_16 of %u is %d\n",var14,closet_smaller_num_16);
	count_bits = CountSetBitsNoLoop(var15);
	printf("count_bits of %u is %lu\n",var15,count_bits);
	printf("The float number %f is:\n",var16);
	PrintFloat(var16);
	
	return 0;
}
