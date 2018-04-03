#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Status.h"

typedef struct term{
	float coef;
	int expn;
	struct term *next;
} *polynomial;

void CreatPolyn (polynomial *, int);
Status DestroyPolyn (polynomial );
Status ClearPolyn (polynomial );
void PrintPolyn (polynomial );
int PolynLength (polynomial );
void AddPolyn (polynomial , polynomial );
void SubtractPolyn (polynomial, polynomial);
Status CalcValue (polynomial, float, float *);
Status AddTerm (polynomial , float, int);
Status LocateTerm (polynomial , term, int *);
#endif
