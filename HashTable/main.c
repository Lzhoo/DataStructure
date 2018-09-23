#include "../Status.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct {
    ElemType *elem;
    int count;
    int sizeindex;
}HashTable;

typedef struct ChainNode {
    ElemType elem;
    struct ChainNode *next;
} *Chain;

typedef struct {
    Chain *chainlist;
    int count;
    int sizeindex;
}ChainHash;

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define NULLKEY 9999
#define TOMBKEY 8888

// global variables
HashTable HT1;
ChainHash HT2;
ElemType keyseq[17] = {43, 71, 93, 35, 89, 05, 38, 90, 61, 30, 54, 39,
                       76, 85, 63, 22, 45};

Status CreateHash(HashTable *, int);
Status InsertHash(HashTable *, ElemType);
Status SearchHash(HashTable, ElemType, int *, int *);
Status DeleteHash(HashTable *, ElemType );
void PrintHash(HashTable);
Status DestroyHash(HashTable *);
Status CreateChainHash(ChainHash *, int);
Status InsertChainHash(ChainHash *, ElemType);
Status SearchChainHash(ChainHash, ElemType, Chain *, int *);
Status DeleteChainHash(ChainHash *, ElemType);
void PrintChainHash(ChainHash);
Status DestroyChainHash(ChainHash *);
int Hash(ElemType, int);
Status LinearDetect(int *, int);
void showhelp(void);
void ASL(void);

int main(void)
{
    CreateHash(&HT1, 23);
    CreateChainHash(&HT2, 23);
    for (int i = 0; i < 17; i++) {
        InsertHash(&HT1, keyseq[i]);
        InsertChainHash(&HT2, keyseq[i]);
    }
    int command;
    showhelp();
    scanf("%d",&command);
    while (command) {
        switch (command) {
            case 1: PrintHash(HT1); PrintChainHash(HT2); break;
            case 2: ASL(); break;
            case 3: {
                printf("input search item: ");
                int item;
                scanf("%d",&item);
                int pos, dummy;
                int i = Hash(item, 23);
                if (SearchHash(HT1, item, &pos, &dummy)) {
                    printf("HT1: SEARCH SUCCESS\n");
                    LinearDetect(&pos, HT1.sizeindex);
                    while (i != pos) {
                        if (HT1.elem[i] == NULLKEY) printf("N(%d) ",i);
                        if (HT1.elem[i] == TOMBKEY) printf("T(%d) ",i);
                        else printf("%d(%d) ",HT1.elem[i],i);
                        LinearDetect(&i, HT1.sizeindex);
                    }
                    printf("\n");
                }
                else {
                    printf("HT1: SEARCH FAILED\n");
                    i = Hash(item, 23);
                    while (HT1.elem[i] != NULLKEY) {
                        if (HT1.elem[i] == TOMBKEY) printf("T(%d) ",i);
                        else printf("%d(%d) ",HT1.elem[i],i);
                        LinearDetect(&i, HT1.sizeindex);
                    }
                    printf("N(%d)\n",i);
                }
                Chain c;
                if (SearchChainHash(HT2, item, &c, &dummy)) printf("HT2: SEARCH SUCCESS\n");
                else printf("HT2: SEARCH FAILED\n");
                i = Hash(item, 23);
                c = HT2.chainlist[i];
                printf("(%d)",i);
                while (c) {
                    printf("->%d",c->elem);
                    if (c->elem == item) break;
                    c = c->next;
                }
                printf("\n");
                break;
            }
            case 4: {
                printf("input delete item: ");
                int item;
                scanf("%d", &item);
                DeleteHash(&HT1, item);
                DeleteChainHash(&HT2, item);
                break;
            }
            case 5: {
                printf("input insert item: ");
                int item;
                scanf("%d", &item);
                InsertHash(&HT1, item);
                InsertChainHash(&HT2, item);
                break;
            }
            default : break;
        }
        showhelp();
        scanf("%d",&command);
    }
    DestroyHash(&HT1);
    DestroyChainHash(&HT2);
    return 0;
}

Status CreateHash(HashTable *pH, int size)
{
    if (!(pH->elem = (ElemType *)malloc(size*sizeof(ElemType)))) exit(OVERFLOW);
    for (int i = 0; i < size; i++)
        pH->elem[i] = NULLKEY;
    pH->count = 0;
    pH->sizeindex = size;
    return SUCCESS;
}

Status InsertHash(HashTable *pH, ElemType e)
{
    if (pH->count >= pH->sizeindex) return UNSUCCESS;
    int p = 0, c = 0;
    if (SearchHash(*pH, e, &p, &c)) return DUPLICATE;
    pH->elem[p] = e;
    pH->count++;
    return SUCCESS;
}

Status SearchHash(HashTable H, ElemType e, int *p, int *c)
{
    int firsttomb = -1, flag = 0;
    *p = Hash(e, 23);
    while (H.elem[*p] != NULLKEY && H.elem[*p] != e) {
        if (!flag && H.elem[*p] == TOMBKEY) { flag = 1; firsttomb = *p; }
        (*c)++;
        LinearDetect(p, H.sizeindex);
    }
    (*c)++;
    if (H.elem[*p] == e)
        return SUCCESS;
    else {
        if (flag) *p = firsttomb;
        return UNSUCCESS;
    }
}

Status DeleteHash(HashTable *pH, ElemType e)
{
    int p = 0, c = 0;
    if (!SearchHash(*pH, e, &p, &c)) return UNSUCCESS;
    pH->elem[p] = TOMBKEY;
    pH->count--;
    return SUCCESS;
}

void PrintHash(HashTable H)
{
    printf("count=%d, sizeindex=%d\n", H.count, H.sizeindex);
    for (int i = 0; i < H.sizeindex; i++)
        switch(H.elem[i]) {
            case NULLKEY: printf("N(%d) ", i); break;
            case TOMBKEY: printf("T(%d) ", i); break;
            default: printf("%d(%d) ", H.elem[i], i);
        }
    printf("\n");
}

Status DestroyHash(HashTable *pH)
{
    free(pH->elem);
    pH->elem = NULL;
    pH->count = 0;
    pH->sizeindex = 0;
    return SUCCESS;
}

Status CreateChainHash(ChainHash *pH, int size)
{
    if (!(pH->chainlist = (Chain *)malloc(size*sizeof(Chain)))) exit(OVERFLOW);
    for (int i = 0; i < size; i++)
        pH->chainlist[i] = NULL;
    pH->count = 0;
    pH->sizeindex = size;
    return SUCCESS;
}

Status InsertChainHash(ChainHash *pH, ElemType e)
{
    int p = Hash(e, 23);
    Chain back = pH->chainlist[p], forw = back;
    Chain tmp;
    if (!back) {
        if (!(tmp = (Chain)malloc(sizeof(struct ChainNode)))) exit(OVERFLOW);
        tmp->elem = e;
        tmp->next = NULL;
        pH->chainlist[p] = tmp;
    }
    else {
        forw = back->next;
        while (forw) {
            if (forw->elem > e) break;
            back = forw;
            forw = forw->next;
        }
        if (!(tmp=(Chain)malloc(sizeof(struct ChainNode)))) exit(OVERFLOW);
        tmp->elem = e;
        tmp->next = forw;
        back->next = tmp;
    }
    pH->count++;
    return SUCCESS;
}

Status SearchChainHash(ChainHash H, ElemType e, Chain *pC, int *c)
{
    int p = Hash(e, 23);
    Chain forw = H.chainlist[p];
    while (forw) {
        if (forw->elem != e) (*c)++;
        else { (*c)++; *pC = forw; return SUCCESS; }
        forw = forw->next;
    }
    return UNSUCCESS;
}

Status DeleteChainHash(ChainHash *pH, ElemType e)
{
    int p = Hash(e, 23);
    Chain back = pH->chainlist[p], forw = back;
    Chain tmp;
    if (!back) return UNSUCCESS;
    else {
        while (forw) {
            if (forw->elem == e) break;
            back = forw;
            forw = forw->next;
        }
        if (forw) {
            if (forw == back) pH->chainlist[p] = forw->next;
            else back->next = forw->next;
        }
        else back->next = NULL;
        free(forw);
    }
    pH->count--;
    return SUCCESS;
}

void PrintChainHash(ChainHash H)
{
    printf("count=%d, sizeindex=%d\n", H.count, H.sizeindex);
    for (int i = 0; i < H.sizeindex; i++) {
        if (!H.chainlist[i]) continue;
        printf("(%d)", i);
        Chain forw = H.chainlist[i];
        while (forw) {
            printf("->%d", forw->elem);
            forw = forw->next;
        }
        printf("\n");
    }
}
Status DestroyChainHash(ChainHash *pH)
{
    Chain forw;
    for (int i = 0; i < pH->sizeindex; i++) {
        forw = pH->chainlist[i];
        while (forw) {
            pH->chainlist[i] = forw->next;
            free(forw);
            forw = pH->chainlist[i];
        }
    }
    free(pH->chainlist);
    pH->count = 0;
    pH->sizeindex = 0;
    return SUCCESS;
}

int Hash(ElemType e, int n)
{ return e % n; }

Status LinearDetect(int *p, int size)
{
    if (*p >= size-1) *p = 0;
    else (*p)++;
    return SUCCESS;
}

void ASL(void)
{
    // success find
    int c1 = 0, c2 = 0;
    int p;
    Chain c;
    for (int i = 0; i < 17; i++) {
        SearchHash(HT1, keyseq[i], &p, &c1);
        SearchChainHash(HT2, keyseq[i], &c, &c2);
    }
    printf("HT1 SUCCESS ASL=%6.2f\n", (float) c1/HT1.count);
    printf("HT2 SUCCESS ASL=%6.2f\n", (float) c2/HT2.count);
    
    c1 = 0;
    for (int i = 0; i < HT1.sizeindex; i++) {
        int j = i;
        int length = 1;
        while (HT1.elem[j] != NULLKEY) {
            LinearDetect(&j, HT1.sizeindex);
            length++;
        }
        c1 += length;
    }
    
    c2 = 0;
    for (int i = 0; i < HT2.sizeindex; i++) {
        Chain dummy = HT2.chainlist[i];
        int length = 0;
        while (dummy) {
            length++;
            dummy = dummy->next;
        }
        c2 += length;
    }
    
    printf("HT1 FAILED ASL=%6.2f\n", (float) c1/HT1.sizeindex);
    printf("HT2 FAILED ASL=%6.2f\n", (float) c2/HT2.sizeindex);
}

void showhelp(void)
{
    printf("usage: 0=退出，1=打印，2=ASL，3=查找，4=删除，5=插入\n");
}
