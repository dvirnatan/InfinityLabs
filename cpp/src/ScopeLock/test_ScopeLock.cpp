#include <iostream>
#include <pthread.h>
#include "ScopeLock.hpp"

using ilrd::ScopeLock;
using std::cout;
using std::endl;

static size_t failed_tests = 0;

static inline void Test(bool expr, size_t test_num)
{
    if (!expr)
    {
        cout << "test: " << test_num << " failed" << endl;
        ++failed_tests;
    }
}

int main()
{
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int position;
    {

       ScopeLock <pthread_mutex_t>Slock(lock, &pthread_mutex_unlock);

        position = pthread_mutex_lock(&lock);

        cout << "lock position: " << position << endl;

    }

        position = pthread_mutex_lock(&lock);

        cout << "lock position: " << position << endl;



    return 0;
}
