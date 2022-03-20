#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static const std::string PathPong = "/tmp/FifoPong";
static const std::string PathPing = "/tmp/FifoPing";
static const std::string ping = "ping";
static const std::string pong = "pong";
static const int ping_length = 5;

void ipc_ping()
{
	static const int number_of_printing = 10; 
	if (-1 == mkfifo(PathPong.c_str(), 0666) ||
		-1 == mkfifo(PathPing.c_str(), 0666) ) //S_IRWXU
	{
		perror("mkfifo failed");
		system("rm /tmp/FifoPing");
		system("rm /tmp/FifoPong");

		return;
	}

	char buffer[ ping_length ];
	FILE *fd;

	int counter = 0;
	while (counter < number_of_printing)
	{
		++counter;
		
        fd = fopen(PathPing.c_str(), "r");
        fread(buffer, ping_length + 1, 1, fd);
        fclose(fd);
		
		printf("%s\n", buffer);
		sleep(1);

       	sprintf(buffer, "%s", ping.c_str());
        fd = fopen(PathPong.c_str(), "w");
        fwrite(buffer, ping_length + 1, 1, fd);
        fclose(fd);
	}
	system("rm /tmp/FifoPing");
	system("rm /tmp/FifoPong");
}

int main()
{
	ipc_ping();

	return 0;
}