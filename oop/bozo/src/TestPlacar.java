import bozo.Placar;
import bozo.Placar.PlacarException;

public class TestPlacar {

	public static void main(String[] args){
		Placar nossoplacar = new Placar();

		int[] t1 = {1, 1, 1, 2, 5};

		try {
			nossoplacar.add(9, t1);
		} catch (PlacarException e) {
			System.out.println(e.getMessage());
		}
		System.out.println("Placar = " + nossoplacar.getScore());

		try {
		nossoplacar.add(1, t1);
		} catch (PlacarException e) {
			System.out.println(e.getMessage());
		}

		System.out.println("Placar = " + nossoplacar.getScore());

		System.out.println(nossoplacar);
	}

}
