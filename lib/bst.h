#pragma once
#include <stdbool.h>

typedef struct BST BST;

BST *bstNew();
void bstInsert(BST *, int);
bool bstContains(BST *, int);
void bstFree(BST **);

void bstInorder(BST *tree);
void bstPreorder(BST *tree);
void bstPostorder(BST *tree);
int bstHeight(BST *tree);
int bstSize(BST *tree);
int bstMin(BST *tree);
int bstMax(BST *tree);
