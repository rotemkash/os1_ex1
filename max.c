/*
 * Ex #1b-max: Find substring in a string
 * This program receives multiple strings and it prints
 * the biggest string in them all
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
    if(argc != 2){
        fprintf(stderr, "Wrong number of arguments!!");
        return EXIT_FAILURE;
    }

    char *string= argv[1];
    char *curr_max, *c_2;

    // Extract the first token
    curr_max = strtok(string, " ");
    c_2 = curr_max;
    // loop through the string to extract all other tokens
    while(c_2 != NULL ) {
        if(strlen(curr_max) <  strlen(c_2)){
            curr_max = c_2;
        }
        c_2 = strtok(NULL, " ");
    }

    if (curr_max == NULL) {
        printf("error\n");
    } else{
        printf("%s\n", curr_max);
    }

    return EXIT_SUCCESS;
}
