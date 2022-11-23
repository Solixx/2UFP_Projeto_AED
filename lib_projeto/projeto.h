//
// Created by pc on 11/11/2022.
//

#ifndef INC_2UFP_PROJETO_AED_PROJETO_H
#define INC_2UFP_PROJETO_AED_PROJETO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <time.h>

#define FIRST_NUMBER '0'

struct matrixString{
    char **matrixPub;
    char **matrixPriv;
    char **matrixCod;
};

struct matrixInts{
    short **matrixPub;
    short **matrixPriv;
    short **matrixCod;
};

typedef struct KEY_HOLDER{
    struct matrixString khString;
    struct matrixInts khInts;
    int data_criacao;
    int data_modificacao;
    struct KEY_HOLDER *next;
} KEY_HOLDER;

int bipolar_number(char *text);

void print_bipolar_numbers(int k);

char* find_mul_bipolar_number(char *k);

int find_mul_bipolar_number_Int(int k);

int hist(char* num, int histo[]);

int RL_V1(char* num, int runLess[]);

int RL_V2(char* num, int runLess[]);

int RL_V2_Ints(int num, int runLess[]);

char* RL_V2_String(char* num, char rL[]);

int numDigits(int num);
int numDigitsLong(unsigned long long num);

void allDigits(int num, int allD[]);
void allDigitsLong(unsigned long long num, int allD[]);

int countColumnPub(int digits, struct matrixString mString, int i, int columnsPub);

int countColumnPriv(int digits, struct matrixString mString, int i, int columnsPriv);

void printStringMatrixPub(struct matrixString mString, int lines);
void printStringMatrixPriv(struct matrixString mString, int lines);
void printStringMatrixCod(struct matrixString mString, int lines);
void printIntMatrixPub(struct matrixInts mInts, int lines, int columns);
void printIntMatrixPriv(struct matrixInts mInts, int lines, int columns);
void printIntMatrixCod(struct matrixInts mInts, int lines);

int readFromFileString(struct matrixString mString, struct matrixInts mInts, int lines, FILE *fileChavesPubRead, char *fileName, int columns[], int digits, int pos);
int readFromString(struct matrixString mString, struct matrixInts mInts, int lines, int columns[], int digits, int pos, char *key);

struct matrixString receiveFileMatrixString(struct matrixString mString, int columns[], int digits, int lines, int pos);
struct matrixString receiveMatrixString(struct matrixString mString, int columns[], int digits, int lines, int pos);

void receiveMatrixPubInt(struct matrixString mString, struct matrixInts mInts, int columnsPub, int lines);
void receiveMatrixPrivInt(struct matrixString mString, struct matrixInts mInts, int columnsPriv, int lines);
void receiveMatrixCodInt(struct matrixString mString, struct matrixInts mInts, int lines);

void randomKey(FILE *fileChavesPubWrite, char *fileName, int n);
char** randomKeyMatrix(char** r, int n);
char* randomKeyValue(char* r);

struct matrixString removeKey(struct matrixString mString, char *key, int lines);

void shellSortChar(char** a, int N, int order);
void shellSortCharDigits(char** a, int N, int order);
void swapChar(char** a, int i, int min);

void shellSortInt(short** a, int N, int order);
void shellSortIntDigits(short** a, int N, int order);
void swapInt(short** a, int i, int min);


void insert_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts);

void cliente0();
void cliente1();
void cliente2();
void cliente3();

void main_lib_projeto();

#endif //INC_2UFP_PROJETO_AED_PROJETO_H
