#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

static const std::string PathPong = "/tmp/FifoPong";
static const std::string PathPing = "/tmp/FifoPing";
static const std::string ping = "ping";
static const std::string pong = "pong";
static const int pong_length = 5;

void ipc_pong()
{
	char buffer[ pong_length ];
	FILE *fd;
	while (1)
	{
		sprintf(buffer, "%s", pong.c_str());
		fd = fopen(PathPing.c_str(), "w");
		fwrite(buffer, pong_length + 1, 1, fd);
		fclose(fd);
		
		fd = fopen(PathPong.c_str(), "r");
		fread(buffer, pong_length + 1, 1, fd);
		fclose(fd);
	
		printf("%s\n", buffer);
		sleep(1);
	}
}

int main()
{
	
	ipc_pong();

	return 0;
}