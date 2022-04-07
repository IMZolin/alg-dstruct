#ifndef BTREE_H
# define BTREE_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define BUF_SIZE 16 //Num of functions with B-tree
#define ERROR -1 //Invalid index
#define BTREE_PARAM 3 //T

//#############################################################################
//                               STRUCTS
//#############################################################################
typedef struct BTreeNode {
    int numKeys; // n of keys the node has
    bool isLeaf; // is this a leaf node? 1 = true, 0 = false
    int* keys; // holds the keys of the node
    struct BTreeNode** children; // holds the children of the node
} BTreeNode;

typedef struct {
    int T; // order(param) of the B-Tree // BTree 
    BTreeNode* root; // root of the B-Tree
} BTree;

//#############################################################################
//                               METHODS
//#############################################################################

// Create a new empty tree
bool btCreate(BTree* tree);
// Return -1 if key is present in tree
bool btSearch(const BTree* tree, const int key);
// Insert a new element into a tree
bool btInsert(BTree* tree, const int key);
// Deletes a key from the tree
void btDelete(BTree* tree, const int key);
// Free the tree
void btDestroy(BTree* tree);

//#############################################################################
//                               HELPER METHODS(WITH THE NODES)
//#############################################################################
static BTreeNode* _nodeAllocate(const int T);
static void _nodeDestroy(BTreeNode* node);
static int _findKeyInArr(const int* arr, const int size, const int key);
static bool _insertNonfull(BTreeNode* node, const int key, const int t);
static bool _splitChild(BTreeNode* node, const int T, const int i);
static BTreeNode* _findNodeContainsKey(const BTree* tree, const int key, int* index);
//Get the neighbor the node lies behind of given node
static int _getPredecessor(BTreeNode* node, const int idx);
//Get the neighbor the node lies ahead of given node
static int _getSuccessor(BTreeNode* node, const int idx);
static void _removeFromArrI(int* arr, const int size, const int idx);
static void _removeFromArrNP(BTreeNode** arr, const int size, const int idx);
static void _leftRotate(BTreeNode* node, const int keyIdx);
static void _rightRotate(BTreeNode* node, const int keyIdx);
static void _mergeChild(BTreeNode* node, const int keyIdx);
static void _removeFromLeaf(BTreeNode* node, const int T, const int key);
static void _remove(BTreeNode* node, BTreeNode* nodeContainsKey, const int idx, const int T, const int key);
static void _destroy(BTreeNode* node, const int T);
#endif