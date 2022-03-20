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
#define NUM_OF_PINGS 10

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr; // my address information
	struct sockaddr_in their_addr; // connector’s address information
	socklen_t addr_len = sizeof(struct sockaddr);
	int numbytes;
	char buf[MAXBUFLEN];
	char *pong = "pong";

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons(MYPORT); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	bzero(&(my_addr.sin_zero), 8); // zero the rest of the struct
	
	if (bind(sockfd, (struct sockaddr *)&my_addr, addr_len) == -1)
	{
		perror("bind");
		exit(1);
	}

	for(int i = 0; i < NUM_OF_PINGS; ++i)
	{
		if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN-1, MSG_WAITALL, 
	       (struct sockaddr *)&their_addr, &addr_len)) == -1)
		{
			perror("recvfrom");
			exit(1);
		}

		buf[numbytes] = '\0';
		printf("packet contains \"%s\"\n",buf);

		if( (numbytes=sendto(sockfd, pong, strlen(pong) , 0, 
		    (struct sockaddr *)&their_addr, addr_len)  == -1 ) )
		{
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}

	if( (numbytes=sendto(sockfd, "quit", strlen("quit") , 0, 
		    (struct sockaddr *)&their_addr, addr_len)  == -1 ) )
		{
			perror("sendto");
			exit(1);
		}

	close(sockfd);

	return 0;
}