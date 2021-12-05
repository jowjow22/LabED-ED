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

void locatedInsertion(Node **first, int searchNodePos, int newNodeKey)
{
  assert(first);
  Node *auxNode = *first;
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
  Comentários da Função base de insercao na metade, ou insercao localizada:
  Essa função recebe como parametro, o ponteiro de ponteiro para o primeiro node da lista, a posição que deseja ser inserida após e a chave do novo node.
  É criado um ponteiro auxiliar que recebe o endereço do primeiro nó da lista, após isso é criado um for que caminha até a posição desejada
  passando de node em node, em todas as voltas do laço, ele verifica se o nó atual tem valor nulo, caso tenha, ou a lista está vazia, ou a 
  posição desejada ainda não existe, sendo assim invalida. Caso a validação seja confirmada, ele verifica se o valor de i é igual ao desejado pelo
  usuário, caso seja, ele cria um ponteiro auxiliar que recebe o endereço do novo node, e assim define o proximo do meu novo node, como o
  próximo do meu node atual, e coloca o proximo do meu node atual como o node que acaba de ser criado, assim criando uma inserção localizada.
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

void locatedRemotion(Node **first, int removePos)
{
  Node *auxList = *first;
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
Nessa função recebemos o ponteiro de ponteiro para o primeiro node da lista, é criado um ponteiro auxiliar para podermos trabalhar com essa lista.
Após isso é criado um for que vai de 1, até o valor anterior ao desejado da remoção, e passa de nó em nó. A primeira coisa verificada é se a lista
é nula, caso não seja, ele verifica se o valor de I é igual a posição anterior a desejada, caso seja, ele cria um ponteiro auxliar para o proximo do
nó atual. Após isso é atribuido ao proximo do meu nó atual, o endereço de memória do nó posterior ao nó desejado na remoção. Por fim, libera-se a
memória do nó proximo ao atual(ou seja, o nó pedido na remoção)
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
      printf("\nkey: %d\n", first->key);
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
  printf("\n*************************\n");
  /*
  imprimo para verificar se tudo foi nos conformes
  */
  removeFirst(&first);
  printNodeList(first);
  printf("\n*************************\n");
  /*
  removo o primeiro e imprimo novamente para verificar
  */
  initInsert(&first, 3);
  initInsert(&first, 4);

  printNodeList(first);
  printf("\n*************************\n");

  locatedInsertion(&first, 123, 9);
  locatedInsertion(&first, 2, 9);
  printNodeList(first);
  printf("\n*************************\n");
  locatedRemotion(&first, 3);
  printNodeList(first);
  printf("\n*************************\n");

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
