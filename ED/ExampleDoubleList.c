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

ListaE *listaE_insere(ListaE *p, int info)
{
  ListaE *novo = (ListaE *)malloc(sizeof(ListaE));
  novo->info = info;
  novo->prox = p;
  novo->ant = NULL;
  if (p != NULL)
    p->ant = novo;
  return novo;
}

DWList *insertInList(DWList *first, int key)
{
  DWList *newNode = (DWList *)malloc(sizeof(DWList));
  newNode->key = key;
  newNode->next = first;
  newNode->previous = NULL;
  if (first != NULL)
  {
    first->previous = newNode
  }
  return newNode;
}

void listaE_imprime(ListaE *p)
{
  ListaE *paux;
  if (p == NULL)
    printf("\nLista vazia!");
  for (paux = p; paux != NULL; paux = paux->prox)
    printf("\n%d", paux->info);
}

void listaE_imprime2(ListaE *p)
{
  ListaE *paux;
  if (p == NULL)
    printf("\nLista vazia!");
  for (paux = p; paux != NULL; paux = paux->ant)
    printf("\n%d", paux->info);
}
ListaE *listaE_busca(ListaE *p, int elem)
{
  ListaE *paux;
  for (paux = p; paux != NULL; paux = paux->prox)
    if (paux->info == elem)
      return paux;
  return NULL;
}

ListaE *listaE_remove(ListaE **p, int elem)
{
  ListaE *apagar, *anterior, *proximo;
  apagar = listaE_busca(*p, elem);
  if (apagar == NULL)
    printf("\nElemento nao encontrado!");
  else
  {
    if (apagar == *p)
    {
      *p = apagar->prox;
      (*p)->ant = NULL;
      free(apagar);
    }
    else
    {
      anterior = apagar->ant;
      proximo = apagar->prox;
      anterior->prox = apagar->prox;
      proximo->ant = apagar->ant;
      free(apagar);
      apagar = NULL;
    }
  }
}

int main()
{
  ListaE *prim = NULL, *ult = NULL;
  prim = listaE_insere(prim, 9);
  ult = prim;
  prim = listaE_insere(prim, 3);
  prim = listaE_insere(prim, 2);
  prim = listaE_insere(prim, 7);
  listaE_imprime(prim);
  listaE_remove(&prim, 7);
  listaE_imprime(prim);
  prim = listaE_insere(prim, 13);
  listaE_imprime(prim);
}
