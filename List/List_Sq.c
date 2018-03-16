#include "List_Sq.h"
#include <stdlib.h>

Status InitList_Sq (SqList *L)
{
// construct an empty linear list L
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (! L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

void DestroyList_Sq (SqList *L)
{
    free(L->elem);
    L->length = 0;
    L->listsize = 0;
}// DestroyList_Sq

void ClearList_Sq (SqList *L)
{
    L->length = 0;
}// ClearList_Sq

Status ListEmpty_Sq (SqList *L)
{
    if (L->length == 0) return TRUE;
    else return FALSE;
}// ListEmpty_Sq

int ListLength_Sq (SqList *L)
{
    return L->length;
}// ListLength_Sq

Status GetElem_Sq (SqList *L, int i, ElemType *e)
{
    if (i < 1 || i > L->length) return ERROR;
    *e = L->elem[i-1];
    return OK;
}// GetElem_Sq

int LocateElem_Sq (SqList *L, ElemType e, int (* compare)(ElemType, ElemType))
{
    int i = 0;
    while (i < L->length && (* compare)(e, L->elem[i]) != 0)
	i++;
    if (i < L->length) return i+1;
    else return -1;
}// LocateElem_Sq

Status ListInsert_Sq (SqList *L, int i, ElemType e)
{
    if (i < 1 || i > L->length+1) return ERROR;
    if (L->length >= L->listsize) {
	ElemType *newbase;
	newbase = (ElemType *)realloc(L->elem,
				      (L->listsize+LISTINCREMENT) * sizeof(ElemType));
	if (!newbase) exit(OVERFLOW);
	L->elem = newbase;
	L->listsize += LISTINCREMENT;
    }
    ElemType *q, *p;
    q = &(L->elem[i-1]);
    for (p = &(L->elem[L->length-1]); p >= q; --p)
	*(p+1) = *p;
    *q = e;
    ++L->length;
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq (SqList *L, int i, ElemType *e)
{
    if (i < 1 || i > L->length) return ERROR;
    ElemType *p, *q;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length - 1;
    for (++p; p <= q; ++p)
	*(p-1) = *p;
    --L->length;
    return OK;
}// ListDelete_Sq
