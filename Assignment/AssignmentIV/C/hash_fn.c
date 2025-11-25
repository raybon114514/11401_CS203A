#include "hash_fn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Hash function for Integer Keys
 * Algorithm: Division Method (key % m)
 */
int myHashInt(int key, int m) {
    if (m <= 0) return 0;
    
    // Ensure the key is non-negative before modulo
    int index = key % m;
    if (index < 0) {
        index += m;
    }
    return index;
}

/*
 * Hash function for String Keys
 * Algorithm: Polynomial Rolling Hash with P = 31
 */
int myHashString(const char* str, int m) {
    if (m <= 0 || str == NULL) return 0;

    unsigned long hash = 0;
    int p = 31; // Prime base

    for (int i = 0; str[i] != '\0'; i++) {
        hash = (hash * p + str[i]) % m;
    }

    return (int)hash;
}