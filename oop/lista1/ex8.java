import Exercises.EntradaTeclado;
import java.io.IOException;

public class ex8{
	public static double EPSILON = 0.0000001;

	/*Data structure*/
	public static class Pair<tA, tB>{
		private final tA first;
		private final tB second;

		public Pair(tA first, tB second){
			this.first  = first;
			this.second = second;
		}

		public tA getFirst(){
			return this.first;
		}
		
		public tB getSecond(){
			return this.second;
		}

	}

	/*Calculate funcs*/
	public static double calcFunc(double x){
		return Math.pow(x, 3) - Math.pow(x, 2) - 13 * x + 8;
	}

	public static double calcFuncDeriv(double x){
		return (3 * Math.pow(x, 2)) - (2 * x) - 13;
	}

	/*Newton-Raphson method itself*/
	public static Pair<Double, Integer> findRootByNewtonRaphson(double x){
		double x_plus_one;
		int counter = 0;
		
		do{
			/*	X_i+1 = X - F(x)/F'(x)	*/
			x_plus_one = x - (calcFunc(x)/calcFuncDeriv(x));
			x = x_plus_one;
			System.out.println("X+1 is :" + x_plus_one);	
			System.out.println("f(X+1) is :" + calcFunc(x_plus_one));	
			counter++;
		}while( Math.abs(calcFunc(x_plus_one)) > EPSILON);// && Math.abs(a - c) > EPSILON);
	
		return new Pair<Double, Integer>(x_plus_one, counter);
	}

	public static void main(String[] args) throws IOException{
		double xGuess;
		
		/*Exception handler*/
		while (true)
		try{
			System.out.print("Insira um chute inicial: ");
			xGuess = EntradaTeclado.leDouble();
			break;		
		} catch (Exception e) {
			System.out.println("O chute deve ser um valor de ponto flutuante!!");

		}


		Pair<Double, Integer> holder = findRootByNewtonRaphson(xGuess);

		System.out.println("O ponto de raiz é: " + holder.getFirst());
		System.out.println("Iterações: " + holder.getSecond());
	}

}
