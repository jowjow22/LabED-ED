#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct lista
{
  int chave;
  struct lista *prox;
} TipoListaCircular;

void insereCircular(TipoListaCircular **p, int info)
{
  assert(p);
  if (*p == NULL)
  {
    *p = (TipoListaCircular *)malloc(sizeof(TipoListaCircular));
    if (*p != NULL)
    {
      (*p)->chave = info;
      (*p)->prox = *p;
    }
  }
  else
  {
    TipoListaCircular *aux = (TipoListaCircular *)malloc(sizeof(TipoListaCircular));
    if (aux == NULL)
      return;
    aux->chave = info;
    aux->prox = (*p)->prox;
    (*p)->prox = aux;
  }
}
void removeCircular(TipoListaCircular **p)
{
  assert(p);
  if (*p == NULL)
  {
    printf("Lista vazia!");
    return;
  }
  TipoListaCircular *pPrim = (*p)->prox;
  TipoListaCircular *pPenult = (*p)->prox;
  if (pPrim->prox != pPrim)
  {
    while (pPenult->prox != *p)
    {
      pPenult = pPenult->prox;
    }
    free(*p);
    *p = pPenult;
    pPenult->prox = pPrim;
  }
  else
  {
    free(*p);
    *p = NULL;
  }
}

void imprime(TipoListaCircular *p)
{
  TipoListaCircular *aux = p->prox;
  if (p == NULL)
    printf("\nLista Vazia!");
  do
  {
    printf("\n%d", aux->chave);
    aux = aux->prox;
  } while (p != aux);
  printf("\n%d", p->chave);
}

int main()
{
  TipoListaCircular *lista = NULL;
  insereCircular(&lista, 89);
  insereCircular(&lista, 25);
  insereCircular(&lista, 44);
  insereCircular(&lista, 23);
  insereCircular(&lista, 19);
  insereCircular(&lista, 225);
  insereCircular(&lista, 464);
  insereCircular(&lista, 293);
  imprime(lista);
  //	removeCircular(&lista);
  //	printf("\n%d", lista->chave);
}