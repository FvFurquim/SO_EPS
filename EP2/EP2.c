#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variaveis globais
int count = 0;
int vez = 0;

void secao_critica();
void secao_nao_critica(int i);
void* p0(void* arg);
void* p1(void* arg);

int main(){
  
  // Declaracao e criacao dos threads	
  pthread_t threadP0, threadP1;

  pthread_create(&threadP0, NULL, p0, NULL);
  pthread_create(&threadP1, NULL, p1, NULL);

  pthread_join(threadP0, NULL);
  pthread_join(threadP0, NULL);

  return 0;
}

// Metodo que acessa secao critica
void secao_critica(){

  printf("Global count: %d\n", count);
  count++;
}

// Metodo que representa a secao nao critica do programa
void secao_nao_critica(int i){

  printf("Secao nao critica P%d\n", i);
}

// Medoto executado por um thread
void* p0(void* arg){
  int meu_id = 0;
  int outro = 1;

  while(1){

  	// Esse while so serve para travar' o thread nesse ponto enquanto nao for a vez dele
    while(vez != meu_id);

    // Executa a sessao critica, passa a vez para o outro e executa a sessao nao critica
    secao_critica();
    vez = outro;
    secao_nao_critica(meu_id);
  }

  return arg;
}

// Metodo executado por outro thread
void* p1(void* arg){
  int meu_id = 1;
  int outro = 0;

  while(1){

  	// Esse while so serve para travar' o thread nesse ponto enquanto nao for a vez dele
    while(vez != meu_id);

    // Executa a sessao critica, passa a vez para o outro e executa a sessao nao critica
    secao_critica();
    vez = outro;
    secao_nao_critica(meu_id);
  }

  return arg;
}

/* OBS: Os metodos p0 e p1 sao identicos propositalmente. Poderiamos ter passado valores 
que mudam o meu_id e o outro, porem opatmos fazer metodos diferentes para ficar mais evidente
o que eh p0 e o que eh p1, como no pseudocodigo passado no enunciado.*/