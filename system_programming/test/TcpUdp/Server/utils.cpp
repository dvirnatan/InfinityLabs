#include <stdio.h> /* printf */
#include <stdlib.h>  /* exit */
#include <sys/ioctl.h> /* ioct */
#include <netinet/in.h> /* htons, INDARR_ANY */
#include <errno.h> /* errno */
#include <cstring> /* strcmp */
#include <unistd.h> /* STDIN_FILENO */

#include "utils.hpp"

#define BUF 80

char ping[] = "ping";
char pong[] = "pong";

/* Create and Bind a reusable non blocking socket */
int CreateServer(in_port_t port, int type, in_addr_t addres, struct sockaddr_in *addr)
{
	int fd = socket(AF_INET, type, 0);
	if (fd < 0)
	{
		perror("socket() failed");
		return errno;
	}

	int on=1;
	int rc = setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(fd);
		exit(-1);
	}

	rc = ioctl(fd, FIONBIO, (char *)&on);
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(fd);
		exit(-1);
	}

	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = addres;
	addr->sin_port = htons(port);
	rc = bind(fd ,(struct sockaddr *)addr, sizeof(*addr));
	if (rc < 0)
	{
		perror("bind() failed");
		close(fd);
		exit(-1);
	}
	return fd;
}

int TCPAccept(int fd, fd_set *master_set, int *fd_max)
{
	printf("Listening socket number: %d is readable\n", fd);
	int fd_new = 0;
	do
	{
		fd_new = accept(fd, NULL, NULL);
		if (fd_new < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("accept() failed");
				return -1;
			}
		}

		printf("New incoming connection - %d\n", fd_new);
		FD_SET(fd_new, master_set);
		if (fd_new > *fd_max)
			{
				*fd_max = fd_new;
			}
	} while (fd_new != -1);

	return 0;
}

int UDPSendAndRecive(int fd, sockaddr_in *addr)
{
	int rc;
	char buffer[BUF];
	socklen_t addr_len = sizeof(*addr);
	rc = recvfrom(fd, buffer, 5, 0, 
					(struct sockaddr *)addr, &addr_len);

	if(rc < 0)
	{
		if(errno != EWOULDBLOCK)
		{
			perror("recvfrom() failed");
			return 1;
		}
	}

	if(rc == 0)
	{
		perror("Connection closed");
		return 1;
	}

	buffer[rc] = '\0';
	printf("%d bytes received from %d.\n%s\n", rc, fd, buffer);

	rc = sendto(fd, pong, 5, 0, (struct sockaddr *)addr, addr_len);
	if(rc < 0)
	{
		perror("sendto() failed");
		return 1;
	}

	return 0;
}

int TCPSendAndRecive(int fd)
{
	int rc;
	char buffer[BUF];

	rc = recv(fd, buffer, 5, 0);
	if(rc < 0)
	{
		if(errno != EWOULDBLOCK)
		{
			perror("recv() failed");
			return 1;
		}
	}

	if(rc == 0)
	{
		perror("Connection closed");
		return 1;
	}

	buffer[rc] = '\0';
	printf("%d bytes received from %d.\n%s\n", rc, fd, buffer);

	rc = send(fd, pong, 5, 0);
	if(rc < 0)
	{
		perror("send() failed");
		return 1;
	}

	return 0;
}

int Stdin(char *buffer)
{
	int rc = read(0, buffer, 10);
	
	if(rc < 0)
	{
		perror("read() failed from stdin");
		return 1;
	}

	buffer[rc] = '\0';

	if(strncmp(buffer, "quit", 4) == 0)
	{
		return 1;
	}
	else if(strncmp(buffer, "ping", 4) == 0)
	{
		printf("pong\n");
		return 0;
	}
	else
	{
		printf("%s", buffer);
		return 0;
	}
	return 0;
}