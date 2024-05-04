#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
  int  reg;
  struct reg *esq;
  struct reg *dir;
  int altura;
} noh;

typedef struct arv {
  noh *topo;
} arvore;

noh *rotaciona_direita(noh *r);
noh *rotaciona_esquerda(noh *r);

arvore* aloca_arvore() {
  arvore *a = (arvore*) malloc(sizeof(arvore));
  a->topo = NULL;
  return a;
}

noh* aloca_noh(int num){
  noh *r = (noh*) malloc(sizeof(noh));
  r->reg = num;
  r->dir = NULL;
  r->esq = NULL;
  r->altura = 1;

  return r;
}

/**calculaFB(), Recebe um no atualiza altura, calcula e retorna o seu fator de balanceamento*/
int calcula_altura_e_fb(noh *arvNo){
  int sae =0,sad=0;

  if(arvNo->esq!=NULL){/*Se existir filho a esquerda*/
    sae=arvNo->esq->altura;/*Calcula altura da sae*/
  }

  if(arvNo->dir!=NULL){/*Se existir filho a direita*/
    sad=arvNo->dir->altura; /*Calcula altura da sad*/
  }

  // Atualiza altura
  arvNo->altura = sad - sae > 0 ? sad + 1: sae + 1;/*Calculando fator de balanceamento e retornando o resultado*/

  return sad - sae;
}

noh *rotaciona_direita(noh *r) {
  if(r->esq->dir != NULL) {
    r->esq = rotaciona_esquerda(r->esq);
  }
  noh *tmp_noh = r->esq;
  r->esq = NULL;
  tmp_noh->dir = r;

  return tmp_noh;
}

noh *rotaciona_esquerda(noh *r) {
  if(r->dir->esq != NULL) {
    r->dir = rotaciona_direita(r->dir);
  }
  noh *tmp_noh = r->dir;
  r->dir = NULL;
  tmp_noh->esq = r;

  return tmp_noh;
}

noh* arvBin_add_no(noh *r,int num){  
  // Caminha pela arvore até encontrar o local ideal para colocar o numero
  if(r->reg > num && r->esq != NULL){/*Se o registro atual da arvore for maior que o numero a ser adicionado, prossegue a busca a esquerda*/
    arvBin_add_no(r->esq, num);
  }else if(r->reg < num && r->dir != NULL){/*Se o registro atual da arvore for menor que o numero a ser adicionado, prossegue a busca a direita*/
    arvBin_add_no(r->dir, num);
  }

  noh *new_noh = aloca_noh(num);/*Alocando n� que ser� adicionado*/
  if(r->reg > num && r->esq == NULL)/*Adicionado n� a direita*/
    r->esq = new_noh;
  else if(r->reg < num &&  r->dir == NULL)/*Adicionado n� a esquerda*/
    r->dir = new_noh;
  
  // Volta a recursão recalculado valor dos nós
  int fb = calcula_altura_e_fb(r);
  if(fb > 1){
    /*Se estiver desbalanceado a direita, chama a rota��o a esquerda*/
    return rotaciona_esquerda(r);
  }else if(fb < -1){
    /*Se estiver desbalanceado a esquerda, chama a rota��o a direita*/
    return rotaciona_direita(r);
  }

  return r;
}

void arvBin_add(arvore *a,int num){
  if(a->topo != NULL) {
    a->topo = arvBin_add_no(a->topo, num);
  }else {
    a->topo = aloca_noh(num);
  }
}

void imprimi_arvBin(noh *arv){
  if(arv!=NULL){
    printf("<");
    if(arv->esq!=NULL)/*Prossegue pela SAE se ela existir*/
      imprimi_arvBin(arv->esq);
    else printf("()");

    printf("REG: %d h: %d ",arv->reg, arv->altura);/*Imprimindo valor do n�*/

    if(arv->dir!=NULL)/*Prossegue pela SAD se ela existir*/
      imprimi_arvBin(arv->dir);
    else printf("()");
    printf(">");
  }  
}

int main() {
  arvore *a = aloca_arvore();

  arvBin_add(a, 5000);  

  arvBin_add(a, 2000);

  arvBin_add(a, 4000);

  // arvBin_add(a, 7000);

  // arvBin_add(a, 1000);

  // arvBin_add(a, 500);

  // arvBin_add(a, 9000);

  // arvBin_add(a, 100);

  imprimi_arvBin(a->topo);

  
  return 0;
}