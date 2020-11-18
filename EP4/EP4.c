#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define COMENDO 0
#define FOME 1
#define PENSANDO 2
#define ESQUERDA (filoNum + 4) % N
#define DIREITA (filoNum + 1) % N

int estado[N];
int filo[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t sem[N];

void teste(int filoNum){

	if(estado[filoNum] == FOME && estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO){

		estado[filoNum] = COMENDO;
		usleep((rand() % 5) * 100000);

		printf("Filosofo %d pegou os garfos %d e %d\n", filoNum+1, ESQUERDA+1, filoNum+1);
		printf("Filosofo %d esta Comendo\n", filoNum+1);

		sem_post(&sem[filoNum]);
	}
}

void pegarGarfo(int filoNum){

	sem_wait(&mutex);

	estado[filoNum] = FOME;

	printf("Filosofo %d esta Com Fome\n", filoNum+1);

	teste(filoNum);

	sem_post(&mutex);
	sem_wait(&sem[filoNum]);

	usleep((rand() % 5) * 100000);
}

void soltarGarfo(int filoNum){

	sem_wait(&mutex);

	estado[filoNum] = PENSANDO;

	printf("Filosofo %d soltou os garfos %d e %d\n", filoNum+1, ESQUERDA+1, filoNum+1);
	printf("Filosofo %d esta pensando\n", filoNum+1);

	teste(DIREITA);
	teste(ESQUERDA);

	sem_post(&mutex);
}

void* filosofo(void* num){

	while(1){
		int* i = num;

		usleep((rand() % 5) * 100000);
		pegarGarfo(*i);
		usleep((rand() % 5) * 100000);
		soltarGarfo(*i);
	}
}

int main(){

	int i;
	pthread_t thread[N];

	sem_init(&mutex, 0, 1);

	for(i = 0; i < N; i++)
		sem_init(&sem[i], 0, 0);

	for(i = 0; i < N; i++){
		pthread_create(&thread[i], NULL, filosofo, &filo[i]);

		printf("Filosofo %d esta Pensando\n", i+1);
	}

	for(i = 0; i < N; i++)
		pthread_join(thread[i], NULL);
}