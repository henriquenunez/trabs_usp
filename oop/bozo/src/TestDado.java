import bozo.Dado;

public class TestDado {

	public static void main(String[] args){
		Dado die = new Dado();
		for (int i = 0 ; i < 5 ; i++) {
			die.rolar();
			System.out.print("\n\n\n\n\n\n\n\n\033[7A");
			System.out.print(die);
		}
	}
}
