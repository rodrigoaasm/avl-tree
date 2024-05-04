// Atividade 4
// Vitor Hugo Bernardes - 2024102224
// Rodrigo A S Maia - 2024100883
// Alisson Omena - 2024100097

#include <iostream>

using namespace std;

struct No { // DEFINICAO DO NO
  int Info; // INFORMACAO DO NO
  No* Esq; // PONTEIRO PARA SUBARVORE ESQ
  No* Dir; // PONTEIRO PARA SUBARVORE DIR
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
void RemoveAbbRec(Arvore &, int);

int main () {
  Arvore A;
  IniciaArvore(A);

  InsereAbbRec(A, 4);
  InsereAbbRec(A, 7);
  InsereAbbRec(A, 2);
  InsereAbbRec(A, 1);
  InsereAbbRec(A, 3);
  InsereAbbRec(A, 5);
  InsereAbbRec(A, 8);

  cout << "Arvore inicial(pre-ordem):  " << endl;
  Preordem(A);
  cout << endl;

  
  cout << "A arvore tem " << ContaNos(A) << " nos." << endl;

  cout << endl;
  cout << "Remove 4. "  << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 4);
  Preordem(A);

  cout << endl;
  cout << "Remove 2. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 2);
  Preordem(A);

  cout << endl;
  cout << "Remove 9. "  << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 9);
  Preordem(A);

  cout << endl;
  cout << "Remove 8. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 8);
  Preordem(A);  

  cout << endl;
  cout << "Remove 5. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 5);
  Preordem(A); 

  cout << endl;
  cout << "Remove 3. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 3);
  Preordem(A); 

  cout << endl;
  cout << "Remove 7. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 7);
  Preordem(A); 

  cout << endl;
  cout << "Remove 1. " << "Arvore atual(pre-ordem):  ";
  RemoveAbbRec(A, 1);
  Preordem(A); 
  
  cout << endl;
  cout << "A arvore tem " << ContaNos(A) << " nos." << endl;

  cout << endl;
  if(ArvoreVazia(A))
    cout << "A arvore esta vazia." << endl;
  else cout << "A arvore nao esta Vazia." << endl;

  ApagaArvore(A);

  return 0;
}

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

// INSERCAO DE UM NO NA ARVORE - RECURSIVA
void InsereAbbRec (Arvore &A, int Info){
  if(A == nullptr){ // SE PONTEIRO NULO, INSERIR UM NOVO NO
    A = new No;
    A->Info = Info;
    A->Esq = A->Dir = nullptr;
  }
  else if(Info > A->Info)
    InsereAbbRec(A->Dir, Info); //INSERINDO NO RAMO DIREITO
  else
    InsereAbbRec(A->Esq, Info); //INSERINDO NO RAMO ESQUERDO
}

// REMOÇÃO DE UM NO NA ARVORE - RECURSIVA
void RemoveAbbRec(Arvore &A, int Info) {
  Arvore Aux = A;
  if(A == nullptr){
    return; 
  }
  
  if(A->Info == Info) {
    if(A->Dir == nullptr && A->Esq == nullptr) {
      delete A;
      A = nullptr;
    } else if (A->Dir != nullptr && A->Esq != nullptr) {
        Arvore Parent = nullptr;
        Aux = A->Dir;        
        while (Aux->Esq != nullptr) {
          Parent = Aux;
          Aux = Aux->Esq;
        }

        A ->Info = Aux->Info;        
        if(Parent == nullptr) {
          A->Dir = A->Dir->Dir;
        } else {
          Parent->Esq = nullptr;
        }
        delete Aux;
    } else if (A->Dir != nullptr) {
      A = A->Dir;
      delete Aux;
    } else {
      A = A->Esq;
      delete Aux;
    }
  } else if (A->Info < Info ) {
    RemoveAbbRec(A->Dir, Info);
  } else {
    RemoveAbbRec(A->Esq, Info);
  }
}

// CAMINHAMENTO EM PRE-ORDEM
void Preordem (Arvore A) {
  if(A!=nullptr) {
    cout << A->Info << "  ";
    Preordem (A->Esq);
    Preordem (A->Dir);
  }
}

// CAMINHAMENTO EM ORDEM
void Ordem (Arvore A) {
  if(A!=nullptr) {
    Ordem (A->Esq);
    cout << A->Info << "  " ;
    Ordem (A->Dir);
  }
}

// CAMINHAMENTO EM POS-ORDEM
void Posordem (Arvore A) {
  if(A!=nullptr) {
    Posordem (A->Esq);
    Posordem (A->Dir);
    cout << A->Info << "  ";
  }
}

// CONTA NOS
int ContaNos (Arvore A) {
  if(A!=NULL)
	return 1 + ContaNos(A->Esq) + ContaNos(A->Dir);
  return 0;
}
