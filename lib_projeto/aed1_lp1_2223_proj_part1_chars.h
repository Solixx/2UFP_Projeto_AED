//
// AED1 & LP1 2022-2023 (PART 1)
//

#ifndef AED1_LP1_2223_PROJ_TESTS_AED1_LP1_2223_PROJ_PART1_CH_H
#define AED1_LP1_2223_PROJ_TESTS_AED1_LP1_2223_PROJ_PART1_CH_H

/**
 * Create an array of digits in ascii i.e. chars for a given key.
* @param key - long key
 * @return address of array of digits in ascii for a given key
 */
char* key_long_2_digits_char(unsigned long long key);

/**
 * Receives an array of digits in ascii i.e. chars and returns the long key.
 * @param keydigits - array of digits of key
 * @return address of array of digits for a given key
 */
unsigned long long key_digits_2_long_char(char* keydigits);

/**
 * Calculate the bipolar private key from a given public key (returns the bipolar private key).
 * @param pubkey - public key for which to calculate the private key
 * @return bipolar number representing the private key
 */
unsigned long long calc_private_key_char(unsigned long long pubkey);

/**
 * Calculate the run-length from a given private key.
 * @param privkey - private key for which to calculate the run-length
 * @return run-length number representing the private key
 */
unsigned long long calc_runlength_char(unsigned long long privkey);

/**
 * Calculate the private key from a run-length.
 * @param runlengthkey - run-length for which to calculate the private key
 * @return private key that corresponds to the runlengthkey arg
 */
unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey);

/**
 * Memory allocation for a char matrix with nlines and ncolumns
 * @param nlines - number of lines
 * @param ncolumns - number of columns
 * @return pointer to the allocated memory of the matrix
 */
char** alloc_matrix_char(int nlines, int ncolumns);

/**
 * Store a key (pub, priv or run-length) into the first available position of given matrix.
 * @param matrix - matrix to store the key
 * @param lines - matrix number of lines
 * @param key - key to be stored
 */
void store_key_char(char **matrix, int lines, unsigned long long key);

/**
 * Verify if a given key exists in the matrix.
 * @param matrix - matrix with keys
 * @param lines - matrix number of lines
 * @param key - key to check if it exists
 * @return 1 if it exists, 0 if it doesn't
 */
int exists_key_char(char **matrix, int lines, unsigned long long key);

/**
 * Returns the private key corresponding to the given public key
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key of the given pubkey
 */
unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey);

/**
 * Returns the run-length key of a given private key
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key runlength of the given pubkey
 */
unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey);

/**
 * Delete a given public key (and corresponding priv and runlength keys) from all matrices.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key to delete
 * @return pubkey that was deleted
 */
unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char* pubkey);

/**
 * Automatically generate and save a given amount (<lines>) of public keys.
 * @param matrix_kpub - public keys matrix
 * @param lines - matrix number of lines
 */
void bulk_populate_public_keys_char(char **matrix_kpub, int lines);

/**
 * Automatically calculate, generate and store all private keys for the existing public keys.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines);

/**
 * Automatically calculate and store all run-lengths for the existing private keys.
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines);

/**
 * Return a list of all private keys matching a given partial public key.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param partialpubkey - part of public key to filter the private keys
 * @return array of private keys matching the partialpubkey
 */
char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey);

/**
 * Sort a matrix keys in ascending or descending order
 * @param matrix - matrix to be sorted
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_matrix_char(char **matrix, int lines, int order);

/**
 * Sort all matrices keys in ascending or descending order
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Print all keys on the console, sorted by pubkeys sizes (i.e. number of digits).
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 0 ? current order : order == 1 ? ascending : descending
 */
void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Save all matrix data to a text file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file where to store the data
 */
void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a text file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file to load data from
 */
void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Save all matrix data to a binary file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the binary file where to store the data
 */
void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a binary file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename -name of the binary file to load data from
 */
void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

#endif //AED1_LP1_2223_PROJ_TESTS_AED1_LP1_2223_PROJ_PART1_CH_H
