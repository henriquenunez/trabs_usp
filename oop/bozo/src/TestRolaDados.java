import bozo.RolaDados;

public class TestRolaDados {

	public static void main (String[] args) throws InterruptedException {
		RolaDados meusDados = new RolaDados(5);
		meusDados.rolar();
		System.out.println(meusDados);
	}
}
