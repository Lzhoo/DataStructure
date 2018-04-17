#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "../../Status.h"

typedef struct term{
	float coef;
	int expn;
	struct term *next;
} term, *polynomial;

polynomial CreatePolyn (int);
Status DestroyPolyn (polynomial *);
Status ClearPolyn (polynomial );
void PrintPolyn (polynomial );
int PolynLength (polynomial );
void AddPolyn (polynomial , polynomial );
void SubtractPolyn (polynomial, polynomial);
void MultiplyPolyn (polynomial, polynomial);
void PowerPolyn (polynomial, int);
void DerivePolyn (polynomial, polynomial, int);
void IntPolyn (polynomial, polynomial, int);
float DIntPolyn (polynomial, int, float, float);
Status CalcValue (polynomial, float, float *);
Status AddTerm (polynomial , float, int);
Status DelTerm (polynomial, int);
Status SetCoef (polynomial, float, int);
Status SetExpn (polynomial, int, int);
Status CopyPolyn (polynomial, polynomial );
#endif
