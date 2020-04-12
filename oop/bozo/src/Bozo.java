package bozo;

import java.io.IOException;
//import PlacarException;

public class Bozo {

	public static void main(String[] args) throws IOException,
InterruptedException {
		//inicializa com 5 dados
		RolaDados nossosDados = new RolaDados(5);
		//instancia placar
		Placar    nossoPlacar = new Placar();
		//Contador de rodadas
		int turnCount = 1;
		//opção temporária
		int op;
		//Array temporário para guardar o valor dos dados
		int[] dadosRolagem;
		//String temporária para guardar os dados que devem ser
		//re-rolados
		String reRolagem;
		//Coloca a mensagem inicial na tela
		System.out.print(welcome);
		System.out.print("\n");
		System.out.print(nossoPlacar);

		while (turnCount <= 10) {
			System.out.printf("******Rodada: %d******", turnCount);
			System.out.print(beginTurn);
			//Espera o ENTER
			EntradaTeclado.leString();
			//atirbui array para temporário
			dadosRolagem = nossosDados.rolar();
			System.out.println(nossosDados);
			for (int i = 0 ; i < 2 ; i++) {
				System.out.print(askReRoll);
				reRolagem = EntradaTeclado.leString();
				if (reRolagem.isEmpty()) break;
				dadosRolagem = nossosDados.rolar(reRolagem);
				System.out.println(nossosDados);
			}
			//Pede para inserir no placar
			System.out.print("\n");
			System.out.println(nossoPlacar);
			while (true) {
				try {
					//passa a opção junto com o array
					System.out.print(insertScore);
					op = EntradaTeclado.leInt();
					if (op == 0) break;
					nossoPlacar.add(op,
							dadosRolagem);
					break;
				} catch(Placar.PlacarException e) {
					System.out.println(e.getMessage());
				}
			}
			System.out.print("\n");
			System.out.print(nossoPlacar);
			turnCount++;
		}

		System.out.println("Placar final: %d" + nossoPlacar.getScore());
	}

	static String welcome = "Bem vindo ao jogo Bozó\n\n© 2020 Hiram, uma organização sem fins lucrativos\n\n\n";
	static String beginTurn = "\n\nPressione ENTER para começar >>>> ";
	static String askReRoll = "Insira os dados que deseja rolar noavamente (Se não quiser re-rolagem, pressione apenas Return) >>>> ";
	static String insertScore = "Agora, coloque na posição desejada do placar (0 para descartar a rodada) >>>> ";
}
