#include "bst.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    BST* tree = bstNew(25);
    bstInsert(tree, 15);
    bstInsert(tree, 20);
    bstInsert(tree, 503);
    bstInsert(tree, 8);

    assert(bstContains(tree, 15));
    assert(bstContains(tree, 20));
    assert(bstContains(tree, 503));
    assert(bstContains(tree, 8));
    assert(bstMin(tree) == 8);
    assert(bstMax(tree) == 503);
    assert(bstSize(tree) == 5);

    return 0;
}
