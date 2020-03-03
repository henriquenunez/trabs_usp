import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex4{

	public static void main(String[] args) throws IOException{

		int n = EntradaTeclado.leInt();
		int div = 2;

		while (div < Math.ceil(Math.sqrt(n))){
			if ( (n/div) == int(n/div) ) 
				System.out.println("Smallest div: " + div);
			div++;
		}
		
	}
}
