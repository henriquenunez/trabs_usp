import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex1{

	public static void main(String[] args) throws IOException{
		double guess, X_i, X_i_prev, error, value;
		int ITER_LIMIT = 	  1000;
		double EPSILON    = 0.000001;
		int iterCounter = 0;
	
		while (true)
		try{
			System.out.print("Valor a ser enraizado:");
			value = Exercises.EntradaTeclado.leDouble();
			break;
		} catch (Exception e) {
			System.out.print("O valor enraziado deve ser um ponto flutuante!!");
		}
		
		while (true)
		try{
			System.out.print("Nosso chute:");
			guess = Exercises.EntradaTeclado.leDouble();
			break;
		} catch (Exception e) {
			System.out.print("O nosso chute deve ser um valor de ponto flutuante!!");
		}

		X_i = guess;

		//Imprime o valor e faz o processo
		do{
			System.out.println("valor:" + value);	
			X_i_prev = X_i;
			//Aproxima mais o chute
			X_i = (X_i + (value/X_i))/2;
			error = X_i_prev - X_i;
			iterCounter++;
		}while(iterCounter <= ITER_LIMIT && Math.abs(error) > EPSILON);

		System.out.println("O valor eh: " + X_i);
	}
}
