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
    char **matrixPub, **matrixPriv;
    char lines = 3, fileLinePos = 0;

    //Alocar espaço para a matriz e inicializar com 0
    matrixPub = (char **) calloc(lines * sizeof (char *), sizeof (char *));
    matrixPriv = (char **) calloc(lines * sizeof (char *), sizeof (char *));

    //Alocar espaço para cada linha da matriz e inicializar com 0
    for (int i = 0; i < lines; ++i) {
        matrixPub[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        matrixPriv[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
    }

    //Cada linha da matriz recebe uma chave publica guardada no ficheiro "data/chaves_publicas"
    while (fgets(matrixPub[fileLinePos], 100, fileChavesPubString) != NULL){
        matrixPub[fileLinePos] = strtok(matrixPub[fileLinePos], "\n");
        fileLinePos++;
    }

    for (int i = 0; i < lines; ++i) {
        matrixPriv[i] = find_mul_bipolar_number(matrixPub[i]);
    }

    for (int i = 0; i < lines; ++i) {
        printf("%s\n", matrixPriv[i]);
    }
}
