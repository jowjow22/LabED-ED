#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
  int key;
  struct Node *next;
} Node;

/*
 Usando a lista simples como referencia, a lista com cabeça não possui diferenças em seu struct
 estou usando uma linguagem com falta de acentos e outras coisas algumas vezes por conta do meu teclado.
 */

Node *createList()
{
  Node *header = (Node *)malloc(sizeof(Node));
  if (header == NULL)
  {
    return NULL;
  }
  else
  {
    header->key = -1; //reservado
    header->next = NULL;
    return header;
  }
}

/*
A primeira diferenca que vemos é a funcao que cria a lista, pois a lista com cabeca nunca vai estar vazia, pois é criado um no
cabeca em tempo de execucao. Nessa funcao é alocado dinamicamente um nó, caso tenha conseguido alocar, ele insere o valor -1
que é um valor reservado do sistema criado pelo programador, e define-se o proximo como nulo, e por fim, retorno o nó cabeça da funcao
*/

Node *allocates(int key)
{
  Node *newNode;
  newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL)
  {
    return NULL;
  }
  else
  {
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
  }
}

/*
  A função aloccates nao tem diferença entre a lista com cabeça e a lista simples
*/
void initInsert(Node *list, int key)
{

  Node *newNode;
  newNode = allocates(key);
  if (newNode == NULL)
  {
    return;
  }
  else
  {
    newNode->next = list->next;
    list->next = newNode;
  }
}

/*
  A primeira diferenca é o parametro da função, que em vez de receber um ponteiro de ponteiro, recebe apenas o ponteiro, ja que a lista
  nunca será vazia, tendo sempre o primeiro nó criado em tempo de execucao. Ele verifica se o novo nó alocado é nulo, caso nao seja, ele
  atribui o proximo nó, desse nó criado, como o primeiro nó da lista (sem ser o cabeça), e após isso, ele coloca o proximo nó depois do 
  no cabeça, como a primeira posiçao atualizada que foi criada acima dele
*/

void locatedInsertion(Node *first, int searchNodePos, int newNodeKey)
{
  assert(first);
  Node *auxNode = first;
  for (int i = 1; i <= searchNodePos; i++, auxNode = auxNode->next)
  {
    if (auxNode != NULL)
    {
      if (i == searchNodePos)
      {
        Node *auxNewNode = allocates(newNodeKey);
        auxNewNode->next = auxNode->next;
        auxNode->next = auxNewNode;
      }
    }
    else
    {
      printf("Invalid position for this list size!\n");
      break;
    }
  }
}
/*
  A unica diferença é que ela recebe um ponteiro, em vez de um ponteiro de ponteiro, já que na main, passamos o ponteiro do proximo e não o 
  ponteiro inicial
*/

void printNodeList(Node *first)
{
  while (first != NULL)
  {
    printf("Key:%d\n", first->key);
    first = first->next;
  }
}

/*
   A unica diferença nessa função é que ela não precisa verificar se a lista é vazia, ja que sempre existirá o nó cabeça
*/
Node *searchNode(Node *first, int key)
{
  Node *auxNode = first;
  while (auxNode != NULL)
  {
    if (auxNode->key == key)
    {
      return auxNode;
    }
    else
    {
      auxNode = auxNode->next;
    }
  }
  return NULL;
}
/*
  A unica diferença é que ela recebe um ponteiro, em vez de um ponteiro de ponteiro, já que na main, passamos o ponteiro do proximo e não o 
  ponteiro inicial
*/

void removeFirst(Node **first)
{
  assert(first);
  if (*first == NULL)
  {
    return;
  }
  else
  {
    Node *auxNode = *first;
    *first = (*first)->next;
    free(auxNode);
  }
}
/*
   não há diferenças
*/
void locatedRemotion(Node *first, int removePos)
{
  Node *auxList = first;
  for (int i = 1; i < removePos; auxList = auxList->next, i++)
  {
    if (auxList != NULL)
    {
      if (i == removePos - 1)
      {
        Node *auxNext = auxList->next;
        auxList->next = auxNext->next;
        free(auxNext);
        auxNext = NULL;
      }
    }
    else
    {
      return;
    }
  }
}
/*
  A unica diferença é que ela recebe um ponteiro, em vez de um ponteiro de ponteiro, já que na main, passamos o ponteiro do proximo e não o 
  ponteiro inicial
*/

int main()
{
  Node *first = createList();
  Node *searchResult;

  initInsert(first, 3);
  initInsert(first, 212);
  initInsert(first, 7);
  locatedInsertion(first->next, 2, 32);
  printNodeList(first->next);
  locatedRemotion(first->next, 2);
  printf("\n*************************\n");
  printNodeList(first->next);
  printf("\n*************************\n");
  //A diferenca aqui é que sempre passamos um a frente do nó cabeca nas funcoes
  searchResult = searchNode(first->next, 212);
  //A diferenca aqui é que sempre passamos um a frente do nó cabeca nas funcoes
  if (searchResult == NULL)
    printf("\nno nao encontrado\n");
  else
    printf("\nsearched key: %d\n", searchResult->key);
  printf("\n*************************\n\n");
  removeFirst(&first->next);
  //A diferenca aqui é que sempre passamos um a frente do nó cabeca nas funcoes
  printNodeList(first->next);
  printf("\n*************************\n");
  //A diferenca aqui é que sempre passamos um a frente do nó cabeca nas funcoes
}
