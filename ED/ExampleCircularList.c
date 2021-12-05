#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct CircularList
{
  int key;
  struct CircularList *next;
} Clist;

void insertCircularList(Clist **pointer, int key)
{
  assert(pointer);
  if (*pointer == NULL)
  {
    *pointer = (Clist *)malloc(sizeof(Clist));
    if (*pointer != NULL)
    {
      (*pointer)->key = key;
      (*pointer)->next = *pointer;
    }
  }
  else
  {
    Clist *aux = (Clist *)malloc(sizeof(Clist));
    if (aux == NULL)
    {
      return;
    }
    aux->key = key;
    aux->next = (*pointer)->next;
    (*pointer)->next = aux;
  }
}

void remotionCircular(Clist **pointer)
{
  assert(pointer);
  if (*pointer == NULL)
  {
    printf("Empty list!\n");
    return;
  }
  Clist *pointerFirst = (*pointer)->next;
  Clist *pointerPenult = (*pointer)->next;
  if (pointerFirst->next != pointerFirst)
  {
    while (pointerPenult->next != *pointer)
    {
      pointerPenult = pointerPenult->next;
    }
    free(*pointer);
    *pointer = pointerPenult;
    pointerPenult->next = pointerFirst;
  }
  else
  {
    free(*pointer);
    *pointer = NULL;
  }
}

void printList(Clist *pointer)
{
  Clist *aux = pointer->next;
  if (pointer == NULL)
  {
    printf("Empty list\n");
  }
  do
  {
    printf("key:%d\n", aux->key);
    aux = aux->next;
  } while (pointer != aux);
  printf("key:%d\n", pointer->key);
}

int main()
{
  Clist *list = NULL;
  insertCircularList(&list, 89);
  insertCircularList(&list, 25);
  printList(list);
  printf("\n*************************\n");
  insertCircularList(&list, 31);
  insertCircularList(&list, 32);
  printList(list);
  printf("\n*************************\n");
  remotionCircular(&list);
  printList(list);
  printf("\n*************************\n");
}