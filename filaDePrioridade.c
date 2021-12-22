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

#include "filaDePrioridade.h"
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
  PONT atual;
  int i;
  
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    tam = tam + 1;
  }
  
  return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual;
  for (int i = 0; i < f->elementosNoHeap; i++){
    atual = f->heap[i];

    if (atual->id == id){
      return atual;
    }
  }
	return NULL;
}


bool inserirElemento(PFILA f, int id, float prioridade){
  PONT x = buscarID(f,id);
  if (id < 0 || id >= MAX || x != NULL){
    return false;
  } 

  PONT aux = (PONT) malloc(sizeof(ELEMENTO));
  
  aux->id = id;
  aux->prioridade = prioridade;
  aux->posicao = tamanho(f);

  f->referencias[tamanho(f)] = aux;
  f->heap[tamanho(f)] = aux;
  f->elementosNoHeap = aux->posicao;
  
  return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  /* COMPLETAR */
  
  return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  /* COMPLETAR */
  
  return res;
}

PONT removerElemento(PFILA f){
  PONT res = NULL;
  
  /* COMPLETAR */
  
  return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool res = false;
  
  /* COMPLETAR */
  
  return res;
}

