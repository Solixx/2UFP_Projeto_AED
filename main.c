#include <stdio.h>
#include "lib_projeto/projeto.h"
#include "lib_projeto/testes.h"

void projetoAED();

int main() {

    //main_lib_projeto();
    //main_test();

    projetoAED();

    return 0;
}

void projetoAED(){

    char *fileName = "../data/chaves_publicas";
    FILE *fileChavesPubString = fopen(fileName, "r");
    int lines = 1, fileLinePos = 0;
    char **matrixPub, **matrixPriv;

    //Alocar espaço para a matriz e inicializar com 0
    matrixPub = calloc(lines * sizeof (char *), sizeof (char *));
    matrixPriv = calloc(lines * sizeof (char *), sizeof (char *));

    for (int i = 0; i < lines; ++i) {
        //Alocar espaço para cada nova linha da matriz e inicializar com 0
        matrixPub[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        matrixPriv[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        //Se já não haver valores para ler sai do array e para de alocar memoria
        if(fgets(matrixPub[lines-1], 100, fileChavesPubString) == NULL){
            break;
        }
        //Recebe os valores do ficheiro e retira o \n
        matrixPub[lines-1] = strtok(matrixPub[lines-1], "\n");
        //Guarda o valor em matrixPriv[i]
        matrixPriv[i] = find_mul_bipolar_number(matrixPub[lines-1]);
        fileLinePos++;
        lines++;
    }
}
