#include "Queue_Sq.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    SqQueue qa;
    QElemType e;
    InitQueue(&qa);
    printf("%d %d\n", *(qa.head), *(qa.head+1));
    for (int i = 0; i != 1000; i++) {printf("%d ", i); EnQueue(&qa, i);}
    printf("len=%d size=%d\n", QueueLength(qa), qa.queuesize);
    printf("%d %d\n", *(qa.head), *(qa.head+1));
    for (int i = 0; i != 1000; i++) {
        DeQueue(&qa, &e);
        printf("%d len=%d size=%d\n", e, QueueLength(qa), qa.queuesize);
    }
    printf("len=%d\n", QueueLength(qa));
    return 0;
}