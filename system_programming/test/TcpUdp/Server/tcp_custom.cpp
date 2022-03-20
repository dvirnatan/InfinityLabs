#define _POSIX_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include <strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include <netdb.h>
#include <time.h>

#define PORT 3490 // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
#define MY_ADDR "127.0.0.1"

int main()
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct sockaddr_in their_addr; // connector’s address information

	// if ((he=gethostbyname(MYNAME)) == -1) // get the host info
	// {
	// 	perror("gethostbyname");
	// 	exit(1);
	// }
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;// host byte order
	their_addr.sin_port = htons(PORT); // short, network byte order
	their_addr.sin_addr.s_addr = inet_addr(MY_ADDR);
	bzero(&(their_addr.sin_zero), 8);

	// zero the rest of the struct
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("connect");
		exit(1);
	}

	srand(time(0));
	int num_of_pings = (rand() % 8) + 3;

	for(int i = 0; i < num_of_pings; ++i)
	{
		int sleeping = (rand() % 8) + 3;
		while(--sleeping > 0)
		{
			sleep(1);
		}
		if( (numbytes=send(sockfd, "ping", 5, 0)) == -1 )
		{
			perror("send");
			close(sockfd);
			exit(1);
		}

		if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) 
		{
			perror("recv");
			close(sockfd);
			exit(1);
		}

		buf[numbytes] = '\0';
		printf("%s\n",buf);
	}

	if ((numbytes=send(sockfd, "quit", 5, 0)) == -1)
	{
		perror("send");
		close(sockfd);
		exit(1);
	}

	close(sockfd);

	return 0;
}