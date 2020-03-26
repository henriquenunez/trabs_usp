import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex4{

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
			System.out.println("Insira o número desejado");
			int n = EntradaTeclado.leInt();
			break;
		} catch (Exception e) {
			System.out.println("O número desejado deve ser inteiro!!");
		}

		System.out.println("Smallest div: " + checkPrime(n));
		
	}
}
