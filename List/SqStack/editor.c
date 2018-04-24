#include "Stack_Sq.h"
#include <stdio.h>
#include <ctype.h>

void LineEdit (char *);
void PushToFile (SqStack *, FILE *);
int main(int argc, char *argv[])
{
    char *filename = NULL;
    if (argc == 2) filename = argv[1];
    if (filename) LineEdit(filename);
    return 0;
}

void LineEdit(char *filename)
{
    SqStack buf;
    InitStack(&buf);
    int c, dummy;
    FILE *save = fopen(filename, "r+");

    while ((c=fgetc(save)) != EOF)
        Push(&buf, c);
    
    while ((c=getchar()) != EOF) {
        switch (c) {
            case 35: {   // '#' is backspace
                if (!StackEmpty(buf)) Pop(&buf, &dummy);
                break;
            }
            case 64: {   // '@' is delete line
                while (GetTop(buf, &dummy)) {
                    if (dummy == 10) break;
                    Pop(&buf, &dummy);
                }
                if (!StackEmpty(buf)) Pop(&buf, &dummy);
                break;
            }
            default: Push(&buf, c);
        }
    }

    fclose(save);
    save = fopen(filename, "w");
    PushToFile(&buf, save);
    fclose(save);
}

void PushToFile (SqStack *pbuf, FILE *file)
{
    if (!StackEmpty(*pbuf)) {
        SqStack tmp;
        InitStack(&tmp);
        int c;
        while (Pop(pbuf, &c)) Push(&tmp, c);
        while (Pop(&tmp, &c)) fprintf(file, "%c", c);
        DestroyStack(&tmp);
    }
}
