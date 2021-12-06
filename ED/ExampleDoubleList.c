#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct DoubleWayList
{
  int key;
  struct DoubleWayList *previous;
  struct DoubleWayList *next;
} DWList;
/*
A primeira diferença notável é que temos dois ponteiros de struct, um apontando para o proximo, e outro para o anterior, por isso
duplamente encadeada
*/

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
Aqui a unica diferença é que foi adicionada uma nova atribuição, da qual é o ponteiro de anterior
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
  Como estamos inserindo no início, e a posição prévia já foi definida como nula, não precisamos definir como nula novamente
  apenas atribuímos a próxima posição como a antiga primeira posicao da lista,e atribuímos isso ao ponteiro da Main. Aqui temos
  uma alteração na função, caso a lista não esteja vazia, definimos o ponteiro anterior da primeira posição da lista, como o novo 
  Node que estamos criando
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
/*
Aqui temos uma alteração da qual não é necessária, em vez de usar o laço while, utilizamos o laço for, fazendo com que nosso aux percorra desde
a primeira posição, até que a lista seja nula, passando de nó em nó. Porém isso poderia ser feito com while também.
*/
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
/*
  Esta função serve para imprimir a lista de trás para frente. Ela recebe como parametro, o ultimo elemento da lista. Utilizando o laço for
  percorremos a lista desde o ultimo elemento atribuído, até que ele seja nulo, utilizando o campo previous ou anterior, da nossa lista duplamente
  encadeada.
*/

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

/*
  Esta função tem como diferenças principais, a utilização do laço for em vez de while para percorrer a lista, e támbem usa apenas um ponteiro
  em vez de um ponteiro de ponteiro. Ela realiza a busca por chave ou dado do struct.
*/

DWList *searchInListPosition(DWList *first, int pos)
{
  DWList *aux = first;
  for (int i = 1; i <= pos; i++, aux = aux->next)
  {
    if (aux != NULL)
    {
      if (i == pos)
      {
        return aux;
      }
    }
  }
  return NULL;
}

void locatedInsertion(DWList *first, int pos, int key)
{
  DWList *aux = searchInListPosition(first, pos - 1);
  if (aux != NULL)
  {
    DWList *newNode = allocates(key);
    newNode->next = aux->next;
    aux->next = newNode;
  }
  else
  {
    printf("Invalid Position!\n");
  }
}
/*
 Esta função foi criada para auxiliar na função de remover no meio, ela é uma busca que retorna o nó por posição, no arquivo de lista simples
 ela foi implementada juntamente da função que remove no meio, aqui somente foi separada para melhor organização, mas basicamente
 ela percorre a lista e verifica se a posição atual que é contada pelo contador i, é igual a posição desejada, caso seja, ela retorna o nó atual,
 caso não seja, ela retorna nulo
*/
DWList *removeFirst(DWList **first)
{
  DWList *aux = *first;
  DWList *newFirst = aux->next;
  if (aux != NULL)
  {
    free(aux);
    aux == NULL;
    newFirst->previous = NULL;
    return newFirst;
  }
  return NULL;
}
/*
  A principal diferença dessa função, é que criamos outro ponteiro auxiliar, para receber o próximo nó do primeiro, e com isso após removermos o primeiro
  nó, colocamos o anterior desse outro ponteiro como nulo.
*/
void removeFromList(DWList **first, int pos)
{
  DWList *toErase, *prev, *next;
  toErase = searchInListPosition(*first, pos);
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
      prev->next = next;
      next->previous = prev;
      free(toErase);
      toErase = NULL;
    }
  }
}
/*
  Esta função tem como diferenças principais, a utilização do laço for em vez de while para percorrer a lista, e támbem usa apenas um ponteiro
  em vez de um ponteiro de ponteiro.
*/

int main()
{
  DWList *first = NULL, *last = NULL;
  /*
  Temos uma 
  */
  first = initInsert(first, 9);
  last = first;
  first = initInsert(first, 3);
  first = initInsert(first, 2);
  first = initInsert(first, 7);
  printNodeList(first);
  printf("\n*************************\n");
  removeFromList(&first, 3);
  printNodeList(first);
  printf("\n*************************\n");
  first = initInsert(first, 13);
  printNodeList(first);
  first = removeFirst(&first);
  printf("\n*************************\n");
  printNodeList(first);
  printf("\n*************************\n");
  locatedInsertion(first, 2, 13);
  printNodeList(first);
  printf("\n*************************\n");
}
