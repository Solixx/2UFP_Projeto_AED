//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

struct matrixString clienteString(struct matrixString mString);
struct matrixInts clienteInt(struct matrixInts mInts);
void clienteKeyHolder(KEY_HOLDER *portaChaves, struct matrixString mString, struct matrixInts mInts);

int main_test(){

    struct matrixString mString;
    struct matrixInts mInts;
    KEY_HOLDER *portaChaves = NULL;

    time_t t1;
    srand((unsigned ) time(&t1));

    //mString = clienteString(mString);
    mInts = clienteInt(mInts);

    /*
    printf("Ints - %hi\n", mInts.matrixPub[1][0]);
    printf("String - %s\n", mString.matrixPub[0]);
    printf("Ints - %hi\n", mInts.matrixPub[0][0]);
    printf("String - %s\n", mString.matrixPub[1]);
    */

    //clienteKeyHolder(portaChaves, mString, mInts);

    return 0;
}

struct matrixString clienteString(struct matrixString mString){
    char filename[] = "../data/chaves_publicas.txt";
    char *publicKeyChar, *privKeyChar, *codKeyChar;
    char **privKeySearch = NULL;
    unsigned long long key = 2014, publicKeyLong = 0, privKeyLong = 0, codKeyLong = 0;
    int lines = 10, columns = 1;

    privKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    codKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    publicKeyChar = key_long_2_digits_char(201);
    //printf("PubChar - %s\n", publicKeyChar);
    publicKeyLong = key_digits_2_long_char(publicKeyChar);
    //printf("PubLong - %llu\n", publicKeyLong);
    privKeyLong = calc_private_key_char(publicKeyLong);
    //printf("PrivLong - %llu\n", privKeyLong);
    sprintf(privKeyChar, "%llu", privKeyLong);
    //printf("PrivChar - %s\n", privKeyChar);
    codKeyLong = calc_runlength_char(privKeyLong);
    //printf("CodLong - %llu\n", codKeyLong);
    sprintf(codKeyChar, "%llu", codKeyLong);
    //printf("CodChar - %s\n", codKeyChar);

    mString.matrixPub = alloc_matrix_char(lines, columns);
    mString.matrixPriv = alloc_matrix_char(lines, columns);
    mString.matrixCod = alloc_matrix_char(lines, columns);

    store_key_char(mString.matrixPub, lines, publicKeyLong);
    store_key_char(mString.matrixPriv, lines, privKeyLong);
    store_key_char(mString.matrixCod, lines, codKeyLong);

    publicKeyChar = key_long_2_digits_char(2014);
    //printf("PubChar - %s\n", publicKeyChar);
    publicKeyLong = key_digits_2_long_char(publicKeyChar);
    //printf("PubLong - %llu\n", publicKeyLong);
    privKeyLong = calc_private_key_char(publicKeyLong);
    //printf("PrivLong - %llu\n", privKeyLong);
    sprintf(privKeyChar, "%llu", privKeyLong);
    //printf("PrivChar - %s\n", privKeyChar);
    codKeyLong = calc_runlength_char(privKeyLong);
    //printf("CodLong - %llu\n", codKeyLong);
    sprintf(codKeyChar, "%llu", codKeyLong);
    //printf("CodChar - %s\n", codKeyChar);

    store_key_char(mString.matrixPub, lines, publicKeyLong);
    store_key_char(mString.matrixPriv, lines, privKeyLong);
    store_key_char(mString.matrixCod, lines, codKeyLong);

    for (int i = 0; i < lines; ++i) {
        if(strcmp(mString.matrixPub[i], "\0") != 0) printf("Pub - %s\n", mString.matrixPub[i]);
        if(strcmp(mString.matrixPriv[i], "\0") != 0) printf("Priv - %s\n", mString.matrixPriv[i]);
        if(strcmp(mString.matrixCod[i], "\0") != 0) printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");

    //printf("Delete a - %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, mString.matrixPub[0]));

    /*
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, 2014));
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, publicKeyLong));
    */

    /*
    printf("A Chave Privada e - %llu\n", get_private_key_char(mString.matrixPub, mString.matrixPriv, 5, 2014));
    printf("A Chave Codificada e - %llu\n", get_runlength_char(mString.matrixPriv, mString.matrixCod, 5, 16));
    */

    //printf("Chave Publica Apagada %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, "2014"));

    //sort_matrix_char(mString.matrixPub, lines, 1);
    //sort_all_matrices_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);
    //list_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);

    privKeySearch = search_private_keys_char(mString.matrixPub, mString.matrixPriv, lines, 20);

    int j = 0;
    while (strcmp(privKeySearch[j], "\0") != 0){
        printf("Priv Encontrada - %s\n", privKeySearch[j]);
        j++;
    }

    /*
    for (int i = 0; i < lines; ++i) {
        if(strcmp(mString.matrixPub[i], "\0") != 0)printf("Pub - %s\n", mString.matrixPub[i]);
        if(strcmp(mString.matrixPriv[i], "\0") != 0) printf("Priv - %s\n", mString.matrixPriv[i]);
        if(strcmp(mString.matrixCod[i], "\0") != 0) printf("Cod - %s\n", mString.matrixCod[i]);
    }
     */

    //save_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    //load_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    /*
    bulk_populate_public_keys_char(mString.matrixPub, lines);

    for (int i = 0; i < lines; ++i) {
        printf("mString PubMatrix de %d - %s\n", i, mString.matrixPub[i]);
    }

    bulk_compute_private_keys_char(mString.matrixPub, mString.matrixPriv, lines);

    for (int i = 0; i < lines; ++i) {
        printf("mString PrivMatrix de %d - %s\n", i, mString.matrixPriv[i]);
    }

    bulk_compute_runlengths_char(mString.matrixPriv, mString.matrixCod, lines); //TODO recebe mas não imprime nos printf

    for (int i = 0; i < lines; ++i) {
        printf("mString CodMatrix de %d - %s\n", i, mString.matrixCod[i]);
    }
     */

    //char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey); //TODO nao percebi muito bem

    return mString;
}

struct matrixInts clienteInt(struct matrixInts mInts){

    char filename[] = "../data/chaves_publicas_ints.txt";
    unsigned long long pubKey = 0, privKey = 0, codKey = 0;
    short *allD = NULL, **privKeySearch = NULL;
    int lines = 5, columns = 1;

    pubKey = new_public_key_int();
    pubKey = 2014;
    allD = key_long_2_digits_int(pubKey);
    pubKey = key_digits_2_long_int(allD);
    privKey = calc_private_key_int(pubKey);
    codKey = calc_runlength_int(privKey);
    //printf("PubKey Random - %llu\n", pubKey);
    /*
    for (int i = 0; i < numDigitsLong(pubKey)+1; ++i) {
        printf("Digits PubKey - %hi\n", allD[i]);
    }
     */
    //printf("PubKey Por Digitos - %llu\n", pubKey);
    //printf("PrivKey - %llu\n", privKey);
    //printf("CodKey - %llu\n", codKey);

    mInts.matrixPub = alloc_matrix_int(lines, columns);
    mInts.matrixPriv = alloc_matrix_int(lines, columns);
    mInts.matrixCod = alloc_matrix_int(lines, columns);

    store_key_int(mInts.matrixPub, lines, pubKey);
    store_key_int(mInts.matrixPriv, lines, privKey);
    store_key_int(mInts.matrixCod, lines, codKey);

    pubKey = new_public_key_int();
    pubKey = 20;
    allD = key_long_2_digits_int(pubKey);
    pubKey = key_digits_2_long_int(allD);
    privKey = calc_private_key_int(pubKey);
    codKey = calc_runlength_int(privKey);

    store_key_int(mInts.matrixPub, lines, pubKey);
    store_key_int(mInts.matrixPriv, lines, privKey);
    store_key_int(mInts.matrixCod, lines, codKey);


    for (int i = 0; i < lines; ++i) {
        if(mInts.matrixPub[i][0] != NULL){
            int j = 0;
            printf("Pub - ");
            while (mInts.matrixPub[i][j] != -1){
                printf("%hi", mInts.matrixPub[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixPriv[i][0] != NULL){
            int j = 0;
            printf("Priv - ");
            while (mInts.matrixPriv[i][j] != -1){
                printf("%hi", mInts.matrixPriv[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixCod[i][0] != NULL){
            int j = 0;
            printf("Cod - ");
            while (mInts.matrixCod[i][j] != -1){
                printf("%hi", mInts.matrixCod[i][j]);
                j++;
            }
            printf("\n");
        }
    }
    printf("\n");

    //printf("Exists - %d\n", exists_key_int(mInts.matrixPub, lines, pubKey));
    //printf("PrivKey da PubKey - %llu\n", get_private_key_int(mInts.matrixPub, mInts.matrixPriv, lines, pubKey));
    //printf("CodKey da PrivKey - %llu\n", get_runlength_int(mInts.matrixPriv, mInts.matrixCod, lines, privKey));

    //printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, pubKey));

    //bulk_populate_public_keys_int(mInts.matrixPub, lines);
    //bulk_compute_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines);
    //bulk_compute_runlengths_int(mInts.matrixPriv, mInts.matrixCod, lines);

    privKeySearch = search_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines, 20);

    for (int i = 0; i < lines; ++i) {
        if(privKeySearch[i][0] != NULL){
            printf("Priv Encontrada - %llu", key_digits_2_long_int(privKeySearch[i]));
            printf("\n");
        }
    }

    /*
    for (int i = 0; i < lines; ++i) {
        if(mInts.matrixPub[i][0] != NULL){
            int j = 0;
            printf("Pub - ");
            while (mInts.matrixPub[i][j] != -1){
                printf("%hi", mInts.matrixPub[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixPriv[i][0] != NULL){
            int j = 0;
            printf("Priv - ");
            while (mInts.matrixPriv[i][j] != -1){
                printf("%hi", mInts.matrixPriv[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixCod[i][0] != NULL){
            int j = 0;
            printf("Cod - ");
            while (mInts.matrixCod[i][j] != -1){
                printf("%hi", mInts.matrixCod[i][j]);
                j++;
            }
            printf("\n");
        }
    }
     */

    //load_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);
    /*
    for (int i = 0; i < lines; ++i) {
        int j = 0;
        while (mInts.matrixPub[i][j] != -1){
            printf("%hi", mInts.matrixPub[i][j]);
            j++;
        }
        printf("\n");
    }
     */

    //sort_matrix_int(mInts.matrixPub, lines, 1);
    //sort_all_matrices_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);
    //list_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);
    /*
    for (int i = 0; i < lines; ++i) {
        printf("PubKey - %hi\n", mInts.matrixPub[i][0]);
        printf("PrivKey - %hi\n", mInts.matrixPriv[i][0]);
        printf("CodKey - %hi\n", mInts.matrixCod[i][0]);
    }
     */

    save_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);

    return mInts;
}

void clienteKeyHolder(KEY_HOLDER *portaChaves, struct matrixString mString, struct matrixInts mInts){

    insert_keyHolder(&portaChaves, mString, mInts);
    printf("Porta Chaves String - %s\n", portaChaves->khString.matrixPub[0]);
    printf("Porta Chaves Ints - %hi\n", portaChaves->khInts.matrixPub[0][0]);
    printf("Porta Chaves String - %s\n", portaChaves->khString.matrixPub[1]);
    printf("Porta Chaves Ints - %hi\n", portaChaves->khInts.matrixPub[1][0]);
}