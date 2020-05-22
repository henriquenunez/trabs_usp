import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex2{

	public static void main(String[] args) throws IOException{

		while (true)
		try{
			System.out.println("Insira o número de linhas:");
			int n = EntradaTeclado.leInt();
			break;
		} catch (Exception e) {
			System.out.println("O número de linhas deve ser inteiro");
		}

		for (int i = 1 ; i <= n ; i++){
			for (int j = 1 ; j <= n - i ; j++){
				System.out.print("*");
			}
			System.out.print("\n");
		}
	}
}
