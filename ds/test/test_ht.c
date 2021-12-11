#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "ht.h"

#define MAX_LEN 25
#define NUM_OF_LINE_IN_DICT 103000


char *strdup(const char *s);
size_t getline(char **lineptr, size_t *n, FILE *stream);

static int action_func (void *data, void *params)
{
    (void)params;
    printf("for each: %s\n" ,(char*)data );

    return 0;
}

static size_t HashFunc(const void *data)
{
    char *str = (char*)data;

    unsigned long hash = 5381;

    while (*str++)
    {
        
        hash = ((hash << 5) + hash) + *str; /* hash * 33 + c */
    }

    return hash % NUM_OF_LINE_IN_DICT;
}

static int IsMatch(const void *one, const void *other)
{
    return (!strcmp((char*)one, (char*)other));
}

int main(int argc , char **argv)
{
    size_t i = 0;
    ht_t *hash_table;
    FILE *stream;
    char *line = NULL;
    size_t len = MAX_LEN;
    size_t counter = 0;
    char **array_of_strings;
    char *find;
    int status = 0;
    char* search_for_me;

    search_for_me = argv[argc - 1];

    printf("search for me - %s\n", search_for_me);

    stream = fopen("/usr/share/dict/words", "r");

    assert(stream != NULL);

    line = malloc(MAX_LEN);
    array_of_strings = malloc(sizeof(char*) * NUM_OF_LINE_IN_DICT);
    
    i = 0;
    while((status = getline(&line, &len, stream)) != -1 && i < NUM_OF_LINE_IN_DICT)
    {
        array_of_strings[i] = strdup(line);
        ++i;
    }

    printf("%d, num of dups %ld\n", status, i);

    hash_table = HTCreate(HashFunc, IsMatch, NUM_OF_LINE_IN_DICT);

    counter = i;
    status = 0;
    for(i = 0; i < counter && status == 0; ++i)
    {
       status =  HTInsert(hash_table, array_of_strings[i]);
    }
    printf("status after insert %d\nsize is %ld\n\n", status, HTSize(hash_table));

    status = HTForEach(hash_table, action_func, NULL); 

    printf("status after ForEach %d\n", status);


    find = HTFind(hash_table, search_for_me);
    printf("%s\n", search_for_me);

    if(find != NULL)
    {
        printf("Find - %s\n",(char*)find);
    }
    else
    {
        puts("find is null");
    }

    free(line);
    for(i = 0; i < counter; ++i)
    {
        free(array_of_strings[i]);
    }
    free(array_of_strings);    

    HTDestroy(hash_table);
    fclose(stream);

    return 0;
}