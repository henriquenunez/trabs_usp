package bozo;

import java.util.stream.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class RolaDados {
	//Estrutura de dados para armazenar os objetos
	List<Dado> dados;

	/* Construtor da classe, instancia n objetos do tipo dado, com um
	 * intervalo de tempo entre eles para promover a aleatoriedade
	*/
	public RolaDados(int n) throws InterruptedException{
		dados = new ArrayList<Dado>();
		for (int i = 0 ; i < n ; i++) {
			dados.add(new Dado());
			Thread.sleep(133);
		}
	}

	//Rola todos e retorna array de int
	public int[] rolar() {

		dados.stream()
			.forEach( d -> d.rolar());

		return dados.stream()
				.mapToInt( d -> d.getLado())
				.toArray();
	}

	public int[] rolar(boolean[] quais) {
		//rola os dados cujo indice no array corresponda a true
		int index = 0;
		for (boolean dice : quais) {
			if (dice) dados.get(index).rolar();
			index++;
		}
		return dados.stream()
				.mapToInt( d -> d.getLado())
				.toArray();
	}

	public int[] rolar(String s) {
		String[] s_dices = s.split(" ");
		boolean[] dices = new boolean[dados.size()];
		//cria um array booleano com os dados correspondentes como true
		for (String dice : s_dices) {
			dices[Integer.parseInt(dice)] = true;
		}
		this.rolar(dices);
		return dados.stream()
				.mapToInt( d -> d.getLado())
				.toArray();
	}

	public String toString() {
		//dá os linefeed necessários e volta para o começo
		String ret = "\n\n\n\n\n\n\n\n\033[8A";
		int idx = 0;
		//comandos de terminal para posicionar o cursor corretamente.
		for (Dado dado : dados) {
			ret += idx++;
			ret += "\033[1B\033[1D";
			//uma linha para baixo e uma coluna para atrás
			ret += dado;
			/*insere o dado e posiciona 9 colunas para frente
			  e 6 para cima, seguindo a lógica de impressão do dado
			*/
			ret += "\033[9C\033[6A";
		}
		ret += "\033[6B\n";
		return ret;
	}
}
