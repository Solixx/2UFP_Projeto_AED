//
// Created by pc on 12/11/2022.
//

#include "projeto.h"
#include "testes.h"
#include "aed1_lp1_2223_proj_part1_chars.h"
#include "aed1_lp1_2223_proj_part1_ints.h"

struct matrixString clienteString(struct matrixString mString);
struct matrixInts clienteInt(struct matrixInts mInts);
KEY_HOLDER* clienteKeyHolder(KEY_HOLDER *portaChaves, struct matrixString mString, struct matrixInts mInts);
void clienteUtilizadores(UTILIZADORES *utilizador, UTILIZADORES_QUEUE queue, KEY_HOLDER *portaChaves);

int main_test(){

    struct matrixString mString;
    struct matrixInts mInts;
    KEY_HOLDER *portaChaves = NULL;
    UTILIZADORES *utilizador = NULL;
    UTILIZADORES_QUEUE queue;
    queue.head = NULL;
    queue.tail = NULL;
    queue.size = 0;

    time_t t1;
    srand((unsigned ) time(&t1));

    clock_t start, end;
    double execution_time;
    start = clock();

    mString = clienteString(mString);
    mInts = clienteInt(mInts);

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Numero de Matrix Strings %d\n", mString.lines);
    printf("Numero de Matrix Ints %d\n", mInts.lines);
    printf("Time = %f\n", execution_time);


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

    portaChaves = clienteKeyHolder(portaChaves, mString, mInts);

    clienteUtilizadores(utilizador, queue, portaChaves);

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
    printf("Utilizadores\n");
    printf("Time = %f\n", execution_time);


    return 0;
}

struct matrixString clienteString(struct matrixString mString){
    char filename[] = "../data/chaves_publicas.txt";
    char filenameBn[] = "../data/chaves_String_Bn.txt";
    char *publicKeyChar, *privKeyChar, *codKeyChar;
    char **privKeySearch = NULL;
    unsigned long long key = 2014, publicKeyLong = 0, privKeyLong = 0, codKeyLong = 0;
    int lines = 15, columns = 1;

    mString.lines = 0;

    printf("Matriz Strings\n");

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


    /*
    for (int i = 0; i < lines; ++i) {
        if(strcmp(mString.matrixPub[i], "\0") != 0) printf("Pub - %s\n", mString.matrixPub[i]);
        if(strcmp(mString.matrixPriv[i], "\0") != 0) printf("Priv - %s\n", mString.matrixPriv[i]);
        if(strcmp(mString.matrixCod[i], "\0") != 0) printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");
    */

    printf("Chave Publica Apagada %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, "230"));


    privKeySearch = search_private_keys_char(mString.matrixPub, mString.matrixPriv, lines, 4);
    int k = 0;
    while (strcmp(privKeySearch[k], "-1") != 0){
        printf("As priv encontradas foram %s\n", privKeySearch[k]);
        k++;
    }


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
    */

    bulk_compute_private_keys_char(mString.matrixPub, mString.matrixPriv, lines);

    /*
    for (int i = 0; i < lines; ++i) {
        printf("mString PrivMatrix de %d - %s\n", i, mString.matrixPriv[i]);
    }
    */

    bulk_compute_runlengths_char(mString.matrixPriv, mString.matrixCod, lines);

    /*
    for (int i = 0; i < lines; ++i) {
        printf("mString CodMatrix de %d - %s\n", i, mString.matrixCod[i]);
    }
    */

    for (int i = 0; i < lines; ++i) {
        printf("Pub - %s\n", mString.matrixPub[i]);
        printf("Priv - %s\n", mString.matrixPriv[i]);
        printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");

    printf("A Chave Privada e - %llu\n", get_private_key_char(mString.matrixPub, mString.matrixPriv, lines, atoll(mString.matrixPub[3])));
    printf("A Chave Codificada e - %llu\n", get_runlength_char(mString.matrixPriv, mString.matrixCod, lines, atoll(mString.matrixPriv[3])));

    printf("Exist - %d\n", exists_key_char(mString.matrixPub, lines, 0));
    printf("Exist - %d\n", exists_key_char(mString.matrixPub, lines, atoll(mString.matrixPub[3])));

    //sort_matrix_char(mString.matrixPub, lines, 1);
    sort_all_matrices_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);
    list_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, 1);

    save_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    //load_txt_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filename);

    save_bin_keys_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, filenameBn);


    for (int i = 0; i < lines; ++i) {
        printf("Pub - %s\n", mString.matrixPub[i]);
        printf("Priv - %s\n", mString.matrixPriv[i]);
        printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");



    privKeyLong = private_key_from_runlength_char(atoll(mString.matrixCod[1]));

    printf("Priv: %llu (RunLength: %llu)\n", privKeyLong, atoll(mString.matrixCod[1]));



    privKeySearch = search_private_keys_char(mString.matrixPub, mString.matrixPriv, lines, 0);
    int p = 0;
    while (strcmp(privKeySearch[p], "-1") != 0){
        printf("Privs Encontradas - %s\n", privKeySearch[p]);
        p++;
    }



    printf("Delete a - %llu\n", delete_key_char(mString.matrixPub, mString.matrixPriv, mString.matrixCod, lines, "2014"));


    for (int i = 0; i < lines; ++i) {
        printf("Pub - %s\n", mString.matrixPub[i]);
        printf("Priv - %s\n", mString.matrixPriv[i]);
        printf("Cod - %s\n", mString.matrixCod[i]);
    }
    printf("\n");


    int y = 0;
    while (strcmp(mString.matrixPub[y], "-1") != 0){
        mString.lines++;
        y++;
    }

    return mString;
}

struct matrixInts clienteInt(struct matrixInts mInts){

    char filename[] = "../data/chaves_publicas_ints.txt";
    char filenameBn[] =  "../data/chaves_Ints_Bn.txt";
    unsigned long long pubKey = 0, privKey = 0, codKey = 0;
    short *allD = NULL, **privKeySearch = NULL;
    int lines = 12, columns = 1;

    mInts.lines = 0;

    printf("Matriz Ints\n");

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


    pubKey = new_public_key_int();
    pubKey = 2;
    allD = key_long_2_digits_int(pubKey);
    pubKey = key_digits_2_long_int(allD);
    privKey = calc_private_key_int(pubKey);
    codKey = calc_runlength_int(privKey);

    store_key_int(mInts.matrixPub, lines, pubKey);
    store_key_int(mInts.matrixPriv, lines, privKey);
    store_key_int(mInts.matrixCod, lines, codKey);


    printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 2));
    //printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines-1, 230));

    bulk_populate_public_keys_int(mInts.matrixPub, lines);
    bulk_compute_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines);
    bulk_compute_runlengths_int(mInts.matrixPriv, mInts.matrixCod, lines);

    /*
    for (int i = 0; i < lines+1; ++i) {
        if(mInts.matrixPub[i][0] == -1) break;
        if(mInts.matrixPub[i][0] == 0 && mInts.matrixPub[i][1] != -1) printf("Pub - 0\n");
        else printf("Pub - %llu\n", key_digits_2_long_int(mInts.matrixPub[i]));
        if(mInts.matrixPriv[i][0] == 0 && mInts.matrixPriv[i][1] != -1) printf("Priv - 0\n");
        else printf("Priv - %llu\n", key_digits_2_long_int(mInts.matrixPriv[i]));
        if(mInts.matrixCod[i][0] == 0 && mInts.matrixCod[i][1] != -1) printf("Cod - 0\n");
        else printf("Cod - %llu\n", key_digits_2_long_int(mInts.matrixCod[i]));
    }
    printf("\n");
    */

    printf("Exists - %d\n", exists_key_int(mInts.matrixPub, lines, 200));
    printf("PrivKey da PubKey - %llu\n", get_private_key_int(mInts.matrixPub, mInts.matrixPriv, lines, key_digits_2_long_int(mInts.matrixPub[2])));
    printf("CodKey da PrivKey - %llu\n", get_runlength_int(mInts.matrixPriv, mInts.matrixCod, lines, 2));


    privKeySearch = search_private_keys_int(mInts.matrixPub, mInts.matrixPriv, lines, 2);

    int p = 0;
    while (privKeySearch[p][0] != -1){
        printf("Priv Encontrada - %llu", key_digits_2_long_int(privKeySearch[p]));
        printf("\n");
        p++;
    }


    //load_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);

    //sort_matrix_int(mInts.matrixPub, lines, 1);
    //sort_all_matrices_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);
    //list_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, 1);


    for (int i = 0; i < lines+1; ++i) {
        if(mInts.matrixPub[i][0] == -1) break;
        if(mInts.matrixPub[i][0] == 0 && mInts.matrixPub[i][1] != -1) printf("Pub - 0\n");
        else printf("Pub - %llu\n", key_digits_2_long_int(mInts.matrixPub[i]));
        if(mInts.matrixPriv[i][0] == 0 && mInts.matrixPriv[i][1] != -1) printf("Priv - 0\n");
        else printf("Priv - %llu\n", key_digits_2_long_int(mInts.matrixPriv[i]));
        if(mInts.matrixCod[i][0] == 0 && mInts.matrixCod[i][1] != -1) printf("Cod - 0\n");
        else printf("Cod - %llu\n", key_digits_2_long_int(mInts.matrixCod[i]));
    }
    printf("\n");



    privKey = private_key_from_runlength_int(key_digits_2_long_int(mInts.matrixCod[2]));

    printf("Priv: %llu (RunLength: %llu)\n", privKey, key_digits_2_long_int(mInts.matrixCod[2]));

    printf("PubKey Apagada - %llu\n", delete_key_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, key_digits_2_long_int(mInts.matrixPub[1])));

    /*
    for (int i = 0; i < lines+1; ++i) {
        if(mInts.matrixPub[i][0] == -1) break;
        if(mInts.matrixPub[i][0] == 0 && mInts.matrixPub[i][1] != -1) printf("Pub - 0\n");
        else printf("Pub - %llu\n", key_digits_2_long_int(mInts.matrixPub[i]));
        if(mInts.matrixPriv[i][0] == 0 && mInts.matrixPriv[i][1] != -1) printf("Priv - 0\n");
        else printf("Priv - %llu\n", key_digits_2_long_int(mInts.matrixPriv[i]));
        if(mInts.matrixCod[i][0] == 0 && mInts.matrixCod[i][1] != -1) printf("Cod - 0\n");
        else printf("Cod - %llu\n", key_digits_2_long_int(mInts.matrixCod[i]));
    }
    printf("\n");
    */

    save_txt_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filename);

    save_bin_keys_int(mInts.matrixPub, mInts.matrixPriv, mInts.matrixCod, lines, filenameBn);

    int y = 0;
    while (mInts.matrixPub[y][0] != -1){
        mInts.lines++;
        y++;
    }

    return mInts;
}

KEY_HOLDER* clienteKeyHolder(KEY_HOLDER *portaChaves, struct matrixString mString, struct matrixInts mInts){

    printf("Porta Chaves\n");

    char filename[] = "../data/portaChaves.txt";
    char filenameSearch[] = "../data/portaChavesPesquisa.txt";
    int stopPos = 1, keyHolderPos = 1;
    insert_keyHolder(&portaChaves, mString, mInts, 0);
    insert_keyHolder(&portaChaves, mString, mInts, 1);
    insert_keyHolder(&portaChaves, mString, mInts, 2);
    print_keyHolders(&portaChaves);

    searchSingleKey_inKeyHolder(portaChaves, 2, 230, 1, filenameSearch);

    edit_keyHolder(&portaChaves, mString, mInts, 2, 10, 3);
    edit_keyHolder(&portaChaves, mString, mInts, 1, 0, 2);
    edit_keyHolder(&portaChaves, mString, mInts, 2, 10, 4);
    edit_keyHolder(&portaChaves, mString, mInts, 2, 10, 6);
    //print_keyHolders(&portaChaves);

    save_txt_keyHolder(&portaChaves, mString, mInts, 2, filename);

    remove_keyHolder(&portaChaves, 1);

    print_keyHolders(&portaChaves);

    /*
    printf("Do ficheiro de texto\n");
    insert_keyHolder(&portaChaves, mString, mInts, 0);
    load_txt_keyHolder(&portaChaves, mString, mInts, 3, 0, filename);
    print_keyHolders(&portaChaves);
    */

    return portaChaves;
}

void clienteUtilizadores(UTILIZADORES *utilizador, UTILIZADORES_QUEUE queue, KEY_HOLDER *portaChaves){

    printf("UTILIZADORES\n");

    /*
    create_utilizador_ordenado(&queue, &utilizador, "Manuel", "m@gmail.com", portaChaves, 0);
    create_utilizador_ordenado(&queue, &utilizador, "Z", "m@gmail.com", portaChaves, 2);
    create_utilizador_ordenado(&queue, &utilizador, "Ricardo", "m@gmail.com", portaChaves, 1);
    create_utilizador_ordenado(&queue, &utilizador, "Mario", "m@gmail.com", portaChaves, 2);
    create_utilizador_ordenado(&queue, &utilizador, "A", "m@gmail.com", portaChaves, 1);
     */

    /*
    create_utilizador_cauda(&queue, &utilizador, "Manuel", "m@gmail.com", portaChaves, 0);
    create_utilizador_cauda(&queue, &utilizador, "Jose", "m@gmail.com", portaChaves, 0);
    create_utilizador_ordenado(&queue, &utilizador, "A", "m@gmail.com", portaChaves, 1);
     */

    create_utilizador_cabeca(&queue, &utilizador, "Manuel", "m@gmail.com", portaChaves, 0);
    create_utilizador_cabeca(&queue, &utilizador, "Josa", "m@gmail.com", portaChaves, 0);
    create_utilizador_cabeca(&queue, &utilizador, "Z", "m@gmail.com", portaChaves, 0);
    create_utilizador_ordenado(&queue, &utilizador, "A", "m@gmail.com", portaChaves, 1);
    create_utilizador_cauda(&queue, &utilizador, "Cauda", "m@gmail.com", portaChaves, 0);
    create_utilizador_cabeca(&queue, &utilizador, "Jose", "m@gmail.com", portaChaves, 0);

    print_utilizadores(&queue);

    remover_nome_utilizador(&queue, "Manuel");
    //remover_cabeca_utilizador(&queue);
    //remover_cauda_utilizador(&queue);

    //print_utilizadores(&queue);

    //printf("Ordenado\n");
    ordenar_utilizadores(&queue);

    print_utilizadores(&queue);

    search_utilizador_by_name(&queue, "Manuel");
    //search_utilizador_by_name(&queue, "Ricardo");

    //print_utilizadores(&queue);

    dequeue(&queue);
}