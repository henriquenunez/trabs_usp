import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex5{

	public static int checkPrime(int n)
	{
		int div = 2;

		while (div <= Math.ceil(Math.sqrt(n))){
			if ( (n%div) == 0) return div;
			div++;
		}
		return -1;
	}


	public static void main(String[] args) throws IOException{

		while (true)
		try{
			System.out.println("Insira o número que deve ter um primo melhor");
			break;		
		} catch (Exception e) {
			System.out.println("O número inserido deve ser inteiro");
		}

		int n = EntradaTeclado.leInt();
		do{
			n--;
			if (n == 0){
				System.out.println("Não há primo menor");
			}
		}while (checkPrime(n) != -1);
		System.out.println("O menor primo é: " + n);		
	}
}
