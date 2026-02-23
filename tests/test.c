#include "bstInternal.h"
#include "bst.h"
#include "iterator.h"
#include <assert.h>
#include <stdio.h>

BST* getInvalidTree()
{
    BST* tree = bstNew(9);
    tree->left = bstNewChild(tree, 8);
    tree->left->left = bstNewChild(tree, 7);
    tree->left->right = bstNewChild(tree, 11);
    tree->right = bstNewChild(tree, 10);
    tree->right->left = bstNewChild(tree, 2);
    tree->right->right = bstNewChild(tree, 15);
    return tree;
}

void testIterators()
{
    BST* tree = bstNew(4);
    assert(tree != NULL);

    int valuesToInsert[] = { 2, 1, 3, 6, 5, 7, 9, 8 };
    for (unsigned i = 0; i < sizeof(valuesToInsert) / sizeof(valuesToInsert[0]); i++) {
        assert(bstInsert(tree, valuesToInsert[i]));
        assert(bstIsValid(tree));
    }

    Iterator* it = iteratorInit(tree);
    assert(it != NULL);
    int count = sizeof(valuesToInsert) / sizeof(valuesToInsert[0]) + 1;
    for (int i = 0; i < count; i++) {
        assert(iteratorIsValid(it));
        assert(iteratorHasNext(it));
        int val = iteratorNext(it);
        assert(val == i + 1);
    }

    assert(!iteratorHasNext(it));
    assert(!iteratorIsValid(it));

    iteratorFree(&it);

    it = iteratorInit(tree);
    assert(bstIsValid(tree));
    assert(bstInsert(tree, 1));
    assert(bstIsValid(tree));
    assert(iteratorIsValid(it));
    assert(bstIsValid(tree));
    assert(bstInsert(tree, 123));
    assert(bstIsValid(tree));
    assert(!iteratorIsValid(it));
    assert(bstIsValid(tree));
    iteratorFree(&it);
    bstFree(&tree);
}

void testInvalidTree()
{
    BST* invalid = getInvalidTree();

    assert(!bstIsValid(invalid));
    bstFree(&invalid);
}

int main()
{
    BST* tree = bstNew(25);
    assert(bstInsert(tree, 15));
    assert(bstIsValid(tree));
    assert(bstInsert(tree, 20));
    assert(bstIsValid(tree));
    assert(bstInsert(tree, 503));
    assert(bstIsValid(tree));
    assert(bstInsert(tree, 8));
    assert(bstIsValid(tree));

    assert(bstContains(tree, 15));
    assert(bstContains(tree, 20));
    assert(bstContains(tree, 503));
    assert(bstContains(tree, 8));
    assert(bstMin(tree) == 8);
    assert(bstMax(tree) == 503);
    assert(bstSize(tree) == 5);

    testIterators();
    return 0;
}
