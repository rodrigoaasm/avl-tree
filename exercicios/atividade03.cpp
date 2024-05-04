// Atividade 3
// Vitor Hugo Bernardes - 2024102224
// Rodrigo A S Maia - 2024100883
// Alisson Omena - 2024100097

#include <iostream>

using namespace std;

struct No {
   char Info;
   No * Lig;
};

typedef struct No *NoPtr;

void InsereLista (NoPtr& L, char Novo) {
  if (L == nullptr) {  // INSERCAO DO PRIMEIRO NO
      L = new No;
      L->Info = Novo;
      L->Lig = nullptr;
  } else {                // AJUSTA PONTEIROS ANT E AUX
      NoPtr Ant = nullptr;
      NoPtr Aux = L;
      while((Aux != nullptr)&&(Aux->Info < Novo)) {//ENCONTRA POSICAO
      	    Ant = Aux;
            Aux = Aux->Lig;
      }
      Aux = new No;
      Aux->Info = Novo;     // INSERE O NO E AJUSTA PONTEIROS
      if (Ant == nullptr) {
            Aux->Lig = L;
            L = Aux;
      } else {
            Aux->Lig = Ant->Lig;
            Ant->Lig = Aux;
      }
  }
}

bool RetiraLista (NoPtr& L, char Novo) {
  NoPtr Ant = nullptr;
  NoPtr Aux = L;
  while ((Aux != nullptr) && (Aux->Info != Novo)) { // TENTA ENCONTRAR ELEMENTO
          Ant = Aux;
          Aux = Aux->Lig;
  }
  if (Aux == nullptr)
         return false;  // RETORNA FALSO SE NAO ENCONTRA ELEMENTO
  if (Aux == L)        // SE ELEMENTO E O PRIMEIRO, REDIRECIONA O PONTEIRO
         L = L->Lig;
  else
         Ant->Lig = Aux->Lig; // REDIRECIONA O PONTEIRO
  delete Aux;  // APAGA O ELEMENTO
  return true;
}

void ImprimeLista (NoPtr L) {
  NoPtr Aux = L;
  cout << "L -> ";
  while ((Aux != nullptr)) {
        cout << Aux->Info << " -> ";
        Aux = Aux->Lig;
  }
  if (Aux == nullptr)
      cout << "nullptr" << endl;
}

NoPtr IntersecaoListas (NoPtr & L1, NoPtr & L2){
  NoPtr new_list = nullptr;
  NoPtr Aux1 = L1;
  NoPtr Aux2 = L2;

  while(Aux1!= nullptr && Aux2 != nullptr) {
    if(Aux1->Info == Aux2->Info){
      InsereLista(new_list, Aux1->Info);
      Aux1= Aux1->Lig;
      Aux2 = Aux2->Lig;
    } else if(Aux1->Info < Aux2->Info){
      Aux1= Aux1->Lig;
    } else {
      Aux2 = Aux2->Lig;
    }
  }

  return new_list;
}

NoPtr UniaoListas (NoPtr & L1, NoPtr & L2){
  NoPtr new_list = nullptr;
  NoPtr Aux1 = L1;
  NoPtr Aux2 = L2;

  while(Aux1!= nullptr && Aux2 != nullptr) {
    if(Aux1->Info == Aux2->Info){
      InsereLista(new_list, Aux1->Info);
      Aux1= Aux1->Lig;
      Aux2 = Aux2->Lig;
    } else if(Aux1->Info < Aux2->Info){
      InsereLista(new_list, Aux1->Info);
      Aux1= Aux1->Lig;
    } else {
      InsereLista(new_list, Aux2->Info);
      Aux2 = Aux2->Lig;
    }
  }

  while (Aux1 != nullptr) {
    InsereLista(new_list, Aux1->Info);
    Aux1 = Aux1->Lig;
  }

  while (Aux2 != nullptr) {
    InsereLista(new_list, Aux2->Info);
    Aux2 = Aux2->Lig;
  }

  return new_list;
}

int main () {
  NoPtr L1 = nullptr;
  NoPtr L2 = nullptr;

  InsereLista(L1, 'c');
  InsereLista(L1, 'd');
  InsereLista(L1, 'a');
  InsereLista(L1, 'b');
  InsereLista(L1, 'e');
  InsereLista(L1, 'f');
  cout << "Lista 1:";
  ImprimeLista(L1);

  InsereLista(L2, 'a');
  InsereLista(L2, 'd');
  InsereLista(L2, 'h');
  InsereLista(L2, 'i');
  InsereLista(L2, 'g');
  InsereLista(L2, 'f');

  cout << "Lista 2:";
  ImprimeLista(L2);
  cout << endl;

  NoPtr interList = IntersecaoListas(L1, L2);
  cout << "Interseção:";
  ImprimeLista(interList);

  cout << "União:";
  NoPtr uniaoList = UniaoListas(L1, L2);
  ImprimeLista(uniaoList);

  return 0;
}
