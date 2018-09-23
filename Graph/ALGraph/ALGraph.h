#ifndef ALGRAPH_H
#define ALGRAPH_H

#include "../../Status.h"
#define MAX_VERTEX_NUM 20
typedef int InfoType;
typedef int VertexType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
    InfoType info;
}ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
}ALGraph;

Status CreateGraph(ALGraph *, int);
Status DestroyGraph(ALGraph *);
int LocateVex(ALGraph *, VertexType);
VertexType GetVex(ALGraph *, int);
Status InsertVex(ALGraph *, VertexType);
Status DeleteVex(ALGraph *, VertexType);
Status InsertArc(ALGraph *, VertexType, VertexType, InfoType);
Status DeleteArc(ALGraph *, VertexType, VertexType);
void PrintGraph(ALGraph *);
void DFSTraverse(ALGraph *, Status(*)(VertexType));
void BFSTraverse(ALGraph *, Status(*)(VertexType));
#endif
