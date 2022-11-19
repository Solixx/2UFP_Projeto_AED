//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

int main_test(){

    struct matrixString mString;
    struct matrixInts mInts;

    char *publicKeyChar, *privKeyChar, *codKeyChar;
    unsigned long long key = 2014, publicKeyLong = 0, privKeyLong = 0, codKeyLong = 0;

    /*
    privKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    codKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    publicKeyChar = key_long_2_digits_char(2014);
    printf("PubChar - %s\n", publicKeyChar);
    publicKeyLong = key_digits_2_long_char(publicKeyChar);
    printf("PubLong - %llu\n", publicKeyLong);
    privKeyLong = calc_private_key_char(publicKeyLong);
    printf("PrivLong - %llu\n", privKeyLong);
    sprintf(privKeyChar, "%llu", privKeyLong);
    printf("PrivChar - %s\n", privKeyChar);
    codKeyLong = calc_runlength_char(privKeyLong);
    printf("CodLong - %llu\n", codKeyLong);
    sprintf(codKeyChar, "%llu", codKeyLong);
    printf("CodChar - %s\n", codKeyChar);
     */

    mString.matrixPub = alloc_matrix_char(2, 5);
    mString.matrixPriv = alloc_matrix_char(2, 5);
    mString.matrixCod = alloc_matrix_char(2, 5);

    /*
    store_key_char(mString.matrixPub, 5, publicKeyLong);
    store_key_char(mString.matrixPriv, 5, privKeyLong);
    store_key_char(mString.matrixCod, 5, codKeyLong);

    publicKeyChar = key_long_2_digits_char(8);
    printf("PubChar - %s\n", publicKeyChar);
    publicKeyLong = key_digits_2_long_char(publicKeyChar);
    printf("PubLong - %llu\n", publicKeyLong);
    privKeyLong = calc_private_key_char(publicKeyLong);
    printf("PrivLong - %llu\n", privKeyLong);
    sprintf(privKeyChar, "%llu", privKeyLong);
    printf("PrivChar - %s\n", privKeyChar);
    codKeyLong = calc_runlength_char(privKeyLong);
    printf("CodLong - %llu\n", codKeyLong);
    sprintf(codKeyChar, "%llu", codKeyLong);
    printf("CodChar - %s\n", codKeyChar);

    store_key_char(mString.matrixPub, 5, publicKeyLong);
    store_key_char(mString.matrixPriv, 5, privKeyLong);
    store_key_char(mString.matrixCod, 5, codKeyLong);

    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, 2014));
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, publicKeyLong));

    printf("A Chave Privada e - %llu\n", get_private_key_char(mString.matrixPub, mString.matrixPriv, 5, 2014));
    printf("A Chave Codificada e - %llu\n", get_runlength_char(mString.matrixPriv, mString.matrixCod, 5, 16));

    printf("Chave Publica Apagada %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, 5, '8'));

     */
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

    return 0;
}