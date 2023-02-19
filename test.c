#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <stdlib.h>
#include<string.h>

int is_file(const char *file_path){
    struct stat sstat;
    stat(file_path, &sstat);
    return S_ISREG(sstat.st_mode);
}

void _cat(char **file_read_name, int i){    
    int j;
    for(j = 1;j<i;j++){
       FILE *fp;
       char buff[255];
       fp = fopen(file_read_name[j], "r");

        while(!feof(fp)){
            char ch = fgetc(fp);
            printf("%c", ch);
        }
        fclose(fp);
    }
}

void _cp(char *file_read_name, char *file_write_name, int i){
    if(i == 1){
        printf("cp: missing file operand\n");
    }else if(i == 2){
        printf("cp: missing destination file operand after '%s'\n", file_read_name);
    }else if(i == 3){
        int fileread, n;
        char data[256];
        fileread = open(file_read_name, O_RDONLY);
        FILE *fptr = fopen(file_write_name, "w");
        while((n=read(fileread, data, 100))>0){
            if(strcmp(data, "U") != 0 && strcmp(data, "V") != 0){
                fprintf(fptr, "%s", data);
            }
        }
        fclose(fptr);
    }else{
        printf("Only 2 arguments allowed.");
    }
}

void _rm(char **file_name, int i){
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

void _mkdir(char **file_name, int i){
    int j;
    for(j = 1;j<i;j++){
        if(mkdir(file_name[j], 0777) == -1){
            printf("mkdir: cannot create directory %s: File exists\n", file_name[j]);
        }
    }
}

void _rmdir(char **file_name, int i){
    int j;
    for(j = 1;j<i;j++){
        if(is_file(file_name[j]) == 0){
            if(remove(file_name[j]) == -1){
                printf("rmdir: failed to remove %s: No such file or directory\n", file_name[j]);
            }
        }else{
            printf("rm: cannot remove '%s': Is a file\n", file_name[j]);
        }
    }
}

void __exit(){
    exit(0);
}

void _echo(char *input, int hasOption){
    char *value = strtok(input, "\"");
    char *value2 = strtok(NULL, "\"");
    if(hasOption == 1){
        printf("%s", value2);
    }else{
        printf("%s\n", value2);
    }
}

#define MAX 20

int main(int argc, char *argv[]) {

    char token[5][7];
    char input[256];
    
    /*tokenizer variables*/
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
            char *argument = strtok(NULL, ""); /*get second token after "="*/
            strcpy(init_prompt, strtok(argument, "\"")); /*copy the argument to init_prompt*/
        }else{
            if(strcmp(A[0],"echo") == 0){
                if(strcmp(A[1], "-n") == 0){
                    _echo(input_copy2, 1);
                }else{
                    _echo(input_copy2, 0);
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