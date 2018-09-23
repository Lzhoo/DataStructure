#include "ALGraph.h"
#include <stdio.h>

Status PrintVex(VertexType);
void showhelp(void);

int main(void)
{
    ALGraph G;
    int command;
    VertexType v, w;
    printf("1=创建有向图 2=创建无向图\n");
    scanf("%d", &command);
    if (command != 1 && command != 2) return -1;
    CreateGraph(&G, command-1);
    showhelp();
    scanf("%d", &command);
    while (command != 9) {
        switch (command) {
            case 1: {
                printf("输入新增顶点:\n");
                scanf("%d",&v);
                InsertVex(&G, v);
                break;
            }
            case 2: {
                printf("输入删除顶点:\n");
                scanf("%d",&v);
                DeleteVex(&G, v);
                break;
            }
            case 3: {
                printf("输入新增弧(v w)\n");
                scanf("%d%d",&v,&w);
                InsertArc(&G, v, w, 10);
                break;
            }
            case 4: {
                printf("输入删除弧(v w)\n");
                scanf("%d%d",&v,&w);
                DeleteArc(&G, v, w);
                break;
            }
            case 5: PrintGraph(&G); break;
            case 6: DFSTraverse(&G, &PrintVex); break;
            case 7: BFSTraverse(&G, &PrintVex); break;
            case 8: DestroyGraph(&G); break;
            default: break;
        }
        showhelp();
        scanf("%d",&command);
    }
    return 0;
}

Status PrintVex(VertexType v)
{
    printf("%d\n", v);
    return OK;
}

void showhelp(void)
{
    printf("1=InsertVex, 2=DeleteVex, 3=InsertArc, 4=DeleteArc\n");
    printf("5=PrintGraph, 6=DFSTraverse, 7=BFSTraverse\n");
    printf("8=DestroyGraph, 9=Quit\n");
}
