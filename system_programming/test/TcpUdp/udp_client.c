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

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in their_addr; // connector’s address information
	struct hostent *he;
	socklen_t addr_len = sizeof(struct sockaddr);
	int numbytes;
	char buf[MAXBUFLEN];

	if (argc != 2) 
	{
		fprintf(stderr,"usage: talker hostname message\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL) // get the host info
	{ 
		perror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET; // host byte order
	their_addr.sin_port = htons(MYPORT); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)(he->h_addr_list[0]));
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct

	while(strcmp(buf, "quit") != 0)
	{
		sleep(1);
		
		if ((numbytes=sendto(sockfd, "ping", strlen("ping"), 0,
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
		
		printf("packet contains \"%s\"\n",buf);
	}

	close(sockfd);

	return 0;
}