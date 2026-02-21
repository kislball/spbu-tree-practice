#include "bst.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BST {
    BST* left;
    BST* right;
    bool hasValue;
    int value;
} BST;

BST* bstNew(int val)
{
    BST* tree = calloc(1, sizeof(*tree));
    if (tree == NULL) {
        assert(false && "Failed to allocate memory for tree");
        return NULL;
    }
    tree->value = val;
    return tree;
}

void bstFree(BST** tree)
{
    BST* t = *tree;
    if (t->left)
        bstFree(&t->left);
    if (t->right)
        bstFree(&t->right);
    free(t);
    *tree = NULL;
}

int* bstGetValue(BST* node)
{
    return node->hasValue ? &node->value : NULL;
}

bool bstInsert(BST* node, int val)
{
    if (node == NULL)
        return false;
    if (node->value == val)
        return true;
    if (node->value < val) {
        if (node->left == NULL) {
            node->left = bstNew(val);
            if (node->left == NULL)
                return false;
            return true;
        }
        return bstInsert(node->left, val);
    } else {
        if (node->right == NULL) {
            node->right = bstNew(val);
            if (node->right == NULL)
                return false;
            return true;
        }
        return bstInsert(node->right, val);
    }
}
bool bstContains(BST* node, int val)
{
    if (node == NULL)
        return false;
    if (node->value == val)
        return true;

    return bstContains(node->left, val) || bstContains(node->right, val);
}

void bstPreorder(BST* tree)
{
	if (tree == NULL) return;
	printf("%d\n", tree->value);
	bstPreorder(tree->left);
	bstPreorder(tree->right);
}

void bstInorder(BST* tree)
{
	if (tree == NULL) return;
	bstInorder(tree->left);
	printf("%d\n", tree->value);
	bstInorder(tree->right);
}

void bstPostorder(BST* tree)
{
	if (tree == NULL) return;
	bstPostorder(tree->left);
	bstPostorder(tree->right);
	printf("%d\n", tree->value);
    return node->hasValue ? &node->value : NULL;
}

bool bstInsert(BST* node, int val)
{
    if (node == NULL)
        return false;
    if (node->value == val)
        return true;
    if (node->value < val) {
        if (node->left == NULL) {
            node->left = bstNew(val);
            if (node->left == NULL)
                return false;
            return true;
        }
        return bstInsert(node->left, val);
    } else {
        if (node->right == NULL) {
            node->right = bstNew(val);
            if (node->right == NULL)
                return false;
            return true;
        }
        return bstInsert(node->right, val);
    }
}
bool bstContains(BST* node, int val)
{
    if (node == NULL)
        return false;
    if (node->value == val)
        return true;

    return bstContains(node->left, val) || bstContains(node->right, val);
}
