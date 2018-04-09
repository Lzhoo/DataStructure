#include "BiTree.h"
#include "../../Status.h"
#include <stdlib.h>
#include <stdio.h>

// private function protype
Status FreeBTNode(BiTree );

// API definition
Status CreateBiTree(BiTree *pT)
{
    char ch = getchar();
    if (ch == ' ' || ch == EOF || ch == '\n') *pT = NULL;
    else {
        if (!(*pT = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
        (*pT)->data = ch;
        (*pT)->next = NULL;
        CreateBiTree(&(*pT)->lchild);
        CreateBiTree(&(*pT)->rchild);
    }
    return OK;
}

Status PreOrderTraverse(BiTree T, Status(* Visit)(BiTree ) )
{
    if (T) {
        if (Visit(T))
            if (PreOrderTraverse(T->lchild, Visit))
                if (PreOrderTraverse(T->rchild, Visit)) return OK;
        return ERROR;
    }
    else return OK;
}

Status PostOrderTraverse(BiTree T, Status(* Visit)(BiTree ) )
{
    if (T) {
        if (PostOrderTraverse(T->lchild, Visit))
            if (PostOrderTraverse(T->rchild, Visit))
                if (Visit(T)) return OK;
        return ERROR;
    }
    else return OK;
}

Status ClearBiTree(BiTree T)
{
    if (T) return PostOrderTraverse(T, &FreeBTNode);
    return OK;
}

// private function definition
Status FreeBTNode(BiTree T)
{
    if (!T->lchild && !T->rchild) {
        free(T);
        T = NULL;
        return OK;
    }
    return ERROR;
}
