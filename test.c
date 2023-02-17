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

void __input(char *argv){
    printf("%c\n", argv[0]);
}

#define MAX 20

int main(int argc, char *argv[]) {
    // char string[50] = "Hello! We are learning about strtok";
    // // Extract the first token
    // char * token = strtok(string, " ");
    // // loop through the string to extract all other tokens
    // while( token != NULL ) {
    //     printf( "%s\n", token ); //printing each token
    //     token = strtok(NULL, " ");
    // }
    // return 0;

    __input("hello world");
}




