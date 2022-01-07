/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <nome do(a) aluno(a)>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct {
  int id;
  float prioridade;
  int posicao;
} ELEMENTO, * PONT;

typedef struct {
  int elementosNoHeap;
  PONT* heap;
  PONT* referencias;
} FILADEPRIORIDADE, * PFILA;

PFILA criarFila();

int tamanho(PFILA f);

bool inserirElemento(PFILA f, int id, float prioridade);

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade);

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade);

PONT removerElemento(PFILA f);

bool consultarPrioridade(PFILA f, int id, float* resposta);

#define MAX 5

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->referencias = (PONT*) malloc(sizeof(PONT)*MAX);
  res->heap = (PONT*) malloc(sizeof(PONT)*MAX);
  int i;
  for (i=0;i<MAX;i++) {
    res->referencias[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}


bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
  for (int i=0;i<f->elementosNoHeap;i++){
    tam = tam + 1;
  }
  
  return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  //Verifica se o ID é um valor válido
  if(id < 0 || id >= MAX){
    return false;
  //e depois verifica se o mesmo id já não fora usado
  }else if (f->referencias[id] != NULL){
    return false;
  }

  //Alocação de memoria inicial da estrutura 
  PONT elemento = (PONT) malloc(sizeof(ELEMENTO));
  elemento->id = id;
  elemento->prioridade = prioridade;
  
  //Ajuste do novo tamanho da árvora e alocação do novo id nas referencias
  f->referencias[id] = elemento;
  f->elementosNoHeap = f->elementosNoHeap + 1;

  //Estrutura temporária para se percorrer o f->heap
  PONT aux;
  
  //Index auxliares
  int index = 1;
  int insertAux = 0;

  //Loop para encontrar o devido lugar de inserção do novo elemento
  if (f->heap[0] != NULL){
    aux = f->heap[0];
    while(prioridade < aux->prioridade ){
      aux = f->heap[index];
      index = index + 1;
      if (aux == NULL){
        break;
      }
    }
    insertAux = index - 1; // Valor da posição que deverá ser colocado
    elemento->posicao = insertAux;
  }

  //Loop para reordenar toda a Estrutura caso a prioridade do novo elemento
  //mude as ordens dos demais elementos
  for(int i = MAX-2; i >= insertAux; i--){

    if(f->heap[i] != NULL){
      f->heap[i]->posicao += 1;
      f->heap[i+1] = f->heap[i];
    }

  }
  //Finalmente se coloca novo elemento no array heap em seu devido lugar
  f->heap[insertAux] = elemento;

  //Retorna Verdadeiro
  return true;
}

void auxiliarPrioridade(PFILA f, int id, float novaPrioridade){

  // Está função irá retirar o elemento do id passado 
  // e o recolocar com um novo id aproveitando a ordenação da realizada
  // na função de inserção

  // Elementos auxiliares
  int indexAux = 1;
  PONT aux = f->heap[0];

  //Loop para encontrar o index auxiliar 
  while(aux->prioridade > novaPrioridade){
    aux = f->heap[indexAux];
    indexAux = indexAux + 1;
    if(aux->id == id){
      break; 
    } 
  }

  //REMOÇÃO E INSERÇÃO
  if(aux->id != id){

    //Retirada do elemento nas referencias 
    f->referencias[id] = NULL;

    //Diminuição do tamanho da estrutura pois ela será aumentada novamente
    //na reinserção 
    f->elementosNoHeap = f->elementosNoHeap - 1;

    // Index auxiliar para exclusão
    int indexDeExclusao;

    // Preenchendo o valor do index de exclusão
    for(indexAux = MAX-1; indexAux >= 0; indexAux--){
      indexDeExclusao = indexAux;
      if(f->heap[indexAux] != NULL && f->heap[indexAux]->id == id){
        break;
      }
    }

    // Excluindo o item e rearranjando o array 
    for(indexAux = indexDeExclusao; indexAux < MAX; indexAux++){
      if(f->heap[indexAux] != NULL && f->heap[indexAux+1] != NULL){
        // Mundança de posição dos elementos
        f->heap[indexAux] = f->heap[indexAux+1];
        f->heap[indexAux]->posicao = f->heap[indexAux]->posicao - 1;

      } else if(f->heap[indexAux+1] == NULL){

        f->heap[indexAux] = NULL;
      }
    }
    inserirElemento(f, id, novaPrioridade);

  } else{
    // Se a fila só tem um elemento basta editar 
    // sua prioridade, nada mais muda
    aux->prioridade = novaPrioridade;
  }
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  
  //Verifica se o ID é um valor válido
  if(id < 0 || id >= MAX){
    return false;
  //Primeiro verifica se o id existe na estrutura e depois se a nova prioridade selecionada é maior que a antiga
  } else if(f->referencias[id] == NULL || f->referencias[id]->prioridade >= novaPrioridade){  
    return false;
  } 

  //O melhor caminho será retirar o elemento da estrutura, organizar a estrutura,
  //para depois reaproveitar a função de inserção recolocando o elemento atualizado

  //Função que realiza retirada e recolocação do elemento modificado
  auxiliarPrioridade(f,id,novaPrioridade);

  //Retorna Verdadeiro
  return true;

}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  
    //Verifica se o ID é um valor válido
  if(id < 0 || id >= MAX){
    return false;
  //Primeiro verifica se o id existe na estrutura e depois se a nova prioridade selecionada é maior que a antiga
  } else if(f->referencias[id] == NULL || f->referencias[id]->prioridade <= novaPrioridade){  
    return false;
  } 

  //O melhor caminho será retirar o elemento da estrutura, organizar a estrutura,
  //para depois reaproveitar a função de inserção recolocando o elemento atualizado
  
  //Função que realiza retirada e recolocação do elemento modificado
  auxiliarPrioridade(f,id,novaPrioridade);

  //Retorna Verdadeiro
  return true;

}

PONT removerElemento(PFILA f){
  // Por meio do tamanho se verifica se é possível excluir elemento
  int tam = tamanho(f);
  if (tam == 0 ){
    return NULL; // Retorna NULL quando não há elementos a serem excluídos
  }

  // Ajustamos o novo tamanho que a fila terá e retiramos das referencias o seu ID
  f->referencias[f->heap[0]->id] = NULL;
  f->elementosNoHeap = f->elementosNoHeap - 1;

  //Criamos o elemento de resposta que será retornado e retirado do f->heap
  PONT resp = f->heap[0];

  //Loop para reorganizar toda a fila fazendo com que todos os elementos 
  //caminhem um elemento para trás já que o atendido é o primeiro da fila
  for(int i = 0; i < MAX; i++){

    if(f->heap[i] != NULL && f->heap[i+1] != NULL){

      f->heap[i] = f->heap[i+1];
      f->heap[i]->posicao = f->heap[i]->posicao - 1;

    }else{
      //quando chega ao final da fila e toda a estrutura já foi rearranjada
      f->heap[i] = NULL;

    }

  }
  // Retorno do elemento retirado da fila
  return resp;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  
  //Verificação padrão se o id é valido e se ele existe dentro da estrutura
  if (id < 0 || id >= MAX || f->referencias[id] == NULL){
    return false;
  } 

  //Alocação do ponteiro resposta com a prioridade do Id selecionado
  *resposta = f->referencias[id]->prioridade;

  //Retorna Verdadeiro
  return true;
}

int main() {
  PFILA f = criarFila();
  exibirLog(f);
  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (1)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (2)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (3)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0)) printf("ok\n");
  else printf("nok (4)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (5)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 5, 10)) printf("ok\n");
  else printf("nok (6)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 0, 15)) printf("ok\n");
  else printf("nok (7)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (8)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (9) - esperado, pois a nova prioridade nao eh maior\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 4, 4)) printf("ok\n");
  else printf("nok (10) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);
  
  PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (1)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (2)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (3)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (4)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (5)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (6)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (7)\n");
  exibirLog(f);

  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (10)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (12)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0.5)) printf("ok\n");
  else printf("nok (13)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (14)\n");
  exibirLog(f);

  printf("\n\nReduzindo prioridade\n");


  if(reduzirPrioridade(f, 5, 0)) printf("ok\n");
  else printf("nok (15)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 0, 1)) printf("ok\n");
  else printf("nok (16) - esperado, nova prioridade eh maior\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 2)) printf("ok\n");
  else printf("nok (17)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 1.5)) printf("ok\n");
  else printf("nok (18) - esperado, nova prioridade eh igual\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 4, 1)) printf("ok\n");
  else printf("nok (19) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);



  return 0;
}