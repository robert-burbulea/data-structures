#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

/* Test list vida */
#define ListaVida(L) (L == NULL)

typedef struct Cell{
    char info;
    struct Cell *next, *prev;
} TCell, *TList;


typedef struct Train{
    TList list;
    TList sentinel;
    TList mechanic;
} Train;



TList AlocCell(char elem);
TList InitList();
Train* InitTrain();
void PrintList(Train *t);
void IntrCell_Right(Train *p_Train, char elem);
void IntrCell_Left(Train *p_Train, char elem);
void MOVE_LEFT(Train *p_Train);
void MOVE_RIGHT(Train *p_Train);
void WRITE(Train *p_Train, char elem);
void CLEAR_CELL(Train *p_Train);
int Initial_state(Train *p_Train);
void CLEAR_ALL(Train *p_Train);
void INSERT_LEFT(FILE *out, Train *p_Train, char elem);
void INSERT_RIGHT(Train *p_Train, char elem);
void SHOW_CURRENT(FILE *out, Train *p_Train);
void SHOW(FILE *out, Train *p_Train);
void DestroyList(TList* aL);

#endif /* LIST_H */