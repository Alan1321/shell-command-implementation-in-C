#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void do_exec(char *progpath, char **paths){
    int status;
    if(fork() == 0){
        execv(progpath, paths);
    }else{
        int child_status;
        waitpid(-1, &child_status, 0);
        if(child_status != 0){
            // strcpy(errmsg, strerror(child_status));
            // status = -1;
        }
    }
}

int find_program(char *progpath, char *progname, char **paths, char **A){
    int found = 0;
    if(found == 0 && progname[0] == '/'){
        /*go through path*/
    }
    /*this one is probably for local path, will do later*/
    // if(found == 0 && strstr(progname, "/")){

    // }

    /*this condition assumes only command was given, so search path first then execute*/
    if(found == 0){
        int i;
        for(i = 0;paths[i] != 0 && found == 0;i++){
            /*appending command to every single PATH here*/
            char path[256];
            strcpy(path, paths[i]);
            strcat(path, "/");
            strcat(path, progname);

            /*test the appended PATH now*/
            if(access(path, X_OK) == 0){
                printf("PATH: %s\n", path);
                do_exec(path, A);
                found = 1;
            }
        }
    }
    return 0;
}


#define MAX 50

int main(int argc, char *argv[]) {

    /*all PATH tokens will be stored in this variable later*/
    char *PATH[MAX];
    int i;
    char *p;
    /*getting all the PATH here*/
    char *args = getenv("PATH");

    /*tokenize PATH here*/
    p = strtok(args, ":");
    for(i = 0;p!=0 && i < MAX; ++i){
        PATH[i] = p;
        p = strtok(0, ":");
    }
    PATH[i] = 0;

    // for(i = 0;i<MAX;i++){
    //     if(PATH[i] == 0){
    //         break;
    //     }else{
    //         printf("%s\n", PATH[i]);
    //     }
    // }

    char token[5][7];
    char input[256];

    /*tokenizer variables*/
    char *A[MAX];
    char init_prompt[256] = "$ ";

    //accept input and tokenize it
    while(1){
        printf("%s", init_prompt);/*print the initial PS1*/
        scanf("%[^\n]%*c", input);/*accept input commands*/

        /*make copy of input*/
        char input_copy[256];
        strcpy(input_copy, input);

        /*tokenize the input*/
        p = strtok(input, " ");
        for(i = 0;p!=0 && i < MAX; ++i){
            A[i] = p;
            p = strtok(0, " \t");
        }
        A[i] = 0;

        find_program("lol", A[0], PATH, A);
    }
}