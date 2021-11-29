#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node
{
  int key;
  struct Node *next;
} Node;

/*
  Comentários sobre a criação da struct de Nó para lista simples:
  A criação desse struct apenas requer uma chave para identificação, e um ponteiro
  para o proximo Node
*/

Node *allocates(int key)
{
  Node *newNodeAlloc = (Node *)malloc(sizeof(Node));
  if (newNodeAlloc == NULL)
  {
    return NULL;
  }
  else
  {
    newNodeAlloc->key = key;
    newNodeAlloc->next = NULL;
    return newNodeAlloc;
  }
}
/*
  Comentários da Função base de alocação:
  Essa função recebe como parâmetro a chave que é um campo do meu nó da lista encadeada,
  Ela cria uma alocação dinamica do tamanho de um tipo Node e verifica se conseguiu realizar
  a alocação, caso nao tenha conseguido, ela retorna nulo, caso tenha conseguido, ela atribui os valores
  de chave passados por parametro para a chave do novo Node alocado e o endereco do proximo Node como nulo
*/

void initInsert(Node **first, int key)
{
  assert(first);
  Node *auxPointer = allocates(key);
  if (auxPointer == NULL)
  {
    return;
  }
  else
  {
    auxPointer->next = *first;
    *first = auxPointer;
  }
}

/*
  Comentários da Função base de insercao no inicio:
  esta funcao tem como parametros o ponteiro de ponteiro do primeiro Node da lista, ela utiliza a funcao assert para
  verificar se existe lista, caso nao tenha, ele para a execuçao do programa, caso tenha, ele cria um ponteiro auxiliar
  que vai receber o retorno da funcao Allocates, ele verifica se o retorno foi nulo, caso seja, ele para a execucao da funcao,
  caso nao seja, ele pega o ponteiro next do ponteiro auxiliar e iguala ao endereco do primeiro ponteiro da lista, e iguala o primeiro
  ponteiro da lista, ao auxiliar, assim adicionando um a mais na primeira posicao.
*/

void locatedInsertion(Node **first, int searchKey, int newNodeKey)
{
  assert(first);
  Node *auxNewNode = allocates(newNodeKey);
  Node *auxNode = *first;
  while (auxNode != NULL)
  {
    if (auxNode->key == searchKey)
    {
      auxNewNode->next = auxNode->next;
      auxNode->next = auxNewNode;
      return;
    }
    else
    {
      auxNode = auxNode->next;
    }
  }
}

/*
  Comentários da Função base de insercao na metade, ou insercao localizada:
   esta funcao eh como uma mistura entre a insercao no inicio e a busca, ela recebe como parametro o ponteiro de ponteiro do primeiro
   elemento, a chave da qual voce quer inserir depois, e a chave do novo node, ela verifica se a lista nao é vazia, e caso nao seja, ela
   aloca o novo node, e cria um auxiliar para a lista, apos isso faz um laço para buscar na lista um node com a mesma chave pesquisada do 
   parametro, caso ele ache, ele define o proximo do novo node, como o proximo daquele node encontrado na lista, e define o proximo desse node
   encontrado, como o novo node criado.
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
  Comentários da Função base de remocao no inicio:
  a funcao recebe como parametro o ponteiro de ponteiro da primeira posicao da lista, apos isso ela verifica se esse parametro eh valido
  atraves da funcao assert, apos isso, ele verifica se existe uma lista, caso nao exista ele para a execucao da funcao, caso exista ele cria
  um ponteiro auxiliar, e passa o primeiro endereco pra ele, apos isso ele coloca o primeiro endereco como o endereco do proximo e após isso
  ele libera a memoria.
*/

Node *searchNode(Node **first, int key)
{
  Node *auxNode = *first;
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
  Comentários da Função base de pesquisa:
  Nesta funcao recebo como parametro o endereco do primeiro Nó da lista e a chave de pesquisa, apos isso, paso esse conteudo para um nó auxiliar
  e crio um laço que percorrerá toda a lista, verificando se a chave passada como parametro, é igual a que está sendo verificada no momento
  caso seja, ele retorna o nó atual, caso não, ele atribui o proximo nó ao meu nó auxiliar e verifica novamente
*/

void printNodeList(Node *first)
{
  if (first == NULL)
  {
    printf("\nLista Vazia!\n");
  }
  else
  {
    while (first != NULL)
    {
      printf("\n%d\n", first->key);
      first = first->next;
    }
  }
}

/*
  Comentários da Função base de impressão da lista:
  a funcao recebe como parametro o ponteiro para uma posicao da lista, com esse ponteiro ele verifica se ele corresponde a nulo, caso seja
  ele imprime a mensagem "Lista Vazia!", caso nao seja, ele inicia um laco de repeticao, percorrendo a lista ate que o valor de first
  seja nulo, dentro desse laco ele imprime o valor da chave e coloca o ponteiro first como o proximo ponteiro da lista.
*/

main()
{
  Node *first = NULL;
  initInsert(&first, 1);
  initInsert(&first, 2);
  /*
  aqui eu faço a inserçao de dois Nodes nessa lista, passando o endereço do ponteiro e sua respectiva chave
  */
  printNodeList(first);
  /*
  imprimo para verificar se tudo foi nos conformes
  */
  removeFirst(&first);
  printNodeList(first);
  /*
  removo o primeiro e imprimo novamente para verificar
  */
  initInsert(&first, 3);
  initInsert(&first, 4);

  locatedInsertion(&first, 3, 9);

  printNodeList(first);

  Node *searchResult = searchNode(&first, 3);
  if (searchResult == NULL)
  {
    printf("node not found\n");
  }
  else
  {
    printf("node key: %d\n", searchResult->key);
  }
  /*
  aqui é criado um ponteiro que recebe o retorno da função searchNode, caso esse retorno seja nulo, ele dirá que nao achou aquele nó
  caso não seja, ele exibe a chave daquele nó pesquisado
  */
}
