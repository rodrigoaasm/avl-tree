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
void imprimeArvore(Arvore, int*, int, int*);
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

void PredefineArvore(Arvore &A) {
  InsereAbbRec(A, 4);
  InsereAbbRec(A, 1);
  // InsereAbbRecW(A, 2);
  // InsereAbbRecW(A, 8);
  // InsereAbbRecW(A, 7);
  // InsereAbbRecW(A, 9);
  // InsereAbbRecW(A, 6);
}

void Menu(Arvore A) {
  char opt = ' ';
  int value = 0;

  do {
    ImprimeArvore(A);
    cout << "Selecione a opção:" << endl;
    cout << "a - Adicionar elemento" << endl;
    cout << "d - Deletar elemento" << endl;
    cout << "x - Pre-definir com valores" << endl;
    cout << "r - Resetar arvore" << endl;
    cout << "s - Sair" << endl;

    cin >> opt;
    switch (opt){
      case 'a':
        cout << "Digite o valor a ser adicionado: ";
        cin >> value;
        InsereAbbRec(A, value);
        break;
      case 'd':
        cout << "Digite o valor a ser removido: ";
        cin >> value;
        break;
      case 'x':
        if (ArvoreVazia(A)) PredefineArvore(A);
        else cout << "Arvore precisa estar vazia";
        break;
      case 'r':
        ApagaArvore(A);
        break;
      case 'q':
        break;
      default:
        break;
    }

  } while (opt != 's');
}

int main () {
  Arvore A;
  IniciaArvore(A);
  PredefineArvore(A);
  Menu(A);
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

  A->FatorBalanceamento = FbDir - FbEsq > 0 ? FbDir + 1 : FbEsq + 1;

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

void imprimeArvore(Arvore A, int *x, int y, int posParentX, int *retCurrent) {
  if(A == nullptr) return;

  if (A->Esq != nullptr) {
    int posChildX = *x;
    imprimeArvore(A->Esq, x, y + 3, -1, &posChildX);

    // Desenha ramo do pai até nó esquerdo.
    for (int i = posChildX + 4; i < *x + 2; i+= 1) {
      Gotoxy(i, y + 2);
      if(i + 1 == *x + 2) {
        cout << "+";
      } else {
        cout << "-";
      }    
    }
  }
  
  int aux = *x;
  Gotoxy(aux + 3, y - 1); // 
  cout << "+";

  // Nó esquerdo retorna para o pai sua posicao para o pai desenhar o ramo
  if (retCurrent != nullptr ) *retCurrent = aux;  
  Gotoxy(aux, y); // Imprime nó
  cout << "(" << A->Info << " <" << A->FatorBalanceamento << ">" << ")";

  Gotoxy(aux + 1, y + 1); // Imprime saida dos ramos
  cout << "|   |";
  
  // Desenha ramo do nó direito até o pai.
  for (int i = aux + 2; posParentX > 0 && i > posParentX + 4; i-= 1) {
    Gotoxy(i, y - 1);
    if(i - 1 == posParentX + 4) {
      cout << "+";
    } else {
      cout << "-";
    }    
  }
  // Calcula posição do proximo nó
  *x += 8;

  if (A->Dir != nullptr) { // A recursão a direita recebe posição do pai para desenho do ramo
    imprimeArvore(A->Dir, x, y + 3, aux, nullptr);
  }
}

// Imprime arvore no console
void ImprimeArvore(Arvore A) {
  int x = 10;
  LimpaTela();
  imprimeArvore(A, &x, 1, -1, nullptr);
  Gotoxy(0, 15);
  cout << endl;
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
