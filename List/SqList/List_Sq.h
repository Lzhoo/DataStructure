#ifndef LISTSQ_H
#define LISTSQ_H
#include "../Status.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq (SqList *);
void DestroyList_Sq (SqList *);
void ClearList_Sq (SqList *);
Status ListEmpty_Sq (SqList *);
int ListLength_Sq (SqList *);
Status GetElem_Sq (SqList *, int, ElemType *);
int LocateElem_Sq (SqList *, ElemType, int (*)(ElemType, ElemType));
Status ListInsert_Sq (SqList *, int, ElemType);
Status ListDelete_Sq (SqList *, int, ElemType *);
#endif

