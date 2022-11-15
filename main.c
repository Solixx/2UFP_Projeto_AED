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
    char **matrixPub, **matrixPriv, **matrixCod;

    //Alocar espaço para a matriz e inicializar com 0
    matrixPub = calloc(lines * sizeof (char *), sizeof (char *));
    matrixPriv = calloc(lines * sizeof (char *), sizeof (char *));
    matrixCod = calloc(lines * sizeof (char *), sizeof (char *));

    for (int i = 0; i < lines; ++i) {
        //Alocar espaço para cada nova linha da matriz e inicializar com 0
        matrixPub = (char **) realloc(matrixPub, lines * sizeof (char *));
        matrixPriv = (char **) realloc(matrixPriv, lines * sizeof (char *));
        matrixCod = (char **) realloc(matrixCod, lines * sizeof (char *));
        matrixPub[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        matrixPriv[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        matrixCod[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        //Se já não haver valores para ler sai do array e para de alocar memoria
        if(fgets(matrixPub[lines-1], 100, fileChavesPubString) == NULL){
            break;
        }
        //Recebe os valores do ficheiro e retira o \n
        matrixPub[lines-1] = strtok(matrixPub[lines-1], "\n");
        //Guarda o valor em matrixPriv[i]
        matrixPriv[i] = find_mul_bipolar_number(matrixPub[lines-1]);
        if(strcmp(matrixPriv[i], "\0")){
            RL_V2_String(matrixPriv[i], matrixCod[i]);
        }
        fileLinePos++;
        lines++;
    }

    printf("\tChaves Publicas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", matrixPub[i]);
    }
    free(matrixPub);

    printf("\n\tChaves Privadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", matrixPriv[i]);
    }
    free(matrixPriv);

    printf("\n\tChaves Codificadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%c\t", matrixCod[i][j]);
        }
        printf("\n");
    }
}
