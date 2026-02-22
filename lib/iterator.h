#pragma once

#include "bst.h"

typedef struct Iterator Iterator;

// Инициализирует итератор центрированного обхода дерева. 
// При операциях вставки или удаления в дереве
// инвалидирует итератор.
Iterator* iteratorInit(BST* tree);
// true - имеет следующий узел для обхода,
// false - нет или итератор невалиден.
bool iteratorHasNext(Iterator* it);
// Возвращает значение следующего узла в центрированном обходе,
// в том случае, если узла нет или итератор невалиден,
// возвращает всегда 0.
int iteratorNext(Iterator* it);
// Освобождает память, занятую итератором.
void iteratorFree(Iterator** it);
// false - если итератор использует изменённое дерево,
// true - в другом случае.
bool iteratorIsValid(Iterator* it);
