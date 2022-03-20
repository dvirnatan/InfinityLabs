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

#define MYPORT 4950 // the port users will be connecting to
#define MAXBUFLEN 100

int main()
{
	int sockfd;
	struct sockaddr_in their_addr; // connector’s address information
	//socklen_t addr_len = sizeof(struct sockaddr);
	int numbytes;
	char buf[MAXBUFLEN];

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

	their_addr.sin_family = AF_INET; // host byte order
	their_addr.sin_port = htons(MYPORT); // short, network byte order
	their_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct

	if (bind(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))== -1) 
	{
		perror("bind");
		exit(1);
	}

	if ((numbytes=recv(sockfd,buf, MAXBUFLEN-1, 0)) == -1)
	{
		perror("recvfrom");
		exit(1);
	}
	
	printf("packet contains \"%s\"\n",buf);
	
	close(sockfd);

	return 0;
}