#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

unsigned char* buffer;
int buffersize=0, datasize=0;

#define ONE_MB 1000000

int ReadBinaryFile(const char* filename);
int IsItText(unsigned char* buffer, int datasize);
int ToUnix(unsigned char* buffer, int datasize);

int main(int argc, char* argv[])
{
    int status;
    const char filename[] = "abc.txt";
    buffersize = 5*ONE_MB;
    buffer = (unsigned char*) malloc(buffersize);

    status = ReadBinaryFile(filename);
    if(status>0){
        if(status == 1) fprintf(stderr, "COULD NOT OPEN FILE!!\n");
        else if(status==2) fprintf(stderr, "FILE IS ZERO LENGTH!!\n");
        else if(status==3) fprintf(stderr, "FILE TOO BIG FOR BUFFER!!\n");
        else if(status==4) fprintf(stderr, "ERROR READING FILE!!\n");
    }else{
        if(!IsItText(buffer, datasize)){
            fprintf(stderr, "file %s is *not* text", filename);
        }else{
            if(strstr((char*) buffer, "\r")){
                fprintf(stdout, "file is windows");
                ToUnix(buffer, datasize);
            }else{
                fprintf(stdout, "File is UNIX");
            }
        }
    }
    if (buffer) free(buffer);
    return 0;
}

int ReadBinaryFile(const char* filename){
    int status=0;
    int bytesInFile=0;
    FILE* ifs=0;

    ifs=fopen(filename,"rb");
    if(!ifs){
        status=1;
    }else{
        fseek(ifs, 0, SEEK_END);
        bytesInFile=(int) ftell(ifs);
        fseek(ifs, 0, SEEK_SET);

        if(bytesInFile == 0){
            status=2;
        }else{
            if(bytesInFile >= (buffersize-1)){
                status=3;
            }else{
                datasize = (int) fread(buffer,1,bytesInFile,ifs);
                if(datasize != bytesInFile){
                    status=4;
                }else{
                    buffer[datasize]='\0';
                }
            }
        }
    }
    if(ifs) fclose(ifs);
    return status;
}

int writeBinaryFile(const char* filename){
    int status=0;
    FILE* ofs;

    ofs=fopen(filename, "wb");
    if(ofs){
        fwrite(buffer, 1, datasize, ofs);
        fclose(ofs);
        status=1;
    }
    return status;
}

int charIsText(char c){
    int status=0;
    if(isprint(c) != 0){
        status=1;
    }else{
        switch(c)
        {
            case '\f':
            case '\t':
            case '\r':
            case '\n':
            case '\a':
            case '\b':
            case '\v':
            status=1;
            break;
        }
    }
    return status;
}

int IsItText(unsigned char* buffer, int datasize){
    int i, count;
    count = datasize < 100 ? datasize : 100;
    return 1;
}

int ToUnix(unsigned char* buffer, int datasize){
    int i, j, count;
    return 1;
}