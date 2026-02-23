#pragma once

#include "bst.h"

typedef struct BST {
    BST* left;
    BST* right;
    int value;
    bool isRoot;
    // Значение версии дерева. Экземпляр хранится у корня,
    // дети хранят указатель. Нужен для того, чтобы
    // просматривать, когда изменилось дерево.
    union {
        unsigned base;
        unsigned* pBase;
    } modVersion;
} BST;
