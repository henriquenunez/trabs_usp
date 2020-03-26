import Exercises.EntradaTeclado;
import java.io.IOException;
import java.io.*;

public class ex7{
	public static double EPSILON = 0.0000001;

	/*User-defined exception*/
	public static class IntervalNotValidException extends Exception{}

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

	public static double calcFunc(double x){
		return Math.pow(x, 3) - Math.pow(x, 2) - 13 * x + 8;
	}

	//For same signal returns true, different return false
	public static boolean checkSignal(double A, double B){
		if ( ((A * B) / Math.abs(A * B)) == 1) {
			System.out.println("Same signal");
			return true;
		}
		else {
			System.out.println("Diff signal");
			return false;
		}
	}

	public static Pair<Double, Integer> findRootByBisection(double a, double b) throws IntervalNotValidException{
		double c;
		int counter = 0;

		if (a > b) throw new IntervalNotValidException();
		
		do{
			c = (a + b)/2;
			if (checkSignal(calcFunc(a), calcFunc(c))){
				a = c;
			}else 
			if (checkSignal(calcFunc(b), calcFunc(c))){
				b = c;
			}
			counter++;
			System.out.println("A= " + a + "C=" + c + "B=" + b);
		}while( Math.abs(calcFunc(c)) > EPSILON); //&& Math.abs(a - c) > EPSILON);
	
		return new Pair<Double, Integer>(c, counter);
	}

	public static void main(String[] args) throws IOException{
		double intervalA, intervalB;
		Pair<Double, Integer> holder;

		while (true)
		try{
			System.out.println("Insira os valores dos intervalos");
			System.out.print("A: ");
			intervalA = EntradaTeclado.leDouble();
			System.out.print("B: ");
			intervalB = EntradaTeclado.leDouble();

			holder = findRootByBisection(intervalA, intervalB);

			break;	
		} catch (IntervalNotValidException e){
			System.out.println("O intervalo deve ser do tipo A < B, por obséquio!!");

		} catch (Exception e) {
			System.out.println("Insira valores em forma ponto flutuante, por obséquio!!");

		}


		System.out.println("O ponto de raiz é: " + holder.getFirst());
		System.out.println("Iterações: " + holder.getSecond());
	}

}
