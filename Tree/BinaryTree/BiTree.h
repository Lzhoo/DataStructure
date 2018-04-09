#ifndef BITREE_H
#define BITREE_H
#include "../../Status.h"

typedef char ElemType;
typedef struct BTNode {
    ElemType data;
    struct BTNode *lchild, *rchild, *next;
}BTNode, *BiTree;

Status CreateBiTree(BiTree* );
Status ClearBiTree(BiTree );
Status PreOrderTraverse(BiTree, Status(*)(BiTree ) );
Status PostOrderTraverse(BiTree, Status(*)(BiTree ) );
#endif
