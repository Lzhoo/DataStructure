#ifndef BITREE_H
#define BITREE_H
#include "Status.h"

typedef char TElemType;
typedef struct BTNode {
    TElemType data;
    struct BTNode *lchild, *rchild, *parent;
} BTNode, *BiTree;

Status CreateBiTree(BiTree* );
Status CreateCompleteBiTree(BiTree *);
Status PrintBiTree(BiTree );
Status ClearBiTree(BiTree *);
Status CopyBiTree(BiTree, BiTree *);
Status MirrorBiTree(BiTree, BiTree *);
Status PreOrderTraverse(BiTree, Status(*)(BiTree ) );
Status InOrderTraverse(BiTree, Status(*)(BiTree ) );
Status PostOrderTraverse(BiTree, Status(*)(BiTree ) );
Status LevelOrderTraverse(BiTree, Status(*)(BiTree ));
BiTree Root(BiTree );
BiTree Parent(BiTree);
BiTree FindNode(BiTree, TElemType);
BiTree Sibling(BiTree);
BiTree Ancestor(BiTree, BiTree);
int NodeNumBiTree(BiTree );
int LeafNumBiTree(BiTree );
int HeightBiTree(BiTree );
int WidthBiTree(BiTree );
int IsBST(BiTree);
int IsBCT(BiTree);
#endif
