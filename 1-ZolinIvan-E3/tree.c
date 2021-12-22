#include "tree.h"

tree_t* InitBinTree()
{
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if (tree == NULL)
	{
		printf("Allocation memory error\n");
		return NULL;
	}
	tree->left = NULL;
	tree->right = NULL;
	tree->key = NONE;
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

void PrintTree(tree_t* tree, int level)
{
	if (tree != NULL)
	{
		PrintTree(tree->left, level+1);
		for (int i = 0; i < level; i++)
			printf("    ");
		if (tree->key == NONE)
			printf("*\n");
		else
			printf("%d\n", tree->key);
		PrintTree(tree->right, level+1);

	}
}

void SubTree(tree_t* parent, int isLeftTrue, int isRightTrue)
{
	if (parent == NULL)
	{
		printf("NULL pointer");
		return;
	}
	if (isLeftTrue == TRUE)
	{
		parent->left = InitBinTree();
	}
	if (isRightTrue == TRUE)
	{
		parent->right = InitBinTree();
	}
}

tree_t* ExampleBinTree(void)
{
	tree_t* root = InitBinTree();
	tree_t* cur;

	cur = root;
	SubTree(cur, TRUE, TRUE);

	cur = root->left;
	SubTree(cur, TRUE, TRUE);
	cur = root->right;
	SubTree(cur, FALSE, FALSE);

	cur = root->left->left;
	SubTree(cur, TRUE, FALSE);
	cur = root->left->right;
	SubTree(cur, FALSE, TRUE);

	cur = root->left->left->left;
	SubTree(cur, TRUE, TRUE);
	cur = root->right;
	SubTree(cur, TRUE, TRUE);
	return root;
}

void MinLeafHeight(tree_t* tree)
{
	if ((tree->left != NULL) && (tree->right != NULL))
	{
		MinLeafHeight(tree->left);
		MinLeafHeight(tree->right);
		if (tree->left->key > NONE)
		{
			tree->key = tree->left->key + 1;
		}
		if (tree->right->key > NONE)
		{
			tree->key = min(tree->key, tree->right->key + 1);
		}
	}
	else
	{
		if (tree->left != NULL)
		{
			MinLeafHeight(tree->left);
			if (tree->left->key > NONE)
			{
				tree->key = tree->left->key + 1;
				return;
			}
			return;
		}
		if (tree->right != NULL)
		{
			MinLeafHeight(tree->right);
			if (tree->right->key > NONE)
			{
				tree->key = tree->right->key + 1;
				return;
			}
			
		}
		else
		{
			tree->key = 0;
		}
	}
}