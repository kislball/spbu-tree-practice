#include "bst.h"
#include "bstInternal.h"
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

void testMerge()
{
    BST* treeA = bstNew(25);
    assert(bstInsert(treeA, 15));
    assert(bstIsValid(treeA));
    assert(bstInsert(treeA, 20));
    assert(bstIsValid(treeA));
    assert(bstInsert(treeA, 503));
    assert(bstIsValid(treeA));
    assert(bstInsert(treeA, 8));
    assert(bstIsValid(treeA));

    BST* treeB = bstNew(16);
    assert(bstInsert(treeB, 15));
    assert(bstIsValid(treeB));
    assert(bstInsert(treeB, 431));
    assert(bstIsValid(treeB));
    assert(bstInsert(treeB, 652));
    assert(bstIsValid(treeB));
    assert(bstInsert(treeB, 32));
    assert(bstIsValid(treeB));

    BST* final = bstMerge(treeA, treeB);

    int values[] = { 25, 15, 20, 503, 8, 16, 431, 652, 32 };
    int totalValues = sizeof(values) / sizeof(*values);
    assert(bstSize(final) == totalValues);

    for (int i = 0; i < totalValues; i++) {
        assert(bstContains(final, values[i]));
    }

    bstFree(&treeA);
    bstFree(&treeB);
    bstFree(&final);
}

void testKthMin()
{
    BST* tree = bstNew(6);
    assert(tree != NULL);
    assert(bstInsert(tree, 4));
    assert(bstInsert(tree, 2));
    assert(bstInsert(tree, 5));
    assert(bstInsert(tree, 1));
    assert(bstInsert(tree, 3));
    assert(bstInsert(tree, 10));
    assert(bstInsert(tree, 8));
    assert(bstInsert(tree, 7));
    assert(bstInsert(tree, 9));
    assert(bstInsert(tree, 4));
    assert(bstInsert(tree, 12));
    assert(bstInsert(tree, 11));
    assert(bstInsert(tree, 13));

    for (int i = 1; i <= 13; i++) {
        bool err = false;
        assert(bstKthMin(tree, i, &err) == i && !err);
    }
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
    testMerge();
    testKthMin();
    return 0;
}
