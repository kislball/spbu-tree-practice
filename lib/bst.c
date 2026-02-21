#include "bst.h"
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BST {
	BST* left;
	BST* right;
	int value;
} BST;

BST* bstNew()
{
	BST* tree = calloc(1, sizeof(*tree));
	if (tree == NULL) {
		assert(false && "Failed to allocate memory for tree");
		return NULL;
	}
	return tree;
}

void bstFree(BST** tree)
{
	BST* t = *tree;
	if (t->left) bstFree(&t->left);
	if (t->right) bstFree(&t->right);
	free(t);
	*tree = NULL;
}
