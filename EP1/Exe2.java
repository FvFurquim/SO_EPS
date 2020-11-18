public class Exe2 {
	public static void main(String[] args) {

		// Este for ira criar 5 threads que executam o que esta no metodo 'run()'
		// da classe interna 
		for(int i = 0; i < 5; i++)
			new Thread(threadHello).start();
	}

	// Criando uma classe interna anonima
	private static Runnable threadHello = new Runnable(){
		public void run(){
			System.out.println("hello world");
		}
	};
}