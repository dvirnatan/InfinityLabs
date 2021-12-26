#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "dhcp.h"
#include "trie.h"

#define OFFSET  (32 - dhcp->prefix_bits)
struct dhcp
{
    unsigned int subnet;
    node_t *root;
    size_t prefix_bits;
};

static unsigned int CharToInt(const ip_t ip)
{
    unsigned int res = 0;
    res |= (ip[0] << 24);
    res |= (ip[1] << 16);
    res |= (ip[2] << 8);
    res |= ip[3];
    return res;
}

static void IntToChar(unsigned int num, ip_t buffer)
{
    buffer[0] = num >> 24;
    buffer[1] = ((num << 8) >> 24);
    buffer[2] = (num << 16) >> 24;
    buffer[3] = (num << 24) >> 24;
}

dhcp_t *DHCPCreate(const ip_t subnet, size_t prefix_bits)
{
    dhcp_t *dhcp;
    unsigned int mask = ~0;
    unsigned int int_to_allocate = 0;
    ip_t ip_to_allocate;

    mask <<= prefix_bits;
    mask >>= prefix_bits;

    dhcp = malloc(sizeof(dhcp_t));
    if(!dhcp)
    {
        return NULL;
    }
    dhcp->subnet = CharToInt(subnet);
    dhcp->prefix_bits = prefix_bits;
    dhcp->root = CreateTrie();

    if(!dhcp->root)
    {
        free(dhcp);
        return NULL;
    }

    DHCPAllocateIp(dhcp, (unsigned char*)subnet);
    int_to_allocate = (dhcp->subnet | mask);
    IntToChar(int_to_allocate, ip_to_allocate);
    DHCPAllocateIp(dhcp, ip_to_allocate);
    int_to_allocate ^= 1;
    IntToChar(int_to_allocate, ip_to_allocate);
    DHCPAllocateIp(dhcp, ip_to_allocate);

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    DestroyTrie(dhcp->root);
    free(dhcp);
}


alloc_status_t DHCPAllocateIp(dhcp_t *dhcp, ip_t req)
{
    unsigned int int_req = CharToInt(req);
    unsigned int int_subnet = dhcp->subnet;
    int status = 0;

    assert(dhcp);

    if((int_req >> OFFSET) == (int_subnet >> OFFSET))
    {
        status =  TrieInsert(dhcp->root, dhcp->prefix_bits, &int_req);    
        IntToChar(int_req, req);
        return status;
    }
    else
    {
        int_subnet = dhcp->subnet;
        status =  TrieInsert(dhcp->root, dhcp->prefix_bits, &int_subnet);    
        IntToChar(int_subnet, req);
        return status;
    }
}

free_status_t DHCPFreeIp(dhcp_t *dhcp, const ip_t ip)
{
    unsigned int int_ip = CharToInt(ip);

    assert(dhcp);

    return TrieRemove(dhcp->root, &int_ip, dhcp->prefix_bits);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    size_t count = 0;

    assert(dhcp);

    count = CountNodes(dhcp->root, OFFSET - 1);

    return (1 << OFFSET) - count;
}

void DHCPPrintTree(dhcp_t *dhcp)
{
    print2DTree(dhcp->root);
}

/*__________________________EOF_________________________*/