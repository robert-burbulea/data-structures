#include "list.h"

/* Allocate a Cell and return pointer */
Tlist AlocCell(char elem) {
    Tlist aux = (Tlist) malloc(sizeof(TCell));   /* allcate */
    if (aux) {                                    /* aux != NULL */
        aux->info = elem;
        aux->next = NULL;
        aux->prev = NULL;
    }
    return aux;                                   /* return address or NULL */
}

Tlist Initlist() {
    Tlist s = (Tlist) malloc(sizeof(TCell));
    if (!s) return NULL;
    s->info = '\0';
    Tlist aux = (Tlist) malloc(sizeof(TCell));
    if (!aux) return NULL;

    aux->info = '#';
    aux->next = s;
    aux->prev = s;
    s->next = aux;
    s->prev = aux;
    return s;
}

Train* InitTrain() {
    Train *aux = (Train*)malloc(sizeof(Train));
    if (!aux) return NULL;
    aux->list = Initlist();
    aux->sentinel = aux->list;
    aux->mechanic = aux->list->next;
    aux->list = aux->list->next;
    return aux;
}

void IntrCell_Right(Train *p_Train, char elem) {
    Tlist x;

    Tlist aux = AlocCell(elem);
    if (!aux) return;
    aux->next = p_Train->mechanic->next;
    aux->prev = p_Train->mechanic;

    p_Train->mechanic->next->prev = aux;
    p_Train->mechanic->next = aux;
}

void IntrCell_Left(Train *p_Train, char elem) {
    Tlist x;

    Tlist aux = AlocCell(elem);
    if (!aux) return;
    aux->prev = p_Train->mechanic->prev;
    aux->next = p_Train->mechanic;

    p_Train->mechanic->prev->next = aux;
    p_Train->mechanic->prev = aux;
}

void MOVE_LEFT(Train *p_Train) {
    if (p_Train->mechanic == p_Train->sentinel->next) {
        p_Train->mechanic = p_Train->sentinel->prev;
    } else {
        p_Train->mechanic = p_Train->mechanic->prev;
    }
}

void MOVE_RIGHT(Train *p_Train) {
    if (p_Train->mechanic->next == p_Train->sentinel) {
        IntrCell_Right(p_Train, '#');
        p_Train->mechanic = p_Train->mechanic->next;
    } else {
        p_Train->mechanic = p_Train->mechanic->next;
    }
}

void WRITE(Train *p_Train, char elem) {
    p_Train->mechanic->info = elem;
}

void CLEAR_CELL(Train *p_Train) {
    if (p_Train->mechanic->prev == p_Train->sentinel &&
        p_Train->mechanic->next == p_Train->sentinel) {
        p_Train->mechanic->info = '#';
        return;
    }
    Tlist aux = p_Train->mechanic;
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    if (p_Train->mechanic->prev == p_Train->sentinel) {
        p_Train->mechanic = p_Train->mechanic->prev->prev;
    } else {
        p_Train->mechanic = p_Train->mechanic->prev;
    }

    aux->prev = NULL;
    aux->next = NULL;
    free(aux);
}

int Initial_State(Train *p_Train) {
    return (p_Train->mechanic->prev == p_Train->sentinel &&
            p_Train->mechanic->next == p_Train->sentinel &&
            p_Train->mechanic->info == '#');
}

void CLEAR_ALL(Train *p_Train) {
    int initial_state = 0;
    while (!initial_state) {
        CLEAR_CELL(p_Train);
        if (Initial_State(p_Train)) initial_state = 1;
    }
}

void INSERT_LEFT(FILE *out, Train *p_Train, char elem) {
    if (p_Train->mechanic->prev == p_Train->sentinel) {
        fprintf(out, "ERROR\n");
        return;
    }

    IntrCell_Left(p_Train, elem);
    p_Train->mechanic = p_Train->mechanic->prev;
}

void INSERT_RIGHT(Train *p_Train, char elem) {
    IntrCell_Right(p_Train, elem);
    p_Train->mechanic = p_Train->mechanic->next;
}

void SHOW_CURRENT(FILE *out, Train *p_Train) {
    fprintf(out, "%c\n", p_Train->mechanic->info);
}

void SHOW(FILE *out, Train *p_Train) {
    Tlist x;
    for (x = p_Train->sentinel->next; x != p_Train->sentinel; x = x->next) {
        if (x == p_Train->mechanic) {
            fprintf(out, "|%c|", x->info);
        } else {
            fprintf(out, "%c", x->info);
        }
    }
    fprintf(out, "\n");
}


/* Deallocate memory list */
void DestroyList(Tlist* aL) {
    Tlist aux;
    while (*aL) {           /* *aL != NULL, dereference address aL */
        aux = *aL;
        *aL = (*aL)->next;
        free(aux);
    }
}