#include <stdio.h>
#include <string.h>
 
#define MAX 20
 
int main(int argc,char *argv[])
{
	char *p, input[256];
	char *A[MAX];
	int i;
 
	strcpy(input, argv[1]);
	
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	printf("%s\n", argv[3]);
	p = strtok(input," ");
	for(i = 0; p != 0 && i < MAX -1; ++i)
	{
		A[i] = p;
		p = strtok(0, " \t");
	}
	A[i] = 0;
 
	/*
	for(i = 0; A[i] ; ++i)
	{
		printf("A[%d] = %s\n", i, A[i]);
	}*/
 
	printf("A[0] = %s\n",A[0]);
	printf("A[1] = %s\n",A[1]);
	printf("A[2] = %s\n",A[2]);
 
	return 0;
}
