/*+---------------------------------+
  | Arvore Binaria de Busca - 2024  |
  | By Sandro Izidoro               |
  +---------------------------------+*/

#include <iostream>

using namespace std;

struct No { // DEFINICAO DO NO
  int Info; // INFORMACAO DO NO
  No* Esq; // PONTEIRO PARA SUBARVORE ESQ
  No* Dir; // PONTEIRO PARA SUBARVORE DIR
  int FatorBalanceamento; // Fator de balanceamento
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
void Gotoxy(int, int);
void ImprimeArvore(Arvore);
void imprimeArvore(Arvore, int, int);
void LimpaTela();

// INSERCAO DE UM NO NA ARVORE - RECURSIVA
void InsereAbbRecW (Arvore &A, int Info){
  if(A == nullptr){ // SE PONTEIRO NULO, INSERIR UM NOVO NO
    A = new No;
    A->Info = Info;
    A->Esq = A->Dir = nullptr;
    cout << "Add here " << Info << endl;
  }
  else if(Info > A->Info) {
    cout << A->Info << "->" ;
    InsereAbbRecW(A->Dir, Info); //INSERINDO NO RAMO DIREITO
  } else {
    cout << A->Info << "->" ; 
    InsereAbbRecW(A->Esq, Info); //INSERINDO NO RAMO ESQUERDO
  }
}

int main () {
   Arvore A;
   IniciaArvore(A);

   if(ArvoreVazia(A))
      cout << "A arvore esta vazia." << endl;
   else cout << "A arvore nao esta Vazia." << endl;

  InsereAbbRecW(A, 3);
  InsereAbbRecW(A, 1);
  //  InsereAbbRec(A, 2);
  InsereAbbRecW(A, 8);
  InsereAbbRec(A, 7);
  InsereAbbRecW(A, 9);
  InsereAbbRec(A, 6);

  ImprimeArvore(A);

   cout << endl;
   cout << "Pre-ordem: ";
   Preordem(A);

  //  cout << endl;
  //  cout << "A arvore tem " << ContaNos(A) << " nos." << endl;

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

// CALCULA FATOR DE BALANCEAMENTO
int CalculaFatorBalanceamento(Arvore A) {
  int FbEsq, FbDir = 0;

  if(A->Esq != nullptr) {
    FbEsq = A->Esq->FatorBalanceamento;
  }

  if(A->Dir != nullptr) {
    FbDir = A->Dir->FatorBalanceamento;
  }
  return FbDir - FbEsq;
}

void RotacionaDireita(Arvore &A){
  if(A->Esq->Dir != nullptr) {
    RotacionaEsquerda(A->Esq);
  }
  Arvore Aux = A->Esq;
  A->Esq = nullptr;
  Aux->Dir = A;
  A = Aux;
}

void RotacionaEsquerda(Arvore &A){
  if(A->Dir->Esq != nullptr) {
    RotacionaDireita(A->Dir);
  }
  Arvore Aux = A->Dir;
  A->Dir = nullptr;
  Aux->Esq = A;
  A = Aux;
}


// INSERCAO DE UM NO NA ARVORE - RECURSIVA
void InsereAbbRec (Arvore &A, int Info){
  if(A == nullptr){ // SE PONTEIRO NULO, INSERIR UM NOVO NO
    A = new No;
    A->Info = Info;
    A->Esq = A->Dir = nullptr;
    A->FatorBalanceamento = 1;
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
// Posiciona cursor
void Gotoxy(int x, int y) {
  cout << "\033[" << y << ";" << x << "H";
}

void LimpaTela() {
  std::cout << "\033[2J\033[1;1H";
}

void imprimeArvore(Arvore A, int x, int y) {
  if(A == nullptr) return;

  Gotoxy(x, y);
  cout << "(" << A->Info << " <" << A->FatorBalanceamento << ">" << ")";

  int offsetX = 4;
  int offsetY = 2;

  // Desenha conexoes da arvore
  if (A->Esq != nullptr) {
    Gotoxy(x - offsetX + 3, y + 1); // Move para a posição do próximo nó
    cout << "+"; // Desenha a linha horizontal para o filho esquerdo
    imprimeArvore(A->Esq, x - offsetX, y + offsetY);
  }

  if (A->Dir != nullptr) {
    Gotoxy(x + offsetX + 3, y + 1); // Move para a posição do próximo nó
    cout << "+"; // Desenha a linha horizontal para o filho esquerdo
    imprimeArvore(A->Dir, x + offsetX, y + offsetY);
  }  
}

// Imprime arvore no console
void ImprimeArvore(Arvore A) {
  LimpaTela();
  imprimeArvore(A, 40, 3);
  cout << endl << endl << endl;
}

// CAMINHAMENTO EM PRE-ORDEM
void Preordem (Arvore A) {
  if(A!=nullptr) {
    cout << A->Info << " (" << A->FatorBalanceamento << ") ";
    Preordem (A->Esq);
    Preordem (A->Dir);
  }
}

// CAMINHAMENTO EM ORDEM
void Ordem (Arvore A) {
  if(A!=nullptr) {
    Ordem (A->Esq);
    cout << A->Info << " (" << A->FatorBalanceamento << ") ";
    Ordem (A->Dir);
  }
}

// CAMINHAMENTO EM POS-ORDEM
void Posordem (Arvore A) {
  if(A!=nullptr) {
    Posordem (A->Esq);
    Posordem (A->Dir);
    cout << A->Info << " (" << A->FatorBalanceamento << ") ";
  }
}

// CONTA NOS
int ContaNos (Arvore A) {
  if(A!=NULL)
	return 1 + ContaNos(A->Esq) + ContaNos(A->Dir);
  return 0;
}
