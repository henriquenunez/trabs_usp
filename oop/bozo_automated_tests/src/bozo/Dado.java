package bozo;

public class Dado {

	//final pois deve ser inicializado apenas uma vez
	private final int type;
	public Random randGenerator; // TESTING PURPOSES ONLY.
	int lado;

	//Construtores
	public Dado () {
		randGenerator = new Random();
		type = 6;
	}

	public Dado (int n) {
		randGenerator = new Random();
		type = n;
	}

	public int rolar() {
		lado = randGenerator.getIntRand(type) + 1;
		return lado;
	}

	public int getLado() {
		return lado;
	}

/* Not possible to be tested.
	public static void main(String[] args) {
		//sem função
	}

*/
	//em cada caso retorna a figura correspondente
	public String toString() {
		//a string de offset controla o cursor do terminal
		String offsetString =
			String.format("\033[7D\033[1B");

		switch (lado) {
			case 1:
			return 			  "+-----+" + offsetString +
						  "|     |" + offsetString +
						  "|  *  |" + offsetString +
						  "|     |" + offsetString +
						  "+-----+" + offsetString;
			case 2:
			return
						  "+-----+" + offsetString +
						  "|*    |" + offsetString +
						  "|     |" + offsetString +
						  "|    *|" + offsetString +
						  "+-----+" + offsetString;

			case 3:
		  	return
						  "+-----+" + offsetString +
						  "|*    |" + offsetString +
						  "|  *  |" + offsetString +
						  "|    *|" + offsetString +
						  "+-----+" + offsetString;
			case 4:
			return
						  "+-----+" + offsetString +
						  "|*   *|" + offsetString +
						  "|     |" + offsetString +
						  "|*   *|" + offsetString +
						  "+-----+" + offsetString;

			case 5:
			return
						  "+-----+" + offsetString +
						  "|*   *|" + offsetString +
						  "|  *  |" + offsetString +
						  "|*   *|" + offsetString +
						  "+-----+" + offsetString;

			case 6:
		  	return
						  "+-----+" + offsetString +
						  "|*   *|" + offsetString +
						  "|*   *|" + offsetString +
						  "|*   *|" + offsetString +
						  "+-----+" + offsetString;
		}
		return "Not Available";

	}
}
