#include "String.h"

void TestStrChr ()
{
	char s1[] = "abcdefg";
	char c = 'e';
	if (strchr (s1, c) != StrChr (s1, c))
		printf("not good \n");
}

void TestStrCat ()
{
	char s1[20] = "This is ";
	char s2[] = "a test";
	char s3[] ="This is a test";
	
	 StrCat (s1, s2);
	 if (StrCmp (s1, s3))
	 	printf("Not good");
}

void TestStrnCat ()
{
	char s1[20] = "12345";
	char s2[] = "6789";
	char s3[] ="123456789";
	
	 StrnCat (s1, s2, 5);
	 if (StrCmp (s1, s3))
	 	printf("Not good StrnCat");
}






int main ()
{
	/* TestStrChr ();  
	 TestStrCat ();*/
	 	
	return 0;
}

