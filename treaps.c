#include "treaps.h"

tree_t* InitTree(int k)
{
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if (tree == NULL)
	{
		printf("Allocation memory error\n");
		return NULL;
	}
	tree->left = NULL;
	tree->right = NULL;
	tree->key = k;
	tree->priority = 1;
	return tree;
}
void DestroyTree(tree_t* tree)
{
	if (tree != NULL)
	{
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}

tree_t* Find(tree_t* p, int k)
{
	if (!p) return 0; 
	if (k == p->key)
		return p;
	if (k < p->key)
		return Find(p->left, k);
	else
		return Find(p->right, k);
}

tree_t* MergeTrees(tree_t* left, tree_t* right)
{
	if (!left) return right;
	if (!right) return left;
	if (right->priority < left->priority)
	{
		left->right = MergeTrees(left->right, right);
		return left;
	}
	else
	{
		right->left = MergeTrees(left, right->left);
		return right;
	}
}
void SplitTree(tree_t* tree, int key, tree_t** left, tree_t** right)
{
	if (!tree) {
		*left = NULL;
		*right = NULL;
		return;
	}
	tree_t* tmp = NULL;
	if (tree->key <= key) {
		SplitTree(tree->right, key, &tmp, right);
		tree->right = tmp;
		*left = tree;
	}
	else {
		SplitTree(tree->left, key, left, &tmp);
		tree->left = tmp;
		*right = tmp;
	}
}

tree_t* Insert(tree_t* tree, int k)
{
	tree_t* left = NULL, * right = NULL;
	if (tree) {
		SplitTree(tree, k, &left, &right);
	}
	tree_t* node = malloc(sizeof(tree_t));
	if (node) {
		node->key = k;
		//srand(time(NULL));
		node->priority = rand();
		node->left = NULL;
		node->right = NULL;
	};
	return MergeTrees(MergeTrees(left, node), right);
}


tree_t* Delete(tree_t* tree, int k) {
	tree_t* left, * main, * right;
	SplitTree(tree, k - 1, &left, &right);
	SplitTree(right, k, &main, &tree);
	DestroyTree(main);
	return MergeTrees(left, tree);
}

int Solution(FILE*f_in, FILE*f_out)
{
	char buf[BUF_SIZE] = { 0 };
	tree_t* treap = NULL;
	char x;
	int value;
	while (fgets(buf, BUF_SIZE, f_in))
	{
		sscanf(buf, "%c %i", &x, &value);
		switch (x) {
		case 'a':
			treap = Insert(treap, value);
			break;
		case 'r':
			treap = Delete(treap, value);
			break;
		case 'f':
			if (Find(treap, value))
				fprintf(f_out, "yes\n");
			else
				fprintf(f_out, "no\n");
			break;
		default:
			DestroyTree(treap);
			break;
		}
	}
	DestroyTree(treap);
	return 0;

}

