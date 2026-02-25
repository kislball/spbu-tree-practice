#include "bst.h"
#include "die.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstInternal.h"

#include "iterator.h"
BST* bstNew(int val)
{
    BST* tree = calloc(1, sizeof(*tree));
    if (tree == NULL) {
        assert(false && "Failed to allocate memory for tree");
        return NULL;
    }
    tree->value = val;
    tree->data.isRoot = true;
    tree->data.childrenCount = 0;
    return tree;
}

BST* bstNewChild(BST* root, int val)
{
    BST* tree = calloc(1, sizeof(*tree));
    if (tree == NULL) {
        assert(false && "Failed to allocate memory for tree");
        return NULL;
    }
    tree->value = val;
    tree->data.isRoot = false;
    tree->data.childrenCount = 0;
    tree->modVersion.pBase = &root->modVersion.base;
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

void bstPreorder(BST* tree)
{
    if (tree == NULL)
        return;
    printf("%d\n", tree->value);
    bstPreorder(tree->left);
    bstPreorder(tree->right);
}

void bstInorder(BST* tree)
{
    if (tree == NULL)
        return;
    bstInorder(tree->left);
    printf("%d\n", tree->value);
    bstInorder(tree->right);
}

void bstPostorder(BST* tree)
{
    if (tree == NULL)
        return;
    bstPostorder(tree->left);
    bstPostorder(tree->right);
    printf("%d\n", tree->value);
}

// Возвращает true, если дерево было изменено,
// при наличии ошибки записывает *err = true.
static bool bstInsertInternal(BST* root, BST* node, int val, bool* err)
{
    if (node == NULL) {
        *err = true;
        return false;
    }
    if (node->value == val) {
        *err = false;
        return false;
    }

    bool res = false;
    if (node->value > val) {
        if (node->left == NULL) {
            node->left = bstNewChild(root, val);
            res = node->left != NULL;
            *err = !res;
        } else {
            res = bstInsertInternal(root, node->left, val, err);
        }
    } else {
        if (node->right == NULL) {
            node->right = bstNewChild(root, val);
            res = node->right != NULL;
            *err = !res;
        } else {
            res = bstInsertInternal(root, node->right, val, err);
        }
    }
    if (res)
        node->data.childrenCount++;
    return res;
}

bool bstInsert(BST* root, int value)
{
    bool err = false;
    bool res = bstInsertInternal(root, root, value, &err);
    if (res)
        root->modVersion.base++;
    return !err;
}

bool bstContains(BST* node, int val)
{
    if (node == NULL)
        return false;
    if (node->value == val)
        return true;

    return bstContains(node->left, val) || bstContains(node->right, val);
}

int bstSize(BST* bst)
{
    if (bst == NULL)
        return 0;
    return 1 + bst->data.childrenCount;
}

int bstHeight(BST* bst)
{
    if (bst == NULL)
        return 0;

    int left = bstHeight(bst->left);
    int right = bstHeight(bst->right);

    return 1 + (left > right ? left : right);
}

int bstMin(BST* bst)
{
    dieIf(bst == NULL, "An empty tree has no minimum");
    int min = bst->value;
    BST* child = bst->left;

    while (child) {
        min = child->value;
        child = child->left;
    }

    return min;
}

int bstMax(BST* bst)
{
    dieIf(bst == NULL, "An empty tree has no maximum");
    int max = bst->value;
    BST* child = bst->right;

    while (child) {
        max = child->value;
        child = child->right;
    }

    return max;
}

bool bstIsValid(BST* tree)
{
    bool res = true;
    if (tree == NULL)
        return true; // Lets consider an empty tree a valid one
    Iterator* it = iteratorInit(tree);
    int prev = iteratorNext(it);

    while (iteratorHasNext(it)) {
        int val = iteratorNext(it);
        if (val <= prev) {
            res = false;
            break;
        }
        prev = val;
    }

    iteratorFree(&it);
    return res;
}

BST* bstMerge(BST* a, BST* b)
{
    Iterator* itA = iteratorInit(a);
    Iterator* itB = iteratorInit(b);

    int firstElement = 0;
    if (iteratorHasNext(itA))
        firstElement = iteratorNext(itA);
    else if (iteratorHasNext(itB))
        firstElement = iteratorNext(itB);
    else {
        iteratorFree(&itA);
        iteratorFree(&itB);
        return NULL;
    }

    BST* tree = bstNew(firstElement);

    while (iteratorHasNext(itA)) {
        bool ok = bstInsert(tree, iteratorNext(itA));
        if (!ok) {
            iteratorFree(&itA);
            iteratorFree(&itB);
            bstFree(&tree);
            return NULL;
        }
    }

    while (iteratorHasNext(itB)) {
        bool ok = bstInsert(tree, iteratorNext(itB));
        if (!ok) {
            iteratorFree(&itA);
            iteratorFree(&itB);
            bstFree(&tree);
            return NULL;
        }
    }

    iteratorFree(&itA);
    iteratorFree(&itB);
    return tree;
}

int bstKthMin(BST* tree, int k)
{
    if (k <= 0 || tree == NULL || bstSize(tree) < k)
        return 0;

    /* k is the kth minimum element of the subtree */
    BST* p = tree;
    while (k > 0) {
        int curK = bstSize(p->left) + 1;
        if (curK == k)
            break;
        /* binary search */
        if (curK < k) {
            k -= curK;
            p = p->right;
        } else {
            p = p->left;
        }
    }

    return p->value;
}
