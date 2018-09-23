#include <stdio.h>
#include "Stack_Sq.h"


int CheckPar(char *);  // 检查表达式的括号是否匹配
float ReadFloat(char *, int *);
int main(void)
{
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    getline(&line, &linecap, stdin);
    printf("%d\n", CheckPar(line));
    return 0;
}

int CheckPar(char *expr)
{
    char *c = expr;
    SqStack par;
    InitStack(&par);
    while (*c != '\0') {
        if (*c == '(') Push(&par, 0);
        if (*c == ')') {
            if (StackEmpty(par)) return 0;
            int i = -1;
            Pop(&par, &i);
            if (i != 0) return 0;
        }
        c++;
    }
    if (StackEmpty(par)) return 1;
    else return 0;
}

float ReadFloat(char *pc, int *incr)
{
    
}
