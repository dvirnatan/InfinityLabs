#include <iostream>
#include "BitArray.hpp"

using ilrd::BitArray;
using std::cout;
using std::endl;


#define S_MSG(func) "SUCCESS: " #func " works as expected!"
#define F_MSG(func) "ERROR: " #func " failed"
static const char *_N_ = "\033[0m";
static const char *_BLD_ = "\033[1m";
static const char *_U_ = "\033[4m";
static const char *_R_ = "\033[31m";
static const char *_G_ = "\033[32m";
static const char *_Y_ = "\033[33m";
static const char *_P_ = "\033[35m";
static const char *_B_ = "\033[36m";

static const size_t N = 35;
#define FRACTION * 2 / 3

void testSetGet()
{
    BitArray<N> bitarr1;
    bool status = true;
    
    cout <<_B_<< "Set all to true" <<_N_<< endl;

    bitarr1.Set(true);
    for (size_t i = 0; i < N; ++i)
    {
        bool result = bitarr1.Get(i);
        if (!result)
        {
            cout <<_R_<< F_MSG(Set) << endl << F_MSG(Get) << endl <<
            "result was " <<_Y_<< result <<_R_<< " at " <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }
    
    cout <<_B_<< "Set all to false" <<_N_<< endl;

    bitarr1.Set(false);
    for (size_t i = 0; i < N; ++i)
    {
        bool result = bitarr1.Get(i);
        if (result)
        {
            cout <<_R_<< F_MSG(Set) << endl << F_MSG(Get) <<_N_<< endl <<
            "result was " <<_Y_<< result <<_R_<< " at " <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }

    cout <<_B_<< "set and reset individually" <<_N_<< endl;

    for (size_t i = 0; i < N; ++i)
    {
        bitarr1.Set(true, i);
        bool result = bitarr1.Get(i);
        if (!result)
        {
            cout <<_R_<< F_MSG(Set) << endl << F_MSG(Get) <<_N_<< endl <<
            "result was " <<_Y_<< result <<_R_<< " at " <<_Y_<< i <<_N_<< endl;
            status = false;
        }

        bitarr1.Set(false, i);
        result = bitarr1.Get(i);
        if (result)
        {
            cout <<_R_<< F_MSG(Set) << endl << F_MSG(Get) <<_N_<< endl <<
            "result was " <<_Y_<< result <<_R_<< " at " <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }
    
    if (status)
    {
        cout <<_G_<< S_MSG(Set) << endl << S_MSG(Get) <<_N_<< endl;
    }
}

void testFlip()
{
    BitArray<N> bitarr1;
    bool status = true;

    bitarr1.Set(false);

    cout <<_B_<< "flip all to true" <<_N_<< endl;

    bitarr1.Flip();
    for (size_t i = 0; i < N; ++i)
    {
        if (!bitarr1.Get(i))
        {
            cout <<_R_<< F_MSG(Flip) << " to " <<_Y_<< 1 <<_R_<< " at i = "
            <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }

    cout <<_B_<< "flip all to false" <<_N_<< endl;

    bitarr1.Flip();
    for (size_t i = 0; i < N; ++i)
    {
        if (bitarr1.Get(i))
        {
            cout <<_R_<< F_MSG(Flip) << " to " <<_Y_<< 0 <<_R_<< " at i = "
            <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }

    cout <<_B_<< "flip back and forth individually" <<_N_<< endl;

    for (size_t i = 0; i < N; ++i)
    {
        bitarr1.Flip(i);
        if (!bitarr1.Get(i))
        {
            cout <<_R_<< F_MSG(Flip) << " to " <<_Y_<< 1 <<_R_<< " at i = "
            <<_Y_<< i <<_N_<< endl;
            status = false;
        }

        bitarr1.Flip(i);
        if (bitarr1.Get(i))
        {
            cout <<_R_<< F_MSG(Flip) << " to " <<_Y_<< 0 <<_R_<< " at i = "
            <<_Y_<< i <<_N_<< endl;
            status = false;
        }
    }

    if (status)
    {
        cout <<_G_<< S_MSG(Flip) <<_N_<< endl;
    }
}

// void testCount()
// {
//     BitArray<N> bitarr1;
//     bool status = true;

//     for (size_t i = 0; i < N; ++i)
//     {
//         size_t count = bitarr1.Count();
//         if (count != i)
//         {
//             cout <<_R_<< F_MSG(count) << endl << " expected: " <<_Y_<< i <<_R_<<
//                     endl << "result: " <<_Y_<< count <<_N_<< endl;
//             status = false;
//         }
//         bitarr1.Flip(i);
//     }
//     for (size_t i = 0; i < N; ++i)
//     {
//         size_t count = bitarr1.Count();
//         if (count != N - i)
//         {
//             cout <<_R_<< F_MSG(count) << endl << " expected: " <<_Y_<< N - i
//                  <<_R_<< endl << "result: " <<_Y_<< count <<_N_<< endl;
//             status = false;
//         }
//         bitarr1.Flip(i);
//     }
//     if (status)
//     {
//         cout <<_G_<< S_MSG(Count) <<_N_<< endl;
//     }
// }

void testStr()
{
    BitArray<N> bitarr1;

    bitarr1.Set(true);
    cout <<_B_<< "print all ones" <<_N_<< endl
         <<_P_<< bitarr1.ToString() <<_N_<< endl;

    bitarr1.Set(false);
    cout <<_B_<< "print all zeros" <<_N_<< endl
         <<_P_<< bitarr1.ToString() <<_N_<< endl;

    bitarr1.Set(true, 0);
    bitarr1.Set(true, N FRACTION);
    cout <<_B_<< "print all zeros except indices 0 and N * 2 / 3" <<_N_<< endl
         <<_P_<< bitarr1.ToString() <<_N_<< endl;
}

void bitarrTest()
{
    BitArray<N> bitarr1;
    cout <<_G_<< S_MSG(Ctor) <<_N_<< endl;
    // BitArray<N FRACTION> bitarr2(bitarr1);  // should not compile

    testSetGet();
    
    testFlip();

    // bitarr1.Set(true, N);  // should throw
    // bitarr1.Get(N);        // should throw
    // bitarr1.Flip(N);       // should throw

    // testCount();

    testStr();
}

int main()
{
    // cout <<_B_<<_BLD_<< "\t\t~" <<_U_<< "SJ SharedPtr Test" <<_N_<<_B_<<_BLD_
    //      << "~" <<_N_<< endl;

    // bitarrTest();

    // cout <<_B_<< "Please check " <<_P_<<_BLD_<< "Valgrind " <<_N_<<_B_<<
    //     "to ensure memory integrity.\n\t\t~Have a lovely day!~" <<_N_<< endl;


    BitArray<8> b1, b2, b3;
    b2.Set(true, 5);
    b2.Set(true, 3);
    std::cout << "b2 after set: " << b2.ToString() << std::endl;
    b3.Set(true, 1);
    b3.Set(true, 5);
    b3.Set(true, 6);
    std::cout << "b3 after set: " << b3.ToString() << std::endl;

    std::cout << "b2 | b3 " << (b2 | b3).ToString() << std::endl;
    std::cout << "b2 & b3 " << (b2 & b3).ToString() << std::endl;
    std::cout << "b2 ^ b3 " << (b2 ^ b3).ToString() << std::endl;

    return 0;
    (void)_Y_;
    (void)_R_;
    (void)_G_;
}

