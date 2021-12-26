#ifndef __TRIE_H__
#define __TRIE_H__

enum {LEFT = 0, RIGHT = 1, CHILDRENS = 2};

typedef struct node node_t;
typedef struct trie trie_t;

node_t *CreateTrie();
int TrieInsert(node_t *node, size_t prefix_bits, unsigned int *ip);
int TrieRemove(node_t *node, unsigned int *ip, size_t prefix_bits);
size_t CountNodes(node_t *node, size_t dept);
void DestroyTrie(node_t *node);
void print2DTree(node_t *root);

#endif /* __TRIE_H__ */