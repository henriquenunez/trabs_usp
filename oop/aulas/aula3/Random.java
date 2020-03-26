/*Instanciacao de classes a.k.a. objetos*/
package Aula3;

import Exercises.EntradaTeclado;
import java.util.Calendar;

public class Random{

	/* X_i+1 = (a + m*x_i)mod(p) */
	private static long max;
	private long p = 23847621;
	private long m = 23278146;
	private long a = 31235532;
	private long xi;

	Random(long _seed, long _max){
		xi = _seed;
		max = _max;
	}

	Random(long _seed){
		xi = _seed;
		max = _max;
	}

	public double getRand(){
		xi = (a + m * xi);
		return (double)xi/p;
	}

	public double getRandInt(long _max){
		return (int)(getRand() * max);
	}


}

//Random numerinho = new Random();

