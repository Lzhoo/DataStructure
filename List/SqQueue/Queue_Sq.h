#ifndef QUEUESQ_H
#define QUEUESQ_H
#include "../../Status.h"
#include "../../Tree/BinaryTree/BiTree.h"

#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10
typedef BiTree QElemType;
typedef struct {
    QElemType *base;
    QElemType *head;
    QElemType *tail;
    int queuesize;
}SqQueue;

Status InitQueue (SqQueue *);
Status DestroyQueue (SqQueue *);
Status ClearQueue (SqQueue *);
Status QueueEmpty (SqQueue );
int QueueLength (SqQueue );
Status EnQueue (SqQueue*, QElemType );
Status DeQueue (SqQueue*, QElemType*);
Status QueueTraverse (SqQueue, Status(*)(QElemType) );
#endif