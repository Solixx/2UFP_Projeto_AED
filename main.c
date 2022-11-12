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

    char *fileName = "E:/GitHub/2UFP_Projeto_AED/data/chaves_publicas.txt";
    FILE *fileChavesPubString = fopen(fileName, "r");
    char **matrixPub;
    char lines = 2, columns = 2;

    if(fileChavesPubString == NULL){
        printf("jdjwahjda");
    }

    matrixPub = (char **) calloc(lines * sizeof (char *), sizeof (char *));

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrixPub[i] = (char *) calloc(columns * sizeof (char *), sizeof (char));
        }
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%s", matrixPub[i]);
        }
        printf("\n");
    }
}
