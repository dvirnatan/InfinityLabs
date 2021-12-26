#include <stdio.h>
#include <stddef.h>

#include "trie.h"
#include "dhcp.h"

int main()
{
    ip_t subnet = {192, 168, 3, 240};
    ip_t req1 = {192, 168, 3, 200};
    ip_t req2 = {192, 168, 3, 254};
    dhcp_t *dhcp = DHCPCreate(subnet, 28);
    alloc_status_t alloc1 = DHCPAllocateIp(dhcp, req1);
    alloc_status_t alloc2 = DHCPAllocateIp(dhcp, req2);
    size_t i = 0;
     DHCPPrintTree(dhcp);
    puts("\n*********************************************************");
    printf("alloc = %d\n", alloc1);
    for(i = 0; i < 4; ++i)
    {
        printf("%d\n",req1[i]);
    }
    printf("alloc = %d\n", alloc2);
    for(i = 0; i < 4; ++i)
    {
        printf("%d\n",req2[i]);
    }
    printf("count = %lu\n", DHCPCountFree(dhcp));
    printf("free = %d\n", DHCPFreeIp(dhcp, req1));
    printf("free = %d\n", DHCPFreeIp(dhcp, req1));
    printf("count = %lu\n", DHCPCountFree(dhcp));
    DHCPDestroy(dhcp);
    
    return 0;
}
