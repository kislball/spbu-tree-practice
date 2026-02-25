#include "stackNode.h"

#include "bstInternal.h"
#include <stdlib.h>

typedef struct StackNode {
    struct StackNode* prev;
    BST* data;
} StackNode;

StackNode* allocStackNode(BST* tree, StackNode* prev)
{
    StackNode* node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    node->data = tree;
    node->prev = prev;
    return node;
}

void stackFree(StackNode* node)
{
    while (node) {
        StackNode* temp = node;
        node = node->prev;
        free(temp);
    }
}

StackNode* stackNodeTraverseLeft(BST* tree, StackNode* prev)
{
    if (tree == NULL)
        return NULL;
    StackNode* node = allocStackNode(tree, prev);
    if (node == NULL)
        return NULL;

    tree = tree->left;
    while (tree) {
        StackNode* newNode = allocStackNode(tree, node);
        if (newNode == NULL)
            stackFree(node);
        node = newNode;
        tree = tree->left;
    }
    return node;
}

StackNode* stackNodeTraverseRight(StackNode* node)
{
    return stackNodeTraverseLeft(node->data->right, node->prev);
}

StackNode* stackNodeGetPrev(StackNode* node)
{
    return node->prev;
}

int stackNodeGetValue(StackNode* node)
{
    if (!node)
        return 0;
    return node->data->value;
}

unsigned stackNodeGetVersion(StackNode* node)
{
    if (!node)
        return ((unsigned)-1);

    return node->data->data.isRoot ? node->data->modVersion.base : *node->data->modVersion.pBase;
}
