#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct DoubleWayList
{
  int key;
  struct listaEnc *previous;
  struct listaEnc *next;
} DWList;
/*
esse struct tem a diferença de ter um outro ponteiro, ele tem um que aponta para o proximo e outro que aponta para o anterior
*/

// ListaE *listaE_insere(ListaE *p, int info)
// {
//   ListaE *novo = (ListaE *)malloc(sizeof(ListaE));
//   novo->info = info;
//   novo->prox = p;
//   novo->ant = NULL;
//   if (p != NULL)
//     p->ant = novo;
//   return novo;
// }

DWList *allocates(int key)
{
  DWList *newNodeAlloc = (DWList *)malloc(sizeof(DWList));
  if (newNodeAlloc == NULL)
  {
    return NULL;
  }
  else
  {
    newNodeAlloc->key = key;
    newNodeAlloc->next = NULL;
    newNodeAlloc->previous = NULL;
    return newNodeAlloc;
  }
}
/*
  a unica alteracao necessaria foi a adicao de uma nova atribuicao, no caso atribui-se nulo ao valor do ponteiro que referencia o anterior
  a ele.
*/

DWList *initInsert(DWList *first, int key)
{
  DWList *newNode = allocates(key);
  newNode->next = first;
  if (first != NULL)
  {
    first->previous = newNode;
  }
  return newNode;
}
/*
  Como estamos inserindo no inicio, e a posicao previa ja foi definida como nula, nao precisamos definir como nula novamente
  apenas atribuimos a proxima posiçao como a antiga primeira posicao da lista. Aqui temos uma alteracao na funcao, caso a lista
  nao esteja vazia, definimos o ponteiro anterior da primeira posicao da lista, como o novo Node que estamos criando
*/

void printNodeList(DWList *first)
{
  DWList *auxNode;
  if (first == NULL)
  {
    printf("Empty List\n");
  }
  else
  {
    for (auxNode = first; auxNode != NULL; auxNode = auxNode->next)
    {
      printf("Key: %d\n", auxNode->key);
    }
  }
}
void printNodeListBackway(DWList *last)
{
  DWList *auxNode;
  if (last == NULL)
  {
    printf("\nLista vazia!");
  }
  for (auxNode = last; auxNode != NULL; auxNode = auxNode->previous)
  {
    printf("Key: %d\n", auxNode->key);
  }
}

DWList *searchInList(DWList *first, int key)
{
  DWList *aux;
  for (aux = first; aux != NULL; aux = aux->next)
  {
    if (aux->key == key)
    {
      return aux;
    }
  }
  return NULL;
}

DWList *removeFromList(DWList **first, int key)
{
  DWList *toErase, *prev, *next;
  toErase = searchInList(*first, key);
  if (toErase == NULL)
  {
    printf("Element not found.\n");
  }
  else
  {
    if (toErase == *first)
    {
      *first = toErase->next;
      (*first)->previous = NULL;
      free(toErase);
      toErase = NULL;
    }
    else
    {
      prev = toErase->previous;
      next = toErase->next;
      prev->next = toErase->next;
      next->previous = toErase->previous;
      free(toErase);
      toErase = NULL;
    }
  }
}

int main()
{
  DWList *first = NULL, *last = NULL;
  first = initInsert(first, 9);
  last = first;
  first = initInsert(first, 3);
  first = initInsert(first, 2);
  first = initInsert(first, 7);
  printNodeList(first);
  printf("-------------------\n");
  removeFromList(&first, 3);
  printNodeList(first);
  printf("-------------------\n");
  first = initInsert(first, 13);
  printNodeList(first);
  printf("-------------------\n");
}
