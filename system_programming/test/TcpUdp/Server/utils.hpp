#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define SERVER_PORT  12345
#define UDP_PORT  4950
#define TCP_PORT  3490
#define BROAD_PORT   5643

#define TRUE   1
#define FALSE  0


int CreateServer(in_port_t port, int type ,in_addr_t addres, struct sockaddr_in *addr);
int TCPAccept(int fd, fd_set *master_set, int *fd_max);
int UDPSendAndRecive(int fd, sockaddr_in *addr);
int TCPSendAndRecive(int fd);
int Stdin(char *buffer);


#endif //__UTILS_HPP__