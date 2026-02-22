#include "bst.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    BST* tree = bstNew(25);
    bool err = false;
    bstInsert(tree, 15, &err);
    assert(!err);
    bstInsert(tree, 20, &err);
    assert(!err);
    bstInsert(tree, 503, &err);
    assert(!err);
    bstInsert(tree, 8, &err);
    assert(!err);

    assert(bstContains(tree, 15));
    assert(bstContains(tree, 20));
    assert(bstContains(tree, 503));
    assert(bstContains(tree, 8));
    assert(bstMin(tree) == 8);
    assert(bstMax(tree) == 503);
    assert(bstSize(tree) == 5);

    return 0;
}
