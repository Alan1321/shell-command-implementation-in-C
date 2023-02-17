#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    _cat("file.txt");
    _cp("file.txt", "helloworld.txt");
}

