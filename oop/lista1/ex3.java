import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex3{

	public static void main(String[] args) throws IOException{

		int n = EntradaTeclado.leInt();
		for (int i = 0 ; i <= n ; i++){
			for (int j = 0 ; j <= n ; j++){
				if (j < i){
					System.out.print(" ");
				}else{
					System.out.print("*");
				}	
			}
			System.out.print("\n");
		}
	}
}
