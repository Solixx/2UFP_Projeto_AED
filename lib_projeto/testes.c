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

    clock_t start, end;
    double execution_time;
    start = clock();

    mString = clienteString(mString);
    mInts = clienteInt(mInts);

    /*
    for (int i = 0; i < 6; ++i) {
        printf("Pub String - %s\n", mString.matrixPub[i]);
        int j = 0;
        while (mInts.matrixPub[i][j] != -1){
            printf("Pub Ints - %hi\n", mInts.matrixPub[i][j]);
            j++;
        }
        printf("\n");
    }
    */

    clienteKeyHolder(portaChaves, mString, mInts);

    freeMatrixChar(mString.matrixPub, mString.lines);
    freeMatrixChar(mString.matrixPriv, mString.lines);
    freeMatrixChar(mString.matrixCod, mString.lines);
    freeMatrixShort(mInts.matrixPub, mInts.lines);
    freeMatrixShort(mInts.matrixPriv, mInts.lines);
    freeMatrixShort(mInts.matrixCod, mInts.lines);
    free(mString.matrixPub);
    free(mString.matrixPriv);
    free(mString.matrixCod);
    free(mInts.matrixPub);
    free(mInts.matrixPriv);
    free(mInts.matrixCod);

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Numero de Matrix Strings %d\n", mString.lines);
    printf("Numero de Matrix Ints %d\n", mString.lines);
    printf("Porta Chaves\n");
    printf("Time = %f\n", execution_time);

    return 0;
}

struct matrixString clienteString(struct matrixString mString){
    char filename[] = "../data/chaves_publicas.txt";
    char *publicKeyChar, *privKeyChar, *codKeyChar;
    char **privKeySearch = NULL;
    unsigned long long key = 2014, publicKeyLong = 0, privKeyLong = 0, codKeyLong = 0;
    int lines = 5000, columns = 1;

    mString.lines = lines;

    privKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    codKeyChar = (char *) malloc(numDigitsLong(key) * sizeof (char));
    publicKeyChar = key_long_2_digits_char(230);
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

    */
    /*
    for (int i = 0; i < lines; ++i) {
        if(strcmp(mString.matrixPub[i], "\0") != 0) printf("Pub - %s\n", mString.matrixPub[i]);
        if(strcmp(mString.matrixPriv[i], "\0") != 0) printf("Priv - %s\n", mString.matrixPriv[i]);
        if(strcmp(mString.matrixCod[i], "\0") != 0) printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");
    */

    //printf("Delete a - %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, mString.matrixPub[0]));


    //printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, 2014));
    //printf("Exist - %d\n", exists_key_char(mString.matrixPub, 5, publicKeyLong));



    //printf("A Chave Privada e - %llu\n", get_private_key_char(mString.matrixPub, mString.matrixPriv, 5, 2014));
    //printf("A Chave Codificada e - %llu\n", get_runlength_char(mString.matrixPriv, mString.matrixCod, 5, 16));


    //printf("Chave Publica Apagada %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, "2014"));

    //privKeySearch = search_private_keys_char(mString.matrixPub, mString.matrixPriv, lines, 4);
    //printf("As priv encontradas foram %s\n", privKeySearch[0]);

    /*
    int j = 0;
    while (strcmp(privKeySearch[j], "\0") != 0){
        printf("Priv Encontrada - %s\n", privKeySearch[j]);
        j++;
    }
     */

    /*
    for (int i = 0; i < lines; ++i) {
        if(mString.matrixPub[i] && mString.matrixPub[i][0] != '\0') printf("Pub - %s\n", mString.matrixPub[i]);
        if(mString.matrixPriv[i] && mString.matrixPub[i][0] != '\0') printf("Priv - %s\n", mString.matrixPriv[i]);
        if(mString.matrixCod[i] && mString.matrixPub[i][0] != '\0') printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");
     */


    bulk_populate_public_keys_char(mString.matrixPub, lines);

    /*
    for (int i = 0; i < lines; ++i) {
        printf("mString PubMatrix de %d - %s\n", i, mString.matrixPub[i]);
    }

    bulk_compute_private_keys_char(mString.matrixPub, mString.matrixPriv, lines);

    for (int i = 0; i < lines; ++i) {
        printf("mString PrivMatrix de %d - %s\n", i, mString.matrixPriv[i]);
    }

    bulk_compute_runlengths_char(mString.matrixPriv, mString.matrixCod, lines);

    for (int i = 0; i < lines; ++i) {
        printf("mString CodMatrix de %d - %s\n", i, mString.matrixCod[i]);
    }
    */

    //sort_matrix_char(mString.matrixPub, lines, 1);
    //sort_all_matrices_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);
    //list_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);

    //save_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    //load_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    /*
    for (int i = 0; i < lines; ++i) {
        if(mString.matrixPub[i]) printf("Pub - %s\n", mString.matrixPub[i]);
        if(mString.matrixPriv[i]) printf("Priv - %s\n", mString.matrixPriv[i]);
        if(mString.matrixCod[i]) printf("Cod - %s\n", mString.matrixCod[i]);
    }
    */

    /*
    privKeySearch = search_private_keys_char(mString.matrixPub, mString.matrixPriv, lines, 1);
    int p = 0;
    while (mString.matrixPub[p] && mString.matrixPub[p][0] != '\0'){
        printf("Privs Encontradas - %s\n", privKeySearch[p]);
        p++;
    }
    */

    return mString;
}

struct matrixInts clienteInt(struct matrixInts mInts){

    char filename[] = "../data/chaves_publicas_ints.txt";
    unsigned long long pubKey = 0, privKey = 0, codKey = 0;
    short *allD = NULL, **privKeySearch = NULL;
    int lines = 5000, columns = 1;

    mInts.lines = lines;

    pubKey = new_public_key_int();
    pubKey = 230;
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

    /*
    pubKey = new_public_key_int();
    pubKey = 2;
    allD = key_long_2_digits_int(pubKey);
    pubKey = key_digits_2_long_int(allD);
    privKey = calc_private_key_int(pubKey);
    codKey = calc_runlength_int(privKey);

    store_key_int(mInts.matrixPub, lines, pubKey);
    store_key_int(mInts.matrixPriv, lines, privKey);
    store_key_int(mInts.matrixCod, lines, codKey);
     */

    /*
    for (int i = 0; i < 1; ++i) {
        if((!mInts.matrixPub[i][0] && mInts.matrixPub[i][1]) || mInts.matrixPub[i][0]){
            int j = 0;
            printf("Pub - ");
            while (mInts.matrixPub[i][j] != -1){
                printf("%hi", mInts.matrixPub[i][j]);
                j++;
            }
            printf("\n");
        }
        if((!mInts.matrixPriv[i][0] && mInts.matrixPriv[i][1]) || mInts.matrixPriv[i][0]){
            int j = 0;
            printf("Priv - ");
            while (mInts.matrixPriv[i][j] != -1){
                printf("%hi", mInts.matrixPriv[i][j]);
                j++;
            }
            printf("\n");
        }
        if((!mInts.matrixCod[i][0] && mInts.matrixCod[i][1]) || mInts.matrixCod[i][0]){
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
    */

    //printf("Exists - %d\n", exists_key_int(mInts.matrixPub, lines, pubKey));
    //printf("PrivKey da PubKey - %llu\n", get_private_key_int(mInts.matrixPub, mInts.matrixPriv, lines, pubKey));
    //printf("CodKey da PrivKey - %llu\n", get_runlength_int(mInts.matrixPriv, mInts.matrixCod, lines, privKey));

    //printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, pubKey));
    //printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 2));
    bulk_populate_public_keys_int(mInts.matrixPub, lines);
    bulk_compute_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines);
    bulk_compute_runlengths_int(mInts.matrixPriv, mInts.matrixCod, lines);

    /*
    for (int i = 0; i < lines; ++i) {
        if(mInts.matrixPub[i]){
            int j = 0;
            printf("Pub - ");
            while (mInts.matrixPub[i][j] != -1){
                printf("%hi", mInts.matrixPub[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixPriv[i]){
            int j = 0;
            printf("Priv - ");
            while (mInts.matrixPriv[i][j] != -1){
                printf("%hi", mInts.matrixPriv[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixCod[i]){
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
    */

    /*
    privKeySearch = search_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines, 2);

    int p = 0;
    while (privKeySearch[p][0]){
        if(privKeySearch[p][0] == 0) break;
        printf("Priv Encontrada - %llu", key_digits_2_long_int(privKeySearch[p]));
        printf("\n");
        p++;
    }
     */

    //load_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);

    //sort_matrix_int(mInts.matrixPub, lines, 1);
    //sort_all_matrices_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);
    //list_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);

    /*
    for (int i = 0; i < lines; ++i) {
        if(mInts.matrixPub[i]){
            int j = 0;
            printf("Pub - ");
            while (mInts.matrixPub[i][j] != -1){
                printf("%hi", mInts.matrixPub[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixPriv[i]){
            int j = 0;
            printf("Priv - ");
            while (mInts.matrixPriv[i][j] != -1){
                printf("%hi", mInts.matrixPriv[i][j]);
                j++;
            }
            printf("\n");
        }
        if(mInts.matrixCod[i]){
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
    */

    //save_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);

    return mInts;
}

void clienteKeyHolder(KEY_HOLDER *portaChaves, struct matrixString mString, struct matrixInts mInts){

    char filename[] = "../data/portaChaves.txt";
    int stopPos = 1, keyHolderPos = 1;
    insert_keyHolder(&portaChaves, mString, mInts, 0); //201
    insert_keyHolder(&portaChaves, mString, mInts, 1); //2014
    print_keyHolders(&portaChaves);

    searchSingleKey_inKeyHolder(portaChaves, 1, "2014", 1);


    edit_keyHolder(&portaChaves, mString, mInts, 2, 1, 3);
    edit_keyHolder(&portaChaves, mString, mInts, 1, 0, 2);
    edit_keyHolder(&portaChaves, mString, mInts, 2, 10, 4);
    edit_keyHolder(&portaChaves, mString, mInts, 2, 10, 6);

    print_keyHolders(&portaChaves);

    save_txt_keyHolder(&portaChaves, mString, mInts, 1, filename);
    save_txt_keyHolder(&portaChaves, mString, mInts, 2, filename);

    //remove_keyHolder(&portaChaves, 2);

    //print_keyHolders(&portaChaves);

    printf("Do ficheiro de texto\n");
    insert_keyHolder(&portaChaves, mString, mInts, 0);
    load_txt_keyHolder(&portaChaves, mString, mInts, 3, 0, filename);
    print_keyHolders(&portaChaves);
}