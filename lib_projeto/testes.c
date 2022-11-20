//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

void clienteString(struct matrixString mString);
void clienteInt(struct matrixInts mInts);

int main_test(){

    struct matrixString mString;
    struct matrixInts mInts;

    time_t t1;
    srand((unsigned ) time(&t1));

    //clienteString(mString);
    clienteInt(mInts);

    return 0;
}

void clienteString(struct matrixString mString){
    char filename[] = "../data/chaves_publicas.txt";
    char *publicKeyChar, *privKeyChar, *codKeyChar;
    unsigned long long key = 2014, publicKeyLong = 0, privKeyLong = 0, codKeyLong = 0;
    int lines = 1, columns = 10000;

    privKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    codKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
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

    mString.matrixPub = alloc_matrix_char(lines, columns);
    mString.matrixPriv = alloc_matrix_char(lines, columns);
    mString.matrixCod = alloc_matrix_char(lines, columns);

    store_key_char(mString.matrixPub, lines, publicKeyLong);
    store_key_char(mString.matrixPriv, lines, privKeyLong);
    store_key_char(mString.matrixCod, lines, codKeyLong);

    /*
    publicKeyChar = key_long_2_digits_char(8);
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

    publicKeyChar = key_long_2_digits_char(312);
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
    */
    /*
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, 2014));
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, publicKeyLong));
    */

    /*
    printf("A Chave Privada e - %llu\n", get_private_key_char(mString.matrixPub, mString.matrixPriv, 5, 2014));
    printf("A Chave Codificada e - %llu\n", get_runlength_char(mString.matrixPriv, mString.matrixCod, 5, 16));
    */

    //printf("Chave Publica Apagada %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, 5, '8'));

    //sort_matrix_char(mString.matrixPub, 5, 1);
    //sort_all_matrices_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, 5, 1);
    //list_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, 5, 1);
    /* for (int i = 0; i < 3; ++i) {
        printf("Chave Publica %s\n", mString.matrixPub[i]);
    }*/
    /*for (int i = 0; i < 3; ++i) {
        printf("Chave Privada %s\n", mString.matrixPriv[i]);
    }*/
    /*for (int i = 0; i < 3; ++i) {
        printf("Chave Codificada %s\n", mString.matrixCod[i]);
    }*/
    //save_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, 5, filename);

    //load_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    for (int i = 0; i < lines; ++i) {
        printf("Chave Publica %s\n", mString.matrixPub[i]);
    }
    for (int i = 0; i < lines; ++i) {
        printf("Chave Privada %s\n", mString.matrixPriv[i]);
    }
    for (int i = 0; i < lines; ++i) {
        printf("Chave Codificada %s\n", mString.matrixCod[i]);
    }
    /*
    bulk_populate_public_keys_char(mString.matrixPub, 2);
    for (int i = 0; i < 2; ++i) {
        printf("mString PubMatrix de %d - %s\n", i, mString.matrixPub[i]);
    }
    bulk_compute_private_keys_char(mString.matrixPub, mString.matrixPriv, 2);
    for (int i = 0; i < 2; ++i) {
        printf("mString PrivMatrix de %d - %s\n", i, mString.matrixPriv[i]);
    }
    bulk_compute_runlengths_char(mString.matrixPriv, mString.matrixCod, 2);
    for (int i = 0; i < 2; ++i) {
        printf("mString CodMatrix de %d - %s\n", i, mString.matrixCod[i]);
    }
     */

    //char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey); //TODO nao percebi muito bem

    for (int i = 0; i < lines; ++i) {
        free(mString.matrixPub[i]);
        free(mString.matrixPriv[i]);
        free(mString.matrixCod[i]);
    }
    free(mString.matrixPub);
    free(mString.matrixPriv);
    free(mString.matrixCod);
}

void clienteInt(struct matrixInts mInts){

    unsigned long long pubKey = 0, privKey = 0, codKey = 0;
    short *allD = NULL;
    int lines = 1, columns = 1;

    pubKey = new_public_key_int();
    pubKey = 130;
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
    printf("PrivKey - %llu\n", privKey);
    //printf("CodKey - %llu\n", codKey);

    mInts.matrixPub = alloc_matrix_int(lines, columns);
    mInts.matrixPriv = alloc_matrix_int(lines, columns);
    mInts.matrixCod = alloc_matrix_int(lines, columns);

    store_key_int(mInts.matrixPub, lines, pubKey);
    store_key_int(mInts.matrixPriv, lines, privKey);
    store_key_int(mInts.matrixCod, lines, codKey);


    for (int i = 0; i < lines; ++i) {
        printf("PubKey - %hi\n", mInts.matrixPub[i][0]);
        printf("PrivKey - %hi\n", mInts.matrixPriv[i][0]);
        printf("CodKey - %hi\n", mInts.matrixCod[i][0]);
    }
    printf("\n");


    //printf("Exists - %d\n", exists_key_int(mInts.matrixPub, lines, pubKey));
    //printf("PrivKey da PubKey - %llu\n", get_private_key_int(mInts.matrixPub, mInts.matrixPriv, lines, pubKey));
    //printf("CodKey da PrivKey - %llu\n", get_runlength_int(mInts.matrixPriv, mInts.matrixCod, lines, privKey));

    //printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, pubKey));

    /*
    bulk_populate_public_keys_int(mInts.matrixPub, 5);
    bulk_compute_private_keys_int(mInts.matrixPub, mInts.matrixPriv, 5);
    bulk_compute_runlengths_int(mInts.matrixPriv, mInts.matrixCod, 5);
    for (int i = 0; i < 5; ++i) {
        printf("PubKey - %hi\n", mInts.matrixPub[i][0]);
        printf("PrivKey - %hi\n", mInts.matrixPriv[i][0]);
        printf("CodKey - %hi\n", mInts.matrixCod[i][0]);
    }
     */
}