#ifndef BTREE_H_
#define BTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_KEYS 1024

typedef struct b_tree_node {
    struct b_tree_node** children;
    int numKeys;
    int* keys;
    int isLeaf;
}b_tree_node;

b_tree_node* CreateNode(void);
void DestroyTree(b_tree_node* tree);

#endif BTREE_H_