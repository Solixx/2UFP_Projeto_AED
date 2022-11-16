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
    int lines = 1, columnsPub = 1, columnsPriv = 1, k = 0, digits = 0;
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
        mString.matrixPub[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixPriv[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixCod[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));

        mInts.matrixPub[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixPriv[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixCod[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));

        //Se já não haver valores para ler sai do array e para de alocar memoria
        if(fgets(mString.matrixPub[lines-1], sizeof (mString.matrixPub[lines-1]), fileChavesPubString) == NULL){
            break;
        }
        lines++;
    }

    for (int i = 0; i < lines-1; ++i) {
        //Recebe os valores do ficheiro e retira o \n e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPub)
        mString.matrixPub[i] = strtok(mString.matrixPub[i], "\n");
        columnsPub = countColumnPub(digits, mString, i, columnsPub);

        //Guarda o valor em matrixPriv[i]  e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPriv)
        if(strcmp(mString.matrixPub[i], "\0")){
            mString.matrixPriv[i] = find_mul_bipolar_number(mString.matrixPub[i]);
            columnsPriv = countColumnPriv(digits, mString, i, columnsPriv);
        }

        //Guarda o valor em matrixCod[i]
        if(strcmp(mString.matrixPriv[i], "\0")){
            RL_V2_String(mString.matrixPriv[i], mString.matrixCod[i]);
        }
    }

    //Guardar os numeros na matriz de inteiros
    for (int i = 0; i < lines-1; ++i) {
        //Array com digitos da mString.matrixPub[i]
        int *allD = (int *) calloc(numDigits(atoi(mString.matrixPub[i])) * sizeof (*allD), sizeof (*allD));
        allDigits(atoi(mString.matrixPub[i]), allD);
        //Guardar os valores de allD em mInts.matrixPub[i][j-1]
        for (int j = 1; j <= columnsPub; j++) {
            //Se J ultrapassar o numero de digitos em mString.matrixPub[i] guarda o valor -1 (este vai ser usardo como valor de referencia para uma coluna vazia visto que é ncessário escrever os '0')
            if(j <= numDigits(atoi(mString.matrixPub[i]))) {
                mInts.matrixPub[i][j-1] = allD[numDigits(atoi(mString.matrixPub[i])) - j];
            }else{
                mInts.matrixPub[i][j-1] = -1;
            }
        }
        free(allD);
    }

    //Guardar os numeros na matriz de inteiros
    for (int i = 0; i < lines; ++i) {
        //Array com digitos da mString.matrixPriv[i]
        int *allD = (int *) calloc(numDigits(atoi(mString.matrixPriv[i])) * sizeof (*allD), sizeof (*allD));
        allDigits(atoi(mString.matrixPriv[i]), allD);
        //Guardar os valores de allD em mInts.matrixPriv[i][j-1]
        for (int j = 1; j <= columnsPriv; ++j) {
            //Se J ultrapassar o numero de digitos em mString.matrixPriv[i] guarda o valor -1 (este vai ser usardo como valor de referencia para uma coluna vazia visto que é ncessário escrever os '0')
            if(j <= numDigits(atoi(mString.matrixPriv[i]))){
                mInts.matrixPriv[i][j-1] = allD[numDigits(atoi(mString.matrixPriv[i]))-j];
            }else{
                mInts.matrixPriv[i][j-1] = -1;
            }
        }
        free(allD);
    }

    //Guardar os numeros na matriz de inteiros
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < 4; ++j) {
            //Se mString.matrixPriv[i] for uma string vazia inserimos -1 (este vai ser usardo como valor de referencia para uma coluna vazia visto que é ncessário escrever os '0')
            if(strcmp(mString.matrixPriv[i], "\0")){
                mInts.matrixCod[i][j] = mString.matrixCod[i][j] - '0';
            }else{
                mInts.matrixCod[i][j] = -1;
            }
        }
    }

    printStringMatrixPub(mString, lines);
    printStringMatrixPriv(mString, lines);
    printStringMatrixCod(mString, lines);
    printIntMatrixPub(mInts, lines, columnsPub);
    printIntMatrixPriv(mInts, lines, columnsPriv);
    printIntMatrixCod(mInts, lines);

}
