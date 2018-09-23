#include "BiTree.h"
#include "BiTreeQueue.h"
#include "Status.h"
#include <stdio.h>
#include <stdlib.h>

Status printNode(BiTree);
void showhelp(void);
BiTree selectTree(BiTree, BiTree);

int main(void)
{
    BiTree T1, T2;
    int command;
    printf("creating tree1\n");
    CreateBiTree(&T1);
    getchar();
    printf("creating tree2\n");
    CreateBiTree(&T2);
    showhelp();
    scanf("%d", &command);
    while(command != 14) {
        switch (command) {
        case 0: PrintBiTree(selectTree(T1,T2)); printf("\n");break;
        case 1: PreOrderTraverse(selectTree(T1,T2), &printNode); printf("\n"); break;
        case 2: InOrderTraverse(selectTree(T1,T2), &printNode); printf("\n"); break;
        case 3: PostOrderTraverse(selectTree(T1,T2), &printNode); printf("\n"); break;
        case 4: LevelOrderTraverse(selectTree(T1,T2), &printNode); printf("\n"); break;
        case 5: {
            printf("1=copy tree1 to tree2 | 2=copy tree2 to tree1\n");
            int i;
            scanf("%d", &i);
            if (i == 1) CopyBiTree(T1, &T2);
            else CopyBiTree(T2, &T1);
            break;
        }
        case 6: {
            printf("1=mirror tree1 to tree2 | 2=mirror tree2 to tree1\n");
            int i;
            scanf("%d", &i);
            if (i == 1) MirrorBiTree(T1, &T2);
            else MirrorBiTree(T2, &T1);
            break;
        }
        case 7: printf("nodenum=%d\n", NodeNumBiTree(selectTree(T1,T2))); break;
        case 8: printf("leafnum=%d\n",LeafNumBiTree(selectTree(T1,T2))); break;
        case 9: printf("height=%d\n", HeightBiTree(selectTree(T1,T2))); break;
        case 10: printf("width=%d\n",WidthBiTree(selectTree(T1,T2))); break;
        case 11: {
            printf("1=clear tree1 | 2=clear tree2\n");
            int i;
            scanf("%d", &i);
            if (i == 1) ClearBiTree(&T1);
            else ClearBiTree(&T2);
            break;
        }
        case 12: {
            if (IsBST(selectTree(T1,T2))) printf("yes\n");
            else printf("nope\n");
            break;
        }
        case 13: {
            if (IsBCT(selectTree(T1,T2))) printf("yes\n");
            else printf("nope\n");
            break;
        }
        default: break;
        }
        showhelp();
        scanf("%d", &command);  
    }
    return 0;
}

Status printNode(BiTree T)
{
    if (T) {
        printf("%c ", T->data);
        return OK;
    }
    return ERROR;
}

void showhelp(void)
{
    printf("0=Print, 1=PreOrder, 2=InOrder, 3=PostOrder\n");
    printf("4=LevelOrder, 5=Copy, 6=Mirror\n");
    printf("7=NodeNum, 8=LeafNum, 9=Height\n");
    printf("10=Width, 11=Clear, 12=IsBST, 13=IsBCT, 14=quit\n");
}

BiTree selectTree(BiTree a, BiTree b)
{
    printf("select the target tree (1 or 2)\n");
    int i;
    scanf("%d", &i);
    if (i == 1) return a;
    return b;
}
