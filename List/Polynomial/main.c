#include <stdio.h>
#include <stdlib.h>
#include "Polynomial.h"

int main(void)
{
	polynomial pa;
	CreatPolyn(&pa,0);
	ClearPolyn(pa);
	PrintPolyn(pa);
	AddTerm(pa,1,2);
	ClearPolyn(pa);
	PolynLength(pa);
	return 0;
}
