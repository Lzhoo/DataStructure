#include "Polynomial.h"
#include "../../Status.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

polynomial CreatePolyn (int m)
{
    polynomial P;
    if (!(P=(polynomial)malloc(sizeof(term)))) exit(OVERFLOW);
    P->coef = 0.0;
    P->expn = -1;
    P->next = NULL;
    
    if (m > 0) {
        printf("input polyn(m=%d):\n", m);
        float coef = 0.0;
        int expn = 0;
        int i = 0;
        while (i < m && scanf("%f%d", &coef, &expn)) {
            AddTerm(P, coef, expn);
            i++;
            }
    }
    return P;
}

void PrintPolyn (polynomial P)
{
    if (!P) printf("NULL\n");
    else {
        term *t = P->next;
        while (t) {
            printf("%.2f*x(%d) ", t->coef, t->expn);
            t = t->next;
        }
        printf("\n");
    }
}

Status AddTerm (polynomial P, float coef, int expn)
{
    if (!P || expn < 0 || coef == 0.0) return FALSE;
    term *eb = P;
    term *ef = P->next;
    while(ef) {
        // insert the new term
        if (ef->expn > expn) {
        term *t; 
        if (!(t=(term *)malloc(sizeof(term)))) exit(OVERFLOW);
        t->coef = coef;
        t->expn = expn;
        t->next = ef;
        eb->next = t;
        return TRUE;
        }
        // add coefs when same expn
        if (ef->expn == expn) {
        ef->coef += coef;
        if (ef->coef == 0.0) {
            eb->next = ef->next;
            free(ef);
            ef = eb->next;
        }
        return TRUE;
        }
        eb = eb->next;
        ef = ef->next;
    }
    // insert the new term to the tail
    if (!ef) {
        term *t; 
        if (!(t=(term *)malloc(sizeof(term)))) exit(OVERFLOW);
        t->coef = coef;
        t->expn = expn;
        t->next = NULL;
        eb->next = t;
    }
    return TRUE;
}

Status DelTerm (polynomial P, int expn)
{
    if (!P) return ERROR;
    term *eb = P, *ef = P->next;
    while (ef) {
        if (ef->expn == expn) {
            eb->next = ef->next;
            free(ef);
            return TRUE;
        }
        if (ef->expn > expn) return ERROR;
        eb = eb->next;
        ef = ef->next;
    }
    return ERROR;
}

Status SetCoef (polynomial P, float coef, int pos)
{
    if (!P) return ERROR;
    term *eb = P, *ef = P->next;
    int i = 1;
    while (ef) {
        if (i == pos) {
            if (coef == 0) {eb->next = ef->next; free(ef);}
            else {ef->coef = coef;}
            return TRUE;
        }
        i++;
        eb = eb->next;
        ef = ef->next;
    }
    return ERROR;
}

Status SetExpn (polynomial P, int expn, int pos)
{
    if (!P || expn < 0) return ERROR;
    term *eb = P, *ef = P->next;
    int i = 1;
    float coef = 0.0;
    while (ef) {
        if (i == pos) {
            eb->next = ef->next;
            coef = ef->coef;
            free(ef);
            break;
        }
        i++;
        eb = eb->next;
        ef = ef->next;
    }
    if (coef == 0.0) return ERROR;
    AddTerm(P, coef, expn);
    return TRUE;
}
Status DestroyPolyn (polynomial *P)
{
    if (!(*P)) return ERROR;
    term *cur = *P;
    term *forw = (*P)->next;
    while (forw) {
        free(cur);
        cur = forw;
        forw = forw->next;
    }
    free(cur);
    *P = NULL;
    return OK;
}

int PolynLength (polynomial P)
{
    if (!P || !P->next) return 0;
    term *t = P->next;
    int len = 0;
    while (t) {
    t = t->next;
    len++;
    }
    return len;
}

void AddPolyn (polynomial Pa, polynomial Pb)
{
    term *qa = Pa->next;
    term *qb = Pb->next;
    term *ha = Pa, *hb = Pb; 
    while (qa && qb) {
    int a = qa->expn;
    int b = qb->expn;
    int flag;
    float sum;
    if (a < b) flag = -1;
    else {
        if (a == b) flag = 0;
        else flag = 1;
    }

    switch (flag) {
    case -1:       // qa->expn < qb->expn
        ha = qa;
        qa = qa->next;
        break;
    case 0:       // qa->expn == qb->expn
        sum = qa->coef + qb->coef;
        if (sum != 0.0) {
        qa->coef = sum;
        ha = qa;
        }
        else {
        ha->next = qa->next;
        free(qa);
        }
        hb->next = qb->next;
        free(qb);
        qb = hb->next;
        qa = ha->next;
        break;
    case 1:       // qa->expn > qb->expn
        hb->next = qb->next;
        qb->next = ha->next;
        ha->next = qb;
        qb = hb->next;
        qa = ha->next;
        break;
    }
    }
    if (qb) {
    ha->next = qb;
    }
    free(hb);
}

void SubtractPolyn (polynomial Pa, polynomial Pb)
{
    term *qb = Pb->next;
    while (qb) {
    qb->coef *= -1;
    qb = qb->next;
    }
    AddPolyn(Pa, Pb);
}

void MultiplyPolyn (polynomial Pa, polynomial Pb)
{
    term *e = Pb->next;
    polynomial Pa_copy = CreatePolyn(0);
    CopyPolyn(Pa, Pa_copy);
    while (e) {
        polynomial dummy = CreatePolyn(0);
        CopyPolyn(Pa_copy, dummy);
        term *t = dummy->next;
        while (t) {
            t->coef *= e->coef;
            t->expn += e->expn;
            t = t->next;
        }
        AddPolyn(Pa, dummy);
        Pb->next = e->next;
        free(e);
        e = Pb->next;
    }
    SubtractPolyn(Pa, Pa_copy);
}

void PowerPolyn (polynomial P, int n)
{
    if (P && P->next && n > 0) {
        polynomial P_copy = CreatePolyn(0);
        CopyPolyn(P, P_copy);
        int i = 1;
        while (i < n) {
            polynomial dummy = CreatePolyn(0);
            CopyPolyn(P_copy, dummy);
            MultiplyPolyn(P, dummy);
            i++;
        }
        DestroyPolyn(&P_copy);
    }
}
Status CalcValue (polynomial P, float x, float *result)
{
    if (!P || !P->next) return ERROR;
    *result = 0.0;
    term *q = P->next;
    while (q) {
        *result += q->coef * powf(x, q->expn);
        q = q->next;
    }
    return OK;
}

Status ClearPolyn (polynomial P)
{
    if (!P) return ERROR;
    if (!P->next) return OK;
    term *cur = P->next;
    term *forw = cur->next;
    while (forw) {
        free(cur);
        cur = forw;
        forw = forw->next;
    }
    free(cur);
    P->next = NULL;
    return OK;
}

void DerivePolyn (polynomial P1, polynomial P2, int n)
{
    if (n > 0 && CopyPolyn(P1,P2) == OK) {
        term *eb = P2, *ef = P2->next;
        while (ef && ef->expn < n) {
            eb->next = ef->next;
            free(ef);
            ef = eb->next;
        }
        while (ef) {
            for (int i = ef->expn; i > ef->expn-n; i--)
                ef->coef *= i;
            ef->expn -= n;
            ef = ef->next;
            eb = eb->next;
        }
    }
}

void IntPolyn (polynomial P1, polynomial P2, int n)
{
    if (n > 0 && CopyPolyn(P1, P2) == OK) {
        term *e = P2->next;
        while (e) {
            for (int i = e->expn+1; i < e->expn+n+1; i++)
                e->coef /= i;
            e->expn += n;
            e = e->next;
        }
    }
}

float DIntPolyn (polynomial P, int n, float start, float end)
{
    polynomial result = CreatePolyn(0);
    IntPolyn(P, result, n);
    float down, up;
    CalcValue(result, start, &down);
    CalcValue(result, end, &up);
    return up - down;
}

// Copy P1 to P2
Status CopyPolyn (polynomial P1, polynomial P2)
{
    if (P1 == P2 || PolynLength(P1) == 0 || ClearPolyn(P2) == ERROR) return ERROR;
    term *e1 = P1->next, *e2 = P2;
    while (e1) {
        term *t;
        if (!(t=(term *)malloc(sizeof(term)))) exit(OVERFLOW);
        t->expn = e1->expn;
        t->coef = e1->coef;
        t->next = NULL;
        e2->next = t;
        e1 = e1->next;
        e2 = e2->next;
    }
    return OK;
}

