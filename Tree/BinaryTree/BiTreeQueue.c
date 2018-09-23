#include "BiTreeQueue.h"
#include <stdlib.h>

QElemType* shift(SqQueue, QElemType*);

// API definition
Status InitQueue(SqQueue *pQ)
{
    pQ->base = (QElemType *)malloc(QUEUE_INIT_SIZE * sizeof (QElemType));
    if (!pQ->base) exit(OVERFLOW);
    pQ->head = pQ->base;
    pQ->tail = pQ->base;
    pQ->queuesize = QUEUE_INIT_SIZE;
    return OK;
}

Status DestroyQueue(SqQueue *pQ)
{
    if (pQ->base) free(pQ->base);
    pQ->base = NULL;
    pQ->head = NULL;
    pQ->tail = NULL;
    pQ->queuesize = 0;
    return OK;
}

Status ClearQueue(SqQueue *pQ)
{
    pQ->head = pQ->tail;
    return OK;
}

Status QueueEmpty(SqQueue Q)
{
    if (Q.head == Q.tail) return TRUE;
    return FALSE;
}

int QueueLength(SqQueue Q)
{
    if (Q.queuesize <= 0) return -1;
    if (Q.tail == Q.head) return 0;
    return (Q.tail - Q.head + Q.queuesize) % Q.queuesize;
}

Status EnQueue(SqQueue *pQ, QElemType e)
{
    if (QueueLength(*pQ)+1 >= pQ->queuesize) {
        QElemType *pnew = (QElemType *)malloc((pQ->queuesize+QUEUEINCREMENT)*sizeof(QElemType));
        if (!pnew) exit(OVERFLOW);
        // copy to new
        QElemType *pold = pQ->head, *pcur = pnew;
        while (pold != pQ->tail) {
            *pcur = *pold;
            pold = shift(*pQ, pold);
            pcur++;
        }
        *pcur = *pold;
        free(pQ->base);
        pQ->base = pnew;
        pQ->head = pnew;
        pQ->tail = pcur;
        pQ->queuesize += QUEUEINCREMENT;
    }
    // 之前把下面这两行的次序写反了，debug就很气
    *(pQ->tail) = e;
    pQ->tail = shift(*pQ, pQ->tail);
    return OK;
}

Status DeQueue(SqQueue *pQ, QElemType *pe)
{
    if (QueueLength(*pQ) <= 0) return ERROR;
    *pe = *(pQ->head);
    pQ->head = shift(*pQ, pQ->head);
    if (QueueLength(*pQ) < pQ->queuesize/4) {
        QElemType *pnew = (QElemType *)malloc((pQ->queuesize/2)*sizeof(QElemType));
        if (!pnew) exit(OVERFLOW);
        // copy to new
        QElemType *pold = pQ->head, *pcur = pnew;
        while (pold != pQ->tail) {
            *pcur = *pold;
            pold = shift(*pQ, pold);
            pcur++;
        }
        *pcur = *pold;
        pQ->base = pnew;
        pQ->head = pnew;
        pQ->tail = pcur;
        pQ->queuesize /= 2;
    }
    return OK;
}

Status QueueTraverse(SqQueue Q, Status(* visit)(QElemType))
{
    if (QueueLength(Q) <= 0) return ERROR;
    QElemType *pcur = Q.head;
    while (pcur != Q.tail) {
        visit(*pcur);
        pcur = shift(Q, pcur);
    }
    visit(*pcur);
    return OK;
}
// private function
QElemType* shift(SqQueue Q, QElemType *pe)
{
    if (pe-Q.base+1 == Q.queuesize) return Q.base;
    return pe+1;
}