import java.util.concurrent.*;

public class EP3 {
	public static void main(String[] args) throws InterruptedException {
		
		// Criando um semaforo que comeca verde
		Semaphore sem = new Semaphore(1);

		// Criando duas instancias de ThreadTeste, que serao os threads
		ThreadTeste t1 = new ThreadTeste(sem, "A", 1);
		ThreadTeste t2 = new ThreadTeste(sem, "B", -1);

		t1.start();
		t2.start();

		t1.join();
		t2.join();

		System.out.println("count: " + Compartilhado.count);
	}
}

// Essa eh a secao critica, compartilhada entre as threads
class Compartilhado {

	static int count = 0;
}

// A classe ThreadTeste que estende Thread
class ThreadTeste extends Thread {

	Semaphore sem;
	String nomeThread;
	int valorAlteracao;

	public ThreadTeste(Semaphore sem, String nomeThread, int valorAlteracao){

		super(nomeThread);
		this.sem = sem;
		this.nomeThread = nomeThread;
		this.valorAlteracao = valorAlteracao;
	}

	// Sobrescrita do metodo 'run' que sera executado nos threads
	@Override
	public void run(){

		System.out.println("Comecando " + nomeThread);

		try{

			System.out.println(nomeThread + " esta esperando pela permissao");

			// Semafaro da a permissão para este thread e bloqueia os outros
			sem.acquire();

			System.out.println(nomeThread + " ganhou permissao");

			for(int i = 0; i < 5; i++){

				Compartilhado.count += valorAlteracao;
				System.out.println(nomeThread + ": " + Compartilhado.count);

				//Thread.sleep(10);
			}
		}

		catch (InterruptedException e){
			System.out.println(e);
		}

		// Semaforo libera o sinal
		System.out.println(nomeThread + " liberou a permissao");
		sem.release();
	}
}