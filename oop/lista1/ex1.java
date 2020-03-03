import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex1{

	public static void main(String[] args) throws IOException{
		double guess, X_i, X_i_prev, error, value;
		int ITER_LIMIT = 	  1000;
		double EPSILON    = 0.000001;
		int iterCounter = 0;

		System.out.print("Valor a ser enraizado:");
		value = Exercises.EntradaTeclado.leDouble();
		//System.out.print("\n");
		System.out.print("Nosso chute:");
		guess = Exercises.EntradaTeclado.leDouble();
		//System.out.print("\n");

		X_i = guess;

		do{
			System.out.println("valor:" + value);	
			X_i_prev = X_i;
			X_i = (X_i + (value/X_i))/2;
			error = X_i_prev - X_i;
			iterCounter++;
		}while(iterCounter <= ITER_LIMIT && Math.abs(error) > EPSILON);

		System.out.println("O valor eh: " + X_i);
	}
}
