package bozo;
import java.util.Calendar;

public class Random {

	private final long p = 23847621;
	private final long m = 23278146;
	private final long a = 31235532;
	private long xi;

	public Random() {
		xi = Calendar.getInstance().getTimeInMillis()%p;
	}

	public Random(long seed) {
		xi = seed;
	}

	//gera com o metodo LCG (Linear Congruencial Generator)
	private double getRand() {
		xi = (a + m * xi) % p;
		return (double) xi/p;
	}

	//Multiplica um valor de 0 a 1 pelo valor maximo
	public int getIntRand(long max) {
		return (int) (getRand() * max);
	}
}

/*
                 \     /
                 \\   //
                  )\-/(
                  /e e\
                 ( =T= )
                 /`---'\
            ____/ /___\ \
       \   /   '''     ```~~"--.,_
    `-._\ /                       `~~"--.,_
   ------>|                                `~~"--.,_
    _.-'/ \                            ___,,,---""~~``'
       /   \____,,,,....----""""~~~~````

*/
