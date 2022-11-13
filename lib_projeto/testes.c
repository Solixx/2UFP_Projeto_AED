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
    char *c = "0";
    int lines = 1, columns = 2;

    matrix = calloc(lines * sizeof (char *), sizeof (char *));

    for (int i = 0; i < lines; ++i) {
        matrix[i] = (char *) calloc(lines * sizeof (char *), sizeof (char));
    }

    for (int i = 0; i < lines; ++i) {
        matrix[i] = c;
        c++;
    }

    for (int i = 0; i < lines; ++i) {
        printf("%s\t", matrix[i]);
        printf("\n");
    }

    matrix = (char **) realloc(matrix, lines+1 * sizeof (char *));
    matrix[lines-1] = "2";
    matrix[lines] = "3";
    lines++;

    for (int i = 0; i < lines; ++i) {
        printf("%s\t", matrix[i]);
        printf("\n");
    }
}