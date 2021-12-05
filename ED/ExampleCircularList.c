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
void locatedInsertionCircular(Clist **pointer, int key, int pos)
{
  assert(pointer);
  Clist *aux = *pointer;
  for (int i = 0; i <= pos; i++, aux = aux->next)
  {
    if (i == pos)
    {
      Clist *newNode = (Clist *)malloc(sizeof(Clist));
      if (newNode != NULL)
      {
        newNode->key = key;
        newNode->next = aux->next;
        aux->next = newNode;
        return;
      }
      else
      {
        printf("Error in new node creation\n");
      }
    }
  }
  printf("Invalid position for this list!\n");
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

Clist *searchNode(Clist **pointer, int key)
{
  Clist *aux = (*pointer)->next;
  if (*pointer == NULL)
  {
    printf("Empty list\n");
    return NULL;
  }
  do
  {
    if (key == aux->key)
    {
      return aux;
    }
    aux = aux->next;
  } while (*pointer != aux);
  return NULL;
}
Clist *searchNodeByPos(Clist **pointer, int pos)
{
  Clist *aux = (*pointer)->next;
  int i = 1;
  if (*pointer == NULL)
  {
    printf("Empty list\n");
    return NULL;
  }
  do
  {
    if (i == pos)
    {
      return aux;
    }
    aux = aux->next;
    i++;
  } while (aux != *pointer);
  return NULL;
}

void locatedRemotion(Clist **pointer, int pos)
{
  Clist *aux = searchNodeByPos(pointer, pos - 1);
  if (aux != NULL)
  {
    Clist *toErase = aux->next;
    Clist *nextToErase = toErase->next;
    aux->next = nextToErase;
    free(toErase);
    toErase = NULL;
  }
  else
  {
    printf("Invalid position!\n");
  }
}

int main()
{
  Clist *list = NULL;
  Clist *searchResult = NULL;
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
  locatedInsertionCircular(&list, 123, 3);
  printList(list);
  printf("\n*************************\n");
  searchResult = searchNode(&list, 123);
  if (searchResult == NULL)
  {
    printf("Node not found!\n");
  }
  else
  {
    printf("Searched key: %d\n", searchResult->key);
  }
  printf("\n*************************\n");
  locatedRemotion(&list, 2);
  printList(list);
}