//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

int main_test(){
    char* publicKeyChar;
    unsigned long long publicKeyLong = 0, privKeyLong = 0, codKey = 0;

    publicKeyChar = key_long_2_digits_char(2014);
    printf("PubChar - %s\n", publicKeyChar);
    publicKeyLong = key_digits_2_long_char(publicKeyChar);
    printf("PubLong - %llu\n", publicKeyLong);
    privKeyLong = calc_private_key_char(publicKeyLong);
    printf("Priv - %llu\n", privKeyLong);
    codKey = calc_runlength_char(privKeyLong);
    printf("Cod - %llu\n", codKey);

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