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
    int digitos = 2, j = 0, changePos = 0, numDigits = 2;

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
    int digitos = 2, j = 0, changePos = 0;

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

/**
 * Função que vai calcular o número de digitos de um número (int)
 * @param num número usado para calcular o seu número de digitos
 * @return número de digitos (int)
 */
int numDigits(int num){
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num != 0);
    return digits;
}

/**
 * Função que vai calcular o número de digitos de um número (unsigned long long)
 * @param num número usado para calcular o seu número de digitos
 * @return número de digitos (int)
 */
int numDigitsLong(unsigned long long num){
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num != 0);
    return digits;
}

/**
 * Função que vai dividir um número (int) por digitos e armazenar os mesmos num array
 * @param num número a ser dividido em digitos
 * @param allD aray com todos os digitos de num
 */
void allDigits(int num, int allD[]){
    int i = 0;
    while (num){
        allD[i] = num%10;
        num /= 10;
        i++;
    }
}

/**
 * Função que vai dividir um número (unsigned long long) por digitos e armazenar os mesmos num array
 * @param num número a ser dividido em digitos
 * @param allD aray com todos os digitos de num
 */
void allDigitsLong(unsigned long long num, int allD[]){
    int i = 0;
    while (num){
        allD[i] = num%10;
        num /= 10;
        i++;
    }
}

/**
 * Função que gera um número aleatório e insere num ficheiro
 * @param fileChavesPubWrite ficheiro qe vai receber o número aleatório
 * @param fileName nome do ficheiro
 * @param n número de números aleatórios a serem gerados para o ficheiro
 */
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

/**
 * Função que vai gerar um número aleatório e retornar o mesmo em char**
 * @param r matrix de strings (char*)
 * @param n número de números aleatórios a serem gerados
 * @return da matrix de strings (char*)
 */
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

/**
 * Função que retorna um número aleatório (char*)
 * @param r apontador de char (char*) usado para armazenar o número em carateres
 * @return do número em carateres
 */
char* randomKeyValue(char* r){
    int random = 0, digits = 0;

    r = (char *) malloc(sizeof (char));
    for (int i = 0; i < 1; ++i) {
        random = rand()%250;
        digits = numDigits(random);
        sprintf(r, "%d", random);
    }
    char *returnval = r;
    r=NULL;
    free(r);
    return returnval;
}

/**
 * Função que retorna um número aleatório em short
 * @param r variável que vai conter o número aleatório a ser retornado
 * @return valor aleatório short
 */
short randomKeyValueShort(short r){
    int digits = 0;
    for (int i = 0; i < 1; ++i) {
        r = rand()%250;
        digits = numDigits(r);
    }
    return r;
}

void shellSortChar(char** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(strcmp(a[i], "\0") == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && atoll(a[j]) < atoll(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && atoll(a[j]) > atoll(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void shellSortCharDigits(char** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(strcmp(a[i], "\0") == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) < numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) > numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void swapChar(char** a, int i, int min){

    char* temp = (char *) calloc(strlen(a[min]) * sizeof (char), sizeof (char));
    strcpy(temp, a[min]);
    strcpy(a[min], a[i]);
    strcpy(a[i], temp);
    temp = NULL;
    free(temp);
}

void shellSortInt(short** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(a[i][0] == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && key_digits_2_long_int(a[j]) < key_digits_2_long_int(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && key_digits_2_long_int(a[j]) > key_digits_2_long_int(a[j-h]); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void shellSortIntDigits(short** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            if(a[i][0] == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && numDigitsLong(key_digits_2_long_int(a[j])) < numDigitsLong(key_digits_2_long_int(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && numDigitsLong(key_digits_2_long_int(a[j])) > numDigitsLong(key_digits_2_long_int(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

void swapInt(short** a, int i, int min){

    short* temp = (short *) calloc(numDigitsLong(key_digits_2_long_int(a[min])), sizeof (short ));
    temp = a[min];
    a[min] = a[i];
    a[i] = temp;
    temp = NULL;
    free(temp);
}


//Funcoes Strings do ficheiro dos professores
char* key_long_2_digits_char(unsigned long long key){
    int digits = numDigits(key);                        //variavel com o numero de digitos de (key)
    char *keydigits = malloc(digits * sizeof (char));   //alocar memória para *keydigits com o valor de (digits)
    sprintf(keydigits, "%llu", key);           //converter o valor de (unsigned long long) para (char*)
    return keydigits;                                         //returnar o valor de (keydigits)
}

unsigned long long key_digits_2_long_char(char* keydigits){
    return atoll(keydigits);    //converter de (char*) para (unsigned long long) e returnar o valor
}

unsigned long long calc_private_key_char(unsigned long long pubkey){
    char *n;                                                                    //Apontador que vai receber cada digito para formar um número
    int digitos = numDigitsLong(pubkey*2), j = 0, changePos = 0, numDigits = 2;                       //digitos = 2 pois o primeiro númnero a ser criado vai ter 2 digitos / j = 0 vai ser usado para comparar o número de digitos atual
                                                                                //changePos = 0 vai ser a variável usada para sabermos quando parar de converter números à direita
    short *allD = key_long_2_digits_int(pubkey*2);
    char rightNum = allD[1]+'0', leftNum = allD[0]+'0';                     //rightNum -> número a inserir à direita começa em 0 -> ++ / leftNum -> número a inserir à esquerda começa em 1 -> ++

    if(pubkey <= 5){
        rightNum = '0';
        leftNum = '1';
    }
    if(digitos < 2) digitos = 2;
    n = (char *) calloc(digitos, sizeof (char));    //Alocar memória para n
    while (1){                                                                  //Ciclo infinito (vai ter condições de paragem dentro dele)
        if(leftNum == '9' && changePos == digitos -1 && rightNum == '8'){       //Se o leftNum = 9 e a changePos = limite de digitos e rightNum = 8 temos (98, 988, 9888) então
            digitos++;                                                          //Chegamos ao ultimo número gerado bipolar com este núemro de digito então incrementamos o número de digitos
            n=NULL;                                                             //Apagamos o conteudo atual de n
            n = (char *) realloc(n, digitos);                  //realocar memória para n com o novo número de digitos

            changePos = 0;                                                        //diminuir a changePos
            leftNum = '1';                                                      //Resetar o valor de leftNum e de rigthNum
            rightNum = '0';
        }
        if(rightNum == '9' && changePos == digitos -1){                         //Se rigthNum = 9 e changePos = limite de digitos do número menos o primeiro digito então
            leftNum++;                                                          //aumentamos o valor de leftNum pois chegamos ao maior valor para este leftNum (19 -> 20, 1999 -> 2000, 19999 -> 20000)
        }
        if(changePos == digitos -1){                                            //Se changePos = limite de digitos do número então
            changePos = 0;                                                      //Resetar a changePos pois chegamos à ultima posição para este valor de rightNum (1112 -> 1122 -> 1222 -> 1113)
            if(rightNum != '9'){                                                //Se rightNum != 9 incrementamos o rightNum
                rightNum++;
            } else{                                                             //Se rigthNum = 9 então resetamos o valor de rigthNum
                rightNum = '0';
            }
        }
        if(leftNum == rightNum){                                                //Se leftNum = rigthNum então podemos dar skip a estes valores pois (1111, 2222, 3333) não são bipolares
            rightNum++;
        }
        if(j > changePos){                                                      //Se a posição do digito a ser mudado atualmente for maior que changePos então
            n[j] = rightNum;                                                    //este valor vai ser igual a rigthNum ex: rigthNum=2 (1112), rigthNum=3 (2333), rigthNum=6 (8866)
        } else{                                                                 //Se não então igualamos ao valor de leftNum
            n[j] = leftNum;
        }
        if(j == digitos-1){                                                             //Se j = ao número de digitos então
                numDigits = digitos;
                n[strlen(n)] = '\0';                                                //Inserir o \0 no final da string
                //printf("PivKey = %llu\n", atoll(n));
                if(atoll(n) > 1000000000000 || atoll(n) < 0 || pubkey == 0){
                    n=NULL;
                    free(allD);
                    free(n);
                    n=NULL;
                    return 0;  //Se o valor for maior que o suportado para (unsigned long long) ou for menor que 0 ou se a pubkey for igual a 0 returna 0
                }
                if(atoll(n) > pubkey && atoll(n)%pubkey == 0){                          //Se (unsigned long long) de n for maior que pubkey(pq a pubkey é multipla dela mesma) e (unsigned long long) de n for multiplo de pubkey
                    unsigned long long valorFinal = atoll(n);                           //valorFinal vai ser igual a (unsigned long long) de n
                    n=NULL;                                                             //Limpa n e dá free à memória
                    free(allD);
                    free(n);
                    n=NULL;
                    return valorFinal;                                                  //retorna o valorFinal
                }
                changePos++;                                                            //Se não changePos++ e resetamos o j
                j = 0;
        } else{                                                                         //Se não incrementamos o j
            j++;
        }
    }
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    unsigned long long codKey = 0;
    int runLessPos = 0, digits, pow = 1;
    digits = numDigitsLong(privkey);
    int allD[digits], runLess[4];

    //Ciclo para zerar runLess
    for (int i = 0; i < 4; ++i) {
        runLess[i] = 0;
    }
    //Se privKey maior ou igual que 10 vai calcular a sua run Length
    if(privkey >= 10){
        allDigitsLong(privkey, allD);
        runLess[runLessPos] = 1;
        runLess[runLessPos+1] = allD[digits-1];
        for (int i = digits-1; i > 0; i--) {
            if(allD[i] != allD[i-1]){
                runLessPos += 2;
                runLess[runLessPos+1] = allD[i-1];
            }
            runLess[runLessPos]++;
        }
        for (int i = 0; i < 4; i++) {
            if ( i == 0){
                codKey = runLess[i];
            } else{
                for (int j = 0; j < numDigitsLong(runLess[i]); ++j) {
                    pow *= 10;
                }
                codKey *= pow;
                codKey += runLess[i];
                pow = 1;
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
    matrix = (char **) calloc(nlines, sizeof (char *));
    for (int i = 0; i < nlines; ++i) {
        matrix[i] = (char *) calloc(ncolumns, sizeof (char));
    }
    return matrix;
}


void store_key_char(char **matrix, int lines, unsigned long long key){
    char *keyChar = malloc(numDigitsLong(key) * sizeof (char));
    sprintf(keyChar, "%llu", key);
    for (int i = 0; i < lines; ++i) {
        if(!matrix[i][0]){
            //matrix[i] = (char *) realloc(matrix[i], strlen(keyChar) * sizeof (char));
            matrix[i] = keyChar;
            break;
        }
    }
    keyChar=NULL;
    free(keyChar);
}


int exists_key_char(char **matrix, int lines, unsigned long long key){
    char *keyChar = malloc(numDigitsLong(key) * sizeof (char));
    sprintf(keyChar, "%llu", key);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix[i], keyChar) == 0){
            keyChar=NULL;
            free(keyChar);
            return 1;
        }
    }
    keyChar=NULL;
    free(keyChar);
    return 0;
}


unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey){
    char *keyChar = malloc(numDigitsLong(pubkey) * sizeof (char));
    sprintf(keyChar, "%llu", pubkey);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], keyChar) == 0){
            keyChar=NULL;
            free(keyChar);
            return atoll(matrix_kpriv[i]);
        }
    }
    keyChar=NULL;
    free(keyChar);
    return 0;
}


unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey){
    char *keyChar = malloc(numDigitsLong(privkey) * sizeof (char));
    sprintf(keyChar, "%llu", privkey);
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpriv[i], keyChar) == 0){
            keyChar=NULL;
            free(keyChar);
            return atoll(matrix_kcod[i]);
        }
    }
    keyChar=NULL;
    free(keyChar);
    return 0;
}


unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char* pubkey){
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpub[i] || matrix_kpub[i][0] == '\0') continue;
        if(strcmp(matrix_kpub[i], pubkey) == 0){
            for (int j = i; j < lines; ++j) {
                if(j == lines-1){
                    matrix_kpub[lines-1] = NULL;
                    matrix_kpriv[lines-1] = NULL;
                    matrix_kcod[lines-1] = NULL;
                    free(matrix_kpub[lines-1]);
                    free(matrix_kpriv[lines-1]);
                    free(matrix_kcod[lines-1]);
                }
                else{
                    matrix_kpub[j] = matrix_kpub[j+1];
                    matrix_kpriv[j] = matrix_kpriv[j+1];
                    matrix_kcod[j] = matrix_kcod[j+1];
                }
            }
            lines--;
        }
    }
    return atoll(pubkey);
}

void bulk_populate_public_keys_char(char **matrix_kpub, int lines){
    char* r = NULL;
    matrix_kpub = (char **) realloc(matrix_kpub, lines * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpub[i] || matrix_kpub[i][0] == '\0'){
            r = randomKeyValue(matrix_kpub[i]);
            matrix_kpub[i] = (char *) calloc(strlen(r), sizeof (char));
            store_key_char(matrix_kpub, lines, atoll(r));
            //matrix_kpub[i] = randomKeyValue(matrix_kpub[i]);
        }
        r=NULL;
        free(r);
    }
}

void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines){
    unsigned long long val = 0;
    matrix_kpriv = (char **) realloc(matrix_kpriv, lines * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpriv[i] || matrix_kpriv[i][0] == '\0'){
            val = calc_private_key_char(atoll(matrix_kpub[i]));
            matrix_kpriv[i] = (char *) calloc(numDigitsLong(val), sizeof (char));
            store_key_char(matrix_kpriv, lines, val);
        }
    }
}

void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines){
    unsigned long long val;
    matrix_kcod = (char **) realloc(matrix_kcod, lines * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kcod[i] || matrix_kcod[i][0] == '\0'){
            val = calc_runlength_char(atoll(matrix_kpriv[i]));
            matrix_kcod[i] = (char *) calloc(numDigitsLong(val), sizeof (char));
            store_key_char(matrix_kcod, lines, val);
        }
    }
}

char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey){

    char **result = malloc(sizeof (char *));
    char *partialPubKeyChar = (char *) malloc(numDigitsLong(partialpubkey) * sizeof (char));
    sprintf(partialPubKeyChar, "%llu", partialpubkey);
    int partialPubKeySize = strlen(partialPubKeyChar);
    int sizeResult = 0, posResult = 0;
    unsigned long long val = 0;

    for (int i = 0; i < lines; ++i) {
        int k = 0;
        if(!matrix_kpub[i] || matrix_kpub[i][0] == '\0') continue;
        for (int j = 0; j < strlen(matrix_kpub[i]); ++j) {
            if(matrix_kpub[i][j] == partialPubKeyChar[k]){
                k++;
            } else{
                k = 0;
            }
            if(k == strlen(partialPubKeyChar)){
                sizeResult++;
                result = (char **) realloc(result, sizeResult * sizeof (char *));
                val = get_private_key_char(matrix_kpub, matrix_kpriv, lines, atoll(matrix_kpub[i]));
                result[posResult] = (char *) malloc(numDigitsLong(val) * sizeof (char));
                sprintf(result[posResult], "%llu", val);
                posResult++;
            }
        }
    }

    partialPubKeyChar = NULL;
    free(partialPubKeyChar);

    return result;

} //TODO escreve o ultimo valor +1 dq devia

void sort_matrix_char(char **matrix, int lines, int order){
    shellSortChar(matrix, lines, order);
}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    shellSortChar(matrix_kpub, lines, order);
    shellSortChar(matrix_kpriv, lines, order);
    shellSortChar(matrix_kcod, lines, order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    shellSortCharDigits(matrix_kpub, lines, order);
    shellSortCharDigits(matrix_kpriv, lines, order);
    shellSortCharDigits(matrix_kcod, lines, order);
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
    unsigned long long privKey = 0, codKey = 0, t = 0, count = 1;
    unsigned long long *value = (unsigned long long *) calloc(count, sizeof (unsigned long long));
    char str[lines][200];

    if(fileChavesPubRead == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    while (fscanf (fileChavesPubRead, "%llu", &value[count-1]) == 1){
        count++;
        value = (unsigned long long *) realloc(value, count * sizeof (unsigned long long));
    }

    while (i <= lines && i < count/3){
        privKey = calc_private_key_char(value[i]);
        codKey = calc_runlength_char(privKey);
        store_key_char(matrix_kpub, lines, value[i]);
        store_key_char(matrix_kpriv, lines, privKey);
        store_key_char(matrix_kcod, lines, codKey);
        i++;
    }

    fclose(fileChavesPubRead);
}


//Funcoes Ints do ficheiro dos professores
unsigned long long new_public_key_int(void){
    unsigned long long r = 0;
    for (int i = 0; i < 1; ++i) {
        r = rand()%250;
    }
    return r;
}

short* key_long_2_digits_int(unsigned long long key){
    int i = 0, s=0, hi = numDigitsLong(key)-1, size = (numDigitsLong(key)+1);
    short *keyDigits = (short *) calloc(size * sizeof (short), sizeof (short ));
    short temp = 0;
    unsigned long long tempKey = key;
    if (keyDigits == NULL) {
        printf("Erro no malloc\n");
        return 0;
    }
    while (tempKey){
        keyDigits[i] = tempKey%10;
        tempKey /= 10;
        i++;
    }
    for (int j = 0; j < numDigitsLong(key); ++j) {
        if(hi <= j) break;
        temp = keyDigits[j];
        keyDigits[j] = keyDigits[hi];
        keyDigits[hi] = temp;
        hi--;
    }
    keyDigits[size-1] = -1;
    return keyDigits;
}

unsigned long long key_digits_2_long_int(short* keydigits){
    int i = 0, size = 0, pow = 10;
    unsigned long long pubKey = 0;

    while (1){
        if(keydigits[i] < 0) break;
        i++;
        size++;
    }
    if(size == 0) return 0;

    for (int j = 0; j < size; j++) {
        if(j == 0){
            pubKey = keydigits[j];
        } else{
            if(keydigits[j] == 0){
                pubKey *= pow;
            } else{
                pubKey *= pow;
                pubKey += keydigits[j];
            }
        }
    }

    return pubKey;
}

unsigned long long calc_private_key_int(unsigned long long pubkey){
    unsigned long long privKey = 0;
    short *n;
    int digitos = numDigitsLong(pubkey*2), j = 0, changePos = 0;
    short *allD = key_long_2_digits_int(pubkey*2);
    short rightNum = allD[1], leftNum = allD[0];

    if(pubkey <= 5){
        rightNum = 0;
        leftNum = 1;
    }
    if(digitos < 2) digitos = 2;
    n = (short *) calloc(digitos, sizeof (short));
    while (1){
        if(leftNum == 9 && changePos == digitos -1 && rightNum == 8){
            digitos++;
            n=NULL;
            free(n);
            n = (short *) calloc(digitos, sizeof (short ));
            //n = (short *) calloc(digitos, sizeof (short ));
            changePos--;
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
            n[digitos] = -1;
            privKey = key_digits_2_long_int(n);
            //printf("PivKey = %llu\n", privKey);
            if(privKey > 1000000000000 || privKey < 0 || pubkey == 0){
                n=NULL;
                free(n);
                return 0;
            }
            if(privKey > pubkey && privKey%pubkey == 0){
                n=NULL;
                free(n);
                return privKey;
            }
            changePos++;
            j = 0;

        } else{
            j++;
        }
    }
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    unsigned long long codKey = 0;
    int runLessPos = 0, digits, pow = 1;
    digits = numDigitsLong(privkey);
    int allD[digits], runLess[4];

    for (int i = 0; i < 4; ++i) {
        runLess[i] = 0;
    }
    if(privkey >= 10){
        allDigitsLong(privkey, allD);
        runLess[runLessPos] = 1;
        runLess[runLessPos+1] = allD[digits-1];
        for (int i = digits-1; i > 0; i--) {
            if(allD[i] != allD[i-1]){
                runLessPos += 2;
                runLess[runLessPos+1] = allD[i-1];
            }
            runLess[runLessPos]++;
        }
        for (int i = 0; i < 4; i++) {
            if ( i == 0){
                codKey = runLess[i];
            } else{
                for (int j = 0; j < numDigitsLong(runLess[i]); ++j) {
                    pow *= 10;
                }
                codKey *= pow;
                codKey += runLess[i];
                pow = 1;
            }
        }
        return codKey;
    }
    else{
        return 0;
    }
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey); //TODO como descobrir a chave privada com a chave cod quando o numero de digitos da cod é maior que 4

short** alloc_matrix_int(int nlines, int ncolumns){
    short **matrix;
    matrix = (short **) calloc(nlines * sizeof (short *), sizeof (short *));
    for (int i = 0; i < nlines; ++i) {
        matrix[i] = (short *) calloc(ncolumns * sizeof (short), sizeof (short));
    }
    return matrix;
}

void store_key_int(short **matrix, int lines, unsigned long long key){
    short *allD = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        if(!matrix[i][0] && matrix[i][1] == -1) continue;
        if(!matrix[i][0]){
            matrix[i] = (short *) calloc(numDigitsLong(key)+1, sizeof (short));
            matrix[i] = allD;
            break;
        }
    }
    allD = NULL;
    free(allD);
}

int exists_key_int(short **matrix, int lines, unsigned long long key){
    short *allD = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        if(!matrix[i][0]){
            break;
        }
        if(key_digits_2_long_int(matrix[i]) == key_digits_2_long_int(allD)){
            allD = NULL;
            free(allD);
            return 1;
        }
        /*
        int j = 0;
        while (matrix[i][j] != -1){
            if(matrix[i][j] != allD[j]){
                break;
            } else{
                if(matrix[i][j+1] == -1 && allD[j+1] == -1){
                    return 1;
                }
            }
            j++;
        }
        */
    }
    return 0;
}

unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey){
    for (int i = 0; i < lines; ++i) {
        if(key_digits_2_long_int(matrix_kpub[i]) == pubkey){
            return key_digits_2_long_int(matrix_kpriv[i]);
        }
    }
    return 0;
}

unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey){
    for (int i = 0; i < lines; ++i) {
        if(key_digits_2_long_int(matrix_kpriv[i]) == privkey){
            return key_digits_2_long_int(matrix_kcod[i]);
        }
    }
    return 0;
}

unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey){
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpub[i] || matrix_kpub[i][0] == 0) continue;
        if(key_digits_2_long_int(matrix_kpub[i]) == pubkey){
            for (int j = i; j < lines; ++j) {
                if(j == lines-1){
                    matrix_kpub[j] = NULL;
                    matrix_kpriv[j] = NULL;
                    matrix_kcod[j] = NULL;
                    free(matrix_kpub[j]);
                    free(matrix_kpriv[j]);
                    free(matrix_kcod[j]);
                    break;
                }
                matrix_kpub[j] = matrix_kpub[j+1];
                matrix_kpriv[j] = matrix_kpriv[j+1];
                matrix_kcod[j] = matrix_kcod[j+1];
            }
            lines--;
        }
    }
    return pubkey;
}

void bulk_populate_public_keys_int(short **matrix_kpub, int lines){
    unsigned long long r;
    matrix_kpub = (short **) realloc(matrix_kpub, lines * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpub[i] || matrix_kpub[i][0] == 0){
            r = new_public_key_int();
            matrix_kpub[i] = (short *) calloc(numDigitsLong(r)+1, sizeof (short ));
            store_key_int(matrix_kpub, lines, r);
        }
    }
}

void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines){
    unsigned long long val = 0;
    matrix_kpriv = (short **) realloc(matrix_kpriv, lines * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kpriv[i] || matrix_kpriv[i][0] == 0){
            val = calc_private_key_int(key_digits_2_long_int(matrix_kpub[i]));
            matrix_kpriv[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kpriv, lines, val);
        }
    }
}

void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines){
    unsigned long long val = 0;
    matrix_kcod = (short **) realloc(matrix_kcod, lines * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        if(!matrix_kcod[i] || matrix_kcod[i][0] == 0){
            val = calc_runlength_int(key_digits_2_long_int(matrix_kpriv[i]));
            matrix_kcod[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kcod, lines, val);
        }
    }
}

short** search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey){
    short **result = malloc(sizeof (short *));
    int sizeResult = 0, posResult = 0;
    unsigned long long val = 0;
    short * valArray = NULL, *partialKeyArray = (short *) malloc(numDigitsLong(partialpubkey));
    partialKeyArray = key_long_2_digits_int(partialpubkey);

    for (int i = 0; i < lines; ++i) {
        //if(matrix_kpub[i][0] == NULL) break;
        int k = 0;
        if(!matrix_kpub[i] || matrix_kpub[i][0] == 0) continue;
        for (int j = 0; j < numDigitsLong(key_digits_2_long_int(matrix_kpub[i])); ++j) {
            if(matrix_kpub[i][j] == partialKeyArray[k]){
                k++;
            } else{
                k = 0;
            }
            if(k == numDigitsLong(partialpubkey)){
                sizeResult++;
                result = (short **) realloc(result, sizeResult * sizeof (short *));
                val = get_private_key_int(matrix_kpub, matrix_kpriv, lines, key_digits_2_long_int(matrix_kpub[i]));
                valArray = (short *) malloc(numDigitsLong(val) * sizeof (short));
                valArray = key_long_2_digits_int(val);
                result[posResult] = (short *) malloc(numDigitsLong(val) * sizeof (short));
                for (int l = 0; l <= numDigitsLong(val); ++l) {
                    result[posResult][l] = valArray[l];
                }
                posResult++;
            }
        }
    }

    valArray = NULL;
    free(valArray);
    partialKeyArray = NULL;
    free(partialKeyArray);
    return result;
}

void sort_matrix_int(short **matrix, int lines, int order){
    shellSortInt(matrix, lines, order);
}

void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    shellSortInt(matrix_kpub, lines, order);
    shellSortInt(matrix_kpriv, lines, order);
    shellSortInt(matrix_kcod, lines, order);
}

void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    shellSortIntDigits(matrix_kpub, lines, order);
    shellSortIntDigits(matrix_kpriv, lines, order);
    shellSortIntDigits(matrix_kcod, lines, order);
}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){

    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "r+");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpub[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpub[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpriv[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }for (int i = 0; i < lines; ++i) {
        if(matrix_kcod[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kcod[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }

    fclose(fileChavesPubWrite);
}

void load_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){

    FILE *fileChavesPubRead;
    fileChavesPubRead = fopen(filename, "r");
    int i = 0;
    unsigned long long privKey = 0, codKey = 0, count = 1;
    unsigned long long *value = (unsigned long long *) calloc(count, sizeof (unsigned long long));

    if(fileChavesPubRead == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    while (fscanf (fileChavesPubRead, "%llu", &value[count-1]) == 1){
        count++;
        value = (unsigned long long *) realloc(value, count * sizeof (unsigned long long));
    }

    while (i <= lines && i < count/3){
        privKey = calc_private_key_int(value[i]);
        codKey = calc_runlength_int(privKey);
        store_key_int(matrix_kpub, lines, value[i]);
        store_key_int(matrix_kpriv, lines, privKey);
        store_key_int(matrix_kcod, lines, codKey);
        i++;
    }

    free(value);
    fclose(fileChavesPubRead);
}


// Funcoes para porta-chaves
void insert_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts, int pos){
    KEY_HOLDER* new_keyHolder = (KEY_HOLDER *) malloc(sizeof (KEY_HOLDER));
    time_t data_criacao;
    time(&data_criacao);
    time_t data_modificacao;
    time(&data_modificacao);

    if(new_keyHolder == NULL){
        exit(1);
    }
    new_keyHolder->next = *portaChaves;
    new_keyHolder->khString.matrixPub = alloc_matrix_char(2, 1);
    new_keyHolder->khString.matrixPriv = alloc_matrix_char(2, 1);
    new_keyHolder->khString.matrixCod = alloc_matrix_char(2, 1);
    new_keyHolder->khInts.matrixPub = alloc_matrix_int(2, 1);
    new_keyHolder->khInts.matrixPriv = alloc_matrix_int(2, 1);
    new_keyHolder->khInts.matrixCod = alloc_matrix_int(2, 1);

    store_key_char(new_keyHolder->khString.matrixPub, 2, atoll(mString.matrixPub[pos]));
    store_key_char(new_keyHolder->khString.matrixPriv, 2, atoll(mString.matrixPriv[pos]));
    store_key_char(new_keyHolder->khString.matrixCod, 2, atoll(mString.matrixCod[pos]));
    store_key_int(new_keyHolder->khInts.matrixPub, 2, key_digits_2_long_int(mInts.matrixPub[pos]));
    store_key_int(new_keyHolder->khInts.matrixPriv, 2, key_digits_2_long_int(mInts.matrixPriv[pos]));
    store_key_int(new_keyHolder->khInts.matrixCod, 2, key_digits_2_long_int(mInts.matrixCod[pos]));

    new_keyHolder->khString.matrixPub[1] = NULL;
    new_keyHolder->khString.matrixPriv[1] = NULL;
    new_keyHolder->khString.matrixCod[1] = NULL;
    new_keyHolder->khInts.matrixPub[1] = NULL;
    new_keyHolder->khInts.matrixPriv[1] = NULL;
    new_keyHolder->khInts.matrixCod[1] = NULL;
    /*
    new_keyHolder->khString = mString;
    new_keyHolder->khInts = mInts;
     */
    new_keyHolder->data_criacao = ctime(&data_criacao);
    new_keyHolder->data_modificacao = ctime(&data_modificacao);

    if(*portaChaves == NULL){
        *portaChaves = new_keyHolder;
        return;
    }

    *portaChaves = new_keyHolder;
}

void edit_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, int keyPosChange, int newKeyPos){
    //KEY_HOLDER* new_keyHolder = (KEY_HOLDER *) malloc(sizeof (KEY_HOLDER));
    KEY_HOLDER *temp = NULL;
    time_t data_modificacao;
    time(&data_modificacao);
    int stopPos=1, isAdd = 0, size = 0, sizeMax = 1;

    KEY_HOLDER * curr = *portaChaves;
    while (stopPos != keyHolderPos){
        temp = curr;
        curr = curr->next;
        stopPos++;
    }
    //portaChaves->next = new_keyHolder;
    for (int i = 0; curr->khString.matrixPub[i] != NULL; ++i) {
        sizeMax++;
    }

    for (int j = 0; j <= keyPosChange; ++j) {
        if(!curr->khString.matrixPub[j]){
            curr->khString.matrixPub[j] = realloc(curr->khString.matrixPub[j],numDigitsLong(atoll(mString.matrixPub[newKeyPos])));
            curr->khString.matrixPub[j] =  mString.matrixPub[newKeyPos];
            isAdd = 1;
        }
        if(!curr->khString.matrixPriv[j]){
            curr->khString.matrixPriv[j] = realloc(curr->khString.matrixPriv[j],numDigitsLong(atoll(mString.matrixPriv[newKeyPos])));
            curr->khString.matrixPriv[j] = mString.matrixPriv[newKeyPos];
            isAdd = 1;
        }
        if(!curr->khString.matrixCod[j]){
            curr->khString.matrixCod[j] = realloc(curr->khString.matrixCod[j],numDigitsLong(atoll(mString.matrixCod[newKeyPos])));
            curr->khString.matrixCod[j] = mString.matrixCod[newKeyPos];
            isAdd = 1;
        }
        if(!curr->khInts.matrixPub[j]){
            curr->khInts.matrixPub[j] = realloc(curr->khInts.matrixPub[j],numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos])));
            for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos]))+1; ++i) {
                curr->khInts.matrixPub[j][i] = mInts.matrixPub[newKeyPos][i];
            }
            isAdd = 1;
        }
        if(!curr->khInts.matrixPriv[j]){
            curr->khInts.matrixPriv[j] = realloc(curr->khInts.matrixPriv[j],numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos])));
            for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1; ++i) {
                curr->khInts.matrixPriv[j][i] = mInts.matrixPriv[newKeyPos][i];
            }
            isAdd = 1;
        }
        if(!curr->khInts.matrixCod[j]){
            curr->khInts.matrixCod[j] = realloc(curr->khInts.matrixCod[j],numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos])));
            for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos]))+1; ++i) {
                curr->khInts.matrixCod[j][i] = mInts.matrixCod[newKeyPos][i];
            }
            isAdd = 1;
        }
        if(isAdd == 1){
            if(j+1 >= sizeMax){
                curr->khString.matrixPub[j+1] = NULL;
                curr->khString.matrixPriv[j+1] = NULL;
                curr->khString.matrixCod[j+1] = NULL;
                curr->khInts.matrixPub[j+1] = NULL;
                curr->khInts.matrixPriv[j+1] = NULL;
                curr->khInts.matrixCod[j+1] = NULL;
            }
            break;
        }
        size++;
    }
    if(isAdd == 0){
        //curr->khString.matrixPub = (char**) realloc(curr->khString.matrixPub, (sizeMax+1)*sizeof (char*));
        //curr->khString.matrixPriv = (char**) realloc(curr->khString.matrixPriv, (sizeMax+1)*sizeof (char*));
        //curr->khString.matrixCod = (char**) realloc(curr->khString.matrixCod, (sizeMax+1)*sizeof (char*));
        //curr->khInts.matrixPub = (short**) realloc(curr->khInts.matrixPub, (sizeMax+1)*sizeof (short*));
        //curr->khInts.matrixPriv = (short**) realloc(curr->khInts.matrixPriv, (sizeMax+1)*sizeof (short*));
        //curr->khInts.matrixCod = (short**) realloc(curr->khInts.matrixCod, (sizeMax+1)*sizeof (short*));

        curr->khString.matrixPub[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixPub[newKeyPos])), sizeof (char ));
        curr->khString.matrixPriv[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixPriv[newKeyPos])), sizeof (char ));
        curr->khString.matrixCod[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixCod[newKeyPos])),  sizeof (char ));
        curr->khInts.matrixPub[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos]))+1, sizeof (short ));
        curr->khInts.matrixPriv[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1, sizeof (short ));
        curr->khInts.matrixCod[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos]))+1, sizeof (short ));

        curr->khString.matrixPub[keyPosChange+1] = NULL;
        curr->khString.matrixPriv[keyPosChange+1] = NULL;
        curr->khString.matrixCod[keyPosChange+1] = NULL;
        curr->khInts.matrixPub[keyPosChange+1] = NULL;
        curr->khInts.matrixPriv[keyPosChange+1] = NULL;
        curr->khInts.matrixCod[keyPosChange+1] = NULL;

        curr->khString.matrixPub[keyPosChange] =  mString.matrixPub[newKeyPos];
        curr->khString.matrixPriv[keyPosChange] = mString.matrixPriv[newKeyPos];
        curr->khString.matrixCod[keyPosChange] = mString.matrixCod[newKeyPos];
        for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos]))+1; ++i) {
            curr->khInts.matrixPub[keyPosChange][i] = mInts.matrixPub[newKeyPos][i];
        }
        for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1; ++i) {
            curr->khInts.matrixPriv[keyPosChange][i] = mInts.matrixPriv[newKeyPos][i];
        }
        for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos]))+1; ++i) {
            curr->khInts.matrixCod[keyPosChange][i] = mInts.matrixCod[newKeyPos][i];
        }
    }

    //new_keyHolder->khInts.matrixPub[posChange] = key_digits_2_long_int(mInts.matrixPub[keyPos]);
    //new_keyHolder->khInts.matrixPriv[posChange] = key_digits_2_long_int(mInts.matrixPriv[keyPos]);
    //new_keyHolder->khInts.matrixCod[posChange] = key_digits_2_long_int(mInts.matrixCod[keyPos]);

    curr->data_modificacao = ctime(&data_modificacao);

    if(keyHolderPos != 1){
        temp->next = curr->next;
        curr->next = *portaChaves;
        *portaChaves = curr;
    }
}

void remove_keyHolder(KEY_HOLDER** portaChaves, int keyHolderPos){
    int removePos = 1;

    if(*portaChaves == NULL) return;

    if(keyHolderPos == 1){
        KEY_HOLDER *temp_remove = *portaChaves;
        *portaChaves = (*portaChaves)->next;
    }

    KEY_HOLDER *curr = *portaChaves;
    while (curr->next != NULL){
        if(removePos+1 == keyHolderPos){
            KEY_HOLDER *temp_remove = curr->next;
            curr->next = curr->next->next;
            free(temp_remove);
            break;
        }
        removePos++;
        curr = curr->next;
    }
}

void searchSingleKey_inKeyHolder(KEY_HOLDER* portaChaves, int keyHolderPos, char* keyToSeach, int type){
    int stopPos = 1, exist = 0;
    while (stopPos != keyHolderPos){
        portaChaves = portaChaves->next;
        stopPos++;
    }

        if(type == 1){
            for (int i = 0; portaChaves->khString.matrixPub[i] ; ++i) {
                if(strcmp(portaChaves->khString.matrixPub[i], keyToSeach) == 0){
                    printf("A chave %s existe na matrix de chaves publicas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves publicas de Strings\n", keyToSeach);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixPub[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixPub[i]) == atoll(keyToSeach)){
                    printf("A chave %s existe na matrix de chaves publicas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves publicas de Inteiros\n", keyToSeach);
            }
            exist = 0;
        }
        else if(type == 2){
            for (int i = 0; portaChaves->khString.matrixPriv[i] ; ++i) {
                if(strcmp(portaChaves->khString.matrixPriv[i], keyToSeach) == 0){
                    printf("A chave %s existe na matrix de chaves privadas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves privadas de Strings\n", keyToSeach);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixPriv[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixPriv[i]) == atoll(keyToSeach)){
                    printf("A chave %s existe na matrix de chaves privadas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves privadas de Inteiros\n", keyToSeach);
            }
            exist = 0;
        }
        else if(type == 3){
            for (int i = 0; portaChaves->khString.matrixCod[i] ; ++i) {
                if(strcmp(portaChaves->khString.matrixCod[i], keyToSeach) == 0){
                    printf("A chave %s existe na matrix de chaves codificada de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves codificadas de Strings\n", keyToSeach);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixCod[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixCod[i]) == atoll(keyToSeach)){
                    printf("A chave %s existe na matrix de chaves codificada de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %s nao existe na matrix de chaves codificadas de Inteiros\n", keyToSeach);
            }
            exist = 0;
        }
}

void save_txt_keyHolder(KEY_HOLDER ** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, char filename[]){

    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "r+");
    int stopPos = 1;

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    KEY_HOLDER * curr = *portaChaves;
    while (stopPos != keyHolderPos){
        curr = curr->next;
        stopPos++;
    }

    int i = 0;
    while (1){
        if(curr->khString.matrixPub[i] != NULL){
            fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixPub[i]);
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(curr->khString.matrixPriv[i] != NULL){
            fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixPriv[i]);
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(curr->khString.matrixCod[i] != NULL){
            fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixCod[i]);
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(curr->khInts.matrixPub[i] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixPub[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(curr->khInts.matrixPriv[i] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixPriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(curr->khInts.matrixCod[i] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixCod[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        i++;
    }

    /*
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpub[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpub[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpriv[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }for (int i = 0; i < lines; ++i) {
        if(matrix_kcod[i][0] != NULL){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kcod[i]));
            fprintf(fileChavesPubWrite,"\n");
        }
    }
     */

    fclose(fileChavesPubWrite);
}

void load_txt_keyHolder(KEY_HOLDER ** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, int newKeysPos, char filename[]){

    FILE *fileChavesPubRead;
    fileChavesPubRead = fopen(filename, "r");
    char * valueString = NULL, *privKey = NULL, *codKey = NULL;
    int i = 0, stopPos = 1, valuePos = 0, sizeMax = 1;
    short *allD = NULL;
    unsigned long long count = 1;
    unsigned long long *value = (unsigned long long *) calloc(count, sizeof (unsigned long long));

    if(fileChavesPubRead == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    KEY_HOLDER * curr = *portaChaves;
    while (stopPos != keyHolderPos){
        curr = curr->next;
        stopPos++;
    }

    for (int j = 0; curr->khString.matrixPub[j] != NULL; ++j) {
        sizeMax++;
    }

    while (fscanf (fileChavesPubRead, "%llu", &value[count-1]) == 1){
        count++;
        value = (unsigned long long *) realloc(value, count * sizeof (unsigned long long));
    }

    while (i < count/6){

        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos]);
        //privKey = (char*) calloc(100, sizeof (char));
        //codKey = (char*) calloc(100,  sizeof (char));
        //sprintf(privKey, "%llu", calc_private_key_char(value[valuePos]));
        //sprintf(codKey, "%llu", calc_runlength_char(calc_private_key_char(value[valuePos])));
        //if(!curr->khString.matrixPub[i]){
            curr->khString.matrixPub[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString)),  sizeof (char));
            curr->khString.matrixPub[newKeysPos+i] = valueString;
        //}

        //free(valueString);
        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos+1]);
        //if(!curr->khString.matrixPriv[i]){
            curr->khString.matrixPriv[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString)),  sizeof (char));
            curr->khString.matrixPriv[newKeysPos+i] = valueString;
        //}

        //free(valueString);
        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos+2]);
        //if(!curr->khString.matrixCod[i]){
            curr->khString.matrixCod[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString)),  sizeof (char));
            curr->khString.matrixCod[newKeysPos+i] = valueString;
        //}

        //free(valueString);
        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos+3]);
        //if(!curr->khInts.matrixPub[i]){
            curr->khInts.matrixPub[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString))+1,  sizeof (short ));
            for (int j = 0; j < numDigitsLong(atoll(valueString)); ++j) {
                curr->khInts.matrixPub[newKeysPos+i][j] = valueString[j]-'0';
            }
            curr->khInts.matrixPub[newKeysPos+i][numDigitsLong(atoll(valueString))] = -1;
        //}

        //free(valueString);
        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos+4]);
        //if(!curr->khInts.matrixPriv[i]){
            curr->khInts.matrixPriv[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString))+1,  sizeof (short ));
            for (int j = 0; j < numDigitsLong(atoll(valueString)); ++j) {
                curr->khInts.matrixPriv[newKeysPos+i][j] = valueString[j]-'0';
            }
            curr->khInts.matrixPriv[newKeysPos+i][numDigitsLong(atoll(valueString))] = -1;
        //}

        //free(valueString);
        valueString = (char*) calloc(100, sizeof (char));
        sprintf(valueString, "%llu", value[valuePos+5]);
        //if(!curr->khInts.matrixCod[i]){
            curr->khInts.matrixCod[newKeysPos+i] = calloc(numDigitsLong(atoll(valueString))+1,  sizeof (short ));
            for (int j = 0; j < numDigitsLong(atoll(valueString)); ++j) {
                curr->khInts.matrixCod[newKeysPos+i][j] = valueString[j]-'0';
            }
        curr->khInts.matrixCod[newKeysPos+i][numDigitsLong(atoll(valueString))] = -1;
        //}

        free(valueString);
        valuePos += 6;
        i++;
    }
    curr->khString.matrixPub[newKeysPos+i+1] = calloc(100, sizeof (char));
    curr->khString.matrixPriv[newKeysPos+i+1] = calloc(100, sizeof (char));
    curr->khString.matrixCod[newKeysPos+i+1] = calloc(100, sizeof (char));
    curr->khInts.matrixPub[newKeysPos+i+1] = calloc(100, sizeof (short ));
    curr->khInts.matrixPriv[newKeysPos+i+1] = calloc(100, sizeof (short ));
    curr->khInts.matrixCod[newKeysPos+i+1] = calloc(100, sizeof (short ));
    curr->khString.matrixPub[newKeysPos+i+1] = NULL;
    curr->khString.matrixPriv[newKeysPos+i+1] = NULL;
    curr->khString.matrixCod[newKeysPos+i+1] = NULL;
    curr->khInts.matrixPub[newKeysPos+i+1] = NULL;
    curr->khInts.matrixPriv[newKeysPos+i+1] = NULL;
    curr->khInts.matrixCod[newKeysPos+i+1] = NULL;

    free(value);
    fclose(fileChavesPubRead);
} //TODO Load porta Chaves de ficheiros

void print_keyHolders(KEY_HOLDER** portaChaves){
    int sair = 0, numPortaChaves = 1;
    for (KEY_HOLDER *curr = *portaChaves; curr != NULL ; curr = curr->next) {
        int i = 0;
        printf("Porta Chaves - %d\n", numPortaChaves);
        while (1){
            if(curr->khString.matrixPub[i]) {
                printf("Porta Chaves PubKey String - %s\n", curr->khString.matrixPub[i]);
                sair = 0;
            } else sair = 1;
            if(curr->khString.matrixPriv[i]) {
                printf("Porta Chaves PrivKey String - %s\n", curr->khString.matrixPriv[i]);
                sair = 0;
            } else sair = 1;
            if(curr->khString.matrixCod[i]) {
                printf("Porta Chaves CodKey String - %s\n", curr->khString.matrixCod[i]);
                sair = 0;
            } else sair = 1;
            int j = 0;
            if(curr->khInts.matrixPub[i]){
                printf("Porta Chaves PubKey Ints - ");
                while (curr->khInts.matrixPub[i][j] != -1){
                    printf("%hi", curr->khInts.matrixPub[i][j]);
                    j++;
                }
                sair = 0;
            } else sair = 1;
            printf("\n");
            j = 0;
            if(curr->khInts.matrixPriv[i]){
                printf("Porta Chaves PrivKey Ints - ");
                while (curr->khInts.matrixPriv[i][j] != -1){
                    printf("%hi", curr->khInts.matrixPriv[i][j]);
                    j++;
                }
                sair = 0;
            } else sair = 1;
            printf("\n");
            j = 0;
            if(curr->khInts.matrixCod[i]){
                printf("Porta Chaves CodKey Ints - ");
                while (curr->khInts.matrixCod[i][j] != -1){
                    printf("%hi", curr->khInts.matrixCod[i][j]);
                    j++;
                }
                sair = 0;
            } else sair = 1;
            if(sair == 1) break;
            i++;
            printf("\n");
        }
        printf("Data Criacao: %s", curr->data_criacao);
        printf("Data Modificacao: %s", curr->data_modificacao);
        printf("\n");
        numPortaChaves++;
    }
}


void freeMatrixChar(char **matrix, int N){
    for (int i = 0; i < N; ++i) {
        matrix[i] = NULL;
        free(matrix[i]);
    }
}
void freeMatrixShort(short **matrix, int N){
    for (int i = 0; i < N; ++i) {
        matrix[i] = NULL;
        free(matrix[i]);
    }
}