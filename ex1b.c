/*
 * Ex #1b-shell:
 * This program receives input from the user:
 * it receives a command (str_str, count, max) and the arguments
 * required for that command.
 * it calles the executable file for the matching command and sends
 * the arguments to it.
 *
 * if it receives exit the program exits, otherwise it prints an error
 * and waits for the next input from the user
 *
 * Written by: Rotem Kashani, Mahmood Jazmawy
 * Id: 209073352, 211345277
 * Login: rotemkash, Mahmoodja
 */

//===================== INCLUDES ===========================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//===================== CONSTS ==================================
size_t MAX_LEN = 1000;

//===================== MAIN ===================================
int main() {
    char *line = NULL,//(char *) malloc(MAX_LEN * sizeof(char)),
            *arg_1 = NULL,
            *arg_2 = NULL,
            *command= NULL;
    pid_t pid;

    while (1) {

        getline(&line, &MAX_LEN, stdin);
        command = strtok(line, " ");
//        scanf("%s", line);
        if (strcmp(command, "exit\n") == 0) {
            exit((EXIT_SUCCESS));
        }

        pid = fork();
        if (pid < 0) {
            fputs("error in fork", stderr);

        } else if (pid == 0) {

            if (strcmp(command, "str_str") == 0) {
                arg_1 = strtok(NULL, " ");
                arg_2 = strtok(NULL, " \n");

                if (execlp("./str_str", "str_str", arg_1, arg_2, NULL) != 0) {
                    perror("execlp() failed");
                    exit(EXIT_FAILURE);
                }
                exit(0);

            } else if (strcmp(command, "count") == 0) {
                arg_1 = strtok(NULL, " ");
                arg_2 = strtok(NULL, " \n");

                if (execlp("./count", "count", arg_1, arg_2, NULL) != 0) {
                    perror("execlp() failed");
                    exit(EXIT_FAILURE);
                }
                exit(0);
            } else if (strcmp(command, "max") == 0) {
                arg_1 = strtok(NULL, "\n");
                if (execlp("./max", "max", arg_1, NULL) != 0) {
                    perror("execlp() failed");
                    exit(EXIT_FAILURE);
                }
                exit(0);
            } else {
                puts("ERROR");
                exit(0);
            }
        }
        waitpid(pid, NULL, 0);
    }
}
