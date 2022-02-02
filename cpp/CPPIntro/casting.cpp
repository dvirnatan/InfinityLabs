#include <stdio.h>

typedef struct Person Person_t;
struct Person
{
    char* name;
    int age;
};
typedef struct List
{
    Person_t list[10] = {0};
}List_t;

void *11_func (int name, int key)
{
    List_t list
    return;
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_func(ll, key);
    Person_t *p = (Person_t*)vv;
    p->age = age;
}