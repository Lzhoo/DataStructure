#include "BiTree.h"
#include "BiTreeQueue.h"
#include "Status.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 100
#define MAXDEPTH 100

// global variables
int nodenum;
int leafnum;
BiTree nodefound;
TElemType target;
int flagfound;
TElemType BSTdatas[MAXSIZE];
int BSTsize;

// private function protype
Status FreeBTNode(BiTree );
Status CountBTNode(BiTree );
Status CountLeaf(BiTree );
Status HWBiTree(BiTree , int*, int*);  // levelordertraverse to count width and height of BiTree.
Status FindBTNode(BiTree);
Status GetBSTdata(BiTree);

// API definition
// 函数：CreateBiTree(BiTree *)
// 作用：根据标准输入先序遍历创建二叉树，空格视为空结点
Status CreateBiTree(BiTree *pT)
{
    char ch = getchar();
    if (ch == ' ' || ch == EOF || ch == '\n') *pT = NULL;
    else {
        if (!(*pT = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
        (*pT)->data = ch;
        (*pT)->parent = NULL;
        CreateBiTree(&(*pT)->lchild);
        CreateBiTree(&(*pT)->rchild);
        if ((*pT)->lchild) (*pT)->lchild->parent = *pT;
        if ((*pT)->rchild) (*pT)->rchild->parent = *pT;
    }
    return OK;
}

// 函数：CreateCompleteBiTree(BiTree *)
// 作用：根据标准输入建立完全二叉树，输入字符序列不含空格
Status CreateCompleteBiTree(BiTree *pT)
{
    int n = 0;
    char ch = getchar();
    BiTree node[MAXSIZE];
    // 分配结点
    while (ch != ' ' && ch != EOF && ch != '\n') {
        if (!(node[n] = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
        node[n]->data = ch;
        n++;
        ch = getchar();
    }
    // 连接结点
    for (int i = 0; i < n; i++) {
        if (2*i+1 < n) {node[i]->lchild = node[2*i+1]; node[2*i+1]->parent = node[i];}
        else node[i]->lchild = NULL;
        if (2*i+2 < n) {node[i]->rchild = node[2*i+2]; node[2*i+2]->parent = node[i];}
        else node[i]->rchild = NULL;
    }
    *pT = node[0];
    return OK;
}

// 函数：PreOrderTraverse
// 目的：先序遍历二叉树
Status PreOrderTraverse(BiTree T, Status(* Visit)(BiTree ) )
{
    if (T) {
        if (Visit(T))
            if (PreOrderTraverse(T->lchild, Visit))
                if (PreOrderTraverse(T->rchild, Visit)) return OK;
        return ERROR;
    }
    else return OK;
}

// 函数：InOrderTraverse
// 目的：中序遍历二叉树
Status InOrderTraverse(BiTree T, Status(* Visit)(BiTree ) )
{
    if (T) {
        if (InOrderTraverse(T->lchild, Visit))
            if (Visit(T))
                if (InOrderTraverse(T->rchild, Visit)) return OK;
        return ERROR;
    }
    else return OK;
}

// 函数：PostOrderTraverse
// 目的：后序遍历二叉树
Status PostOrderTraverse(BiTree T, Status(* Visit)(BiTree ) )
{
    if (T) {
        if (PostOrderTraverse(T->lchild, Visit))
            if (PostOrderTraverse(T->rchild, Visit))
                if (Visit(T)) return OK;
        return ERROR;
    }
    else return OK;
}

// 函数：LevelOrderTraverse
// 目的：层次遍历二叉树
Status LevelOrderTraverse(BiTree T, Status(* Visit)(BiTree ))
{
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    BiTree tmp;
    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &tmp);
        if (!Visit(tmp)) return ERROR;
        if (tmp->lchild) EnQueue(&Q, tmp->lchild);
        if (tmp->rchild) EnQueue(&Q, tmp->rchild);
    }
    return OK;    
}

// 函数：PrintBiTree(BiTree )
// 目的：按照 右子树-根节点-左子树 的顺序打印二叉树
Status PrintBiTree(BiTree T)
{
    if (T) {
        if (PrintBiTree(T->rchild)) {
            printf("%c ", T->data);
            if (PrintBiTree(T->lchild)) return OK;
        }
        return ERROR;
    }
    else return OK;
}

// 函数：ClearBiTree(BiTree *)
// 目的：清空二叉树
Status ClearBiTree(BiTree *pT)
{
    if (*pT) {
        PostOrderTraverse(*pT, &FreeBTNode);
        *pT = NULL;
        return OK;
    }
    return ERROR;
}

// 函数：NodeNumBiTree(BiTree )
// 目的：统计二叉树结点总数
int NodeNumBiTree(BiTree T)
{
    nodenum = 0;
    PreOrderTraverse(T, &CountBTNode);
    return nodenum;
}

// 函数：LeafNumBiTree(BiTree )
// 目的：统计二叉树叶子总数
int LeafNumBiTree(BiTree T)
{
    leafnum = 0;
    PreOrderTraverse(T, &CountLeaf);
    return leafnum;
}

// 函数：HeightBiTree(BiTree )
// 目的：计算二叉树高度
int HeightBiTree(BiTree T)
{
    int height, width;
    HWBiTree(T, &height, &width);
    return height;
}

// 函数：WidthBiTree(BiTree )
// 目的：计算二叉树最大宽度
int WidthBiTree(BiTree T)
{
    int height, width;
    HWBiTree(T, &height, &width);
    return width;
}

// 函数：CopyBiTree
// 目的：复制二叉树a到b
Status CopyBiTree(BiTree a, BiTree *pb)
{
    // copy a to b
    ClearBiTree(pb);
    SqQueue Qa, Qb;
    InitQueue(&Qa); InitQueue(&Qb);
    EnQueue(&Qa, a);
    if (!(*pb = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
    (*pb)->lchild = NULL; (*pb)->rchild = NULL; (*pb)->parent = NULL;
    (*pb)->data = a->data;
    EnQueue(&Qb, *pb);
    BiTree tmpa, tmpb, tmpc;
    while (!QueueEmpty(Qa)) {
        DeQueue(&Qa, &tmpa);
        DeQueue(&Qb, &tmpb);
        if (tmpa->lchild) {
            EnQueue(&Qa, tmpa->lchild);
            if (!(tmpb->lchild = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
            tmpc = tmpb->lchild;
            tmpc->lchild = NULL;
            tmpc->rchild = NULL;
            tmpc->parent = tmpb;
            tmpc->data = tmpa->lchild->data;
            EnQueue(&Qb, tmpc);
        }
        if (tmpa->rchild) {
            EnQueue(&Qa, tmpa->rchild);
            if (!(tmpb->rchild = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
            tmpc = tmpb->rchild;
            tmpc->lchild = NULL;
            tmpc->rchild = NULL;
            tmpc->parent = tmpb;
            tmpc->data = tmpa->rchild->data;
            EnQueue(&Qb, tmpc);
        }
    }
    DestroyQueue(&Qa); DestroyQueue(&Qb);
    return OK;
}

// 函数：MirrorBiTree
// 目的：制作二叉树的镜像，b为a的镜像
Status MirrorBiTree(BiTree a, BiTree *pb)
{
    // copy a to b
    ClearBiTree(pb);
    SqQueue Qa, Qb;
    InitQueue(&Qa); InitQueue(&Qb);
    EnQueue(&Qa, a);
    if (!(*pb = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
    (*pb)->lchild = NULL; (*pb)->rchild = NULL; (*pb)->parent = NULL;
    (*pb)->data = a->data;
    EnQueue(&Qb, *pb);
    BiTree tmpa, tmpb, tmpc;
    while (!QueueEmpty(Qa)) {
        DeQueue(&Qa, &tmpa);
        DeQueue(&Qb, &tmpb);
        if (tmpa->lchild) {
            EnQueue(&Qa, tmpa->lchild);
            if (!(tmpb->rchild = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
            tmpc = tmpb->rchild;
            tmpc->lchild = NULL;
            tmpc->rchild = NULL;
            tmpc->parent = tmpb;
            tmpc->data = tmpa->lchild->data;
            EnQueue(&Qb, tmpc);
        }
        if (tmpa->rchild) {
            EnQueue(&Qa, tmpa->rchild);
            if (!(tmpb->lchild = (BiTree)malloc(sizeof(BTNode)))) exit(OVERFLOW);
            tmpc = tmpb->lchild;
            tmpc->lchild = NULL;
            tmpc->rchild = NULL;
            tmpc->parent = tmpb;
            tmpc->data = tmpa->rchild->data;
            EnQueue(&Qb, tmpc);
        }
    }
    DestroyQueue(&Qa); DestroyQueue(&Qb);
    return OK;
}

// 返回给定树的根
BiTree Root(BiTree T)
{
    while (T->parent)
        T = T->parent;
    return T;
}

// 返回给定树的双亲
BiTree Parent(BiTree e)
{
    return e->parent;
}

// 根据数据查找结点
BiTree FindNode(BiTree T, TElemType e)
{
    // 这里为了方便，使用了遍历的方法
    nodefound = NULL;
    flagfound = 0;
    target = e;
    PreOrderTraverse(T, &FindBTNode);
    return nodefound;
}

// 返回给定树的兄弟
BiTree Sibling(BiTree T)
{
    if (!T) return NULL;
    BiTree parent = T->parent;
    if (parent) {
        if (parent->lchild == T) return parent->rchild;
        return parent->lchild;
    } 
    return NULL;
}

// 返回两棵树的祖先
BiTree Ancestor(BiTree T1, BiTree T2)
{
    BiTree ancestors[MAXDEPTH];
    int depth = 0;
    while (T1) {
        ancestors[depth] = T1;
        depth++;
        T1 = T1->parent;
    }
    while (T2) {
        for (int i = 0; i < depth; i++)
            if (T2 == ancestors[i]) return T2;
        T2 = T2->parent;
    }
    return NULL;
}

// 判断是否二叉排序树
int IsBST(BiTree T)
{
    BSTsize = 0;
    InOrderTraverse(T, &GetBSTdata);
    for (int i = 0; i < BSTsize-1; i++)
        if (BSTdatas[i] > BSTdatas[i+1]) return 0;
    return 1;
}

// 判断是否完全二叉树
int IsBCT(BiTree T)
{
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    int end = 0;
    BiTree tmp;
    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &tmp);
        if (!tmp->lchild && tmp->rchild) return 0;
        if (end && (tmp->lchild || tmp->rchild)) return 0;
        if ((!tmp->lchild && !tmp->rchild) || (tmp->lchild && !tmp->rchild)) end = 1;
        if (tmp->lchild) EnQueue(&Q, tmp->lchild);
        if (tmp->rchild) EnQueue(&Q, tmp->rchild);
    }
    DestroyQueue(&Q);
    return 1;
}

// private function definition
Status FreeBTNode(BiTree T)
{
    free(T);
    return OK;
}

Status CountBTNode(BiTree T)
{
    if (T) nodenum++;
    return OK;
}

Status CountLeaf(BiTree T)
{
    if (T && !T->lchild && !T->rchild) leafnum++;
    return OK;
}

Status HWBiTree(BiTree T, int *height, int *width)
{
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    int curlevel = 0, curlevelnode = 1, nextlevelnode = 0, levelnodemax = 1;
    BiTree tmp;
    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &tmp);
        curlevelnode--;
        if (tmp->lchild) {EnQueue(&Q, tmp->lchild); nextlevelnode++; }
        if (tmp->rchild) {EnQueue(&Q, tmp->rchild); nextlevelnode++; }
        if (curlevelnode == 0) {
            curlevelnode = nextlevelnode;
            levelnodemax = (levelnodemax < nextlevelnode) ? nextlevelnode : levelnodemax;
            curlevel++;
            nextlevelnode = 0;
        }
    }
    *height = curlevel;
    *width = levelnodemax;
    return OK;
}

Status FindBTNode(BiTree T)
{
    if (!flagfound && T->data == target) {
        nodefound = T;
        flagfound = 1;
    } 
        return OK;
}

Status GetBSTdata(BiTree T)
{
    BSTdatas[BSTsize] = T->data;
    BSTsize++;
    return OK;
}
