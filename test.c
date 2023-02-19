#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <stdlib.h>
#include<string.h>

void _cat(char *file_read_name){
    int file,n;
    char data[100];
    file=open(file_read_name,O_RDONLY);
    while((n=read(file,data,100))>0){
        write(1,data,n);
    }
}

void _cp(char *file_read_name, char *file_write_name){
    int fileread, n;
    char data[100];
    fileread = open(file_read_name, O_RDONLY);
    FILE *fptr = fopen(file_write_name, "w");
    while((n=read(fileread, data, 100))>0){
        fprintf(fptr, "%s", data);
    }
}

void _rm(char *file_name){
    int value = remove(file_name);
    if(value == -1){
        printf("rm: cannot remove %s: No such file or directory\n", file_name);
    }
}

void _mkdir(char *dir_name){
    int value = mkdir(dir_name, 0777);
    if(value == -1){
        printf("mkdir: cannot create directory %s: File exists\n", dir_name);
    }
}

void _rmdir(char *dir_name){
    int value = remove(dir_name);
    if(value == -1){
        printf("rmdir: failed to remove %s: No such file or directory\n", dir_name);
    }
}

void __exit(){
    exit(0);
}

void _echo(char *input, int value){
    if(value == 1){
        //option added
        printf("%s", input);
    }else{
        //option not added
        printf("%s\n", input);
    }
}

#define MAX 20

int main(int argc, char *argv[]) {
    char token[5][7];
    char input[256];
    
    //tokenizer variables
    char *p;
    char *A[MAX];
    int i;
    char init_prompt[256] = "$ ";

    while(1){
        printf("%s", init_prompt);
        scanf("%[^\n]%*c", input);
        char input_copy[256], input_copy2[256];
        strcpy(input_copy, input);
        strcpy(input_copy2, input);

        p = strtok(input, " ");
        for(i = 0;p!=0 && i < MAX; ++i){
            A[i] = p;
            p = strtok(0, " \t");
        }
        A[i] = 0;

        char combo_string[256];

        char *PS1 = strtok(input_copy, "=");
        if(strcmp(PS1, "PS1") == 0){
            char *argument = strtok(NULL, ""); // get second token after "="
            strcpy(init_prompt, strtok(argument, "\"")); // copy the argument to init_prompt
        }else{
            if(strcmp(A[0],"echo") == 0){
                if(strcmp(A[1], "-n") == 0){
                    _echo(A[2], 1);
                }else{
                    _echo(A[1], 0);
                }
            }else if(strcmp(A[0],"cat") == 0){
                _cat(A[1]);
                //printf("The command was cat.\n");
            }else if(strcmp(A[0],"cp") == 0){
                _cp(A[1], A[2]);
                //printf("The command was cp.\n");
            }else if(strcmp(A[0],"rm") == 0){
                _rm(A[1]);
                //printf("The command was rm.\n");
            }else if(strcmp(A[0],"mkdir") == 0){
                _mkdir(A[1]);
                //printf("The command was mkdir.\n");
            }else if(strcmp(A[0],"rmdir") == 0){
                _rmdir(A[1]);
                //printf("The command was rmdir.\n");
            }else if(strcmp(A[0],"exit") == 0){
                __exit();
                //printf("The command was exit.\n");
            }else{
                printf("%s: command not found.\n", A[0]);
            }
        }

    }
}




