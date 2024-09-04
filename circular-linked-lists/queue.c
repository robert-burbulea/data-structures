/*-- -- queue is represented as an open list*/
#include "queue.h"
#include "list.h"
#include <string.h>


* InitQ ()  /* create empty queue with elements of size d;*/
{ 
  TQueue* c;          /* queue descriptor space*/
  c = (TQueue*)malloc(sizeof(TQueue));
  if ( ! c ) return NULL;                  /* no space -> "fail" */

  c->first = c->last = NULL;
  return c;          /* returns queue descriptor address */
}

int IntrQ(TQueue *c, char *x)  /* add element at the back of the queue */
{ 
  TListCommand aux;
  aux = (TListCommand)malloc(sizeof(TCommand));      /* allocate new cell*/
  if (!aux) return -1;             /* impossible allocation -> "fail" */

  aux->info = (char*)malloc(sizeof(char*));
  strcpy(aux->info, x);

  aux->next = NULL;
  aux->prev = NULL;

  if (c->last != NULL) {             /* not empty queue */
    aux->prev = c->last;
    c->last->next = aux;                   /* -> links cell after the last cell from the queue */
  }          
  else {                             /* empty queue */
    c->first = aux;                    /* -> new cell is at the beginning of the queue */
  }
  c->last = aux;  	            /* update end of queue */
  return 1;                         /*  "succes" */
}

int ExtrQ(TQueue *c, char *x)  /* extracts first element from queue */
{ 
  if (c == NULL || c->first == NULL) return 0;
  TListCommand aux = c->first;
  strcpy(x, c->first->info);
  c->first = c->first->next;
  if (!c->first) {
    c->last = NULL;
  } else {
    c->first->prev = NULL;
  }

  free(aux->info);
  free(aux);
  return 1;
}

int ExtrQ_Switched(TQueue *c, char *x) {
    if (c == NULL || c->first == NULL) return 0;
    TListCommand aux = c->last;
    strcpy(x, c->last->info);
    c->last = c->last->prev;
    if (!c->last) {
      c->first = NULL;
    } else {
      c->last->next = NULL;
    }

    free(aux->info);
    free(aux);
    return 1;
}

void DistrQ(TQueue **c) /* destroy queue */
{
  TListCommand p, aux;
  p = (*c)->first;
  while(p)
  {
    aux = p;
    p = p->next;
    free(aux->info);
    free(aux);
  }
  free(*c);
  *c = NULL;
}

void PrintQ(TQueue *c)  /* print queue elements */
{
  TListCommand p;
  if(c->first == NULL)  /* null queue */
  {
    printf("Null queue\n");
    return;
  } 
  printf("Queue elements:\n");
  for(p = c->first; p != NULL; p = p->next)
    printf("%s\n", p->info);
  printf("\n");
}