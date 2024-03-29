//
// Created by pc on 11/11/2022.
//

#include "projeto.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

// ===================================================================================================================================== //
// ===================================== FUNÇÕES STRINGS DO FICHEIRO DOS PROFESSORES =================================================== //
// ===================================================================================================================================== //
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

    if(bipolar_numberInt(allD) ==  0) return key_digits_2_long_int(allD);
    if(pubkey <= 5){
        rightNum = '0';
        leftNum = '1';
    }
    if(digitos < 2) digitos = 2;
    if(pubkey == 0) return 0;
    n = (char *) calloc(digitos, sizeof (char));    //Alocar memória para n

    unsigned long long max_iterations = (unsigned long long) 18446744073709551615;
    for (int i = 0; atoll(n) < max_iterations; i++) {
        if(leftNum == '9' && changePos == digitos -1 && rightNum == '8'){       //Se o leftNum = 9 e a changePos = limite de digitos e rightNum = 8 temos (98, 988, 9888) então
            digitos++;                                                          //Chegamos ao ultimo número gerado bipolar com este núemro de digito então incrementamos o número de digitos
            n = NULL;
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
                if(atoll(n) > 1000000000000 || atoll(n) < 0){
                    n=NULL;
                    free(allD);
                    free(n);
                    return 0;  //Se o valor for maior que o suportado para (unsigned long long) ou for menor que 0 ou se a pubkey for igual a 0 returna 0
                }
                if(atoll(n) > pubkey && atoll(n)%pubkey == 0){                          //Se (unsigned long long) de n for maior que pubkey(pq a pubkey é multipla dela mesma) e (unsigned long long) de n for multiplo de pubkey
                    unsigned long long valorFinal = atoll(n);                           //valorFinal vai ser igual a (unsigned long long) de n
                    n=NULL;                                                             //Limpa n e dá free à memória
                    free(allD);
                    free(n);
                    return valorFinal;                                                  //retorna o valorFinal
                }
                changePos++;                                                            //Se não changePos++ e resetamos o j
                j = 0;
        } else{                                                                         //Se não incrementamos o j
            j++;
        }
    }
    return 0;
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    unsigned long long codKey = 0;
    int runLessPos = 0, digits, pow = 1;
    digits = numDigitsLong(privkey);
    int allD[digits], runLess[4];

    //Ciclo para zerar runLess
    for (int i = 0; i < 6; ++i) {
        runLess[i] = 0;
    }
    //Se privKey maior ou igual que 10 vai calcular a sua run Length
    if(privkey >= 10){
        allDigitsLong(privkey, allD);          // Insere no array allD todos os digitos da privKey
        runLess[runLessPos+1] = 1;                  // iguala a segunda posição do runLength a 1(count de frequencia de um numero)
        runLess[runLessPos] = allD[digits-1];       // iguala a primeira posição do runLength ao ultimo digito de allD (ultimode allD é o primeiro da privKey pois o allD fica invertido)
        for (int i = digits-1; i > 0; i--) {
            if(allD[i] != allD[i-1]){               // compara se o valor atual de allD é igual ao proximo valor (i-1 é o proximo porque o array está a andar de tras para a frente)
                runLessPos += 2;                    // se os 2 valores forem iguais então mudamos de digito e subimos então a runLessPos+2 pois a pos 0 e 2 do runLength são os digitos
                runLess[runLessPos] = allD[i-1];    // igualo runLess[2] ao valor valor de allD[i-1] (i-1 pois o array está a ir de tras para a frente então o i-1 é que é o prox valor)
            }
            runLess[runLessPos+1]++;                // frequencia do digitos++
        }
        for (int i = 1; i <= 4; i++) {             // array que vai concatenar todo o array runLess num numero
            if ( i == 1){
                codKey = runLess[i-1];              // codKey = ao primeiro digito
            } else{
                if(i%2 == 0){                       // se estivermos numa posição multipla de 2 então estamos em posições de frequencias de digitos
                    codKey *= 100;                  // mutiplicamos o valor de codKey por 100 pois cada frequencia vai ocupar 2 espaços exemplo (101 isto é o numero 1 aparece 1 vez / 1 é o numero e 01 é a frequencia)
                    codKey += runLess[i-1];         // soma de codKey com o valor de runLess
                    pow = 1;
                } else{
                    for (int j = 0; j < numDigitsLong(runLess[i-1]); ++j) { // Ciclo para saber quanto se tem de multiplicar codKey para poder fazer a soma e juntar runLess sabemos isso pelo numero de digitos
                        pow *= 10;
                    }
                    codKey *= pow;              // multiplicamos codKey pelo pow
                    codKey += runLess[i-1];     // soamos codKey e runLess
                    pow = 1;                    // voltamos o pow a 1
                }
            }
        }
        return codKey;
    }
    else{
        return 0;
    }
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){

    unsigned long long privKey = 0;
    short *allDigits, freq = 0, pow = 1;
    allDigits = key_long_2_digits_int(runlengthkey);

    privKey = allDigits[0];         // privKey = ao primeiro digito do allDigits
    freq = allDigits[1] * 10;       // frequecia = ao segundp digito de allDigits * 10
    freq += allDigits[2];           // frequencia + o terceiro digito de allDigits = frequencia do primeiro digito da privKey
    for (int i = 1; i < freq; ++i) {    // ciclo para coclocar o digito da privkey com o seu nº de frequencias
        privKey *= 10;
        privKey += allDigits[0];
    }

    privKey *= 10;                  // multiplicamos a privKey * 10 para juntar os restantes valores
    privKey += allDigits[3];
    freq = allDigits[4] * 10;
    freq += allDigits[5];
    for (int i = 1; i < freq; ++i) {
        privKey *= 10;
        privKey += allDigits[3];
    }

    return privKey;
}

char** alloc_matrix_char(int nlines, int ncolumns){
    char **matrix;
    matrix = (char **) calloc((nlines+1) * sizeof (char *), sizeof (char *));
    for (int i = 0; i < nlines; ++i) {
        matrix[i] = (char *) calloc(ncolumns * sizeof (char), sizeof (char));
    }
    matrix[nlines] = (char *) calloc(3 * sizeof (char), sizeof (char));   // Linha que vai ser usada para saber o fim da matriz
    strcpy(matrix[nlines], "-1");
    return matrix;
}

void store_key_char(char **matrix, int lines, unsigned long long key){
    char *keyChar = (char *) calloc((numDigitsLong(key)+1) * sizeof (char), sizeof (char));
    sprintf(keyChar, "%llu", key);
    for (int i = 0; i < lines; ++i) {
        if(!matrix[i][0]){      // Se o valor for vazio
            matrix[i] = (char *) calloc(strlen(keyChar)+1, sizeof (char));
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
    int exist = 0;
    for (int i = 0; i < lines+1; ++i) {
        if(strcmp(matrix_kpub[i], "-1") == 0) break;
        if(strcmp(matrix_kpub[i], pubkey) == 0){
            exist = 1;
            for (int j = i; j < lines; ++j) {
                if(j == lines-1){
                    matrix_kpub[j] = matrix_kpub[j+1];
                    matrix_kpriv[j] = matrix_kpriv[j+1];
                    matrix_kcod[j] = matrix_kcod[j+1];
                    matrix_kpub[j+1] = NULL;
                    matrix_kpriv[j+1] = NULL;
                    matrix_kcod[j+1] = NULL;
                    free(matrix_kpub[j+1]);
                    free(matrix_kpriv[j+1]);
                    free(matrix_kcod[j+1]);
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
    if(exist == 0){
        printf("Chave Nao Encontrada\n");
        return 0;
    }

    return atoll(pubkey);
}

void bulk_populate_public_keys_char(char **matrix_kpub, int lines){
    unsigned long long r;
    matrix_kpub = (char **) realloc(matrix_kpub, (lines+1) * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], "\0") == 0){      // Se a linha estiver vazia
            r = new_public_key_int();               // gerar numero aleatorio
            char* rString = malloc(numDigitsLong(r)+1 * sizeof (char));
            sprintf(rString, "%llu", r);
            matrix_kpub[i] = (char *) calloc(strlen(rString)+1, sizeof (char));
            store_key_char(matrix_kpub, lines, r);  // meter o valor aleatorio na matriz
            rString=NULL;
            free(rString);
        }
        if(strcmp(matrix_kpub[i], "-1") == 0){      // Se estivermos na ultima linha da matriz
            r = new_public_key_int();               // geramos o numero aleatorio
            char* rString = malloc(numDigitsLong(r)+1 * sizeof (char));
            sprintf(rString, "%llu", r);
            matrix_kpub[i] = (char *) calloc(strlen(rString)+1, sizeof (char));
            store_key_char(matrix_kpub, lines, r);  // colocamos o numero aleatorio na matriz
            matrix_kpub[i+1] = (char *) calloc(3*sizeof (char), sizeof (char));
            strcpy(matrix_kpub[i+1], "-1");         // atualizamos a posição do -1 para a prox
            rString=NULL;
            free(rString);
        }
    }
}

void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines){
    unsigned long long val = 0;
    matrix_kpriv = (char **) realloc(matrix_kpriv, (lines+1) * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpriv[i], "\0") == 0){     // se o valor for vazio
            val = calc_private_key_char(atoll(matrix_kpub[i]));     // calcula a privKey
            matrix_kpriv[i] = (char *) calloc(numDigitsLong(val)+1, sizeof (char));
            store_key_char(matrix_kpriv, lines, val);           // guarda na matriz privada
        }
        if(strcmp(matrix_kpriv[i], "-1") == 0){     // se estivermos na ultima linha da matriz
            val = calc_private_key_char(atoll(matrix_kpub[i]));     // calcula a privKey
            matrix_kpriv[i] = (char *) calloc(numDigitsLong(val)+1, sizeof (char));
            store_key_char(matrix_kpriv, lines, val);           // guarda ana matriz de privadas
            matrix_kpriv[i+1] = (char *) calloc(3 * sizeof (char), sizeof (char));
            strcpy(matrix_kpriv[i+1], "-1");                    // atualizamos a posição do -1
        }
    }
}

void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines){
    unsigned long long val;
    matrix_kcod = (char **) realloc(matrix_kcod, (lines+1) * sizeof (char*));
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kcod[i], "\0") == 0){      // se a posição estiver vazia
            val = calc_runlength_char(atoll(matrix_kpriv[i]));  // calcula a runLength
            matrix_kcod[i] = (char *) calloc(numDigitsLong(val)+1, sizeof (char));
            store_key_char(matrix_kcod, lines, val);        // guarda na matriz
        }
        if(strcmp(matrix_kcod[i], "-1") == 0){     // se estiver na ultima linha da matriz
            val = calc_runlength_char(atoll(matrix_kpriv[i]));  // calcula o runLength
            matrix_kcod[i] = (char *) calloc(numDigitsLong(val)+1, sizeof (char));
            store_key_char(matrix_kcod, lines, val);        // guarda na matriz
            matrix_kcod[i+1] = (char *) calloc(3 * sizeof (char), sizeof (char));
            strcpy(matrix_kcod[i+1], "-1");                 // atualiza a pos do -1
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
        if(strcmp(matrix_kpub[i], "-1") == 0) break;        // se for -1 estamos no fim da matriz então já podemos sair
        for (int j = 0; j < strlen(matrix_kpub[i]); ++j) {
            if(matrix_kpub[i][j] == partialPubKeyChar[k]){
                k++;
            } else{
                k = 0;
            }
            if(k == strlen(partialPubKeyChar)){
                sizeResult++;
                result = (char **) realloc(result, (sizeResult+1) * sizeof (char *));
                val = get_private_key_char(matrix_kpub, matrix_kpriv, lines, atoll(matrix_kpub[i]));
                result[posResult] = (char *) malloc(numDigitsLong(val) * sizeof (char));
                sprintf(result[posResult], "%llu", val);
                posResult++;
            }
        }
    }

    result[posResult] = (char *) malloc(2 * sizeof (char));
    result[posResult] = "-1";

    partialPubKeyChar = NULL;
    free(partialPubKeyChar);

    return result;

}

void sort_matrix_char(char **matrix, int lines, int order){
    //shellSortChar(matrix, lines, order);
    merge_char_sort_base(matrix, lines, order);
}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    //shellSortChar(matrix_kpub, lines, order);
    //shellSortChar(matrix_kpriv, lines, order);
    //shellSortChar(matrix_kcod, lines, order);
    merge_char_sort_base(matrix_kpub, lines, order);
    merge_char_sort_base(matrix_kpriv, lines, order);
    merge_char_sort_base(matrix_kcod, lines, order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    //shellSortCharDigits(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
    mergeDigits_char_sort_base(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "a+");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], "-1") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kpub[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(strcmp(matrix_kpriv[i], "-1") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kpriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(strcmp(matrix_kcod[i], "-1") != 0){
            fprintf(fileChavesPubWrite,"%llu" , atoll(matrix_kcod[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
    }

    fclose(fileChavesPubWrite);
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fileChavesPubRead;
    fileChavesPubRead = fopen(filename, "r");
    int i = 0, j = 0;
    unsigned long long privKey = 0, codKey = 0, t = 0, count = 1;
    char **value = (char **) calloc(count, sizeof (char*));
    value[0] = malloc(1 * sizeof (char));
    char str[lines][200];

    if(fileChavesPubRead == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    while (fscanf (fileChavesPubRead, "%s", value[count-1]) == 1){
        count++;
        value = (char **) realloc(value, count * sizeof (char*));
        value[count-1] = (char *) calloc(1, sizeof (char));
    }

    j = 0;
    while (i < lines && i < count){
        strcpy(matrix_kpub[j], value[i]);
        strcpy(matrix_kpriv[j], value[i+1]);
        strcpy(matrix_kcod[j], value[i+2]);
        i += 3;
        j++;
    }

    fclose(fileChavesPubRead);
}

void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "a+b");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(strcmp(matrix_kpub[i], "-1") != 0){
            fwrite(matrix_kpub[i], sizeof (char), strlen(matrix_kpub[i]), fileChavesPubWrite);
            fwrite("\n", sizeof (char), 1, fileChavesPubWrite);
        } else break;
        if(strcmp(matrix_kpriv[i], "-1") != 0){
            fwrite(matrix_kpriv[i], sizeof (char), strlen(matrix_kpriv[i]), fileChavesPubWrite);
            fwrite("\n", sizeof (char), 1, fileChavesPubWrite);
        } else break;
        if(strcmp(matrix_kcod[i], "-1") != 0){
            fwrite(matrix_kcod[i], sizeof (char), strlen(matrix_kcod[i]), fileChavesPubWrite);
            fwrite("\n", sizeof (char), 1, fileChavesPubWrite);
        } else break;
    }

    fclose(fileChavesPubWrite);
}


// ===================================================================================================================================== //
// ===================================== FUNÇÕES INTS DO FICHEIRO DOS PROFESSORES ====================================================== //
// ===================================================================================================================================== //
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
    for (int j = 0; j < numDigitsLong(key); ++j) {      // inverter o array (para guardar com a ordem normal da key)
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

    if(bipolar_numberInt(allD) ==  0) return key_digits_2_long_int(allD);
    if(pubkey <= 5){
        rightNum = 0;
        leftNum = 1;
    }
    if(digitos < 2) digitos = 2;
    if (pubkey == 0) return 0;
    n = (short *) calloc(digitos, sizeof (short));

    unsigned long long max_iterations = (unsigned long long) 18446744073709551615;
    for (int i = 0; privKey < max_iterations; i++) {
        if (leftNum == 9 && changePos == digitos - 1 && rightNum == 8) {
            digitos++;
            n = NULL;
            n = realloc(n, digitos * sizeof(int));
            changePos = 0;
            leftNum = 1;
            rightNum = 0;
        }
        if (rightNum == 9 && changePos == digitos - 1) {
            leftNum++;
        }
        if (changePos == digitos - 1) {
            changePos = 0;
            if (rightNum != 9) {
                rightNum++;
            } else {
                rightNum = 0;
            }
        }
        if (leftNum == rightNum) {
            rightNum++;
        }
        if (j > changePos) {
            n[j] = rightNum;
        } else {
            n[j] = leftNum;
        }
        if(j == digitos-1){
            n[digitos] = -1;
            privKey = key_digits_2_long_int(n);
            //printf("PivKey = %llu\n", privKey);
            if(privKey > 1000000000000 || privKey < 0){
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
    return 0;
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    unsigned long long codKey = 0;
    int runLessPos = 0, digits, pow = 1;
    digits = numDigitsLong(privkey);
    int allD[digits], runLess[4];

    for (int i = 0; i < 6; ++i) {
        runLess[i] = 0;
    }
    if(privkey >= 10){
        allDigitsLong(privkey, allD);
        runLess[runLessPos+1] = 1;
        runLess[runLessPos] = allD[digits-1];
        for (int i = digits-1; i > 0; i--) {
            if(allD[i] != allD[i-1]){
                runLessPos += 2;
                runLess[runLessPos] = allD[i-1];
            }
            runLess[runLessPos+1]++;
        }
        for (int i = 1; i <= 4; i++) {
            if ( i == 1){
                codKey = runLess[i-1];
            } else{
                if(i%2 == 0){
                    codKey *= 100;
                    codKey += runLess[i-1];
                    pow = 1;
                } else {
                    for (int j = 0; j < numDigitsLong(runLess[i-1]); ++j) {
                        pow *= 10;
                    }
                    codKey *= pow;
                    codKey += runLess[i-1];
                    pow = 1;
                }
            }
        }
        return codKey;
    }
    else{
        return 0;
    }
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey){

    unsigned long long privKey = 0;
    short *allDigits, freq = 0, pow = 1;
    allDigits = key_long_2_digits_int(runlengthkey);

    privKey = allDigits[0];
    freq = allDigits[1] * 10;
    freq += allDigits[2];
    for (int i = 1; i < freq; ++i) {
        privKey *= 10;
        privKey += allDigits[0];
    }

    privKey *= 10;
    privKey += allDigits[3];
    freq = allDigits[4] * 10;
    freq += allDigits[5];
    for (int i = 1; i < freq; ++i) {
        privKey *= 10;
        privKey += allDigits[3];
    }

    return privKey;
}

short** alloc_matrix_int(int nlines, int ncolumns){
    short **matrix;
    matrix = (short **) calloc((nlines+1) * sizeof (short *), sizeof (short *));
    for (int i = 0; i < nlines; ++i) {
        matrix[i] = (short *) calloc(ncolumns * sizeof (short), sizeof (short));
        matrix[i][0] = 0;
    }
    matrix[nlines] = (short *) calloc(2 * sizeof (short), sizeof (short));
    matrix[nlines][0] = -1;
    return matrix;
}

void store_key_int(short **matrix, int lines, unsigned long long key){
    short *allD = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        if(!matrix[i][0] && matrix[i][1] == -1) continue;   //Caso tenha um 0 mas seja mesmo um 0 e não um valor NULL eu sei que é mesmo um 0 porque eu vejo se na pos 1 do array tem um -1 se tiver é mesmo um 0 se não é uma pos vazia
        if(!matrix[i][0] || matrix[i][0] == -1){
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
        /*if(!matrix[i][0]){
            break;
        }*/
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
    allD = NULL;
    free(allD);
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
    printf("Chave Nao Encontrada\n");
    return 0;
}

unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey){
    int exist = 0;
    for (int i = 0; i < lines+1; ++i) {
        //if(!matrix_kpub[i] || matrix_kpub[i][0] == 0) continue;
        if(matrix_kpub[i][0] == -1) break;
        if(key_digits_2_long_int(matrix_kpub[i]) == pubkey){
            exist = 1;
            for (int j = i; j < lines; ++j) {
                if(j == lines-1){
                    matrix_kpub[j] = matrix_kpub[j+1];
                    matrix_kpriv[j] = matrix_kpriv[j+1];
                    matrix_kcod[j] = matrix_kcod[j+1];
                    matrix_kpub[j+1] = NULL;
                    matrix_kpriv[j+1] = NULL;
                    matrix_kcod[j+1] = NULL;
                    free(matrix_kpub[j+1]);
                    free(matrix_kpriv[j+1]);
                    free(matrix_kcod[j+1]);
                    break;
                }
                matrix_kpub[j] = matrix_kpub[j+1];
                matrix_kpriv[j] = matrix_kpriv[j+1];
                matrix_kcod[j] = matrix_kcod[j+1];
            }
            lines--;
        }
    }
    if(exist == 0){
        printf("Chave Nao Encontrada\n");
        return 0;
    }
    return pubkey;
}

void bulk_populate_public_keys_int(short **matrix_kpub, int lines){
    unsigned long long r;
    matrix_kpub = (short **) realloc(matrix_kpub, (lines+1) * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpub[i][0] == 0 && matrix_kpub[i][1] != -1){
            r = new_public_key_int();
            matrix_kpub[i] = (short *) calloc(numDigitsLong(r)+1, sizeof (short ));
            store_key_int(matrix_kpub, lines, r);
        }
        if(matrix_kpub[i][0] == -1){
            r = new_public_key_int();
            matrix_kpub[i] = (short *) calloc(numDigitsLong(r)+1, sizeof (short ));
            store_key_int(matrix_kpub, lines, r);
            matrix_kpub[i+1] = (short *) calloc(2, sizeof (short));
            matrix_kpub[i][0] = -1;
        }
    }
}

void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines){
    unsigned long long val = 0;
    matrix_kpriv = (short **) realloc(matrix_kpriv, lines * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        //if(!matrix_kpriv[i] || matrix_kpriv[i][0] == 0){
        if(matrix_kpriv[i][0] == 0 && matrix_kpriv[i][1] != -1){
            val = calc_private_key_int(key_digits_2_long_int(matrix_kpub[i]));
            matrix_kpriv[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kpriv, lines, val);
        }
        if(matrix_kpriv[i][0] == -1){
            val = calc_private_key_int(key_digits_2_long_int(matrix_kpub[i]));
            matrix_kpriv[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kpriv, lines, val);
            matrix_kpriv[i+1] = (short *) calloc(2, sizeof (short ));
            matrix_kpriv[i+1][0] = -1;
        }
    }
}

void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines){
    unsigned long long val = 0;
    matrix_kcod = (short **) realloc(matrix_kcod, lines * sizeof (short *));
    for (int i = 0; i < lines; ++i) {
        //if(!matrix_kcod[i] || matrix_kcod[i][0] == 0){
        if(matrix_kcod[i][0] == 0 && matrix_kcod[i][1] != -1){
            val = calc_runlength_int(key_digits_2_long_int(matrix_kpriv[i]));
            matrix_kcod[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kcod, lines, val);
        }
        if(matrix_kcod[i][0] == -1){
            val = calc_runlength_int(key_digits_2_long_int(matrix_kpriv[i]));
            matrix_kcod[i] = (short *) calloc(numDigitsLong(val)+1, sizeof (short ));
            store_key_int(matrix_kcod, lines, val);
            matrix_kcod[i+1] = (short *) calloc(2, sizeof (short ));
            matrix_kcod[i+1][0] = -1;
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
        int k = 0;
        if(matrix_kpub[i][0] == -1) break;
        for (int j = 0; j < numDigitsLong(key_digits_2_long_int(matrix_kpub[i])); ++j) {
            if(matrix_kpub[i][j] == partialKeyArray[k]){
                k++;
            } else{
                k = 0;
            }
            if(k == numDigitsLong(partialpubkey)){
                sizeResult++;
                result = (short **) realloc(result, (sizeResult+1) * sizeof (short *));
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

    result[posResult] = (short *) malloc(1 * sizeof (short));
    result[posResult][0] = -1;

    valArray = NULL;
    free(valArray);
    partialKeyArray = NULL;
    free(partialKeyArray);
    return result;
}

void sort_matrix_int(short **matrix, int lines, int order){
    //shellSortInt(matrix, lines, order);
    merge_int_sort_base(matrix, lines, order);
}

void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    //shellSortInt(matrix_kpub, lines, order);
    //shellSortInt(matrix_kpriv, lines, order);
    //shellSortInt(matrix_kcod, lines, order);
    merge_int_sort_base(matrix_kpub, lines, order);
    merge_int_sort_base(matrix_kpriv, lines, order);
    merge_int_sort_base(matrix_kcod, lines, order);
}

void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    //shellSortIntDigits(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
    mergeDigits_int_sort_base(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){

    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "a+");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpub[i][0] != -1){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpub[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(matrix_kpriv[i][0] != -1){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kpriv[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
        if(matrix_kcod[i][0] != -1){
            fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(matrix_kcod[i]));
            fprintf(fileChavesPubWrite,"\n");
        } else break;
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

void save_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){

    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "a+b");

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }
    for (int i = 0; i < lines; ++i) {
        if(matrix_kpub[i][0] != -1){
            char *temp = malloc(numDigitsLong(key_digits_2_long_int(matrix_kpub[i])) * sizeof (char));
            sprintf(temp, "%llu", key_digits_2_long_int(matrix_kpub[i]));
            fwrite(temp, sizeof(char), strlen(temp), fileChavesPubWrite);
            fwrite("\n", sizeof(char), 1, fileChavesPubWrite);
        } else break;
        if(matrix_kpriv[i][0] != -1){
            char *temp = malloc(numDigitsLong(key_digits_2_long_int(matrix_kpriv[i])) * sizeof (char));
            sprintf(temp, "%llu", key_digits_2_long_int(matrix_kpriv[i]));
            fwrite(temp, sizeof(char), strlen(temp), fileChavesPubWrite);
            fwrite("\n", sizeof(char), 1, fileChavesPubWrite);
        } else break;
        if(matrix_kcod[i][0] != -1){
            char *temp = malloc(numDigitsLong(key_digits_2_long_int(matrix_kcod[i])) * sizeof (char));
            sprintf(temp, "%llu", key_digits_2_long_int(matrix_kcod[i]));
            fwrite(temp, sizeof(char), strlen(temp),fileChavesPubWrite);
            fwrite("\n", sizeof(char), 1, fileChavesPubWrite);
        } else break;
    }

    fclose(fileChavesPubWrite);
}


// ===================================================================================================================================== //
// ========================================== FUNÇÕES PARA PORTA-CHAVES ================================================================ //
// ===================================================================================================================================== //

/**
 * Esta função vai criar um novo porta chaves e inserir uma dada linha das matrizes nesse porta chaves e inserilo no inicio da lista ligada
 * @param portaChaves apontador para os apontadores dos porta chaves
 * @param mString  struct das matrizes de Strings
 * @param mInts struct das matrizes de Ints
 * @param pos linha das matrizes a ser inserida no porta chaves
 */
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
    new_keyHolder->khString.matrixPub = alloc_matrix_char(1, 1);
    new_keyHolder->khString.matrixPriv = alloc_matrix_char(1, 1);
    new_keyHolder->khString.matrixCod = alloc_matrix_char(1, 1);
    new_keyHolder->khInts.matrixPub = alloc_matrix_int(1, 1);
    new_keyHolder->khInts.matrixPriv = alloc_matrix_int(1, 1);
    new_keyHolder->khInts.matrixCod = alloc_matrix_int(1, 1);

    if(pos >= mString.lines){       // se tentar adicionar uma linha que não exista é inserido 0
        store_key_char(new_keyHolder->khString.matrixPub, 1, 0);
        store_key_char(new_keyHolder->khString.matrixPriv, 1, 0);
        store_key_char(new_keyHolder->khString.matrixCod, 1, 0);
    } else{
        store_key_char(new_keyHolder->khString.matrixPub, 1, atoll(mString.matrixPub[pos]));
        store_key_char(new_keyHolder->khString.matrixPriv, 1, atoll(mString.matrixPriv[pos]));
        store_key_char(new_keyHolder->khString.matrixCod, 1, atoll(mString.matrixCod[pos]));
    }
    if(pos >= mInts.lines){       // se tentar adicionar uma linha que não exista é inserido 0
        store_key_int(new_keyHolder->khInts.matrixPub, 1, 0);
        store_key_int(new_keyHolder->khInts.matrixPriv, 1, 0);
        store_key_int(new_keyHolder->khInts.matrixCod, 1, 0);
    } else{
        store_key_int(new_keyHolder->khInts.matrixPub, 2, key_digits_2_long_int(mInts.matrixPub[pos]));
        store_key_int(new_keyHolder->khInts.matrixPriv, 2, key_digits_2_long_int(mInts.matrixPriv[pos]));
        store_key_int(new_keyHolder->khInts.matrixCod, 2, key_digits_2_long_int(mInts.matrixCod[pos]));
    }

    new_keyHolder->data_criacao = ctime(&data_criacao);             // insere a data de criação
    new_keyHolder->data_modificacao = ctime(&data_modificacao);     // insere a data de modificação

    if(*portaChaves == NULL){           // se não existirem porta chaves
        new_keyHolder->sieInts++;
        new_keyHolder->sizeStrings++;
        *portaChaves = new_keyHolder;
        return;
    }

    new_keyHolder->sieInts++;
    new_keyHolder->sizeStrings++;
    *portaChaves = new_keyHolder;       // se já existirem porta chaves o primeiro agora é o new_keyHolder
}

/**
 * Função que serve para editar um porta chaves tanto para adicionar uma nova linha de matrizes como para editar uma já existente
 * A posição na lista ligada deste porta chaves vai ser atualizada para a primeira posição pois vais começar a ser o porta chaves com a data de modificação mais recente
 * @param portaChaves apontador para os apontadores dos porta chaves
 * @param mString struct das matrizes de strings
 * @param mInts strucr para as matrizes de ints
 * @param keyHolderPos posição do porta chaves a ser editado
 * @param keyPosChange linha do porta chaves a ser editada/adicionada
 * @param newKeyPos linha da matriz de string/ints a ser adicionada
 */
void edit_keyHolder(KEY_HOLDER** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, int keyPosChange, int newKeyPos){
    KEY_HOLDER *temp = NULL;
    time_t data_modificacao;
    time(&data_modificacao);
    int stopPos=1, isAdd = 0, size = 0, sizeMax = 1;

    KEY_HOLDER * curr = *portaChaves;
    while (stopPos != keyHolderPos){    // andar na lista ligada até chegar ao porta chaves a ser editado
        if(curr == NULL){
            printf("Porta Chaves Nao Encontrado\n");
            return;
        }
        temp = curr;            // guarda o porta chaves anterior
        curr = curr->next;
        stopPos++;
    }

    for (int i = 0; strcmp(curr->khString.matrixPub[i], "-1") != 0; ++i) {  // calcula o tamanho das matrizes deste prota chaves
        sizeMax++;
    }

    for (int j = 0; j <= keyPosChange; ++j) {       // ciclo que vai verificar se a linha do porta chaves já existe ou não, se nãon existir vamos adicionar
        if(strcmp(curr->khString.matrixPub[j], "-1") == 0){ // se estamos na ultima linha do porta chaves quer dizer que a linha que o utilizador escolheu não existe
            if(newKeyPos > mString.lines){  // verificar se a linha a diconar existe na matriz de strings
                curr->khString.matrixPub[j] = realloc(curr->khString.matrixPub[j],2 * sizeof (char));
                strcpy(curr->khString.matrixPub[j], "0");   // se não existir adicionamos 0
            } else{
                curr->khString.matrixPub[j] = realloc(curr->khString.matrixPub[j],(numDigitsLong(atoll(mString.matrixPub[newKeyPos]))+1)*sizeof (char));
                strcpy(curr->khString.matrixPub[j], mString.matrixPub[newKeyPos]);  // se existir adicionamos essa linha
            }
            isAdd = 1;
        }
        // Mesma coisa que na matriz de String de chaves Publicas
        if(strcmp(curr->khString.matrixPriv[j], "-1") == 0){
            if(newKeyPos > mString.lines){
                curr->khString.matrixPriv[j] = realloc(curr->khString.matrixPriv[j],2 * sizeof (char));
                curr->khString.matrixPriv[j] =  "0\0";
            } else {
                curr->khString.matrixPriv[j] = realloc(curr->khString.matrixPriv[j],(numDigitsLong(atoll(mString.matrixPriv[newKeyPos]))+1) * sizeof (char));
                curr->khString.matrixPriv[j] = mString.matrixPriv[newKeyPos];
            }
            isAdd = 1;
        }
        if(strcmp(curr->khString.matrixCod[j], "-1") == 0){
            if(newKeyPos > mString.lines){
                curr->khString.matrixCod[j] = realloc(curr->khString.matrixCod[j],2 * sizeof (char));
                curr->khString.matrixCod[j] =  "0\0";
            } else {
                curr->khString.matrixCod[j] = realloc(curr->khString.matrixCod[j],(numDigitsLong(atoll(mString.matrixCod[newKeyPos]))+1) * sizeof (char));
                curr->khString.matrixCod[j] = mString.matrixCod[newKeyPos];
            }
            isAdd = 1;
        }
        if(curr->khInts.matrixPub[j][0] == -1){
            if(newKeyPos > mInts.lines){
                curr->khInts.matrixPub[j] = realloc(curr->khInts.matrixPub[j],2 * sizeof (short));
                curr->khInts.matrixPub[j][0] = 0;
                curr->khInts.matrixPub[j][1] = -1;
            } else {
                curr->khInts.matrixPub[j] = realloc(curr->khInts.matrixPub[j],(numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos]))+1) * sizeof (short));
                for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos])) + 1; ++i) {
                    curr->khInts.matrixPub[j][i] = mInts.matrixPub[newKeyPos][i];
                }
            }
            isAdd = 1;
        }
        if(curr->khInts.matrixPriv[j][0] == -1){
            if(newKeyPos > mInts.lines){
                curr->khInts.matrixPriv[j] = realloc(curr->khInts.matrixPriv[j],2 * sizeof (short));
                curr->khInts.matrixPriv[j][0] = 0;
                curr->khInts.matrixPriv[j][1] = -1;
            } else{
                curr->khInts.matrixPriv[j] = realloc(curr->khInts.matrixPriv[j],(numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1) * sizeof (short));
                for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1; ++i) {
                    curr->khInts.matrixPriv[j][i] = mInts.matrixPriv[newKeyPos][i];
                }
            }
            isAdd = 1;
        }
        if(curr->khInts.matrixCod[j][0] == -1){
            if(newKeyPos > mInts.lines){
                curr->khInts.matrixCod[j] = realloc(curr->khInts.matrixCod[j],2 * sizeof (short));
                curr->khInts.matrixCod[j][0] = 0;
                curr->khInts.matrixCod[j][1] = -1;
            } else {
                curr->khInts.matrixCod[j] = realloc(curr->khInts.matrixCod[j],(numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos]))+1) * sizeof (short));
                for (int i = 0; i < numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos])) + 1; ++i) {
                    curr->khInts.matrixCod[j][i] = mInts.matrixCod[newKeyPos][i];
                }
            }
            isAdd = 1;
        }
        if(isAdd == 1){ // se a linha foi adicionada então
            curr->sieInts++;        // aumentamos o numero de linhas ints deste porta chaves
            curr->sizeStrings++;    // aumentamos o numeri de linhas strings deste porta chaves

            // Atualizo o valor de -1 nas matrizes
            curr->khString.matrixPub = realloc(curr->khString.matrixPub, (sizeMax+1) * sizeof (char*));
            curr->khString.matrixPub[sizeMax] = calloc(3, sizeof (char));
            curr->khString.matrixPriv[sizeMax] = calloc(3, sizeof (char));
            curr->khString.matrixCod[sizeMax] = calloc(3, sizeof (char));
            strcpy(curr->khString.matrixPub[sizeMax], "-1");
            strcpy(curr->khString.matrixPriv[sizeMax], "-1");
            strcpy(curr->khString.matrixCod[sizeMax], "-1");

            curr->khInts.matrixPub = realloc(curr->khInts.matrixPub, (sizeMax+1) * sizeof (short*));
            curr->khInts.matrixPub[sizeMax] = calloc(2, sizeof (short));
            curr->khInts.matrixPriv[sizeMax] = calloc(2, sizeof (short));
            curr->khInts.matrixCod[sizeMax] = calloc(2, sizeof (short));
            curr->khInts.matrixPub[sizeMax][0] = -1;
            curr->khInts.matrixPriv[sizeMax][0] = -1;
            curr->khInts.matrixCod[sizeMax][0] = -1;

            // se não for o primeiro porta chaves, atualizamos a lista ligada
            if(keyHolderPos != 1) {
                temp->next = curr->next;    // o porta chaves anterior vai agora apontar para o proximo deste porta chaves editado
                curr->next = *portaChaves;  // o porta chaves editado agora vai apontar para o primeiro porta chaves
                *portaChaves = curr;        // o primeiro porta chaves agora é este porta chaves que foi editado
            }

            return;
        }
        size++;
    }
    if(isAdd == 0){     // se a linha não foi adicionada então quer dizer que já existe no porta chaves e vamos editar

        if(newKeyPos >= mString.lines){ // se a linha das matrizes não existir é inserido um 0
            curr->khString.matrixPub[keyPosChange] = (char *) calloc(1, sizeof (char ));
            curr->khString.matrixPriv[keyPosChange] = (char *) calloc(1, sizeof (char ));
            curr->khString.matrixCod[keyPosChange] = (char *) calloc(1,  sizeof (char ));
            strcpy(curr->khString.matrixPub[keyPosChange], "0");
            strcpy(curr->khString.matrixPriv[keyPosChange], "0");
            strcpy(curr->khString.matrixCod[keyPosChange], "0");
        } else{     // se existir essa linha é inserida
            curr->khString.matrixPub[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixPub[newKeyPos]))+1, sizeof (char ));
            curr->khString.matrixPriv[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixPriv[newKeyPos]))+1, sizeof (char ));
            curr->khString.matrixCod[keyPosChange] = (char *) calloc(numDigitsLong(atoll(mString.matrixCod[newKeyPos]))+1,  sizeof (char ));
            curr->khString.matrixPub[keyPosChange] =  mString.matrixPub[newKeyPos];
            curr->khString.matrixPriv[keyPosChange] = mString.matrixPriv[newKeyPos];
            curr->khString.matrixCod[keyPosChange] = mString.matrixCod[newKeyPos];
        }
        if(newKeyPos >= mInts.lines){ // se a linha das matrizes não existir é inserido um 0
            curr->khInts.matrixPub[keyPosChange] = (short *) calloc(2, sizeof (short ));
            curr->khInts.matrixPriv[keyPosChange] = (short *) calloc(2, sizeof (short ));
            curr->khInts.matrixCod[keyPosChange] = (short *) calloc(2, sizeof (short ));
            curr->khInts.matrixPub[keyPosChange][0] = 0;
            curr->khInts.matrixPriv[keyPosChange][0] = 0;
            curr->khInts.matrixCod[keyPosChange][0] = 0;
            curr->khInts.matrixPub[keyPosChange][1] = -1;
            curr->khInts.matrixPriv[keyPosChange][1] = -1;
            curr->khInts.matrixCod[keyPosChange][1] = -1;
        } else{     // se existir essa linha é inserida
            curr->khInts.matrixPub[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixPub[newKeyPos]))+1, sizeof (short ));
            curr->khInts.matrixPriv[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixPriv[newKeyPos]))+1, sizeof (short ));
            curr->khInts.matrixCod[keyPosChange] = (short *) calloc(numDigitsLong(key_digits_2_long_int(mInts.matrixCod[newKeyPos]))+1, sizeof (short ));
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
    }

    curr->data_modificacao = ctime(&data_modificacao);      // artualizo a data de modificação

    // se não for o primeiro porta chaves, atualizo a lista ligada
    if(keyHolderPos != 1){
        temp->next = curr->next;    // o porta chaves anterior agora vai apontador para o proximo deste prota chaves editado
        curr->next = *portaChaves;  // este porta chaves vai agora apontar para o primeiro porta chaves
        *portaChaves = curr;        // este porta chaves editado vai passar a ser o primeiro porta chaves da lista ligada
    }
}

/**
 * Esta função remove um porta chaves numa dada posição
 * @param portaChaves apontador que aponta para os vários porta chaves
 * @param keyHolderPos posição do porta chaves
 */
void remove_keyHolder(KEY_HOLDER** portaChaves, int keyHolderPos){
    int removePos = 1;

    if(*portaChaves == NULL) return;

    // se for o primeiro porta chaves, o segundo porta chaves vai agora passar a ser o primeiro
    if(keyHolderPos == 1){
        *portaChaves = (*portaChaves)->next;    // igualar o primeiro porta chaves ao seu proximo(segundo porta chaves)
    }

    // percorrer os porta chaves até ao na posição dada
    KEY_HOLDER *curr = *portaChaves;
    while (curr->next != NULL){
        if(removePos+1 == keyHolderPos){       // quando o proximo porta chaves for o escolhido
            curr->next = curr->next->next;     // este porta chaves(1 antes do que vai ser removido) vai apontador para o proximo porta chaves do porta chaves que vai ser removido
            if(curr->next == NULL) break;      // se o porta chaves não existir saimos do ciclo
        }
        removePos++;
        curr = curr->next;
    }
}

/**
 * Função que escreve na consola e num ficheiro se uma dada chave existe num dado porta chaves
 * Complexidade algoritmica Best case: O(1) / Average: O(n) / Worst: O(n^2)
 * @param portaChaves apontador que aponta para os vários porta chaves
 * @param keyHolderPos posição do porta chaves
 * @param keyToSeach chave a ser procurada
 * @param type tipode chave (1 - chave publica / 2 - chave privada / 3 - chave codificada)
 * @param filenamenome do ficheiro a inserir as informações
 */
void searchSingleKey_inKeyHolder(KEY_HOLDER* portaChaves, int keyHolderPos, unsigned long long keyToSeach, int type, char* filename){

    FILE *fp = fopen(filename, "a+");
    int stopPos = 1, exist = 0;
    if(type > 3 || type <= 0){  // se for inserido um tipo de chave que não existe
        printf("Tipo de chaves nao existe (1 - Publica / 2 - Privada / 3 - Codificada)\n");
        return;
    }
    // ciclo para percorrer a lista ligada até encontrar o porta chaves escolhido
    while (stopPos != keyHolderPos){
        portaChaves = portaChaves->next;
        stopPos++;
        if(portaChaves == NULL){        // se o porta chaves não existir
            printf("Porta Chaves nao existe\n");
            return;
        }
    }

        if(type == 1){  // chaves publicas
            for (int i = 0; portaChaves->khString.matrixPub[i] ; ++i) {
                if(atoll(portaChaves->khString.matrixPub[i]) == keyToSeach){
                    printf("A chave %llu existe na matrix de chaves publicas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves publicas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves publicas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves publicas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixPub[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixPub[i]) == keyToSeach){
                    printf("A chave %llu existe na matrix de chaves publicas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves publicas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves publicas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves publicas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
        }
        else if(type == 2){     // chaves privadas
            for (int i = 0; portaChaves->khString.matrixPriv[i] ; ++i) {
                if(atoll(portaChaves->khString.matrixPriv[i]) == keyToSeach){
                    printf("A chave %llu existe na matrix de chaves privadas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves privadas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves privadas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves privadas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixPriv[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixPriv[i]) == keyToSeach){
                    printf("A chave %llu existe na matrix de chaves privadas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves privadas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves privadas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves privadas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
        }
        else if(type == 3){     // chaves codificadas
            for (int i = 0; portaChaves->khString.matrixCod[i] ; ++i) {
                if(atoll(portaChaves->khString.matrixCod[i]) == keyToSeach){
                    printf("A chave %llu existe na matrix de chaves codificada de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves codificadas de Strings na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves codificadas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves codificadas de Strings do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
            for (int i = 0; portaChaves->khInts.matrixCod[i] ; ++i) {
                if(key_digits_2_long_int(portaChaves->khInts.matrixCod[i]) == atoll(keyToSeach)){
                    printf("A chave %llu existe na matrix de chaves codificada de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    fprintf(fp, "A chave %llu existe na matrix de chaves codificadas de Inteiros na prosicao %d do porta chaves %d\n", keyToSeach, i, keyHolderPos);
                    exist = 1;
                }
            }
            if(exist == 0){
                printf("A chave %llu nao existe na matrix de chaves codificadas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
                fprintf(fp, "A chave %llu nao existe na matrix de chaves codificadas de Inteiros do porta chaves %d\n", keyToSeach, keyHolderPos);
            }
            exist = 0;
        }
    fclose(fp);
}

/**
 * Função que guarda um porta chaves num ficheiro
 * @param portaChaves apontador que aponta para os vários porta chaves
 * @param mString struct de matrizes de string
 * @param mInts struct de matrizes de ints
 * @param keyHolderPos posição do porta chaves
 * @param filename nome do ficheiro
 */
void save_txt_keyHolder(KEY_HOLDER ** portaChaves, struct matrixString mString, struct matrixInts mInts, int keyHolderPos, char filename[]){

    FILE *fileChavesPubWrite;
    fileChavesPubWrite = fopen(filename, "a+");
    int stopPos = 1;

    if(fileChavesPubWrite == NULL){
        printf("Ficheiro nao existe\n");
        return;
    }

    KEY_HOLDER * curr = *portaChaves;
    while (stopPos != keyHolderPos){
        curr = curr->next;
        if(curr == NULL){
            printf("Porta Chaves Nao Encontrado\n");
            return;
        }
        stopPos++;
    }

    int i = 0;
    while (i < curr->sizeStrings){
        fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixPub[i]);
        fprintf(fileChavesPubWrite,"\n");
        fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixPriv[i]);
        fprintf(fileChavesPubWrite,"\n");
        fprintf(fileChavesPubWrite,"%s" , curr->khString.matrixCod[i]);
        fprintf(fileChavesPubWrite,"\n");

        i++;
    }
    i = 0;
    while (i < curr->sieInts){
        fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixPub[i]));
        fprintf(fileChavesPubWrite,"\n");
        fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixPriv[i]));
        fprintf(fileChavesPubWrite,"\n");
        fprintf(fileChavesPubWrite,"%llu" , key_digits_2_long_int(curr->khInts.matrixCod[i]));
        fprintf(fileChavesPubWrite,"\n");

        i++;
    }

    fclose(fileChavesPubWrite);
}

/**
 * Funçãoq eu recebe um porta chaves de um ficheiro
 * @param portaChaves apontador que aponta para os vários porta chaves
 * @param mString struct de matrizes string
 * @param mInts struct de matrizes ints
 * @param keyHolderPos posição do porta chaves
 * @param newKeysPos linha do porta chaves a adicionar
 * @param filename nome do ficheiro
 */
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

/**
 * Função que escreve os vários porta chaves na consola
 * @param portaChaves apontador que aponta para os vários porta chaves
 */
void print_keyHolders(KEY_HOLDER** portaChaves){
    int sair = 0, numPortaChaves = 1;
    for (KEY_HOLDER *curr = *portaChaves; curr != NULL ; curr = curr->next) {
        int i = 0;
        printf("Porta Chaves - %d\n", numPortaChaves);
        while (1){  // ciclo infinito (termina quando as matrizes chegarem ao fim)
            if(strcmp(curr->khString.matrixPub[i], "-1") != 0) {
                printf("Porta Chaves PubKey String - %s\n", curr->khString.matrixPub[i]);
                sair = 0;
            } else sair = 1;
            if(strcmp(curr->khString.matrixPriv[i], "-1") != 0) {
                printf("Porta Chaves PrivKey String - %s\n", curr->khString.matrixPriv[i]);
                sair = 0;
            } else sair = 1;
            if(strcmp(curr->khString.matrixCod[i], "-1") != 0) {
                printf("Porta Chaves CodKey String - %s\n", curr->khString.matrixCod[i]);
                sair = 0;
            } else sair = 1;
            int j = 0;
            if(curr->khInts.matrixPub[i][0] != -1){
                printf("Porta Chaves PubKey Ints - ");
                while (curr->khInts.matrixPub[i][j] != -1){
                    printf("%hi", curr->khInts.matrixPub[i][j]);
                    j++;
                }
                sair = 0;
                printf("\n");
            } else sair = 1;
            j = 0;
            if(curr->khInts.matrixPriv[i][0] != -1){
                printf("Porta Chaves PrivKey Ints - ");
                while (curr->khInts.matrixPriv[i][j] != -1){
                    printf("%hi", curr->khInts.matrixPriv[i][j]);
                    j++;
                }
                sair = 0;
                printf("\n");
            } else sair = 1;
            j = 0;
            if(curr->khInts.matrixCod[i][0] != -1){
                printf("Porta Chaves CodKey Ints - ");
                while (curr->khInts.matrixCod[i][j] != -1){
                    printf("%hi", curr->khInts.matrixCod[i][j]);
                    j++;
                }
                sair = 0;
                printf("\n");
            } else sair = 1;
            if(sair == 1) break;
            i++;
        }
        printf("Data Criacao: %s", curr->data_criacao);
        printf("Data Modificacao: %s", curr->data_modificacao);
        printf("\n");
        numPortaChaves++;
    }
}


// ===================================================================================================================================== //
// ========================================== FUNÇÕES PARA UTILIZADORES ================================================================ //
// ===================================================================================================================================== //

/**
 * Função que cria um utilizador com uma dada lista de porta chaves (ordenado alfabeticamente por nome)
 * @param queue fila de utilizadores
 * @param utilizadores apontador que aponta para os vários utilizadores
 * @param name nome a ser inserido no utilizador
 * @param email email a ser inserido no utilizador
 * @param key_holder_list lista de porta chaves a ser inserida no utilizador
 * @param pos posição do primeiro porta chaves
 */
void create_utilizador_ordenado(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos) {
    int stopKeyHolderPos = 1;
    UTILIZADORES* utilizador = malloc(sizeof(UTILIZADORES));
    utilizador->name = malloc(sizeof (char) * (strlen(name) + 1));
    strcpy(utilizador->name, name);
    utilizador->email = malloc(sizeof (char) * (strlen(email) + 1));
    strcpy(utilizador->email, email);
    utilizador->email = email;
    utilizador->next = NULL;
    KEY_HOLDER *currKeyHolder = key_holder_list;
    while (stopKeyHolderPos < pos){     // ciclo até chegar ao porta chaves escolhido
        currKeyHolder = currKeyHolder->next;
        stopKeyHolderPos++;
        if (currKeyHolder == NULL){     // se não existir o porta chaves
            printf("Porta Chaves nao encontrado\n");
            return;
        }
    }
    utilizador->key_holder_list = currKeyHolder;

    // se a lista de utilizadores estiver vazia
    if(*utilizadores == NULL){
        *utilizadores = utilizador; // este vai ser o primerio utilizador
        queue->size++;
        enqueue(queue, utilizador); // chama a função para ordenar (head & tail) na fila de utilizadores
        return;
    }

    // ciclo para encontrar a posição do novo utilizador (ordenado alfabeticamente)
    UTILIZADORES *curr = *utilizadores;
    UTILIZADORES *prev = NULL;
    while (curr != NULL && strcmp(curr->name, name) < 0) {  // o ciclo continua a procurar a pos enquanto existirem porta chaves com um nome alfabeticamente "menor" que o utilizador a ser criado
        prev = curr;        // porta chaves anterior vai passar a ser igual ao atual
        curr = curr->next;  // porta chaves atual vai passar a ser o proximo porta chaves
    }

    // se não existirem porta chaves anteriores quer dizer que este utilizador é o que tem o nome alfabeticamente "menor" etnão fica em primeiro
    if (prev == NULL) {
        utilizador->next = *utilizadores;
        *utilizadores = utilizador;
        queue->head = utilizador;
    } else {    // se existirem utilizadores com nome "menor"
        utilizador->next = prev->next;  // o novo utilizador vai apontar para o antigo utilizador apontado pelo anterior
        prev->next = utilizador;        // e o utilizador anteriro agora vai apontar para o novo utilizador
    }

    queue->size++;
}

/**
 * Função que cria um utilizador à cauda com uma dada lista de porta chaves
 * @param queue fila de utilizadores
 * @param utilizadores apontador que aponta para os vários utilizadores
 * @param name nome a ser inserido no utilizador
 * @param email email a ser inserido no utilizador
 * @param key_holder_list lista de porta chaves a ser inserida no utilizador
 * @param pos posição do primeiro porta chaves
 */
void create_utilizador_cauda(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos) {
    int stopKeyHolderPos = 1;
    UTILIZADORES* utilizador = malloc(sizeof(UTILIZADORES));
    utilizador->name = malloc(sizeof (char) * (strlen(name) + 1));
    strcpy(utilizador->name, name);
    utilizador->email = malloc(sizeof (char) * (strlen(email) + 1));
    strcpy(utilizador->email, email);
    utilizador->email = email;
    utilizador->next = NULL;
    KEY_HOLDER *currKeyHolder = key_holder_list;
    while (stopKeyHolderPos < pos){     // ciclo até chegar ao porta chaves escolhido
        currKeyHolder = currKeyHolder->next;
        stopKeyHolderPos++;
        if (currKeyHolder == NULL){     // se não existir o porta chaves
            printf("Porta Chaves nao encontrado\n");
            return;
        }
    }
    utilizador->key_holder_list = currKeyHolder;

    // se a lista de utilizadores estiver vazia
    if(*utilizadores == NULL){
        *utilizadores = utilizador; // este vai ser o primerio utilizador
        queue->size++;
        enqueue(queue, utilizador); // chama a função para ordenar (head & tail) na fila de utilizadores
        return;
    }

    // ciclo para percorrer os utilizadores até chegar ao penultimo
    UTILIZADORES *curr = *utilizadores;
    while (curr->next != NULL){
        curr = curr->next;
    }
    // o penultimo utilizador vai apontar para o novo utilizar
    curr->next = utilizador;
    queue->size++;
    enqueue(queue, curr->next);  // chama a função para ordenar (head & tail) na fila de utilizadores
}

/**
 * Função que cria um utilizador à cabeça com uma dada lista de porta chaves
 * @param queue fila de utilizadores
 * @param utilizadores apontador que aponta para os vários utilizadores
 * @param name nome a ser inserido no utilizador
 * @param email email a ser inserido no utilizador
 * @param key_holder_list lista de porta chaves a ser inserida no utilizador
 * @param pos posição do primeiro porta chaves
 */
void create_utilizador_cabeca(UTILIZADORES_QUEUE* queue, UTILIZADORES **utilizadores, char* name, char* email, KEY_HOLDER* key_holder_list, int pos) {
    int stopKeyHolderPos = 1;
    UTILIZADORES* utilizador = malloc(sizeof(UTILIZADORES));
    utilizador->name = malloc(sizeof (char) * (strlen(name) + 1));
    strcpy(utilizador->name, name);
    utilizador->email = malloc(sizeof (char) * (strlen(email) + 1));
    strcpy(utilizador->email, email);
    utilizador->email = email;
    utilizador->next = *utilizadores;
    KEY_HOLDER *currKeyHolder = key_holder_list;
    while (stopKeyHolderPos < pos){     // ciclo até chegar ao porta chaves escolhido
        currKeyHolder = currKeyHolder->next;
        stopKeyHolderPos++;
        if (currKeyHolder == NULL){     // se não existir o porta chaves
            printf("Porta Chaves nao encontrado\n");
            return;
        }
    }
    utilizador->key_holder_list = currKeyHolder;

    // se a lista de utilizadores estiver vazia
    if(*utilizadores == NULL){
        *utilizadores = utilizador; // este vai ser o primerio utilizador
        queue->size++;
        enqueue(queue, utilizador); // chama a função para ordenar (head & tail) na fila de utilizadores
        return;
    }

    // Insere o novo utilizador no inicio da lista ligada
    queue->size++;
    *utilizadores = utilizador; // o primeiro utilizador vai ser este novo utilizador
    queue->head = utilizador;   // a head da fila vai passar a ser este novo utilizador
}

/**
 * Atualiza a head e tail da fila de utilizadores
 * @param queue fila de utilizadores
 * @param utilizador apontador de um utilizador
 */
void enqueue(UTILIZADORES_QUEUE* queue, UTILIZADORES* utilizador) {
    if (queue->tail == NULL) {  // se a tail for NULL que dizer que a fila está vaiza
        queue->head = utilizador;   // então a head vai ser o utilizador
        queue->tail = utilizador;   // a tail tambem vai ser o utilizador
    } else {    // se a fila não estiver vazia
        queue->tail->next = utilizador; // a antiga tail vai apontador para o utilizador
        queue->tail = utilizador;       // tail vai ser atualizada para o utilizador (no fim a tail aponta para ela mesma por causa da linha anterior)
    }
}

/**
 * Função para dar free a toda a fila de utilizadores
 * @param queue fila de utilizadors
 */
void dequeue(UTILIZADORES_QUEUE* queue){
    while (queue->head != NULL){        // cilco enquanto a head for diferente de NULL
        if(queue->head == queue->tail){ // se a head e a tail forem iguais então só existe 1 utilizador
            queue->head = NULL;
            queue->tail = NULL;
        }
        else{                                   // se a head e a tail não forem iguais a fila tem vários utilizadores
            UTILIZADORES *temp = queue->head;   // temp a apontar para a head
            queue->head = queue->head->next;    // a head vai passar a ser o prox utilizador
            free(temp);                 // free à antiga head
        }
    }
}

/**
 * Função que escreve na consola todos os utilizadores
 * @param queue fila de utilizadores
 */
void print_utilizadores(UTILIZADORES_QUEUE* queue) {
    UTILIZADORES* curr = queue->head;
    while (curr != NULL) {
        printf("Name: %s\n", curr->name);
        printf("Email: %s\n", curr->email);
        print_keyHolders(&curr->key_holder_list);   // chama a função para escrever todos os porta chaves (deste utilizador)
        curr = curr->next;
    }
}

/**
 * Função que remove um utilizasdor por nome
 * @param queue fila de utilizadores
 * @param name nome do utilizador
 */
void remover_nome_utilizador(UTILIZADORES_QUEUE* queue, char* name) {
    UTILIZADORES* curr = queue->head;
    UTILIZADORES* previous = NULL;

    // percorre a fila de utilizadores até encontrar um utilizador com o nome a ser procurado
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        previous = curr;        // o utilizador o valor de prev com o utilizador anterior
        curr = curr->next;      // percorre a fila de utilizadores
    }

    // se não encontrar nenhum utilizador com o nome a ser procurado
    if (curr == NULL) {
        printf("Utilizador Nao Encontrado\n");
        return;
    }

    // se existe um utilizador com o nome a ser procurado remove
    printf("Utilizador Apagado: %s\n", curr->name);
    // se o prev for NULL quer dizer que é o primeiro utilizador
    if (previous == NULL) {
        queue->head = curr->next;    // atualiza a head para o proximo utilizador
    } else {    // se não for o primeiro
        previous->next = curr->next;   // o anterior vai apontar para o proximo do utilizador a ser removido
    }

    // se o utilizador removido fosee o ultimo da fila a tail vai passar a ser o utilizador anterior ao que foi apagado
    if (curr->next == NULL) {
        queue->tail = previous;
    }

    queue->size--;
    free(curr);
}

/**
 * Função que remove um utilizador à cabeça
 * @param queue fila de utilizadores
 */
void remover_cabeca_utilizador(UTILIZADORES_QUEUE* queue) {
    printf("Utilizador Apagado: %s\n", queue->head->name);
    queue->head = queue->head->next;    // a head passa a ser o prox utilizador

    queue->size--;
}

/**
 * Função que remove um utilizador à cauda
 * @param queue fila de utilizadores
 */
void remover_cauda_utilizador(UTILIZADORES_QUEUE* queue) {
    UTILIZADORES *curr = queue->head;
    UTILIZADORES* previous = NULL;

    // percorre a fila de utilizadores
    while (curr->next != NULL){
        previous = curr;
        curr = curr->next;
    }

    printf("Utilizador Apagado: %s\n", curr->name);
    // se o utilizador a ser apagado não tinha anterior então era o primeiro
    if (previous == NULL) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {    // se não era o primeiro
        previous->next = NULL;  // o utilizador anterior vai apontar para NULL
        queue->tail = previous; // a tail vai passar a ser o utilizador anterior
    }

    queue->size--;
}

/**
 * Procura um utilizador por um dado nome
 * Complexidade algoritmica Best case: O(1) / Average: O(n) / Worst: O(n)
 * @param queue fila de utilizadores
 * @param name nome a ser procurado
 */
void search_utilizador_by_name(UTILIZADORES_QUEUE* queue, char* name) {
    int exist = 0;
    char nomeMinisculas[strlen(name)];  // array que vai ter o nome a ser procurado em minusculas
    UTILIZADORES* curr = queue->head;

    for (int i = 0; i < strlen(name); ++i) {    // mudar todos os carateres do nome a procurar para minusculas
        nomeMinisculas[i] = tolower(name[i]);
    }
    nomeMinisculas[strlen(name)] = '\0';    // inserir o \0 no fim da string
    while (curr != NULL) {
        char nomeUtilMinusculas[strlen(curr->name)];    // array que vai ter o nome do utilizador em minusculas
        for (int i = 0; i < strlen(curr->name); ++i) {  // mudar todos os carateres do nome do utilizador para minusculas
            nomeUtilMinusculas[i] = tolower(curr->name[i]);
        }
        nomeUtilMinusculas[strlen(curr->name)] = '\0';  // inserir o \0 no fim da string
        if (strstr(nomeUtilMinusculas, nomeMinisculas) != NULL) {   // se existir a sub string "nomeMinusculas" (nome a ser procurado) no nome do utilizador
            exist = 1;                                              // existe
            printf("Name: %s\n", curr->name);                // escreve na consola
            printf("Email: %s\n", curr->email);
            print_keyHolders(&curr->key_holder_list);
        }
        curr = curr->next;
    }
    if(exist == 0){ // se nao existir
        printf("Utilizador Nao Econtrado\n");
    }
}

/**
 * Funçãoq eu ordena os utilizador por nome
 * Complexidade algoritmica Best case: O(n) / Average: O(n^2) / Worst: O(n^2)
 * @param queue fila de utilizadores
 */
void ordenar_utilizadores(UTILIZADORES_QUEUE* queue){
    UTILIZADORES* curr;
    UTILIZADORES* index;

    // se a fila estiver vazia
    if (queue == NULL) {
        return;
    }

    if (queue->head == NULL) {
        return;
    }

    // bubble sort
    // ciclo que percorre os utilizadores até o proximo ser NULL
    for (curr = queue->head; curr->next != NULL; curr = curr->next) {
        // ciclo que percorre os utilizadors até o index ser NULL (index inicial é sempre o prox utilizador do primeiro ciclo)
        for (index = curr->next; index != NULL; index = index->next) {
            if (strcmp(curr->name, index->name) > 0) {   // se o index->name for menor que o curr->name
                char* temp_name = curr->name;            // guarda temporariamente o nome do curr
                char* temp_email = curr->email;          // guarda temporariamente o email do curr
                KEY_HOLDER* temp_key_holder_list = curr->key_holder_list;    // guardar temporariamente a lista de porta chaves do curr
                // Troca as posições dos utilizadores curr e index
                curr->name = index->name;
                curr->email = index->email;
                curr->key_holder_list = index->key_holder_list;
                index->name = temp_name;
                index->email = temp_email;
                index->key_holder_list = temp_key_holder_list;
            }
        }
    }
}


// ===================================================================================================================================== //
// ============================================== FUNÇÕES FREE ========================================================================= //
// ===================================================================================================================================== //

/**
 * Função que dá free à matriz de Char em N linhas
 * @param matrix matriz
 * @param N numero de linhas
 */
void freeMatrixChar(char **matrix, int N){
    for (int i = 0; i < N; ++i) {
        matrix[i] = NULL;
        free(matrix[i]);
    }
}

/**
 * Função que dá free à matriz de Ints em N linhas
 * @param matrix matriz
 * @param N nuero de linhas
 */
void freeMatrixShort(short **matrix, int N){
    for (int i = 0; i < N; ++i) {
        if(matrix[i] != NULL){
            matrix[i] = NULL;
            free(matrix[i]);
        }
    }
}

// ===================================================================================================================================== //
// =============================================== FUNÇÕES EXTRA ======================================================================= //
// ===================================================================================================================================== //

/**
 * Função que vai verificar se um dado numero é bipolar
 * @param text array com os vários digitos do numero
 * @return 0 se for bipolar / -1 se não for bipolar
 */
int bipolar_numberInt(short text[]){

    int bipolar = 0, changes = 0, exits = 0;
    int number, pow, digits = 0;

    for (int i = 0; text[i+1] != -1; ++i) {
        if(text[i] != text[i+1]){
            changes++;
        }
    }
    //changes--;
    if(changes == 1){
        return 0;
    }
    else{
        return -1;
    }
}

/**
 * Versão antiga da função para calcular chave privada
 * @param k string com os vários digitos da chave publica
 * @return chave privada
 */
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

/**
 * Versão antiga da função para calcular chave privada
 * @param k chave publica
 * @return chave privada
 */
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

/**
 * Retorna o valor de uma posição de um array
 * @param a array
 * @param d posição
 * @return retorna o valor dessa posição ou -1 se não existir
 */
int charPos(char *a, int d){
    if(d < strlen(a)) return a[d];
    else return -1;
}

/**
 * Algoritmos de ordenacao ShellSort
 * Complexidade algoritmica Best case: Nlog3(N) / Average: ? / Worst: cN^3/2
 * @param a mmatriz de strings
 * @param N tamanho da matriz
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void shellSortChar(char** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            //if(strcmp(a[i], "\0") == 0) return;
            if(strcmp(a[i], "-1") == 0) return;
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

/**
 * Algoritmos de ordenacao ShellSort (ordenar por numero de digitos)
 * Complexidade algoritmica Best case: Nlog3(N) / Average: ? / Worst: cN^3/2
 * @param a matriz de strings com chaves publicas
 * @param priv matriz de strings com chaves privadas
 * @param cod matriz de strings com chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void shellSortCharDigits(char** a, char** priv, char** cod, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            //if(strcmp(a[i], "\0") == 0) return;
            if(strcmp(a[i], "-1") == 0) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) < numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapCharDigits(a, priv, cod, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && numDigitsLong(atoll(a[j])) > numDigitsLong(atoll(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapCharDigits(a, priv, cod, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

/**
 * Troca valores de 2 posições diferentes
 * @param a matriz de strings com chaves publicas
 * @param priv matriz de strings com chaves privadas
 * @param cod matriz de strigns com chaves codificadas
 * @param i primeira posição do array a ser trocada
 * @param min segunda posição do array a ser trocada
 */
void swapCharDigits(char** a, char** priv, char** cod, int i, int min){

    char* temp = (char *) calloc(strlen(a[min]) * sizeof (char), sizeof (char));
    strcpy(temp, a[min]);
    strcpy(a[min], a[i]);
    strcpy(a[i], temp);
    strcpy(temp, priv[min]);
    strcpy(priv[min], priv[i]);
    strcpy(priv[i], temp);
    strcpy(temp, cod[min]);
    strcpy(cod[min], cod[i]);
    strcpy(cod[i], temp);
    temp = NULL;
    free(temp);
}

/**
 * Troca valores de 2 posições diferentes
 * @param a matriz de strings
 * @param i primeira posição do array a ser trocada
 * @param min segunda posição do array a ser trocada
 */
void swapChar(char** a, int i, int min){

    char* temp = (char *) calloc(strlen(a[min]) * sizeof (char), sizeof (char));
    strcpy(temp, a[min]);
    strcpy(a[min], a[i]);
    strcpy(a[i], temp);
    temp = NULL;
    free(temp);
}

/**
 * Algoritmos de ordenacao ShellSort
 * Complexidade algoritmica Best case: Nlog3(N) / Average: ? / Worst: cN^3/2
 * @param a matriz de short
 * @param N tamanho da matriz
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void shellSortInt(short** a, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            //if(a[i][0] == 0) return;
            if(a[i][0] == -1) return;
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

/**
 * Algoritmos de ordenacao ShellSort (ordenar por numero de digitos)
 * Complexidade algoritmica Best case: Nlog3(N) / Average: ? / Worst: cN^3/2
 * @param a matriz de short com chaves publicas
 * @param priv matriz de short com chaves privadas
 * @param cod matriz de short com chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void shellSortIntDigits(short** a, short** priv, short** cod, int N, int order){
    int h = 1;
    while (h < N/3){
        h = 3*h + 1;
    }
    while (h >= 1){
        for (int i = 0; i < N; ++i) {
            //if(a[i][0] == 0) return;
            if(a[i][0] == -1) return;
            if(order == 1){ // 1 -> ascendente
                for (int j = i; j >= h && numDigitsLong(key_digits_2_long_int(a[j])) < numDigitsLong(key_digits_2_long_int(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapIntDigits(a, priv, cod, j, j-h);
                }
            } else{ // 0 -> descendente
                for (int j = i; j >= h && numDigitsLong(key_digits_2_long_int(a[j])) > numDigitsLong(key_digits_2_long_int(a[j-h])); j -= h) {  //Para ordenar descendente é mudar de "<" para ">"
                    swapIntDigits(a, priv, cod, j, j-h);
                }
            }
        }
        h /= 3;
    }
}

/**
 * Troca valores de 2 posições diferentes
 * @param a matriz de short com chaves publicas
 * @param priv matriz de short com chaves privadas
 * @param cod matriz de short com chaves codificadas
 * @param i primeira posição do array a ser trocada
 * @param min segunda posição do array a ser trocada
*/
void swapIntDigits(short** a, short** priv, short** cod, int i, int min){

    short* temp = (short *) calloc(numDigitsLong(key_digits_2_long_int(a[min])), sizeof (short ));
    temp = a[min];
    a[min] = a[i];
    a[i] = temp;
    temp = priv[min];
    priv[min] = priv[i];
    priv[i] = temp;
    temp = cod[min];
    cod[min] = cod[i];
    cod[i] = temp;
    temp = NULL;
    free(temp);
}

/**
 * Troca valores de 2 posições diferentes
 * @param a matriz de short
 * @param i primeira posição do array a ser trocada
 * @param min segunda posição do array a ser trocada
 */
void swapInt(short** a, int i, int min){

    short* temp = (short *) calloc(numDigitsLong(key_digits_2_long_int(a[min])), sizeof (short ));
    temp = a[min];
    a[min] = a[i];
    a[i] = temp;
    temp = NULL;
    free(temp);
}

/**
 * Cria o array auxiliar para utilizar no algoritmo de merge sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings
 * @param N tamanho da matriz
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void merge_char_sort_base(char* a[], int N, int order){
    char **aux = malloc(N * sizeof (char*));
    merge_char_sort_recursive_cutoff(a, aux, 0, N-1, order);
}

/**
 * faz o merge dos 2 arrays de forma a ficarem ordenados
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings
 * @param aux matriz auxiliar
 * @param lo menor posição
 * @param mid posição do meio
 * @param hi maior posição
 * @param order tipo de ordem (1 - ascendente e 0 - descendente)
 */
void merge_char(char* a[], char* aux[], int lo, int mid, int hi, int order){
    for (int k = lo; k <= hi; ++k) {
        if(strcmp(a[k], "-1") == 0){
            hi--;
            continue;
        }
        aux[k] = malloc(strlen(a[k]) * sizeof (char));
        strcpy(aux[k], a[k]);
    }
    int i = lo, j = mid+1;
    if(order == 1){
        for (int k = lo; k <= hi; ++k) {
            if      (i > mid)                           strcpy(a[k], aux[j++]);
            else if (j > hi)                            strcpy(a[k], aux[i++]);
            else if (atoll(aux[j]) < atoll(aux[i]))     strcpy(a[k], aux[j++]);
            else                                        strcpy(a[k], aux[i++]);
        }
    } else{
        for (int k = lo; k <= hi; ++k) {
            if      (i > mid)                           strcpy(a[k], aux[j++]);
            else if (j > hi)                            strcpy(a[k], aux[i++]);
            else if (atoll(aux[j]) > atoll(aux[i]))     strcpy(a[k], aux[j++]);
            else                                        strcpy(a[k], aux[i++]);
        }
    }
}

/**
 * Calcula a posição do meio de ambas as metades do array
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings
 * @param aux matriz auxiliar
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordem (1 - ascendente e 0 - descendente)
 */
void merge_char_sort_recursive_basic(char* a[], char* aux[], int lo, int hi, int order){

    if(hi <= lo) return;
    int mid = lo + (hi-lo)/2;
    merge_char_sort_recursive_basic(a, aux, lo, mid, order);
    merge_char_sort_recursive_basic(a, aux, mid+1, hi, order);
    merge_char(a, aux, lo, mid, hi, order);
}

/**
 * Calcula a posição do meio de ambas as metades do array e caso o tamanho do array seja menor que 10 usa o insertion sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings
 * @param aux matriz auxiliar
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordem (1 - ascendente e 0 - descendente)
 */
void merge_char_sort_recursive_cutoff(char* a[], char* aux[], int lo, int hi, int order){

    if (hi <= lo + CUTOFF - 1)
    {
        insertionSort_char(&a[lo], hi-lo+1, order);
        return;
    }
    int mid = lo + (hi-lo)/2;
    merge_char_sort_recursive_basic(a, aux, lo, mid, order);
    merge_char_sort_recursive_basic(a, aux, mid+1, hi, order);
    merge_char(a, aux, lo, mid, hi, order);
}

/**
 * Algoritmo de ordenação insertion sort pega num valor do array e compara com os anteriores
 * Complexidade algoritmica: Best case: N / Average: 1/4N^2 / Worst: 1/2N^2
 * @param a matriz de strings
 * @param N tamanho da matriz
 * @param order tipo de ordem (1 - ascendente e 0 - descendente)
 */
void insertionSort_char(char* a[], int N, int order){
    for (int i = 0; i < N; ++i) {
        for (int j = i; j > 0; j--) {
            if(order == 1){
                if(strcmp(a[j], "-1") == 0) break;
                if(atoll(a[j]) < atoll(a[j-1])){  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-1);
                } else break;
            } else{
                if(strcmp(a[j], "-1") == 0) break;
                if(atoll(a[j]) > atoll(a[j-1])){  //Para ordenar descendente é mudar de "<" para ">"
                    swapChar(a, j, j-1);
                } else break;
            }
        }
    }
}

/**
 * Cria os arrais auxiliares para utilizar no algoritmo de merge sort (ordem por digitos)
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings com chaves publicas
 * @param priv matriz de strings com chaves privadas
 * @param cod matriz de strings com chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_char_sort_base(char* a[], char* priv[], char* cod[], int N, int order){
    char **aux = malloc(N * sizeof (char*));
    char **auxPriv = malloc(N * sizeof (char*));
    char **auxCod = malloc(N * sizeof (char*));
    mergeDigits_char_sort_recursive_cutoff(a, aux, priv, cod, auxPriv, auxCod, 0, N-1, order);
}

/**
 * faz o merge dos 2 arrays de forma a ficarem ordenados (por digitos)
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de strings com chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de strings com chaves privadas
 * @param cod matriz de strings co chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matriz auxiliar de chaves codificadas
 * @param lo menor posição
 * @param mid posição do meio
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_char(char* a[], char* aux[], char* priv[], char* cod[], char* auxPriv[], char* auxCod[], int lo, int mid, int hi, int order){
    for (int k = lo; k <= hi; ++k) {
        if(strcmp(a[k], "-1") == 0){
            hi--;
            continue;
        }
        aux[k] = malloc((strlen(a[k])+1) * sizeof (char));
        auxPriv[k] = malloc((strlen(priv[k])+1) * sizeof (char));
        auxCod[k] = malloc((strlen(cod[k])+1) * sizeof (char));
        strcpy(aux[k], a[k]);
        strcpy(auxPriv[k], priv[k]);
        strcpy(auxCod[k], cod[k]);
    }
    int i = lo, j = mid+1;
    if(order == 1){
        for (int k = lo; k <= hi; ++k) {
            if (i > mid){
                strcpy(a[k], aux[j++]);
                j--;
                strcpy(priv[k], auxPriv[j++]);
                j--;
                strcpy(cod[k], auxCod[j++]);
            }
            else if (j > hi){
                strcpy(a[k], aux[i++]);
                i--;
                strcpy(priv[k], auxPriv[i++]);
                i--;
                strcpy(cod[k], auxCod[i++]);
            }
            else if (numDigitsLong(atoll(aux[j])) < numDigitsLong(atoll(aux[i]))){
                strcpy(a[k], aux[j++]);
                j--;
                strcpy(priv[k], auxPriv[j++]);
                j--;
                strcpy(cod[k], auxCod[j++]);
            }
            else{
                strcpy(a[k], aux[i++]);
                i--;
                strcpy(priv[k], auxPriv[i++]);
                i--;
                strcpy(cod[k], auxCod[i++]);
            }
        }
    } else{
        for (int k = lo; k <= hi; ++k) {
            if (i > mid){
                strcpy(a[k], aux[j++]);
                j--;
                strcpy(priv[k], auxPriv[j++]);
                j--;
                strcpy(cod[k], auxCod[j++]);
            }
            else if (j > hi) {
                strcpy(a[k], aux[i++]);
                i--;
                strcpy(priv[k], auxPriv[i++]);
                i--;
                strcpy(cod[k], auxCod[i++]);
            }
            else if (numDigitsLong(atoll(aux[j])) > numDigitsLong(atoll(aux[i]))){
                strcpy(a[k], aux[j++]);
                j--;
                strcpy(priv[k], auxPriv[j++]);
                j--;
                strcpy(cod[k], auxCod[j++]);
            }
            else {
                strcpy(a[k], aux[i++]);
                i--;
                strcpy(priv[k], auxPriv[i++]);
                i--;
                strcpy(cod[k], auxCod[i++]);
            }
        }
    }
}

/**
 * Calcula a posição do meio de ambas as metades do array
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de string de chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de chaves privadas
 * @param cod matriz de chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matriz auxiliar de chaves codificadas
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_char_sort_recursive_basic(char* a[], char* aux[], char* priv[], char* cod[], char* auxPriv[], char* auxCod[], int lo, int hi, int order){

    if(hi <= lo) return;
    int mid = lo + (hi-lo)/2;
    mergeDigits_char_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, lo, mid, order);
    mergeDigits_char_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, mid+1, hi, order);
    mergeDigits_char(a, aux, priv, cod, auxPriv, auxCod, lo, mid, hi, order);
}

/**
 * Calcula a posição do meio de ambas as metades do array e caso o tamanho do array seja menor que 10 usa o insertion sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de string de chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de string de chaves privadas
 * @param cod matriz de string de chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matriz auxiliar de chaves codificadas
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_char_sort_recursive_cutoff(char* a[], char* aux[], char* priv[], char* cod[], char* auxPriv[], char* auxCod[], int lo, int hi, int order){

    if (hi <= lo + CUTOFF - 1)
    {
        insertionSortDigits_char(&a[lo], priv, cod, hi-lo+1, order);
        return;
    }
    int mid = lo + (hi-lo)/2;
    mergeDigits_char_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, lo, mid, order);
    mergeDigits_char_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, mid+1, hi, order);
    mergeDigits_char(a, aux, priv, cod, auxPriv, auxCod, lo, mid, hi, order);
}

/**
 * Algoritmo de ordenação insertion sort pega num valor de digitos do array e compara com os anteriores
 * Complexidade algoritmica: Best case: N / Average: 1/4N^2 / Worst: 1/2N^2
 * @param a matriz de string de chaves publicas
 * @param priv matriz de strignde chaves privadas
 * @param cod matriz de string de chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void insertionSortDigits_char(char* a[], char* priv[], char* cod[], int N, int order){
    for (int i = 0; i < N; ++i) {
        for (int j = i; j > 0; j--) {
            if(order == 1){
                if(strcmp(a[j], "-1") == 0) break;
                if(numDigitsLong(atoll(a[j])) < numDigitsLong(atoll(a[j-1]))){  //Para ordenar descendente é mudar de "<" para ">"
                    swapCharDigits(a, priv, cod, j, j-1);
                } else break;
            } else{
                if(strcmp(a[j], "-1") == 0) break;
                if(numDigitsLong(atoll(a[j])) > numDigitsLong(atoll(a[j-1]))){  //Para ordenar descendente é mudar de "<" para ">"
                    swapCharDigits(a, priv, cod, j, j-1);
                } else break;
            }
        }
    }
}

/**
 * Cria o array auxiliar para utilizar no algoritmo de merge sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short
 * @param N tamanho da matriz
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void merge_int_sort_base(short* a[], int N, int order){
    short **aux = malloc(N * sizeof (short*));
    merge_int_sort_recursive_cutoff(a, aux, 0, N-1, order);
}

/**
 * faz o merge dos 2 arrays de forma a ficarem ordenados
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short
 * @param aux matriz auxiliar de short
 * @param lo menor posição
 * @param mid posição do meio
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void merge_int(short* a[], short* aux[], int lo, int mid, int hi, int order){
    for (int k = lo; k <= hi; ++k) {
        if(a[k][0] == -1){
            hi--;
            continue;
        }
        aux[k] = malloc(numDigitsLong(key_digits_2_long_int(a[k]) * sizeof (short)));
        aux[k] = a[k];
    }
    int i = lo, j = mid+1;
    if(order == 1){
        for (int k = lo; k <= hi; ++k) {
            if      (i > mid)                           a[k] = aux[j++];
            else if (j > hi)                            a[k] = aux[i++];
            else if (key_digits_2_long_int(aux[j]) < key_digits_2_long_int(aux[i]))                   a[k] = aux[j++];
            else                                        a[k] = aux[i++];
        }
    } else{
        for (int k = lo; k <= hi; ++k) {
            if      (i > mid)                           a[k] = aux[j++];
            else if (j > hi)                            a[k] = aux[i++];
            else if (key_digits_2_long_int(aux[j]) > key_digits_2_long_int(aux[i]))     a[k] = aux[j++];
            else                                        a[k] = aux[i++];
        }
    }
}

/**
 * Calcula a posição do meio de ambas as metades do array
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short
 * @param aux matriz auxiliar de short
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void merge_int_sort_recursive_basic(short* a[], short* aux[], int lo, int hi, int order){

    if(hi <= lo) return;
    int mid = lo + (hi-lo)/2;
    merge_int_sort_recursive_basic(a, aux, lo, mid, order);
    merge_int_sort_recursive_basic(a, aux, mid+1, hi, order);
    merge_int(a, aux, lo, mid, hi, order);
}

/**
 * Calcula a posição do meio de ambas as metades do array e caso o tamanho do array seja menor que 10 usa o insertion sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short
 * @param aux matriz auxiliar de short
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void merge_int_sort_recursive_cutoff(short* a[], short* aux[], int lo, int hi, int order){

    if (hi <= lo + CUTOFF - 1)
    {
        insertionSort_int(&a[lo], hi-lo+1, order);
        return;
    }
    int mid = lo + (hi-lo)/2;
    merge_int_sort_recursive_basic(a, aux, lo, mid, order);
    merge_int_sort_recursive_basic(a, aux, mid+1, hi, order);
    merge_int(a, aux, lo, mid, hi, order);
}

/**
 * Algoritmo de ordenação insertion sort pega num valor do array e compara com os anteriores
 * Complexidade algoritmica: Best case: N / Average: 1/4N^2 / Worst: 1/2N^2
 * @param a matriz de short
 * @param N tamanho da matriz
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void insertionSort_int(short* a[], int N, int order){
    for (int i = 0; i < N; ++i) {
        for (int j = i; j > 0; j--) {
            if(order == 1){
                if(a[j][0] == -1) break;
                if(key_digits_2_long_int(a[j]) < key_digits_2_long_int(a[j-1])){  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-1);
                } else break;
            } else{
                if(a[j][0] == -1) break;
                if(key_digits_2_long_int(a[j]) > key_digits_2_long_int(a[j-1])){  //Para ordenar descendente é mudar de "<" para ">"
                    swapInt(a, j, j-1);
                } else break;
            }
        }
    }
}

/**
  * Cria os arrais auxiliares para utilizar no algoritmo de merge sort (ordem por digitos)
  * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short com chaves publicas
 * @param priv matriz de short com  chaves privadas
 * @param cod matriz de short com chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_int_sort_base(short* a[], short* priv[], short* cod[], int N, int order){
    short **aux = malloc(N * sizeof (short*));
    short **auxPriv = malloc(N * sizeof (short*));
    short **auxCod = malloc(N * sizeof (short*));
    mergeDigits_int_sort_recursive_cutoff(a, aux, priv, cod, auxPriv, auxCod, 0, N-1, order);
}

/**
 * Faz o merge dos 2 arrays de forma a ficarem ordenados (por digitos)
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short com chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de short de chaves privadas
 * @param cod matriz de short de chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matriz auxiliar de chaves codificadas
 * @param lo menor posição
 * @param mid posição do meio
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_int(short* a[], short* aux[], short* priv[], short* cod[], short* auxPriv[], short* auxCod[], int lo, int mid, int hi, int order){
    for (int k = lo; k <= hi; ++k) {
        if(a[k][0] == -1){
            hi--;
            continue;
        }
        aux[k] = malloc(numDigitsLong(key_digits_2_long_int(a[k]) * sizeof (short)));
        auxPriv[k] = malloc(numDigitsLong(key_digits_2_long_int(priv[k]) * sizeof (short)));
        auxCod[k] = malloc(numDigitsLong(key_digits_2_long_int(cod[k]) * sizeof (short)));
        aux[k] = a[k];
        auxPriv[k] = priv[k];
        auxCod[k] = cod[k];
    }
    int i = lo, j = mid+1;
    if(order == 1){
        for (int k = lo; k <= hi; ++k) {
            if (i > mid){
                a[k] = aux[j++];
                j--;
                priv[k] = auxPriv[j++];
                j--;
                cod[k] = auxCod[j++];
            }
            else if (j > hi){
                a[k] = aux[i++];
                i--;
                priv[k] = auxPriv[i++];
                i--;
                cod[k] = auxCod[i++];
            }
            else if (numDigitsLong(key_digits_2_long_int(aux[j])) < numDigitsLong(key_digits_2_long_int(aux[i]))){
                a[k] = aux[j++];
                j--;
                priv[k] = auxPriv[j++];
                j--;
                cod[k] = auxCod[j++];
            }
            else{
                a[k] = aux[i++];
                i--;
                priv[k] = auxPriv[i++];
                i--;
                cod[k] = auxCod[i++];
            }
        }
    } else{
        for (int k = lo; k <= hi; ++k) {
            if (i > mid){
                a[k] = aux[j++];
                j--;
                priv[k] = auxPriv[j++];
                j--;
                cod[k] = auxCod[j++];
            }
            else if (j > hi) {
                a[k] = aux[i++];
                i--;
                priv[k] = auxPriv[i++];
                i--;
                cod[k] = auxCod[i++];
            }
            else if (numDigitsLong(key_digits_2_long_int(aux[j])) > numDigitsLong(key_digits_2_long_int(aux[i]))){
                a[k] = aux[j++];
                j--;
                priv[k] = auxPriv[j++];
                j--;
                cod[k] = auxCod[j++];
            }
            else {
                a[k] = aux[i++];
                i--;
                priv[k] = auxPriv[i++];
                i--;
                cod[k] = auxCod[i++];
            }
        }
    }
}

/**
 * Calcula a posição do meio de ambas as metades do array
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short de chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de short de chaves privadas
 * @param cod matriz de short de chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matrix auxiliar de chaves codificadas
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_int_sort_recursive_basic(short* a[], short* aux[], short* priv[], short* cod[], short* auxPriv[], short* auxCod[], int lo, int hi, int order){

    if(hi <= lo) return;
    int mid = lo + (hi-lo)/2;
    mergeDigits_int_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, lo, mid, order);
    mergeDigits_int_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, mid+1, hi, order);
    mergeDigits_int(a, aux, priv, cod, auxPriv, auxCod, lo, mid, hi, order);
}

/**
 * Calcula a posição do meio de ambas as metades do array e caso o tamanho do array seja menor que 10 usa o insertion sort
 * Complexidade algoritmica: Best case: 1/2NlgN / Average: NlgN / Worst: NlgN
 * @param a matriz de short de chaves publicas
 * @param aux matriz auxiliar de chaves publicas
 * @param priv matriz de short de chaves privadas
 * @param cod matriz de short de chaves codificadas
 * @param auxPriv matriz auxiliar de chaves privadas
 * @param auxCod matriz auxiliar de chaves codificadas
 * @param lo menor posição
 * @param hi maior posição
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void mergeDigits_int_sort_recursive_cutoff(short* a[], short* aux[], short* priv[], short* cod[], short* auxPriv[], short* auxCod[], int lo, int hi, int order){

    if (hi <= lo + CUTOFF - 1)
    {
        insertionSortDigits_int(&a[lo], priv, cod, hi-lo+1, order);
        return;
    }
    int mid = lo + (hi-lo)/2;
    mergeDigits_int_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, lo, mid, order);
    mergeDigits_int_sort_recursive_basic(a, aux, priv, cod, auxPriv, auxCod, mid+1, hi, order);
    mergeDigits_int(a, aux, priv, cod, auxPriv, auxCod, lo, mid, hi, order);
}

/**
 * Algoritmo de ordenação insertion sort pega num valor de digitos do array e compara com os anteriores
 * Complexidade algoritmica: Best case: N / Average: 1/4N^2 / Worst: 1/2N^2
 * @param a matriz de short de chaves publicas
 * @param priv matriz de short de chves privadas
 * @param cod matriz de short de chaves codificadas
 * @param N tamanho das matrizes
 * @param order tipo de ordenação (1 - ascendente / 0 - descendente)
 */
void insertionSortDigits_int(short* a[], short* priv[], short* cod[], int N, int order){
    for (int i = 0; i < N; ++i) {
        for (int j = i; j > 0; j--) {
            if(order == 1){
                if(a[j][0] == -1) break;
                if(numDigitsLong(key_digits_2_long_int(a[j])) < numDigitsLong(key_digits_2_long_int(a[j-1]))){  //Para ordenar descendente é mudar de "<" para ">"
                    swapIntDigits(a, priv, cod, j, j-1);
                } else break;
            } else{
                if(a[j][0] == -1) break;
                if(numDigitsLong(key_digits_2_long_int(a[j])) > numDigitsLong(key_digits_2_long_int(a[j-1]))){  //Para ordenar descendente é mudar de "<" para ">"
                    swapIntDigits(a, priv, cod, j, j-1);
                } else break;
            }
        }
    }
}