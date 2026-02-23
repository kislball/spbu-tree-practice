#include "iterator.h"
#include "stackNode.h"
#include <stdlib.h>

struct Iterator {
    struct StackNode* head;
    unsigned modVersion;
};

Iterator* iteratorInit(BST* tree)
{
    Iterator* it = calloc(1, sizeof(*it));
    if (it == NULL)
        return NULL;

    // Итератор на пустом дереве.
    if (tree == NULL) {
        return it;
    }

    it->head = stackNodeTraverseLeft(tree, NULL);
    if (it->head == NULL) {
        free(it);
        return NULL;
    }
    it->modVersion = stackNodeGetVersion(it->head);
    return it;
}

bool iteratorHasNext(Iterator* it)
{
    return it != NULL && it->head != NULL;
}

int iteratorNext(Iterator* it)
{
    if (it == NULL)
        return 0;
    StackNode* curNode = it->head;
    if (curNode == NULL || !iteratorIsValid(it))
        return 0;

    stackNodeTraverseRight(curNode);
    StackNode* nextNodes = stackNodeTraverseRight(curNode);
    it->head = nextNodes == NULL ? stackNodeGetPrev(curNode) : nextNodes;

    int result = stackNodeGetValue(curNode);
    free(curNode);
    return result;
}

bool iteratorIsValid(Iterator* it)
{
    if (it == NULL || it->head == NULL)
        return false;
    return stackNodeGetVersion(it->head) == it->modVersion;
}

void iteratorFree(Iterator** it)
{
    if (it == NULL || *it == NULL)
        return;
    stackFree((*it)->head);
    free(*it);
    *it = NULL;
}
