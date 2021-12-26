#ifndef __DHCP_H__OL111
#define __DHCP_H__OL111

#include <stddef.h> /*size_t*/

typedef struct dhcp dhcp_t;
typedef unsigned char ip_t[4];
typedef enum {ALLOC_SUCCESS  = 0, NO_AVAILABLE_IP = 1, MEMORY_ALLOCATION_FAILED = 2} alloc_status_t;
typedef enum {FREE_SUCCESS  = 0, ALREADY_FREE = 1, INVALID_IP = 2} free_status_t;
 
/* prefix is numbers of bits that are not managed by the DHCP */
dhcp_t *DHCPCreate(const ip_t subnet, size_t prefix_bits);

void DHCPDestroy(dhcp_t *dhcp);

/* Returns status, if sucseed req will hold the allocated ip.
The allocated ip will be equal or closest to req*/
alloc_status_t DHCPAllocateIp(dhcp_t *dhcp, ip_t req);

free_status_t DHCPFreeIp(dhcp_t *dhcp, const ip_t ip);

size_t DHCPCountFree(const dhcp_t *dhcp);

void DHCPPrintTree(dhcp_t *dhcp);


#endif /*__DHCP_H__OL111*/