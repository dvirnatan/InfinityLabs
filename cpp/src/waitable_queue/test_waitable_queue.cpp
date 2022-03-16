#include <iostream>
#include <thread>
#include "waitable_queue.hpp"
#include "PQWrapper.hpp"

using ilrd::WaitableQueue;
using std::cout;
using std::endl;
void Test2();



static size_t failed_tests = 0;

static inline void Test(bool expr, size_t test_num)
{
    if (!expr)
    {
        cout << "test:"  << test_num <<  "failed" << endl;
        ++failed_tests;
    }
}

void Test2()
{
    WaitableQueue<int> wq;
    int data = 1;
    int data_out;
    wq.Enqueue(data);
    wq.Dequeue(&data_out);
    Test(1 == data_out, 1);
    data = 2;
    wq.Enqueue(data);
    wq.Dequeue(&data_out, boost::chrono::duration<size_t, boost::milli>());
    Test(2 == data_out, 2);

    WaitableQueue<int, PQWrapper<int> > wq2;
    data = 3;
    wq2.Enqueue(data);
    wq2.Dequeue(&data_out);
    Test(3 == data_out, 3);
    data = 4;
    wq2.Enqueue(data);
    wq2.Dequeue(&data_out, boost::chrono::duration<size_t, boost::milli>());
    Test(4 == data_out, 4);
}

// void task(int i)

// void Test3()
// {
//     WaitableQueue<int> wq;

//     std::thread t1(task, i);

// }

int main()
{
    Test2();

    return 0;
}
