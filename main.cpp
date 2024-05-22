#include <iostream>
#include "arvore_binaria_avl.h"

using namespace std;

void Gotoxy(int, int);
void ImprimeArvore(Arvore);
void imprimeArvore(Arvore, int*, int, int*);
void LimpaTela();
void Menu(Arvore);
void PredefineArvore(Arvore &);

int main () {
  Arvore A;
  IniciaArvore(A);
  PredefineArvore(A);
  Menu(A);
  ApagaArvore(A);
  return 0;
}

void PredefineArvore(Arvore &A) {
  InsereAbbRec(A, 400);
  InsereAbbRec(A, 100);
  InsereAbbRec(A, 300);
  InsereAbbRec(A, 1000);
  InsereAbbRec(A, 500);
  InsereAbbRec(A, 50);
  InsereAbbRec(A, 350);
}

void Menu(Arvore A) {
  char opt = ' ';
  int value = 0;

  LimpaTela();
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
        LimpaTela();
        InsereAbbRec(A, value);
        break;
      case 'd':
        cout << "Digite o valor a ser deletado: ";
        cin >> value;
        LimpaTela();
        RemoveAbbRec(A, value);
        break;
      case 'x':        
        if (ArvoreVazia(A)) {
          PredefineArvore(A);
          LimpaTela();
        } else cout << "Arvore precisa estar vazia!";
        break;
      case 'r':
        LimpaTela();
        ApagaArvore(A);
        break;
      case 'q':
        break;
      default:
        break;
    }

  } while (opt != 's');
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
  cout << "(" << A->Info << " <" << A->Altura << ">" << ")";

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
  int x = 40;
  imprimeArvore(A, &x, 1, -1, nullptr);
  Gotoxy(0, 15);
  cout << endl;
}
