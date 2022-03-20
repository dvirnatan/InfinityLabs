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
#include <time.h>

#define MYPORT 5643 // the port users will be connecting to
#define MAXBUFLEN 100
#define NUM_OF_PINGS 5

int main(void)
{
	char buffer[80] = {0};
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

	srand(time(0));
	int num_of_pings = ((rand() % 8) + 3);

	for(int i = 0; i < num_of_pings; ++i)
	{
		int sleeping = (rand() % 8 + 3);
		while(--sleeping > 0)
		{
			sleep(1);
		}

		if ((numbytes=sendto(sockfd, "ping", 5, 0, 
	       (struct sockaddr *)&my_addr, addr_len)) == -1)
		{
			perror("sendto");
			exit(1);
		}


		// if ((numbytes=recvfrom(sockfd,buffer , MAXBUFLEN-1, 0, 
		// 		(struct sockaddr *)&my_addr, &addr_len)) == -1)
		// {
		// 	perror("recvfrom");
		// 	exit(1);
		// }
		
		// printf("%s\n",buffer);

	}

	close(sockfd);

	return 0;
}