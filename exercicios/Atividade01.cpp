//ATIVIDADE 01
// Vitor Hugo Bernardes - 2024102224
// Rodrigo A S Maia - 2024100883
// Alisson Omena - 2024100097

#include <iostream>
#include <cmath>

using namespace std;

struct No{
    int expoente;
    float coeficiente;
    No *prox;
};

typedef struct No *Polinomio;


void Inicia_Polinomio(Polinomio &P){
    P = nullptr;
}

void Insere_Termo (Polinomio &P, float c, int e){
    if(P == nullptr){      //CASO SEJA O PRIMEIRO VALOR A SER INSERIDO
        P = new No;
        P->expoente = e;
        P->coeficiente = c;
        P->prox = NULL;
    } else{               //CASO EM QUE JA TENHA ALGO INSERIDO
        Polinomio Ant = NULL; //VARIAVEL AUXILIAR
        Polinomio Aux = P;

        while(Aux != nullptr && Aux->expoente > e){//LOOP PARA ENCONTRAR A POSIÇÃO
            Ant = Aux;
            Aux = Aux->prox;
        }

        if(Aux == nullptr){ //aux é null, insere final
            Aux = new No{};
            Aux->coeficiente = c;
            Aux->expoente = e;

            Ant->prox = Aux;
        } else if (Aux->expoente == e){ // aux não é null e expoente é igual, soma
            Aux->expoente = e;
            Aux->coeficiente = Aux->coeficiente + c;
        }
        else { // aux não é null e expoente não é igual
            Polinomio tmp = new No{};
            tmp->coeficiente = c;
            tmp->expoente = e;
            tmp->prox = Aux;

            if(Ant == nullptr) { // insere no inicio
                P = tmp;
            } else {
                Ant->prox = tmp; // insere no meio
            }
        }
    }
}


float Calcular_Polinomio(Polinomio &P, float valor){
    Polinomio Aux = P;
    float resultado = 0;
    while ((Aux != nullptr)) {
        resultado = resultado + Aux->coeficiente *pow(valor,Aux->expoente); //ADICIONAR A RECURSÃO.
        Aux = Aux->prox;
    }
    return resultado;
}

void Imprimir(Polinomio P){
    Polinomio Aux = P;
    cout << "Expressão: ";
    while (Aux != nullptr) {
        cout << Aux->coeficiente << "X^" << Aux->expoente; //ADICIONAR A RECURSÃO.
        if(Aux->prox != nullptr) //Insere '+' entre os termos 
            cout << " + ";
        Aux = Aux->prox;
    }
    cout << endl;
}

int main(){
    Polinomio P;
    Inicia_Polinomio(P);

    Insere_Termo(P, 5.0f, 3);
    Insere_Termo(P, 0.5f, 5);
    Insere_Termo(P, 10.0f, 4);   
    Insere_Termo(P, 2.0f, 2);

    Imprimir(P);
    float res = Calcular_Polinomio(P,2);

    cout << "Resultado: " << res << endl;

    return 0;
}
