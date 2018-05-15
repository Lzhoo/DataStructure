#include "Queue_Sq.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    SqQueue qa;
    QElemType e;
    InitQueue(&qa);
    for (int i = 0; i != 1000; i++) EnQueue(&qa, i);
    printf("len=%d\n", QueueLength(qa));
    for (int i = 0; i != 10; i++) {
        DeQueue(&qa, &e);
        printf("%d\n", e);
    }
    ClearQueue(&qa);
    printf("len=%d\n", QueueLength(qa));
    DestroyQueue(&qa);
    printf("len=%d\n", QueueLength(qa));
    return 0;
}