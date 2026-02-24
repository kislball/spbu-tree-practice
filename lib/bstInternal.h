#pragma once

#include "bst.h"

typedef struct BST {
    BST* left;
    BST* right;
    int value;
    struct {
        unsigned childrenCount : 31;
        bool isRoot : 1;
    } data;
    // Значение версии дерева. Экземпляр хранится у корня,
    // дети хранят указатель. Нужен для того, чтобы
    // просматривать, когда изменилось дерево.
    union {
        unsigned base;
        unsigned* pBase;
    } modVersion;
} BST;
BST* bstNewChild(BST* root, int val);
