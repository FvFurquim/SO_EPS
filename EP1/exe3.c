#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print(void *ptr);

int main(){

	pthread_t thread[5];

	char* hello = "hello word";

	// Criando 5 threads
	int i;
	for(i = 0; i < 5; i++)
		pthread_create( &thread[i], NULL, print, (void*) hello);

	for(i = 0; i < 5; i++)
		pthread_join(thread[i], NULL);

	exit(0);
	return 0;
}

// Metodo que sera executado nas threads
void* print(void* msg){

	printf("%s\n", msg);

	return msg;
}

