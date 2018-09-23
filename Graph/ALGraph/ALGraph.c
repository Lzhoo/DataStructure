#include <stdlib.h>
#include <stdio.h>
#include "ALGraph.h"
#include "VexQueue.h"
#include "../../Status.h"

Status InsertArcByPos(ALGraph *, int, int, InfoType);
Status DeleteArcByPos(ALGraph *, int, int);
void DFS(ALGraph *, int);

int visited[MAX_VERTEX_NUM];
Status (* VisitFunc)(VertexType);

// kind=0 Digraph; kind=1 Undigraph
Status CreateGraph(ALGraph *pG, int kind)
{
    pG->vexnum = 0;
    pG->arcnum = 0;
    pG->kind = kind;
    return OK;
}

Status DestroyGraph(ALGraph *pG)
{
    ArcNode *parc;
    for (int i = 0; i < pG->vexnum; i++) {
        parc = pG->vertices[i].firstarc;
        while (parc) {
            pG->vertices[i].firstarc = parc->nextarc;
            free(parc);
            parc = pG->vertices[i].firstarc;
        }
    }
    pG->vexnum = 0;
    pG->arcnum = 0;
    return OK;
}
int LocateVex(ALGraph *pG, VertexType v)
{
    for (int i = 0; i < pG->vexnum; i++)
        if (pG->vertices[i].data == v) return i;
    return -1;
}

VertexType GetVex(ALGraph *pG, int i)
{
    if (i < pG->vexnum && i > -1) return pG->vertices[i].data;
    return 0;
}

Status InsertVex(ALGraph *pG, VertexType v)
{
    if (pG->vexnum >= MAX_VERTEX_NUM) return ERROR;
    if (LocateVex(pG, v) != -1) return ERROR;
    pG->vertices[pG->vexnum].data = v;
    pG->vertices[pG->vexnum].firstarc = NULL;
    pG->vexnum++;
    return OK;
}

Status DeleteVex(ALGraph *pG, VertexType v)
{
    int vpos = LocateVex(pG, v);
    if (vpos == -1) return ERROR;
    ArcNode *back, *forw;
    int arcdelete = 0;
    
    // traverse all arcs
    // delete arcs whose tail is v
    // change arcs whose tail is after v
    for (int i = 0; i < pG->vexnum; i++) {
        back = pG->vertices[i].firstarc;
        forw = back;
        // traverse the arc linklist
        while (forw) {
            if (forw->adjvex == vpos) {
                if (forw == back) {
                    pG->vertices[i].firstarc = forw->nextarc;
                    free(forw);
                    back = pG->vertices[i].firstarc;
                    forw = back;
                    arcdelete++;
                    continue;
                }
                back->nextarc = forw->nextarc;
                free(forw);
                forw = back->nextarc;
                arcdelete++;
                continue;
            }
            if (forw->adjvex > vpos) forw->adjvex--;
            back = forw;
            forw = back->nextarc;
        }
    }
    
    // delete the arc linklist of vex v
    forw = pG->vertices[vpos].firstarc;
    while (forw) {
        pG->vertices[vpos].firstarc = forw->nextarc;
        free(forw);
        forw = pG->vertices[vpos].firstarc;
        arcdelete++;
    }
    
    // move vexs that are behind v
    for (int i = vpos; i < pG->vexnum-1; i++) {
        pG->vertices[i].data = pG->vertices[i+1].data;
        pG->vertices[i].firstarc = pG->vertices[i+1].firstarc;
    }
    
    pG->vexnum--;
    pG->arcnum -= arcdelete;
    return OK;
}

Status InsertArc(ALGraph *pG, VertexType v, VertexType w, InfoType info)
{
    int vpos = LocateVex(pG, v);
    int wpos = LocateVex(pG, w);
    if (vpos == -1 || wpos == -1 || vpos == wpos) return ERROR;
    
    InsertArcByPos(pG, vpos, wpos, info);
    if (pG->kind) InsertArcByPos(pG, wpos, vpos, info);
    return OK;
}

Status DeleteArc(ALGraph *pG, VertexType v, VertexType w)
{
    int vpos = LocateVex(pG, v);
    int wpos = LocateVex(pG, w);
    if (vpos == -1 || wpos == -1 || vpos == wpos) return ERROR;
    
    DeleteArcByPos(pG, vpos, wpos);
    if (pG->kind) DeleteArcByPos(pG, wpos, vpos);
    return OK;
}

void PrintGraph(ALGraph *pG)
{
    printf("vexnum=%d arcnum=%d kind=%d\n", pG->vexnum, pG->arcnum, pG->kind);
    ArcNode *parc;
    for (int i = 0; i < pG->vexnum; i++) {
        parc = pG->vertices[i].firstarc;
        while (parc) {
            printf("%d->%d(%d) ", pG->vertices[i].data, pG->vertices[parc->adjvex].data, parc->info);
            parc = parc->nextarc;
        }
        printf("\n");
    }
    printf("PrintGraph Done\n");
}

void DFSTraverse(ALGraph *pG, Status(* Visit)(VertexType))
{
    VisitFunc = Visit;
    for (int i = 0; i < pG->vexnum; i++) visited[i] = 0;
    for (int i = 0; i < pG->vexnum; i++)
        if (!visited[i]) DFS(pG, i);
}

void BFSTraverse(ALGraph *pG, Status(* Visit)(VertexType))
{
    for (int i = 0; i < pG->vexnum; i++) visited[i] = 0;
    SqQueue Q;
    QElemType u;
    ArcNode *parc;
    InitQueue(&Q);
    for (int i = 0; i < pG->vexnum; i++)
        if (!visited[i]) {
            visited[i] = 1;
            Visit(pG->vertices[i].data);
            EnQueue(&Q, &(pG->vertices[i]));
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &u);
                parc = u->firstarc;
                while (parc) {
                    if (!visited[parc->adjvex]) {
                        visited[parc->adjvex] = 1;
                        Visit(pG->vertices[parc->adjvex].data);
                        EnQueue(&Q, &(pG->vertices[parc->adjvex]));
                    }
                    parc = parc->nextarc;
                }
            }
        }
}
// private function
Status InsertArcByPos(ALGraph *pG, int vpos, int wpos, InfoType info)
{
    ArcNode *back, *forw;
    
    // insert arc v->w, vpos != wpos
    back = pG->vertices[vpos].firstarc;
    forw = back;
    while (forw) {
        if (forw->adjvex == wpos) return OK;
        back = forw;
        forw = back->nextarc;
    }
    if (!(forw = (ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
    forw->adjvex = wpos;
    forw->nextarc = NULL;
    forw->info = info;
    if (!back) pG->vertices[vpos].firstarc = forw;
    else back->nextarc = forw;
    pG->arcnum++;
    return OK;
}

Status DeleteArcByPos(ALGraph *pG, int vpos, int wpos)
{
    ArcNode *back, *forw;
    
    // delete arc v->w, vpos != wpos
    back = pG->vertices[vpos].firstarc;
    forw = back;
    while (forw) {
        if (forw->adjvex == wpos) {
            if (forw == back) pG->vertices[vpos].firstarc = forw->nextarc;
            else back->nextarc = forw->nextarc;
            free(forw);
            pG->arcnum--;
            return OK;
        }
        back = forw;
        forw = back->nextarc;
    }
    return OK;
}

void DFS(ALGraph *pG, int vpos)
{
    visited[vpos] =  1;
    VisitFunc(pG->vertices[vpos].data);
    ArcNode *parc = pG->vertices[vpos].firstarc;
    while (parc) {
        if (!visited[parc->adjvex]) DFS(pG, parc->adjvex);
        parc = parc->nextarc;
    }
}
