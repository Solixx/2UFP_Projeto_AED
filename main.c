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
    int lines = 1, columnsPub = 0, columnsPriv = 0, k = 0, digits = 0;
    int columns[2] = {0,0}; // 0 -> columnsPub / 1 -> columnsPriv

    //Alocar espaço para a matriz e inicializar com 0
    mString.matrixPub = calloc(lines * sizeof (char *), sizeof (char *));
    mString.matrixPriv = calloc(lines * sizeof (char *), sizeof (char *));
    mString.matrixCod = calloc(lines * sizeof (char *), sizeof (char *));

    mInts.matrixPub = calloc(lines * sizeof (int *), sizeof (int *));
    mInts.matrixPriv = calloc(lines * sizeof (int *), sizeof (int *));
    mInts.matrixCod = calloc(lines * sizeof (int *), sizeof (int *));

    //Ler do ficheiro e guardar em mString.matrixPub e recebr o numero de linhas para a matriz
    lines = readFromFileString(mString, mInts, lines, fileChavesPubString);

    //Receber os valores de mString.matrixPub sem o "\n" & mString.matrixPriv & mString.matrixCod e valores das columnsPub, e columnsPriv
    mString = receiveMatrixString(mString, columns, digits, lines);
    columnsPub = columns[0];
    columnsPriv = columns[1];

    //Guardar os numeros na matriz de inteiros
    receiveMatrixPubInt(mString, mInts, columnsPub, lines);

    //Guardar os numeros na matriz de inteiros
    receiveMatrixPrivInt(mString, mInts, columnsPriv, lines);

    //Guardar os numeros na matriz de inteiros
    receiveMatrixCodInt(mString, mInts, lines);

    printStringMatrixPub(mString, lines);
    printStringMatrixPriv(mString, lines);
    printStringMatrixCod(mString, lines);
    printIntMatrixPub(mInts, lines, columnsPub);
    printIntMatrixPriv(mInts, lines, columnsPriv);
    printIntMatrixCod(mInts, lines);

}
