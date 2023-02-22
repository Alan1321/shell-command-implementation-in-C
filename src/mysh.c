/*
Alan Subedi
CS390 -- UNIX/LINUX , Spring 2023
Date -- Feb 19th, 2023
Task: Impleming basic shell command (without options) such as cat, rm, rmdir, mkdir, echo, PS1, exit, cp
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <stdlib.h>
#include<string.h>
#include <errno.h>

/*The Function below determines if a given path is a file or not*/
int is_file(char *file_path){
    struct stat sb;
    stat(file_path, &sb);
    return S_ISREG(sb.st_mode);
}

/*
Implementation of cat command
Read from a file using fopen and output data to screen
*/
void _cat(char **file_read_name, int i){    
    if(i == 1){
        printf("cp: missing file operand\n");
    }else{
        int j;
        for(j = 1;j<i;j++){
            FILE *fp;
            char buff[255];
            int fileread;
            fileread = open(file_read_name[j], O_RDONLY);
            if(fileread == -1){
                printf("cat: %s: No such file or directory\n", file_read_name[j]);
                continue;
            }
            close(fileread);
            fp = fopen(file_read_name[j], "r");
            while(!feof(fp)){
                char ch = fgetc(fp);
                printf("%c", ch);
            }
            fclose(fp);
        }
    }
}

/*
Implementation of cp command
open input file, read data, 
open outfile, write data to it
close both files
*/
void _cp(char *file_read_name, char *file_write_name, int i){
    if(i == 1){
        printf("cp: missing file operand\n");
    }else if(i == 2){
        printf("cp: missing destination file operand after '%s'\n", file_read_name);
    }else if(i == 3){
        int fileread;
        char data[256];
        fileread = open(file_read_name, O_RDONLY);
        if(fileread == -1){
            printf("cp: cannot stat '%s': No such file or directory\n", file_read_name);
        }else{
            FILE *fptr = fopen(file_write_name, "w");
            while(read(fileread, data, 255)>0){
                if(strcmp(data, "U") != 0 && strcmp(data, "V") != 0){
                    fprintf(fptr, "%s", data);
                }
            }
            fclose(fptr);
        }
        close(fileread);
    }else{
        printf("Only 2 arguments allowed.");
    }
}

/*
Implementation of rm command
check if the path is file type
if yes remove file
*/
void _rm(char **file_name, int i){
    if(i == 1){
        printf("cp: missing file operand\n");
    }else{
        int j;
        for(j = 1;j<i;j++){
            if(is_file(file_name[j]) == 1){
                if(remove(file_name[j]) == -1){
                    printf("rmdir: failed to remove %s: No such file or directory\n", file_name[j]);
                }
            }else{
                printf("rm: cannot remove '%s': Is a directory\n", file_name[j]);
            }
        }
    }
}

/*
Implementation of mkdir command
uses mkdir() system call
*/
void _mkdir(char **file_name, int i){
    if(i == 1){
        printf("cp: missing file operand\n");
    }else{        
        int j;
        for(j = 1;j<i;j++){
            if(mkdir(file_name[j], 0777) == -1){
                printf("mkdir: cannot create directory %s: %s\n", file_name[j], strerror(errno));
            }
        }
    }
}

/*
Implementation of rmdir command
check if a given path is a directory
if yes remove it using remove() call
*/
void _rmdir(char **file_name, int i){
    if(i == 1){
        printf("cp: missing file operand\n");
    }else{
        int j;
        for(j = 1;j<i;j++){
            if(rmdir(file_name[j]) == -1){
                printf("rmdir: failed to remove '%s': %s\n", file_name[j], strerror(errno));
            }
        }
    }
}

/*Implementation of exit call*/
void __exit(){
    exit(0);
}

/*
Implementation of echo command
uses printf to print data to screen
--No longer used. Found a Bug so Implemented directly on main --> last minute resort
*/
void _echo(char *input, int hasOption){
    char *value = strtok(input, "\"");
    printf("%s\n", value);
    char *value2 = strtok(NULL, "\"");
    if(hasOption == 1){
        printf("%s", value2);
    }else{
        printf("%s\n", value2);
    }
}

#define MAX 20

/*Main program when the program initially begins*/
int main(int argc, char *argv[]) {

    char token[5][7];
    char input[256];
    
    /*tokenizer variables*/
    char *p;
    char *A[MAX];
    int i;
    char init_prompt[256] = "$ ";

    while(1){
        printf("%s", init_prompt);/*print the initial PS1*/
        scanf("%[^\n]%*c", input);/*accept input commands*/
        
        /*make copies of input, will be used by echo and PS1*/
        char input_copy[256], input_copy2[256];
        strcpy(input_copy, input);
        strcpy(input_copy2, input);

        /*splitting string to view all arguments properly*/
        p = strtok(input, " ");
        for(i = 0;p!=0 && i < MAX; ++i){
            A[i] = p;
            p = strtok(0, " \t");
        }
        A[i] = 0;

        char combo_string[256];

        /*tokenize for the PS1 command*/
        char *PS1 = strtok(input_copy, "=");
        if(strcmp(PS1, "PS1") == 0){
            char *argument = strtok(NULL, ""); /*get second token after "="*/
            strcpy(init_prompt, strtok(argument, "\"")); /*copy the argument to init_prompt*/
        }else{
            /*call functions based on the input command*/
            if(strcmp(A[0],"echo") == 0){
                /*if echo has no argument then just the newline is printed, same as the original shell*/
                if(i == 1){
                    printf("\n");
                    continue;
                }
                int j;
                if(strcmp(A[1], "-n") == 0){
                    j = 2;
                }else{
                    j = 1;
                }
                for(j;j<i;j++){
                    printf("%s ", A[j]);
                }
                if(strcmp(A[1], "-n") == 0){
                }else{
                    printf("\n");
                }
            }else if(strcmp(A[0],"cat") == 0){
                _cat(A, i);
            }else if(strcmp(A[0],"cp") == 0){
                _cp(A[1], A[2], i);
            }else if(strcmp(A[0],"rm") == 0){
                _rm(A, i);
            }else if(strcmp(A[0],"mkdir") == 0){
                _mkdir(A, i);
            }else if(strcmp(A[0],"rmdir") == 0){
                _rmdir(A, i);
            }else if(strcmp(A[0],"exit") == 0){
                __exit();
            }else{
                printf("%s: command not found.\n", A[0]);
            }
        }
    }
}