#include <stdio.h>
#include <stdlib.h>
#include "Polynomial.h"

void usage (void);
int main(void)
{
    int n1, n2;
    printf("f(x)有几项?\n");
    scanf("%d", &n1);
    polynomial f = CreatePolyn(n1);
    printf("g(x)有几项?\n");
    scanf("%d", &n2);
    polynomial g = CreatePolyn(n2);

    int op;
    int i = 1;
    while (i) {
        usage();
        scanf("%d", &op);
        switch (op) {
            case 0: i = 0; break;
            case 1: {
                printf("f(x) ");
                PrintPolyn(f);
                printf("g(x) ");
                PrintPolyn(g);
                break; 
            }
            case 2: {
                polynomial dummy_f = CreatePolyn(0);
                polynomial dummy_g = CreatePolyn(0);
                CopyPolyn(f, dummy_f);
                CopyPolyn(g, dummy_g);
                AddPolyn(dummy_f, dummy_g);
                PrintPolyn(dummy_f);
                DestroyPolyn(&dummy_f);
                break; 
            }
            case 3: {
                printf("> input term (coef expn)\n");
                float coef; int expn;
                scanf("%f%d", &coef, &expn);
                AddTerm(f, coef, expn);
                break; 
            }
            case 4: {
                printf("> input expn:\n");
                int expn;
                scanf("%d", &expn);
                DelTerm(f, expn);
                break;
            }
            case 5: {
                printf("> input new cofficient and position\n");
                float coef; int pos;
                scanf("%f%d", &coef, &pos);
                SetCoef(f, coef, pos);
                break;
            }
            case 6: {
                printf("> input new expn and position\n");
                int expn, pos;
                scanf("%d%d", &expn, &pos);
                SetExpn(f, expn, pos);
                break;
            }
            case 7: {
                printf("> input Derive n\n");
                int n;
                scanf("%d", &n);
                polynomial dummy = CreatePolyn(0);
                DerivePolyn(f, dummy, n);
                printf("f(x) ");
                PrintPolyn(f);
                printf("after Derive ");
                PrintPolyn(dummy);
                DestroyPolyn(&dummy);
                break;
            }
            case 8: {
                printf("> input Integrate n\n");
                int n;
                scanf("%d", &n);
                polynomial dummy = CreatePolyn(0);
                IntPolyn(f, dummy, n);
                printf("f(x) ");
                PrintPolyn(f);
                printf("after Integrate ");
                PrintPolyn(dummy);
                DestroyPolyn(&dummy);
                break;
            }
            case 9: {
                printf("> input Integrate n, start, end\n");
                int n;
                float start, end;
                scanf("%d%f%f", &n, &start, &end);
                printf("DInt output = %f\n", DIntPolyn(f, n, start, end));
                break;
            }
            case 10: {
                polynomial dummy_f = CreatePolyn(0);
                polynomial dummy_g = CreatePolyn(0);
                CopyPolyn(f, dummy_f);
                CopyPolyn(g, dummy_g);
                MultiplyPolyn(dummy_f, dummy_g);
                PrintPolyn(dummy_f);
                DestroyPolyn(&dummy_f);
                break;
            }
            case 11: {
                printf("> input power\n");
                int n;
                scanf("%d", &n);
                PowerPolyn(f, n);
                break;
            }
            case 12: {
                ClearPolyn(f);
                break;
            }
            case 13: {
                DestroyPolyn(&f);
                break;
            }
            default: break;
        }
    }
    return 0;
}

void usage (void)
{
    printf("Please input command: (0=quit, 1=display, 2=AddPolyn, 3=AddTerm, 4=DelTerm, 5=SetCoef, 6=SetExpn, 7=Derive, 8=Integrate, 9=DIntegrate, 10=Multiply, 11=Power, 12=Clear, 13=Destroy)\n");
}