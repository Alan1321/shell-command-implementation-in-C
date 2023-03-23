#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char command[100];

    printf("Enter the Linux command to execute: ");
    fgets(command, 100, stdin);

    // Remove newline character from command
    command[strcspn(command, "\n")] = 0;

    // Tokenize the command into arguments
    char *args[20];
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    i = 0;
    for (i = 0;i<2;i++){
        printf("%s\n", args[i]);
    }


    execv("/usr/bin/ls", args);

    return 0;
}