#include "Stack_Sq.h"
#include <stdlib.h>

Status InitStack(SqStack S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack S)
{
    if (S.base) free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}

Status ClearStack(SqStack S)
{
    S.top = S.base;
    return OK;
}

Status StackEmpty(SqStack S)
{
    if (S.top == S.base) return TRUE;
    return FALSE;
}

int StackLength(SqStack S)
{
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *pe)
{
    if (S.top == S.base) return ERROR;
    *pe = *(S.top - 1);
    return OK;
}

Status Push(SqStack S, SElemType e)
{
    if (S.top - S.base >= S.stacksize) {
        S.base = (SElemType *)realloc(S.base, (S.stacksize+STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack S, SElemType *pe)
{
    if (S.top == S.base) return ERROR;
    *pe = * --S.top;
    int length = S.top - S.base;
    if (length < S.stacksize/4) {
        S.base = (SElemType *)realloc(S.base, (S.stacksize/2) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + length;
        S.stacksize /= 2;
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

