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
  if (A == nullptr) return 0;

  int FbEsq = 0, FbDir = 0;
  if(A->Esq != nullptr) {
    FbEsq = A->Esq->Altura;
  }

  if(A->Dir != nullptr) {
    FbDir = A->Dir->Altura;
  }

  return FbEsq - FbDir;
}

void RotacionaDireita(Arvore &A){
  cout << " > Rotacao p/ Direita: " << A->Info << " <- " << A->Esq->Info << endl;
  Arvore Aux = A->Esq;
  A->Esq = Aux->Dir;
  Aux->Dir = A;

  AtualizaAltura(A);
  AtualizaAltura(Aux);
  A = Aux; 
}

void RotacionaEsquerda(Arvore &A){
  cout << " > Rotacao p/ Esquerda: " << A->Info << " <- " << A->Dir->Info << endl;
  Arvore Aux = A->Dir;
  A->Dir = Aux->Esq;
  Aux->Esq = A;

  AtualizaAltura(A);
  AtualizaAltura(Aux);
  A = Aux;
}

void RotacionaEsquerdaDireita(Arvore &A){
  cout << " > Rotacao dupla:" << endl;
  RotacionaEsquerda(A->Esq);
  RotacionaDireita(A);
}

void RotacionaDireitaEsquerda(Arvore &A){
  cout << " > Rotacao dupla:" << endl;
  RotacionaDireita(A->Dir);
  RotacionaEsquerda(A);
}

void BalanceamentoAVL (Arvore &A) {
  // Volta a recursão recalculado valor dos nós
  int fb = CalculaFatorBalanceamento(A);
  cout <<  A->Info << " Balanceamento AVL. FB: " << fb << endl;
  if (fb < -1 && CalculaFatorBalanceamento(A->Dir) <= 0) {
    //Se estiver desbalanceado a direita, chama a rotação a esquerda
    RotacionaEsquerda(A);
  } else if (fb > 1 && CalculaFatorBalanceamento(A->Esq) >= 0) {
    //Se estiver desbalanceado a esquerda, chama a rotação a direita
    RotacionaDireita(A);
  } else if (fb > 1 && CalculaFatorBalanceamento(A->Esq) < 0) {
    RotacionaEsquerdaDireita(A);
  } else if (fb < -1 && CalculaFatorBalanceamento(A->Dir) > 0) {
    RotacionaDireitaEsquerda(A);
  }
}

// INSERCAO DE UM NO NA ARVORE - RECURSIVA
void InsereAbbRec (Arvore &A, int Info){
  
  if(A == nullptr){ // SE PONTEIRO NULO, INSERIR UM NOVO NO
    cout << " > Adiciona: " << Info << endl;
    A = new No;
    A->Info = Info;
    A->Esq = A->Dir = nullptr;
    A->Altura = 1;
    return;
  } else if(Info < A->Info) {
    cout << "Nó " << A->Info << ". Avança para esquerda." << endl;
    InsereAbbRec(A->Esq, Info); //INSERINDO NO RAMO ESQUERDO
  }  else  {
    cout << "Nó " << A->Info << ". Avança para direita." << endl;
    InsereAbbRec(A->Dir, Info); //INSERINDO NO RAMO DIREITO
  } 

  BalanceamentoAVL(A);
  AtualizaAltura(A);
}

void SubstituirPorMenor(Arvore &A, Arvore &Sub) {
  cout << "Busca Menor Dos Maiores: " << Sub->Info << endl;
  if(Sub->Esq == nullptr) {
    cout << " > Substitui " << A->Info << " <- " << Sub->Info << endl;
    A->Info = Sub->Info;
    if(Sub->Dir != nullptr) {
      cout << " > Substitui " << Sub->Info << " <- " << Sub->Esq->Info << endl;
      Arvore Aux = Sub;
      Sub = Sub->Dir;
      cout << " > Removendo nó" << endl;
      delete Aux;
    } else {
      cout << " > Removendo nó" << endl;
      delete Sub;
      Sub = nullptr;
    }
    
    return;
  }

  cout << " > Não é o Menor, Proximo." << endl;
  SubstituirPorMenor(A, Sub->Esq);
  AtualizaAltura(Sub);

  BalanceamentoAVL(Sub);
}

void SubstituirPorMaior(Arvore &A, Arvore &Sub) {
  cout << "Busca Maior Dos Menores: " << Sub->Info << endl;
  if(Sub->Dir == nullptr) {
    cout << " > Substitui " << A->Info << " <- " << Sub->Info << endl;
    A->Info = Sub->Info;
    if (Sub->Esq != nullptr) {
      cout << " > Substitui " << Sub->Info << " <- " << Sub->Esq->Info << endl;
      Arvore Aux = Sub;
      Sub = Sub->Esq;
      cout << " > Removendo nó" << endl;
      delete Aux;
    } else {
      cout << " > Removendo nó" << endl;
      delete Sub;
      Sub = nullptr;
    }
    
    return;
  }

  cout << " > Não é o Maior, Proximo." << endl;
  SubstituirPorMaior(A, Sub->Dir);
  AtualizaAltura(Sub);

  BalanceamentoAVL(Sub);
}

void RemoveAbbRec (Arvore &A, int Info){  
  if (A == nullptr){
    cout << "Não Foi Encontrado: " << Info << endl;
    return; 
  }

  cout << "Busca: " << A->Info << endl;
  Arvore Aux = A;
  if (A->Info < Info ) {
    RemoveAbbRec(A->Dir, Info);
    AtualizaAltura(A);
    BalanceamentoAVL(A);
  } else if (A->Info > Info ) {
    RemoveAbbRec(A->Esq, Info);
    AtualizaAltura(A);
    BalanceamentoAVL(A);    
  } else {
    cout << " > Encontrado!" << endl;
    if (A->Dir != nullptr && A->Esq != nullptr) {
      if(A->Esq->Altura > A->Dir->Altura ) {
        SubstituirPorMaior(A, A->Esq);
      } else {
        SubstituirPorMenor(A, A->Dir);
      }
      AtualizaAltura(A);
      BalanceamentoAVL(A);      
    } else {
      cout << " > Removendo nó" << endl;
      if (A->Dir != nullptr) {
        A = A->Dir;        
      } else if(A->Esq != nullptr){
        A = A->Esq;
      } else {
        A = nullptr;
      }

      delete Aux; 
    }
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
