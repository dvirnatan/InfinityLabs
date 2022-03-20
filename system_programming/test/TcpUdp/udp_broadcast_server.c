#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4950 // the port users will be connecting to
#define MAXBUFLEN 100
#define NUM_OF_PINGS 5

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr; // my address information
	socklen_t addr_len = sizeof(struct sockaddr);
	int numbytes;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	int yes = 1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int)) == -1) 
	{
		perror("setsockopt");
		exit(1);
	}

	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons(MYPORT); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_BROADCAST; 
	bzero(&(my_addr.sin_zero), 8); // zero the rest of the struct

	for(int i = 0; i < NUM_OF_PINGS; ++i)
	{
		if ((numbytes=sendto(sockfd, "ping", 5, 0, 
	       (struct sockaddr *)&my_addr, addr_len)) == -1)
		{
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}

	close(sockfd);

	return 0;
}