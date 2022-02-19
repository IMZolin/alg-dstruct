#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define NONE -1
#define BUF_SIZE 10
#pragma warning(disable: 4996)
typedef struct tree{
	int key;
	int priority;
	struct tree* left;
	struct tree* right;
}tree_t;

tree_t* InitTree(int k);
tree_t* Find(tree_t* p,int key);
tree_t* Insert(tree_t* p, int k);
void SplitTree(tree_t* tree, int key, tree_t** left, tree_t** right);
tree_t* MergeTrees(tree_t* left, tree_t* right);
tree_t* Delete(tree_t* p, int k);
void DestroyTree(tree_t* tree);
int Solution(FILE* f_in, FILE* f_out);