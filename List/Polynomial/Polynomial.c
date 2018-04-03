#include "Polynomial.h"
#include "Status.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void CreatPolyn (polynomial *P, int m)
{
    *P = (polynomial)malloc(sizeof(term));
    (*P)->coef = 0.0;
    (*P)->expn = -1;
    (*P)->next = NULL;

	if (m > 0) printf("input poly(m=%d):\n", m);
	for (int i = 0; i < m; i++) {
		float coef = 0.0;
		int expn = 0;
		scanf("%f %d ", &coef, &expn);
		AddTerm(*P, coef, expn);
	}
}

Status LocateTerm (polynomial P, term e, int *q)
{
    if (P->next == NULL) {
	*q = -1;
	return FALSE;
    }

    term *t = P->next;
    int pos = 1;
    while (t) {
	if (t->expn == e.expn) {
	    *q = pos;
	    return TRUE;
	}
	else {
	    pos++;
	    t = t->next;
	}
    }
    return TRUE;
}

void PrintPolyn (polynomial P)
{
    term *t = P->next;
    if (!P->next) printf("NULL\n");
    else {
	while (t) {
	    printf("%.2f*x(%d) ", t->coef, t->expn);
	    t = t->next;
	}
	printf("\n");
    }
}

Status AddTerm (polynomial P, float coef, int expn)
{
    if (expn < 0 || coef == 0.0) return FALSE;
    if (!P->next) {
	term *t = (term *)malloc(sizeof(term));
	t->coef = coef;
	t->expn = expn;
	t->next = NULL;
	P->next = t;
    }
    else {
	term *eb = P;
	term *ef = P->next;
	while(ef) {
	    if (ef->expn == expn) {
		ef->coef += coef;
		if (ef->coef == 0.0) {
		    eb->next = ef->next;
		    free(ef);
		    ef = eb->next;
		}
		return TRUE;
	    }
	    if (ef->expn > expn) {
		term *t = (term *)malloc(sizeof(term));
		t->coef = coef;
		t->expn = expn;
		t->next = ef;
		eb->next = t;
		return TRUE;
	    }
	    eb = eb->next;
	    ef = ef->next;
	}
	if (!ef) {
	    term *t = (term *)malloc(sizeof(term));
	    t->coef = coef;
	    t->expn = expn;
	    t->next = NULL;
	    eb->next = t;
	}
    }
    return TRUE;
}

Status DestroyPolyn (polynomial P)
{
	if (!P) return ERROR;
	term *cur = P;
	term *forw = P->next;
	while (forw) {
	    free(cur);
	    cur = forw;
	    forw = forw->next;
	}
	free(cur);
	P = NULL;
	return OK;
}

int PolynLength (polynomial P)
{
    if (!P->next) return 0;
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

	printf("a%d, b%d, flag%d\n", a, b, flag);
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

	

