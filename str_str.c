/*
 * Ex #1b-str_str: Find substring in a string
 * This program receives two strings and it checks if the first string
 * appears in the second string then it returns the index where it starts.
 *
 * Written by: Rotem Kashani, Mahmood Jazmawy
 * Id: 209073352, 211345277
 * Login: rotemkash, Mahmoodja
 */

//===================== INCLUDES ===========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===================== MAIN ===================================
int main(int argc, char* argv[]) {
    if(argc != 3){
        fprintf(stderr, "Wrong number of arguments!!");
        return EXIT_FAILURE;
    }

    char *word1 = argv[1];
    char *word2 = argv[2];
    int pos;

    char *p = strstr(word2, word1);

    if(p == NULL){
        pos = -1;
    } else {
        pos = (int)(p - word2);
    }
    printf("%d\n", pos);

    return EXIT_SUCCESS;
}
