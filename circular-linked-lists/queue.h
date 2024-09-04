#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Command{
    char *info;
    struct Command *prev, *next;
} TCommand, *TListCommand;

typedef struct queue {
    TListCommand first, last;
} TQueue;

TQueue* InitQ () ;
int ExtrQ(TQueue *c, char *x);
int ExtrQ_Switched(TQueue *c, char *x);
int IntrQ(TQueue *c, char *x);
void DistrQ(TQueue **c);

void PrintQ(TQueue *c);

#endif /* QUEUE_H */