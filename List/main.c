#include <stdio.h>
#include "List_Sq.h"

int main()
{
    SqList L;
    InitList_Sq(&L);
    printf("%d %d\n", L.length, L.listsize);
    ListInsert_Sq(&L, 1, 30);
    int q = 100;
    GetElem_Sq(&L, 1, &q);
    printf("%d\n", q);
    printf("%d\n", GetElem_Sq(&L, 3, &q));
    DestroyList_Sq(&L);
    return 0;
}
