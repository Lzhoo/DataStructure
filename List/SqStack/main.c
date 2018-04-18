#include "Stack_Sq.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    SqStack sa;
    InitStack(&sa);
    for (int i = 0; i != 1000; ++i) Push(&sa, i);
    printf("len=%d\n", StackLength(sa));
    ClearStack(&sa);
    printf("len=%d\n", StackLength(sa));
    DestroyStack(&sa);
    printf("len=%d\n", StackLength(sa));
    #ifdef STATUS_H
    printf("yes\n");
    #endif
    return 0;
}