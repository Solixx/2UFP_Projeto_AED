//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"

int main_test(){

    //matrixDinamicaInt();
    matrixDinamicaString();

    return 0;
}

void matrixDinamicaInt(){

    int **matrix, lines = 3, columns = 6, c = 0;

    matrix = (int **) malloc(lines * sizeof (int *));

    for (int i = 0; i < lines; ++i) {
        matrix[i] = (int *) malloc(columns * sizeof (int));
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = c;
            c++;
        }
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixDinamicaString(){

    char **matrix;
    char c = 0;
    int lines = 3, columns = 6;

    matrix = (char **) malloc(lines * sizeof (char *));

    for (int i = 0; i < lines; ++i) {
        matrix[i] = (char *) malloc(columns * sizeof (char));
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = c;
            c++;
        }
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}