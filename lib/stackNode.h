#pragma once

/*
 Используется итератором, чтобы проходиться по дереву.
 Стек реализован, как связный список узлов.
*/

#include "bst.h"

// Реализация стека узлов BST
typedef struct StackNode StackNode;

// Создаёт новый элемент стека
StackNode* stackNodeAlloc(BST* tree, StackNode* prev);

// Проходится до крайнего левого листа, записывая всё в StackNode
// Возвращает NULL, если дерево пусто или не удалось выделить память.
// prev нужен для связности стека
StackNode* stackNodeTraverseLeft(BST* tree, StackNode* prev);

// Удаляет все узлы в стеке
void stackFree(StackNode* node);

// Заходит на правый лист и вызывает traverseToLeft()
StackNode* stackNodeTraverseRight(StackNode* node);

// Возвращает элемент, лежащий под верхним на стеке
StackNode* stackNodeGetPrev(StackNode* node);

// Возвращает элемент узла дерева, на который ссылается элемент стека.
// Если node == NULL, возвращает 0.
int stackNodeGetValue(StackNode* node);

// Возвращает версию узла дерева, на который ссылается элемент стека.
// Версия узла изменяется при изменении дерева.
unsigned stackNodeGetVersion(StackNode* node);
