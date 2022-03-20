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
#include <netdb.h>
#include <time.h>

#define MYPORT 4950 // the port users will be connecting to
#define MAXBUFLEN 100
#define MY_ADDR "127.0.0.1"

int main()
{
	int sockfd;
	struct sockaddr_in their_addr; // connector’s address information
	socklen_t addr_len = sizeof(struct sockaddr);
	int numbytes;
	char buf[MAXBUFLEN];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET; // host byte order
	their_addr.sin_port = htons(MYPORT); // short, network byte order
	their_addr.sin_addr.s_addr = inet_addr(MY_ADDR);
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct

	srand(time(0));
	int num_of_pings = ((rand() % 8) + 3);

	for(int i = 0; i < num_of_pings; ++i)
	{
		int sleeping = (rand() % 8 + 3);
		while(--sleeping > 0)
		{
			sleep(1);
		}
		if ((numbytes=sendto(sockfd, "ping", strlen("ping") + 1, 0,
			(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) 
		{
			perror("sendto");
			exit(1);
		}
		
		if ((numbytes=recvfrom(sockfd,buf, MAXBUFLEN-1, MSG_WAITALL, 
				(struct sockaddr *)&their_addr, &addr_len)) == -1)
		{
			perror("recvfrom");
			exit(1);
		}
		
		printf("%s\n",buf);
	}

	close(sockfd);

	return 0;
}