#include <iostream>

using namespace std;

struct No { // DEFINICAO DO NO
  int Info; // INFORMACAO DO NO
  No* Esq; // PONTEIRO PARA SUBARVORE ESQ
  No* Dir; // PONTEIRO PARA SUBARVORE DIR
  int Altura; // Fator de balanceamento
};

typedef No* Arvore; // DEFINE TIPO ARVORE

void IniciaArvore (Arvore &); // INICIA A ARVORE
void InsereAbbRec (Arvore &, int); // INSERE NO - RECURSIVO
void Preordem (Arvore); // PERCURSO PRE-ORDEM
void Ordem (Arvore); // PERCURSO EM ORDEM
void Posordem (Arvore); // PERCURSO POS-ORDEM
bool ArvoreVazia (Arvore); // VERIFICA ARVORE VAZIA
void ApagaNo (Arvore &); // APAGA NO
void ApagaArvore (Arvore &); // APAGA ARVORE
int  ContaNos (Arvore); // CONTA NOS
int  CalculaFatorBalanceamento(Arvore); //CALCULA BALANCEAMENTO
void RotacionaEsquerda(Arvore &); // ROTACIONA A ESQUERDA
void RotacionaDireita(Arvore &); // ROTACIONA A DIREITA

// IMPLEMENTACAO DAS FUNCOES

// INICIA A ARVORE
void IniciaArvore(Arvore &Raiz){
  Raiz = nullptr;
}

// ARVORE VAZIA
bool ArvoreVazia (Arvore A){
   if(A!=nullptr)
    return false;
   return true;
}

// APAGA NO
void ApagaNo (Arvore &A){
  if(A == nullptr)
     return;
  ApagaNo(A->Esq);
  ApagaNo(A->Dir);
  delete A;
}

// APAGA ARVORE
void ApagaArvore (Arvore &A){
  if(A==nullptr)
     return;
  ApagaNo(A);
  IniciaArvore(A);
}

// Atuaiza da Arvore
void AtualizaAltura(Arvore &A){
  int FbEsq = 0, FbDir = 0;

  if(A->Esq != nullptr) {
    FbEsq = A->Esq->Altura;
  }

  if(A->Dir != nullptr) {
    FbDir = A->Dir->Altura;
  }

  if(FbEsq > 0 || FbDir > 0) {
    A->Altura = FbDir - FbEsq > 0 ? FbDir + 1 : FbEsq + 1;
  } else {
    A->Altura = 1;
  }
}

// CALCULA FATOR DE BALANCEAMENTO
int CalculaFatorBalanceamento(Arvore A) {
  int FbEsq = 0, FbDir = 0;

  if(A->Esq != nullptr) {
    FbEsq = A->Esq->Altura;
  }

  if(A->Dir != nullptr) {
    FbDir = A->Dir->Altura;
  }

  return FbDir - FbEsq;
}

void RotacionaDireita(Arvore &A){
  if(A->Esq->Dir != nullptr && A->Esq->Esq == nullptr) {
    RotacionaEsquerda(A->Esq);
    AtualizaAltura(A->Esq);
  }

  Arvore Aux = A->Esq;
  A->Esq = Aux->Dir;
  Aux->Dir = A;

  AtualizaAltura(A);
  AtualizaAltura(Aux);
  A = Aux; 
}

void RotacionaEsquerda(Arvore &A){
  if(A->Dir->Esq != nullptr && A->Dir->Dir == nullptr) {
    RotacionaDireita(A->Dir);
    CalculaFatorBalanceamento(A->Dir);
  }
  Arvore Aux = A->Dir;
  A->Dir = Aux->Esq;
  Aux->Esq = A;

  CalculaFatorBalanceamento(A);
  A = Aux;
}

// INSERCAO DE UM NO NA ARVORE - RECURSIVA
void InsereAbbRec (Arvore &A, int Info){
  if(A == nullptr){ // SE PONTEIRO NULO, INSERIR UM NOVO NO
    A = new No;
    A->Info = Info;
    A->Esq = A->Dir = nullptr;
    A->Altura = 1;
    return;
  }
  else if(Info > A->Info)
    InsereAbbRec(A->Dir, Info); //INSERINDO NO RAMO DIREITO
  else
    InsereAbbRec(A->Esq, Info); //INSERINDO NO RAMO ESQUERDO

  // Volta a recursão recalculado valor dos nós
  int balanceamento = CalculaFatorBalanceamento(A);
  if (balanceamento > 1) {
    //Se estiver desbalanceado a direita, chama a rotação a esquerda
    RotacionaEsquerda(A);
  } else if (balanceamento < -1) {
    //Se estiver desbalanceado a esquerda, chama a rotação a direita
    RotacionaDireita(A);
  }
}

// CAMINHAMENTO EM PRE-ORDEM
void Preordem (Arvore A) {
  if(A!=nullptr) {
    cout << A->Info << " (" << A->Altura << ") ";
    Preordem (A->Esq);
    Preordem (A->Dir);
  }
}

// CAMINHAMENTO EM ORDEM
void Ordem (Arvore A) {
  if(A!=nullptr) {
    Ordem (A->Esq);
    cout << A->Info << " (" << A->Altura << ") ";
    Ordem (A->Dir);
  }
}

// CAMINHAMENTO EM POS-ORDEM
void Posordem (Arvore A) {
  if(A!=nullptr) {
    Posordem (A->Esq);
    Posordem (A->Dir);
    cout << A->Info << " (" << A->Altura << ") ";
  }
}

// CONTA NOS
int ContaNos (Arvore A) {
  if(A!=NULL)
	return 1 + ContaNos(A->Esq) + ContaNos(A->Dir);
  return 0;
}
