#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>

// Metodo que sera chamado no processo pai
void parentProcess(){
	printf("hello parent\n");
}

// Metodo que sera chamado no processo filho
void childProcess(){
	printf("hello child\n");
}

int main() { 

int p = fork();
	
	// Se o valor de p for 0, execute o metodo especifico do processo filho
	if(p == 0){
	  	childProcess();
	 	kill(p,SIGKILL);
	}

	else if(p > 0)
  		parentProcess();

	return 0;
}