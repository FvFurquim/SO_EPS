#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>

int main() { 
    
    // Este fork que criara um processo executando todas as intrucoes abaixo
	fork();
	printf("hello world\n");

	return 0;
}