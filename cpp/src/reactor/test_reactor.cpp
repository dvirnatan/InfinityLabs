#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <cstddef>
#include <sys/stat.h>
#include <fcntl.h>


#include "reactor.hpp"

using ilrd::Reactor;
using std::cout;
using std::endl;


void WrapperStop(Reactor *r)
{
    cout << "call to stop\n";
    r->Stop();
}

void Print()
{
    cout << "Print\n";
}

int main()
{
    char buff[10];
    Reactor r;
    int fd;

    fd = open("testing.txt", O_CREAT, S_IRWXU);

    r.Add(fd, &Print);

    r.Add(0, std::bind(&WrapperStop, &r));

    r.Run();

    cout << "Doing Somthing\n";

    write(fd, &"this", 5);

    //read(fd,buff,5);

    close (fd);

    return 0;
}
