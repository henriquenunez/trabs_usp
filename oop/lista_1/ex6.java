import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex6{

	public static void main(String[] args) throws IOException{
		double min = -1, max = -1, n;
		boolean flag = false;

		while (true) {
		
			try{
				System.out.println("Insira um valor:");
				n = EntradaTeclado.leDouble();

			} catch (Exception e) {
				System.out.println("O valor deve ser double!!");
				continue;
			}

			if (n == 0) break;
			if (flag == false) min = max = n;

			flag = true;

			if (n < min) min = n;
			else if (n > max) max = n;
		}

		System.out.println("Min: " + min + ", Max: " + max);
	}
}
