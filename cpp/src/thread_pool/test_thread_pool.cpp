#include <iostream>
#include "thread_pool.hpp"

using ilrd::ThreadPool;
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

void func_nothing()
{
    cout << "function that does nothing" << endl;
    return;
}

void func_something()
{
    cout << "function that does something" << endl;
    // sleep(2);
}

int main()
{
    ThreadPool pool(4);
    pool.Pause();
    // sleep(1);
    cout << "Main Thread: Waiting..." << endl;
    // sleep(1);
    cout << "Main Thread: Done Waiting..." << endl;

    pool.AddTask(ilrd::ThreadPool::LOW ,func_nothing);
    pool.AddTask(ilrd::ThreadPool::HIGH ,func_something);

    pool.AddTask(ilrd::ThreadPool::LOW ,func_nothing);
    pool.AddTask(ilrd::ThreadPool::MEDIUM ,func_something);
    
    pool.Continue();
    
    // sleep(1);
    // pool.SetNumThreads(0);

    std::chrono::duration<int, std::milli> wait_for(3000); //miliseconds_t;

    sleep(1);
    bool res = pool.Finish(wait_for);
    // cout << "Finish returned:" << res << endl;
    return 0;
}
