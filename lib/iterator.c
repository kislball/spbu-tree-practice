#include "iterator.h"
#include "bst.h"
#include <stdlib.h>
#include "bst.c"

typedef struct StackNode {
    struct StackNode* prev;
    BST* data;
} StackNode;

struct Iterator {
    struct StackNode* head;
    unsigned modVersion;
};

static StackNode* allocStackNode(BST* tree, StackNode* prev)
{
    StackNode* node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    node->data = tree;
    node->prev = prev;
    return node;
}

// Удаляет все узлы в связном списке.
static void stackFree(StackNode* node)
{
    while (node) {
        StackNode* temp = node;
        node = node->prev;
        free(temp);
    }
}

// Проходится до крайнего левого листа, записывая всё в StackNode
static StackNode* traverseToLeft(BST* tree)
{
    if (tree == NULL)
        return NULL;
    StackNode* node = allocStackNode(tree, NULL);
    if (node == NULL)
        return NULL;

    while (tree->left) {
        StackNode* newNode = allocStackNode(tree, node);
        if (newNode == NULL)
            stackFree(node);
        node = newNode;
        tree = tree->left;
    }
    return node;
}

Iterator* iteratorInit(BST* tree)
{
    Iterator* it = malloc(sizeof(*it));
    if (it == NULL)
        return NULL;

    // Итератор на пустом дереве.
    if (tree == NULL) {
        it->head = NULL;
        it->modVersion = 0;
        return it;
    }

    it->modVersion = tree->modVersion;
    it->head = traverseToLeft(tree);
    if (it->head == NULL) {
        free(it);
        return NULL;
    }
    return it;
}
