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
#define MAX_NAME_LEN 256

struct matrixString{
    char **matrixPub;
    char **matrixPriv;
    char **matrixCod;
    int lines;
};

struct matrixInts{
    short **matrixPub;
    short **matrixPriv;
    short **matrixCod;
    int lines;
};

typedef struct KEY_HOLDER{
    struct matrixString khString;
    struct matrixInts khInts;
    char* data_criacao;
    char* data_modificacao;
    int sizeStrings;
    int sieInts;
    struct KEY_HOLDER *next;
} KEY_HOLDER;

typedef struct UTILIZADORES {
    char* name;
    char* email;
    KEY_HOLDER* key_holder_list;
    struct UTILIZADORES* next;
} UTILIZADORES;

typedef struct UTILIZADORES_QUEUE {
    UTILIZADORES* head;
    UTILIZADORES* tail;
    int size;
} UTILIZADORES_QUEUE;

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
int charPos(char *a, int d);

struct matrixString removeKey(struct matrixString mString, char *key, int lines);

void shellSortChar(char** a, int N, int order);
void shellSortCharDigits(char** a, char** priv, char** cod, int N, int order);
void swapChar(char** a, int i, int min);
void swapCharDigits(char** a, char** priv, char** cod, int i, int min);

void shellSortInt(short** a, int N, int order);
void shellSortIntDigits(short** a, short** priv, short** cod, int N, int order);
void swapInt(short** a, int i, int min);
void swapIntDigits(short** a, short** priv, short** cod, int i, int min);

void updateLines_MatrixString(struct matrixString mString, int lines);

void insert_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts, int pos);
void edit_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, int posChange, int keyPos);
void remove_keyHolder(KEY_HOLDER** portaChaves, int keyHolderPos);
//Type -> 1 = PubKey / Type -> 2 = PrivKey / Type -> 3 = CodKey
void searchSingleKey_inKeyHolder(KEY_HOLDER* portaChaves, int keyHolderPos, unsigned long long keyToSeach, int type, char* filename);
void save_txt_keyHolder(KEY_HOLDER ** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, char filename[]);
void load_txt_keyHolder(KEY_HOLDER ** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, int newKeysPos, char filename[]);
void print_keyHolders(KEY_HOLDER** portaChaves);

void create_utilizador_ordenado(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos);
void create_utilizador_cabeca(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos);
void create_utilizador_cauda(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos);
void enqueue(UTILIZADORES_QUEUE* queue, UTILIZADORES* utilizador);
void dequeue(UTILIZADORES_QUEUE* queue);
void print_utilizadores(UTILIZADORES_QUEUE* queue);
void remover_nome_utilizador(UTILIZADORES_QUEUE* queue, char* name);
void remover_cabeca_utilizador(UTILIZADORES_QUEUE* queue);
void remover_cauda_utilizador(UTILIZADORES_QUEUE* queue);
void search_utilizador_by_name(UTILIZADORES_QUEUE* queue, char* name);
void ordenar_utilizadores(UTILIZADORES_QUEUE* queue);

void freeMatrixChar(char **matrix, int N);
void freeMatrixShort(short **matrix, int N);

void cliente0();
void cliente1();
void cliente2();
void cliente3();

void main_lib_projeto();

#endif //INC_2UFP_PROJETO_AED_PROJETO_H
