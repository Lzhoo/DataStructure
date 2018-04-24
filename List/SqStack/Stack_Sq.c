#include "Stack_Sq.h"
#include <stdlib.h>

Status InitStack(SqStack *pS)
{
    pS->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!pS->base) exit(OVERFLOW);
    pS->top = pS->base;
    pS->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack *pS)
{
    if (pS->base) free(pS->base);
    pS->base = NULL;
    pS->top = NULL;
    pS->stacksize = 0;
    return OK;
}

Status ClearStack(SqStack *pS)
{
    pS->top = pS->base;
    return OK;
}

Status StackEmpty(SqStack S)
{
    if (S.top == S.base) return TRUE;
    return FALSE;
}

int StackLength(SqStack S)
{
    if (S.stacksize <= 0) return -1;
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *pe)
{
    if (S.top == S.base) return ERROR;
    *pe = *(S.top - 1);
    return OK;
}

Status Push(SqStack *pS, SElemType e)
{
    if (pS->top - pS->base >= pS->stacksize) {
        pS->base = (SElemType *)realloc(pS->base, (pS->stacksize+STACKINCREMENT) * sizeof(SElemType));
        if (!pS->base) exit(OVERFLOW);
        pS->top = pS->base + pS->stacksize;
        pS->stacksize += STACKINCREMENT;
    }
    *(pS->top++) = e;
    return OK;
}

Status Pop(SqStack *pS, SElemType *pe)
{
    if (pS->top == pS->base) return ERROR;
    *pe = * (--(pS->top));
    int length = pS->top - pS->base;
    if (length < pS->stacksize/4) {
        pS->base = (SElemType *)realloc(pS->base, (pS->stacksize/2) * sizeof(SElemType));
        if (!pS->base) exit(OVERFLOW);
        pS->top = pS->base + length;
        pS->stacksize /= 2;
    }
    return OK;
}

Status StackTraverse(SqStack S, Status(* visit)(SElemType))
{
    if (S.top == S.base) return ERROR;
    for (SElemType *p = S.base; p != S.top; p++)
        visit(*p);
    return OK;
}

