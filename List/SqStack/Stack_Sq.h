#ifndef STACKSQ_H
#define STACKSQ_H
#include "../../Status.h"

#define STACK_INIT_SIZE 100;
#define STACKINCREMENT 10;
typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

Status InitStack (SqStack );
Status DestroyStack (SqStack );
Status ClearStack (SqStack );
Status StackEmpty (SqStack );
int StackLength (SqStack );
Status GetTop (SqStack, SElemType* );
Status Push (SqStack, SElemType );
Status Pop (SqStack, SElemType* );
Status StackTraverse (SqStack, Status(*)(SElemType) );
#endif
