#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"
#include "Status.h"

#define MAXTREESIZE 100
BiTree TreeList[MAXTREESIZE];
int size = 0;

Status SaveTree(BiTree );
Status hasNext(BiTree );

int main(void)
{
    BiTree T;
    CreateBiTree(&T);
    PostOrderTraverse(T, &hasNext);
    PostOrderTraverse(T, &SaveTree);
    for (int i = 0; i < size-1; i++)
        TreeList[i]->next = TreeList[i+1];
    TreeList[size-1]->next = NULL;
    PostOrderTraverse(T, &hasNext);
    ClearBiTree(T);
    return 0;
}

Status SaveTree(BiTree T)
{
    if (size >= MAXTREESIZE) return ERROR;
    TreeList[size] = T;
    size++;
    return OK;
}

Status hasNext(BiTree T)
{
    if(!T->next) printf("NULL\n");
    return TRUE;
}
