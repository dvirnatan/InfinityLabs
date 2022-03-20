
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

#define MYPORT 3490// the port users will be connecting to
#define BACKLOG 10// how many pending connections queue will hold

int main(void)
{
	int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
	struct sockaddr_in my_addr;// my address information
	struct sockaddr_in their_addr; // connector’s address information
	socklen_t sin_size;
	int yes=1;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) 
	{
		perror("setsockopt");
		exit(1);
	}

	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons(MYPORT); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	bzero(&(my_addr.sin_zero), 8);

	// zero the rest of the struct
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) 
	{
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) 
	{
		perror("listen");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) 
	{
		perror("accept");
		exit(1);
	}

	char buf[BUFSIZ];
	while(strcmp(buf, "quit") != 0)
	{
		sleep(1);
		int numofbytes;
		if( (numofbytes = recv(new_fd, buf, 5, MSG_WAITALL) == -1) )
		{
			perror("recive");
			exit(1);
		}

		buf[numofbytes - 1] = '\0';
		printf("%s\n", buf);

		if (send(new_fd, "pong", 4, 0) == -1)
		{
			perror("send");
		}

	}
	close(new_fd);
	close(sockfd); 
	return 0;
}