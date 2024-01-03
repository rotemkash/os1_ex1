/*
 * Ex #1b-max: Find Max string
 * This program receives two strings and count how much of the first string's letters
 * appears in the second string.
 *
 * Written by: Rotem Kashani, Mahmood Jazmawy
 * Id: 209073352, 211345277
 * Login: rotemkash, Mahmoodja
 */

//===================== INCLUDES ===========================
#include <stdio.h>
#include <stdlib.h>

//===================== MAIN ===================================
int main(int argc, char* argv[]) {
    if(argc != 3){
        fprintf(stderr, "Wrong number of arguments entered\n");
        return EXIT_FAILURE;
    }

    char *word1 = argv[1];
    char *word2 = argv[2];
    int counter = 0;

    for (char *c1 = word1; *c1 != '\0' ; ++c1) {
        for (char *c2 = word2; *c2 != '\0' ; ++c2) {
            if (*c1 == *c2) {
                counter++;
            }
        }
    }

    printf("%d\n", counter);
    return EXIT_SUCCESS;
}
