#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable: 4996)
#define TRUE 1
#define FALSE 0
#define NONE -1
typedef struct tree_t 
{
	int key;
	struct tree_t* left;
	struct tree_t* right;

}tree_t;

tree_t* InitBinTree();
void PrintTree(tree_t* tree, int level);
void DestroyTree(tree_t* tree);
void PrintTree(tree_t* tree, int level);
void SubTree(tree_t* parent, int isLeftTrue, int isRightTrue);
tree_t* ExampleBinTree(void);
void MinLeafHeight(tree_t* tree);