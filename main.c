#include <stdio.h>
#include "lib_projeto/projeto.h"
#include "lib_projeto/testes.h"

void projetoAED(struct matrixString mString, struct matrixInts mInts);

int main(int argc, const char *argv[]) {

    struct matrixString mStrings;
    struct matrixInts mInts;

    //main_lib_projeto();
    //main_test();

    projetoAED(mStrings, mInts);

    return 0;
}

void projetoAED(struct matrixString mString, struct matrixInts mInts){

    char *fileName = "../data/chaves_publicas";
    FILE *fileChavesPubString = fopen(fileName, "r");
    int output;
    int lines = 1, fileLinePos = 0, k = 0;
    //char **matrixPub, **matrixPriv, **matrixCod;

    //Alocar espaço para a matriz e inicializar com 0
    mString.matrixPub = calloc(lines * sizeof (char *), sizeof (char *));
    mString.matrixPriv = calloc(lines * sizeof (char *), sizeof (char *));
    mString.matrixCod = calloc(lines * sizeof (char *), sizeof (char *));

    mInts.matrixPub = calloc(lines * sizeof (int *), sizeof (int *));
    mInts.matrixPriv = calloc(lines * sizeof (int *), sizeof (int *));
    mInts.matrixCod = calloc(lines * sizeof (int *), sizeof (int *));

    for (int i = 0; i < lines; ++i) {
        //Alocar espaço para cada nova linha da matriz e inicializar com 0
        mString.matrixPub = (char **) realloc(mString.matrixPub, lines * sizeof (char *));
        mString.matrixPriv = (char **) realloc(mString.matrixPriv, lines * sizeof (char *));
        mString.matrixCod = (char **) realloc(mString.matrixCod, lines * sizeof (char *));
        mString.matrixPub[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixPriv[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixCod[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));

        mInts.matrixPub = (int **) realloc(mInts.matrixPub, lines * sizeof (int *));
        mInts.matrixPriv = (int **) realloc(mInts.matrixPriv, lines * sizeof (int *));
        mInts.matrixCod = (int **) realloc(mInts.matrixCod, lines * sizeof (int *));
        mInts.matrixPub[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixPriv[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixCod[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        //Se já não haver valores para ler sai do array e para de alocar memoria
        if(fgets(mString.matrixPub[lines-1], sizeof (mString.matrixPub[lines-1]), fileChavesPubString) == NULL){
            break;
        }
        //Recebe os valores do ficheiro e retira o \n
        mString.matrixPub[lines-1] = strtok(mString.matrixPub[lines-1], "\n");
        mInts.matrixPub[lines-1][0] = atoi(mString.matrixPub[lines-1]);
        //Guarda o valor em matrixPriv[i]
        if(strcmp(mString.matrixPub[i], "\0")){
            mString.matrixPriv[i] = find_mul_bipolar_number(mString.matrixPub[lines-1]);
            mInts.matrixPriv[lines-1][0] = atoi(mString.matrixPriv[lines-1]);
        }
        if(strcmp(mString.matrixPriv[i], "\0")){
            RL_V2_String(mString.matrixPriv[i], mString.matrixCod[i]);
        }
        fileLinePos++;
        lines++;
    }

    for (int i = 0; i < lines; ++i) {
        RL_V2_Ints(mInts.matrixPriv[i][0], mInts.matrixCod[i]);
    }

    printf("\tStrings - Chaves Publicas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", mString.matrixPub[i]);
    }
    free(mString.matrixPub);

    printf("\n\tStrings - Chaves Privadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", mString.matrixPriv[i]);
    }
    free(mString.matrixPriv);

    printf("\n\tStrings - Chaves Codificadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%c\t", mString.matrixCod[i][j]);
        }
        printf("\n");

    }

    printf("\tInts - Chaves Publicas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%d\t", mInts.matrixPub[i][0]);
    }
    free(mInts.matrixPub);

    printf("\n\tInts - Chaves Privadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%d\t", mInts.matrixPriv[i][0]);
    }
    free(mInts.matrixPriv);

    printf("\n\tInts - Chaves Codificadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%d\t", mInts.matrixCod[i][j]);
        }
        printf("\n");
    }
}
