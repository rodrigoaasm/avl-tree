//ATIVIDADE 02
// Vitor Hugo Bernardes - 2024102224
// Rodrigo A S Maia - 2024100883
// Alisson Omena - 2024100097

#include <iostream>

using namespace std;

int *decimal_binario(int decimal, int &tam){
    int aux = decimal;
    tam = 0;            //VARIÁVEL PARA SALVAR O VALOR DO TAMANHO
    while(aux > 0){     //DEFINE O TAMANHO DO NÚMERO BINÁRIO
        aux = aux / 2;  //ATUALIZANDO
        tam++;
    }

    int *binario = new int[tam];   //VARIÁVEL DEFINIDA PARA SALVAR O BINÁRIO

    for (int i = 0; i < tam; i++){
        binario[i] = decimal % 2;   //SALVANDO O NÚMERO BINÁRIO
        decimal = decimal / 2;      //ATUALIZANDO
    }

    return binario;
}

int main(){
    int decimal;
    cout << "Digite um numero decimal: ";
    cin >> decimal;     //USUÁRIO DEFINE O DECIMAL

    int tam = 0;
    int *binario = decimal_binario(decimal, tam);   //CHAMANDO A FUNÇÃO

    cout << "O numero binario é: ";
    for (int i = tam - 1; i >= 0; i--){     //MOSTRANDO A VARIAVEL BINARIO
        cout << binario[i];
    }

    cout << endl;
    cout << "Tamanho do número binario: " << tam << endl;

    delete [] binario;

    return 0;
}
