#include <stdio.h>
#include <string.h> /*strcmp()*/
#include <stdlib.h> /*malloc()*/

#include "ht.h"

#define NUM_OF_BUCKETS 100

size_t hash_func(const void *data)
{
    return *(int *)data % 10;
}

int is_match_func(const void *one, const void *other)
{
    return *(int *)one == *(int *)other;
}

size_t hash_func_dictionary(const void *data)
{
    char *str = (char *)data;
    size_t sum_ascii = 0;
    while ('\0' != *str)
    {
        ++str;
        sum_ascii += *str;
    }
    
    return sum_ascii % NUM_OF_BUCKETS;
}

int is_match_string(const void *one, const void *other)
{
    return !strcmp(one,other);
}

int action(void *data, void *params)
{
    (void)params;
    printf("%d,",*(int *)data);

    return 0;
}

char *LoadDict(ht_t *ht)
{
    FILE *dictionary = fopen("/usr/share/dict/words","r");
   
    char *buffer;
    size_t count = 0;
    char c = 0;
    size_t len;

    while(EOF != fgetc(dictionary))
    {
       ++count;
    }

    buffer = malloc(count + 1);

    fseek(dictionary,0,SEEK_SET);

    c = fgetc(dictionary);
    while(EOF != c)
    {
        if('\n' == c)
        {
            c = '\0';
        }
        *buffer = c;
        ++buffer;
        c = fgetc(dictionary);
       
    }
    *buffer = EOF;

    buffer -= count;

    while(EOF != *buffer)
    {
       
        len = strlen(buffer) + 1;
        HTInsert(ht, buffer);
        
        buffer += len;
    }

    buffer -= count;

    fclose(dictionary);
    return buffer;
}

int main(int argc, char **argv)
{
    ht_t *ht_dict = HTCreate(hash_func_dictionary,is_match_string,NUM_OF_BUCKETS);
    char *dict_buffer = NULL;
    char *str = argv[argc - 1];
    void *found2;
    ht_t *ht = HTCreate(hash_func,is_match_func,10);
    int a, b, c, d, e, f, g, h;
    void *found;
    
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    g = 7;
    h = 8;
   
    dict_buffer = LoadDict(ht_dict);

	printf("-----Dictionary----\n");									 

    found2 = HTFind(ht_dict, str);
    if (found2)
    {
        printf("Found! its %s\n", (char *)found2);
    }
    else
    {
        printf("not found :(\n");
    }

    printf("Load Factor is %f\n",HTLoadFactor(ht_dict));
/*    printf("Standard Deviation is %f\n",HTStandardDeviation(ht_dict));*/

    free(dict_buffer);
    HTDestroy(ht_dict);

    printf("-------------\n");
    printf("size is %lu\n",HTSize(ht));
    printf("is empty is %d\n",HTIsEmpty(ht));

    HTInsert(ht, &a);
    HTInsert(ht, &b);
    HTInsert(ht, &c);
    HTInsert(ht, &d);
    HTInsert(ht, &e);
    HTInsert(ht, &f);
    HTInsert(ht, &g);
    HTInsert(ht, &h);

    printf("Print table element\n");
    printf("\nstatus is %d\n",HTForEach(ht,action,NULL));
    HTRemove(ht,&d);
    printf("After remove:\n");
    printf("\nstatus is %d\n",HTForEach(ht,action,NULL));

    found = HTFind(ht, &c);
    if (found)
    {
        printf("Found! its %d\n", *(int *)found);
    }
    else
    {
        printf("not found :(\n");
    }
   
    printf("size is %lu\n",HTSize(ht));
    printf("is empty is %d\n",HTIsEmpty(ht));
   
    printf("LoadFactor is %f\n",HTLoadFactor(ht));
   /* printf("Standard Deviation is %f\n",HTStandardDeviation(ht));*/
   
    HTDestroy(ht);

    return 0;
}