/* gd trie.c -I ../include -o trie.out */
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "dhcp.h"

#define ADDRSPACE 32
#define OFFSET (ADDRSPACE - 1 - prefix_bits)

struct node
{
    node_t *child[CHILDRENS];
    int is_full;
};

#define PRINT_COUNT 10
static void print2D(node_t *root, int space)
{
    int i;
    if (root == NULL)
        return;
        
    space += PRINT_COUNT;
    print2D(root->child[RIGHT], space);

    printf("\n");
    for (i = PRINT_COUNT; i < space; ++i)
        printf(" ");
    printf("full=%d\n", root->is_full);

    print2D(root->child[LEFT], space);
}

void print2DTree(node_t *root)
{
    print2D(root, 0);
}

int TrieRemove(node_t *node, unsigned int *ip, size_t prefix_bits)
{
    int status = 0;
    unsigned int mask = 1 << OFFSET;
    int side = *ip & mask;

    if(prefix_bits == ADDRSPACE - 1)
    {
        if(node->is_full == 0)
        {
            return ALREADY_FREE;
        }
        else
        {
            node->is_full = 0;
            return FREE_SUCCESS;
        }
    }

    if(node->child[(side != 0)] == NULL)
    {
        return INVALID_IP;
    }

    status = TrieRemove(node->child[(side != 0)], ip, prefix_bits + 1);

    if(status < 2)
    {
        node->is_full = 0;
    }

    return status;
}

int TrieInsert(node_t *node, size_t prefix_bits, unsigned int *ip)
{
    unsigned int status = 0;
    unsigned int side = 0;

    size_t mask = 1 << (OFFSET);

    if(node->is_full == 1)
    {
        return NO_AVAILABLE_IP;
    }

    if(prefix_bits == ADDRSPACE - 1)
    {
        node->is_full = 1;
        return ALLOC_SUCCESS;
    }
    side = ((*ip & (mask >> 1)) != 0); 
    if(node->child[side] == NULL)
    {
        node->child[side] = calloc(1, sizeof(node_t));
        if(node->child[side] == NULL)
        {
            return MEMORY_ALLOCATION_FAILED;
        }
    }

    status = TrieInsert(node->child[side], prefix_bits + 1, ip);
  
    if(status == 1)
    {   
        *ip ^= (mask >> 1);
        return TrieInsert(node, prefix_bits, ip);
    }
  
    node->is_full = !status && node->child[RIGHT] && node->child[RIGHT]->is_full
                                && node->child[LEFT]&& node->child[LEFT]->is_full;
        
    return status;
}

node_t *CreateTrie()
{
    node_t *root = NULL;
    root = calloc(1, sizeof(node_t));
    if(!root)
    {
        return NULL;
    }
    root->is_full = 0;
    
    return root;
}

void DestroyTrie(node_t *node)
{
    if(node == NULL)
    {
        return;
    }
    DestroyTrie(node->child[LEFT]);
    DestroyTrie(node->child[RIGHT]);

    free(node);
}

size_t CountNodes(node_t *node, size_t dept)
{
    if(node == NULL)
    {
        return 0;
    }

    if(dept == 0 && node->is_full == 1)
    {
        return 1;
    }

    return  CountNodes(node->child[LEFT], dept - 1) + CountNodes(node->child[RIGHT], dept - 1);
}

/*__________________________EOF_________________________*/