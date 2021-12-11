/*int arr[8] = {-2, 4, 3, -2, 1, -6, -3, 10 };
	    
i = 0
sub ( 0 , 0 )
max ( 0 , 0 )
כל עוד האיבר הבא לא מקטין את SUB מתחת ל0 צרף אותו.

אם sub גדול מהמקסימום עד כה עדכן את max

i <-- 0 to len
{
	if ( sub + arr[i] > 0 )
		sub += arr[i]
		end = i;
	else
	{
		++i;
		start = i
		end = i
		sub = arr[i]
	}
	if (sub > max)
	{
		update the max struct
	}
}
return max


*/
#include <stdio.h>
#include <stddef.h>

struct res
{
	int start, end, sum;
};

struct res MaxSubArray (int *arr, int len)
{
	int i = 0;
	int end, start, sum;
	struct res res;
	
	end = start = sum = 0;
	
	for (i = 0; i < len ; ++i)
	{
		if (sum + arr[i] < 0)
		{
			++i;
			start = end = i;
			sum = arr[i];
		}
		else
		{
			end = i;
			sum += arr[i];
		}
		
		if (res.sum < sum)
		{
			res.sum = sum;
			res.start = start;
			res.end = end;
		}
	}
	return res;
}

int main ()
{
	int arr[] = {11,2,2,-5,-10,1,9,-8,8,-2};
	int len;
	struct res res;
	len = sizeof(arr)/sizeof (arr[0]);
	res = MaxSubArray(arr, len);
	printf("%d (%d, %d)\n",res.sum,res.start,res.end);
	return 0;
}



















/*
#include <stdio.h>

struct sub
{
	int start ;
	int end ;
	int res ;
};
int main ()
{
	int arr[8] = {-2, 4, 3, -4, -1, 2, 3, 5 };
	int i = 0;
	int start = 0;
	int end = 0;
	int sub = 0;
	struct sub sub_r;	
	sub_r.end = 0;
	sub_r.start = 0;
	sub_r.res = 0;
	
	
	for (i = 0; i < 8; ++i)
	{
		if((sub + arr[i]) < sub)
		{
			++i;
			start = end = i;
			sub =  arr[i];
		}
		else
		{
			if (arr[i-1] < 0)
			{
				start = i;
			}
				
			end = i;
			sub += arr[i];
		}		
		
		if (sub > sub_r.res)
		{
			sub_r.start = start;
			sub_r.end = end;
			sub_r.res = sub;
		}
		
		
	}
	printf("start - %d,end - %d,res - %d \n", sub_r.start, sub_r.end,
	 sub_r.res);
	return 0;
}

*/
