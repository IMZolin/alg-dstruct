#include "tree.h"

int main(void)
{
	tree_t* tree = ExampleBinTree();
	PrintTree(tree,0);
	printf("\n\n");
	MinLeafHeight(tree);
	PrintTree(tree, 0);
	return 0;
}