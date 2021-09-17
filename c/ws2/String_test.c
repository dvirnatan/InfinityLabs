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

void TestStr ()
{
	char haystack[] = "abcdefghijklmnop";
	char needle[] = "hijk";
	
	if (StrStr (haystack, needle) != strstr (haystack, needle))
		printf("Not good StrStr\n"); 
		
	printf("strtr: %c\n", *strstr(haystack,needle));
	if (StrStr(haystack,needle) != NULL)
		printf("StrStr: %c\n", *StrStr(haystack,needle));
	else 
		printf("NULL\n");
}

void TestStrSpn ()
{
	char s[] = "abcdefghijklmnopqrstuwxy";
	char a[] = "abccz";
	
	if(strspn(s,a) != StrSpn(s,a))
		printf("Not good StrSpn");
	printf("%ld" , strspn(s,a));
	printf("%ld" , StrSpn(s,a));

}

void TestPalin()
{
	char sA[] = "redivider";
	char sB[] = "redivqder";
	
	printf("%ld, %ld" ,Palin(sA), Palin(sB));
}



int main ()
{
	/* TestStrChr ();  
	 TestStrCat ();
	 TestStr();
	 TestStrSpn (); */
	 TestPalin();	
	return 0;
}

