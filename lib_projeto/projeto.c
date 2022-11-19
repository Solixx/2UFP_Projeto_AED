//
// Created by pc on 11/11/2022.
//

#include "projeto.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

void main_lib_projeto(){

    //cliente0();
    //cliente1();
    //cliente2();
    cliente3();
}

void cliente0(){
    char t[] = "2211";

    printf("%d\n", bipolar_number(t));
}

void cliente1(){
    int k = 4;
    int n[k];

    //print_bipolar_numbers(k);
    printf("%s\n", find_mul_bipolar_number("2014"));
}

void cliente2(){
    char t[] = "77555";
    int histo[10];

    if(bipolar_number(t) == 0){
        hist(t, histo);
        for (int i = 0; i < 10; ++i) {
            printf("histo de %d = %d\n", i, histo[i]);
        }
    }
}

void cliente3(){
    char t[] = "77555";
    char rL[4];
    int r = 77555;
    int runLess[4];
    int mat[1][4];

    if(bipolar_number(t) == 0){
        for (int i = 0; i < 4; ++i) {
            runLess[i] = 0;
        }
        //RL_V1(t, runLess);
        //RL_V2(t, runLess);
        RL_V2_Ints(r, mat[0]);
        //RL_V2_String(t,rL);
        printf("RL\n");
        for (int i = 0; i < 4; ++i) {
            //printf("%d ", runLess[i]);
            //printf("%c ", rL[i]);
        }
        for (int i = 0; i < 1; ++i) {
            for (int j = 0; j < 4; ++j) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
    }
}

int bipolar_number(char *text){

    int bipolar = 0, changes = 0, exits = 0;
    int number, pow, digits = 0;
    char *str = &text[0];

    for (int i = 0; i < strlen(text); ++i) {
        if(isalpha(text[i])){
            printf("Nao pode ter letras\n");
            return -1;
        }
        if(text[i] != text[i+1]){
            changes++;
        }
    }
    changes--;
    if(changes == 1){
        for (int i = 0; i < 3; ++i) {
            *(str+i) = text[i];
            if(text[i] == text[i+1]){
                bipolar = 1;
            }
        }
        number = atoi(str);
        return 0;
    }
    else{
        return -1;
    }
}

void print_bipolar_numbers(int k){

    int n[4] = {};
    int num = 1, rightNum = 0, leftNum = 0;
    int j = 0, changePos = k-1;

    /*
    for (int i = 0; i < k; ++i) {
        n[i] = leftNum;
        printf("%d", n[i]);
    }
    */

    while (1){
        if(leftNum == 9 && changePos == 0 && rightNum == 8){
            break;
        }
        if(rightNum == 9 && changePos == 0){
            rightNum = -1;
            leftNum++;
        }
        if(changePos == 0){
            changePos = k-1;
            if(rightNum != 9){
                rightNum++;
            } else{
                rightNum = -1;
            }
        }
        if(leftNum == rightNum){
            rightNum++;
        }
        if(j >= changePos){
            n[j] = rightNum;
        } else{
            n[j] = leftNum;
        }
        if(j == k){
            printf("\t");
            changePos--;
            j = 0;
        } else{
            printf("%d", n[j]);
            j++;
        }
    }
}

char* find_mul_bipolar_number(char *k){
    char *n;
    char rightNum = '0', leftNum = '1';
    int digitos = 2, j = 0, changePos = 0, numDigits = 2, findNonZero = 0;

    n = (char *) calloc(digitos, sizeof (char));
    while (1){
        n = (char *) realloc(n, digitos);
        if(leftNum == '9' && changePos == digitos -1 && rightNum == '8'){
            digitos++;
            changePos--;
            leftNum = '1';
            rightNum = '0';
        }
        if(rightNum == '9' && changePos == digitos -1){
            leftNum++;
        }
        if(changePos == digitos -1){
            changePos = 0;
            if(rightNum != '9'){
                rightNum++;
            } else{
                rightNum = '0';
            }
        }
        if(leftNum == rightNum){
            rightNum++;
        }
        if(j > changePos){
            n[j] = rightNum;
        } else{
            n[j] = leftNum;
        }
        if(j == digitos-1){
            if(atoi(n) > 2147483647 || atoi(n) < 0){
                n = "\0";
                return n;
            } else{
                numDigits = digitos;
                n[strlen(n)] = '\0';
                if(atoi(n) > atoi(k) && atoi(n)%atoi(k) == 0){
                    return n;
                }
                changePos++;
                j = 0;
            }

        } else{
            j++;
        }
    }
}

int find_mul_bipolar_number_Int(int k){
    int *n;
    int rightNum = 0, leftNum = 1;
    int digitos = 2, j = 0, changePos = 0, findNonZero = 0;

    n = (int *) calloc(digitos, sizeof (int));
    while (1){
        n = (int *) realloc(n, digitos);
        if(leftNum == 9 && changePos == digitos -1 && rightNum == 8){
            digitos++;
            leftNum = 1;
            rightNum = 0;
        }
        if(rightNum == 9 && changePos == digitos -1){
            leftNum++;
        }
        if(changePos == digitos -1){
            changePos = 0;
            if(rightNum != 9){
                rightNum++;
            } else{
                rightNum = 0;
            }
        }
        if(leftNum == rightNum){
            rightNum++;
        }
        if(j > changePos){
            n[j] = rightNum;
        } else{
            n[j] = leftNum;
        }
        if(j == digitos-1){
            if(*n > 2147483647 || *n < 0){
                n = NULL;
                return *n;
            } else{
                if(*n > k && *n%k == 0){
                    return *n;
                }
                changePos++;
                j = 0;
            }

        } else{
            j++;
        }
    }
}

int hist(char* num, int histo[]){
    for (int i = 0; i < 10; ++i) {
        histo[i] = 0;
    }
    for (int i = 0; i < strlen(num); ++i) {
        histo[*(num+i)-'0']++;
    }
    return 0;
}

int RL_V1(char* num, int runLess[]){
    int runLessPos = 0;
    char temp;
    for (int i = 0; i < strlen(num); ++i) {
        if(i == 0){
            runLess[runLessPos]++;
        } else{
            if(*(num+i) == temp){
                runLess[runLessPos]++;
            } else{
                runLessPos++;
                runLess[runLessPos] = temp-'0';
                runLessPos++;
                runLess[runLessPos]++;
            }
        }
        temp = *(num+i);
    }
    runLessPos++;
    runLess[runLessPos] = temp-'0';
}

int RL_V2(char *num, int runLess[]){
    int runLessPos = 0;
    runLess[runLessPos] = 1;
    runLess[runLessPos+1] = *(num)-'0';
    for (int i = 1; i < strlen(num); ++i) {
        if(*(num+i) != *(num+(i-1))){
            runLessPos += 2;
            runLess[runLessPos+1] = *(num+i)-'0';
        }
        runLess[runLessPos]++;
    }
}

int RL_V2_Ints(int num, int runLess[]){
    int runLessPos = 0, digits;
    digits = numDigits(num);
    int allD[digits];
    for (int i = 0; i < digits; ++i) {
        runLess[i] = 0;
    }
    if(num != 0){
        allDigits(num, allD);
        runLess[runLessPos] = 1;
        runLess[runLessPos+1] = allD[digits-1];
        for (int i = digits-1; i >= 0; i--) {
            if(allD[i] != allD[i-1]){
                runLessPos += 2;
                runLess[runLessPos+1] = allD[i-1];
            }
            runLess[runLessPos]++;
        }
    }
    else{
        return 0;
    }
}

char* RL_V2_String(char* num, char rL[]){
    int runLessPos = 0;
    char count = '1';
    *(rL+runLessPos) = count;
    *(rL+(runLessPos+1)) = *(num);
    for (int i = 1; i < strlen(num); ++i) {
        if(*(num+i) != *(num+(i-1))){
            runLessPos += 2;
            *(rL+(runLessPos+1)) = *(num+i);
            count='0';
        }
        count++;
        *(rL+runLessPos) = count;
    }
}

int numDigits(int num){
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num != 0);
    return digits;
}

int numDigitsLong(unsigned long long num){
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num != 0);
    return digits;
}

void allDigits(int num, int allD[]){
    int i = 0;
    while (num){
        allD[i] = num%10;
        num /= 10;
        i++;
    }
}

void allDigitsLong(unsigned long long num, int allD[]){
    int i = 0;
    while (num){
        allD[i] = num%10;
        num /= 10;
        i++;
    }
}

int countColumnPub(int digits, struct matrixString mString, int i, int columnsPub){
    digits = numDigits(atoi(mString.matrixPub[i]));
    if(digits > columnsPub){
        columnsPub = digits;
    }
    return columnsPub;
}
int countColumnPriv(int digits, struct matrixString mString, int i, int columnsPriv){
    digits = numDigits(atoi(mString.matrixPriv[i]));
    if(digits > columnsPriv){
        columnsPriv = digits;
    }
    return columnsPriv;
}

void printStringMatrixPub(struct matrixString mString, int lines){
    printf("\tStrings - Chaves Publicas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", mString.matrixPub[i]);
    }
}

void printStringMatrixPriv(struct matrixString mString, int lines){
    printf("\n\tStrings - Chaves Privadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        printf("%s\t", mString.matrixPriv[i]);
    }
}

void printStringMatrixCod(struct matrixString mString, int lines){
    printf("\n\tStrings - Chaves Codificadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%c\t", mString.matrixCod[i][j]);
        }
        printf("\n");
    }
}

void printIntMatrixPub(struct matrixInts mInts, int lines, int columns){
    printf("\n\tInts - Chaves Publicas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(mInts.matrixPub[i][j] >= 0) printf("%d\t", mInts.matrixPub[i][j]);
        }
        printf("\n");
    }
}

void printIntMatrixPriv(struct matrixInts mInts, int lines, int columns){
    printf("\n\tInts - Chaves Privadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(mInts.matrixPriv[i][j] >= 0) printf("%d\t", mInts.matrixPriv[i][j]);
        }
        printf("\n");
    }
}

void printIntMatrixCod(struct matrixInts mInts, int lines){
    printf("\n\tInts - Chaves Codificadas\t\n");
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(mInts.matrixCod[i][j] >= 0) printf("%d\t", mInts.matrixCod[i][j]);
            else printf("0\t");
        }
        printf("\n");
    }
}

int readFromFileString(struct matrixString mString, struct matrixInts mInts, int lines, FILE *fileChavesPubRead, char *fileName, int columns[], int digits, int pos){

    if(lines < pos) printf("Insira uma posicao possivel\n");
    fileChavesPubRead = fopen(fileName, "r");

    for (int i = pos; i < lines; ++i) {

        //Alocar espaço para cada nova linha da matriz e inicializar com 0
        mString.matrixPub[i] = (char *) calloc(lines * sizeof (char*), sizeof (char));
        mString.matrixPriv[i] = (char *) calloc(lines * sizeof (char*), sizeof (char));
        mString.matrixCod[i] = (char *) calloc(lines * sizeof (char*), sizeof (char));

        mInts.matrixPub[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixPriv[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixCod[i] = (int *) calloc(lines * sizeof (int *), sizeof (int));

        //Se já não haver valores para ler sai do array e para de alocar memoria
        if(fgets(mString.matrixPub[i], sizeof (mString.matrixPub[i]), fileChavesPubRead) == NULL){
            free(mString.matrixPub[i]);
            free(mString.matrixPriv[i]);
            free(mString.matrixCod[i]);
            free(mInts.matrixPub[i]);
            free(mInts.matrixPriv[i]);
            free(mInts.matrixCod[i]);
            break;
        }
        mString = receiveFileMatrixString(mString, columns, digits, lines, pos);
        lines++;
    }
    fclose(fileChavesPubRead);
    return lines;
}

int readFromString(struct matrixString mString, struct matrixInts mInts, int lines, int columns[], int digits, int pos, char *key){

    if(lines < pos) printf("Insira uma posicao possivel\n");

        //Alocar espaço para cada nova linha da matriz e inicializar com 0
        mString.matrixPub[pos] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixPriv[pos] = (char *) calloc(lines * sizeof (char *), sizeof (char));
        mString.matrixCod[pos] = (char *) calloc(lines * sizeof (char *), sizeof (char));

        mInts.matrixPub[pos] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixPriv[pos] = (int *) calloc(lines * sizeof (int *), sizeof (int));
        mInts.matrixCod[pos] = (int *) calloc(lines * sizeof (int *), sizeof (int));

        //Se já não haver valores para ler sai do array e para de alocar memoria
        mString.matrixPub[pos] = key;
        mString = receiveMatrixString(mString, columns, digits, lines, pos);
        lines++;
    return lines;
}

struct matrixString receiveFileMatrixString(struct matrixString mString, int columns[], int digits, int lines, int pos){
    for (int i = pos; i < lines; ++i) {
        //Recebe os valores do ficheiro e retira o \n e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPub)
        mString.matrixPub[i] = strtok(mString.matrixPub[i], "\n");
        *(mString.matrixPub[i]+ strlen(mString.matrixPub[i])) = '\0';
        columns[0] = countColumnPub(digits, mString, i, columns[0]);

        //Guarda o valor em matrixPriv[i]  e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPriv)
        if(strcmp(mString.matrixPub[i], "\0")){
            mString.matrixPriv[i] = find_mul_bipolar_number(mString.matrixPub[i]);
            columns[1] = countColumnPriv(digits, mString, i, columns[1]);
        }

        //Guarda o valor em matrixCod[i]
        if(strcmp(mString.matrixPriv[i], "\0")){
            RL_V2_String(mString.matrixPriv[i], mString.matrixCod[i]);
        }
    }
    return mString;
}
struct matrixString receiveMatrixString(struct matrixString mString, int columns[], int digits, int lines, int pos){
    //Recebe os valores do ficheiro e retira o \n e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPub)
    columns[0] = countColumnPub(digits, mString, pos, columns[0]);
    //Guarda o valor em matrixPriv[i]  e conta o numero de colunas que vao ser necessárias para a matriz de inteiros (columnsPriv)
    if(strcmp(mString.matrixPub[pos], "\0")){
        mString.matrixPriv[pos] = find_mul_bipolar_number(mString.matrixPub[pos]);
        columns[1] = countColumnPriv(digits, mString, pos, columns[1]);
    }
    //Guarda o valor em matrixCod[i]
    if(strcmp(mString.matrixPriv[pos], "\0")){
        RL_V2_String(mString.matrixPriv[pos], mString.matrixCod[pos]);
    }
    return mString;
}

void receiveMatrixPubInt(struct matrixString mString, struct matrixInts mInts, int columnsPub, int lines){
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
}

void receiveMatrixPrivInt(struct matrixString mString, struct matrixInts mInts, int columnsPriv, int lines){
    for (int i = 0; i < lines-1; ++i) {
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
}

void receiveMatrixCodInt(struct matrixString mString, struct matrixInts mInts, int lines){
    for (int i = 0; i < lines-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            //Se mString.matrixPriv[i] for uma string vazia inserimos -1 (este vai ser usardo como valor de referencia para uma coluna vazia visto que é ncessário escrever os '0')
            if(strcmp(mString.matrixPriv[i], "\0")){
                mInts.matrixCod[i][j] = mString.matrixCod[i][j] - '0';
            }else{
                mInts.matrixCod[i][j] = -1;
            }
        }
    }
}

void randomKeyFile(FILE *fileChavesPubWrite, char *fileName, int n){

    fileChavesPubWrite = fopen(fileName, "a");
    time_t t1;
    srand((unsigned ) time(&t1));
    for (int i = 0; i < n; ++i) {
        int r = rand()%250;
        fprintf(fileChavesPubWrite,"%d",r);
        fprintf(fileChavesPubWrite,"\n");
    }
    fclose(fileChavesPubWrite);
}

char** randomKeyMatrix(char** r, int n){
    int random = 0, digits = 0;

    r = (char **) malloc(n*sizeof (char *));
    for (int i = 0; i < n; ++i) {
        random = rand();
        digits = numDigits(random);
        r[i] = (char *) malloc(digits * sizeof (char));
        sprintf(r[i], "%d", random);
    }
    return r;
}

char* randomKeyValue(char* r){
    int random = 0, digits = 0;

    r = (char *) malloc(sizeof (char));
    for (int i = 0; i < 1; ++i) {
        random = rand()%250;
        digits = numDigits(random);
        sprintf(r, "%d", random);
    }
    return r;
}

struct matrixString removeKeyMatrix(struct matrixString mString, char *key, int lines){
    for (int i = 0; i < lines; ++i) {
        if(strcmp(mString.matrixPub[i], key) == 0){
            for (int j = i; j < lines-1; ++j) {
                strcpy(mString.matrixPub[j], mString.matrixPub[j+1]);
                strcpy(mString.matrixPriv[j], mString.matrixPriv[j+1]);
                strcpy(mString.matrixCod[j], mString.matrixCod[j+1]);
            }
            lines--;
        }
    }
    return mString;
}


//Funcoes do ficheiro dos professores
char* key_long_2_digits_char(unsigned long long key){
    int digits = numDigits(key);
    char *keydigits = malloc(digits * sizeof (char));
    sprintf(keydigits, "%llu", key);
    return keydigits;
}

unsigned long long key_digits_2_long_char(char* keydigits){
    return atoll(keydigits);
}

unsigned long long calc_private_key_char(unsigned long long pubkey){
    char *n;
    char rightNum = '0', leftNum = '1';
    int digitos = 2, j = 0, changePos = 0, numDigits = 2, findNonZero = 0;

    n = (char *) calloc(digitos, sizeof (char));
    while (1){
        n = (char *) realloc(n, digitos);
        if(leftNum == '9' && changePos == digitos -1 && rightNum == '8'){
            digitos++;
            changePos--;
            leftNum = '1';
            rightNum = '0';
        }
        if(rightNum == '9' && changePos == digitos -1){
            leftNum++;
        }
        if(changePos == digitos -1){
            changePos = 0;
            if(rightNum != '9'){
                rightNum++;
            } else{
                rightNum = '0';
            }
        }
        if(leftNum == rightNum){
            rightNum++;
        }
        if(j > changePos){
            n[j] = rightNum;
        } else{
            n[j] = leftNum;
        }
        if(j == digitos-1){
                numDigits = digitos;
                n[strlen(n)] = '\0';
                if(atoll(n) > ULONG_LONG_MAX || atoll(n) < 0) return 0;
                if(atoll(n) > pubkey && atoll(n)%pubkey == 0){
                    return atoll(n);
                }
                changePos++;
                j = 0;

        } else{
            j++;
        }
    }
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    unsigned long long codKey = 0;
    int runLessPos = 0, digits, pow = 10;
    digits = numDigitsLong(privkey);
    int allD[digits], runLess[4];

    for (int i = 0; i < 4; ++i) {
        runLess[i] = 0;
    }
    if(privkey >= 10){
        allDigitsLong(privkey, allD);
        runLess[runLessPos] = 1;
        runLess[runLessPos+1] = allD[digits-1];
        for (int i = digits-1; i >= 0; i--) {
            if(allD[i] != allD[i-1]){
                runLessPos += 2;
                runLess[runLessPos+1] = allD[i-1];
            }
            runLess[runLessPos]++;
        }
        for (int i = 3; i >= 0; i--) {
            if ( i == 3){
                codKey = runLess[i];
            } else{
                codKey += runLess[i]*pow;
                pow *= 10;
            }
        }
        return codKey;
    }
    else{
        return 0;
    }
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){} //TODO como descobrir a chave privada com a chave cod quando o numero de digitos da cod é maior que 4

char** alloc_matrix_char(int nlines, int ncolumns){
    char **matrix;
    matrix = (char **) calloc(nlines * sizeof (char *), sizeof (char *));
    for (int i = 0; i < nlines; ++i) {
        matrix[i] = (char *) calloc(ncolumns * sizeof (char), sizeof (char));
    }
    return matrix;
}

void store_key_char(char **matrix, int lines, unsigned long long key){
    char *keyChar = malloc(numDigitsLong(key) * sizeof (char));
    sprintf(keyChar, "%llu", key);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix[i], "\0") == 0){
            matrix[i] = keyChar;
            break;
        }
    }
}

int exists_key_char(char **matrix, int lines, unsigned long long key){
    char *keyChar = malloc(numDigitsLong(key) * sizeof (char));
    sprintf(keyChar, "%llu", key);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix[i], keyChar) == 0){
            return 1;
        }
    }
    return 0;
}

unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey){
    char *keyChar = malloc(numDigitsLong(pubkey) * sizeof (char));
    sprintf(keyChar, "%llu", pubkey);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], keyChar) == 0){
            return atoll(matrix_kpriv[i]);
        }
    }
    return 0;
}

unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey){
    char *keyChar = malloc(numDigitsLong(privkey) * sizeof (char));
    sprintf(keyChar, "%llu", privkey);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpriv[i], keyChar) == 0){
            return atoll(matrix_kcod[i]);
        }
    }
    return 0;
}

unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char pubkey){
    char *keyChar = malloc(numDigitsLong(pubkey) * sizeof (char));
    sprintf(keyChar, "%llu", pubkey);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], keyChar) == 0){
            free(matrix_kpub[i]);
            free(matrix_kpriv[i]);
            free(matrix_kcod[i]);
            break;
        }
    }
    return pubkey-'0';
} //TODO a chave publica não deveria ser *char ou invés de char porque assim só posso por 1 carater sendo que as chaves publicas podem ter mais de 1 carater

void bulk_populate_public_keys_char(char **matrix_kpub, int lines){
    time_t t1;
    srand((unsigned ) time(&t1));
    char** r = (char **) malloc(sizeof (char *));
    matrix_kpub = (char **) realloc(matrix_kpub, lines * sizeof (char *));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], "\0") == 0){
            matrix_kpub[i] = randomKeyValue(matrix_kpub[i]);
        }
    }
}

void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines){
    unsigned long long val;
    matrix_kpriv = (char **) realloc(matrix_kpriv, lines * sizeof (char *));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpriv[i], "\0") == 0){
            val = calc_private_key_char(atoll(matrix_kpub[i]));
            store_key_char(matrix_kpriv, lines, val);
        }
    }
}

void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines){
    unsigned long long val;
    matrix_kcod = (char **) realloc(matrix_kcod, lines * sizeof (char *));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kcod[i], "\0") == 0){
            val = calc_runlength_char(atoll(matrix_kpriv[i]));
            store_key_char(matrix_kcod, lines, val);
        }
    }
}

void sort_matrix_char(char **matrix, int lines, int order){
    shellSort(matrix, lines, order);
}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    shellSort(matrix_kpub, lines, order);
    shellSort(matrix_kpriv, lines, order);
    shellSort(matrix_kcod, lines, order);
}

void shellSort(char** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(strcmp(a[i], "\0") == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && atoll(a[j]) < atoll(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swap(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && atoll(a[j]) > atoll(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swap(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void shellSortDigits(char** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(strcmp(a[i], "\0") == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) < numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swap(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) > numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swap(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void swap(char** a, int i, int min){

    char* temp = (char *) calloc(strlen(a[min]) * sizeof (char), sizeof (char));
    strcpy(temp, a[min]);
    strcpy(a[min], a[i]);
    strcpy(a[i], temp);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    shellSortDigits(matrix_kpub, lines, order);
    shellSortDigits(matrix_kpriv, lines, order);
    shellSortDigits(matrix_kcod, lines, order);
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "r+");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], "\0") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kpub[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpriv[i], "\0") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kpriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kcod[i], "\0") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kcod[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }

    fclose(fileChavesPubWrite);
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fileChavesPubRead;
    fileChavesPubRead = fopen(filename, "r");
    int i = 1;
    unsigned long long privKey = 0, codKey = 0, t = 0;
    unsigned long long value;
    char str[lines][200];

    if(fileChavesPubRead == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    while (fscanf (fileChavesPubRead, "%llu", &value) == 1 && i < lines){
        privKey = calc_private_key_char(value);
        codKey = calc_runlength_char(privKey);
        store_key_char(matrix_kpub, lines, value);
        store_key_char(matrix_kpriv, lines, privKey);
        store_key_char(matrix_kcod, lines, codKey);
        i++;
    }

    fclose(fileChavesPubRead);
}