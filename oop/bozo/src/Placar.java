package bozo;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.*;

public class Placar {

	//classe auxiliar para imprimir corretmante o placar
	class ScorePos {
		int position;
		int value;

		ScorePos(int _position) {
			position = _position;
			value = 0;
		}

		public String toString() {
			if (value == 0) {
				return String.format(" (%2d) ", position);
			} else {
				return String.format(" %3d  ", value);
			}
		}

		public int getVal(){
			return value;
		}

		public void setVal(int _value) {
			value = _value;
		}
	}

	//Posições dos placares
	private ScorePos N1  ;
	private ScorePos N2  ;
	private ScorePos N3  ;
	private ScorePos N4  ;
	private ScorePos N5  ;
	private ScorePos N6  ;
	private ScorePos FULL;
	private ScorePos SEQ ;
	private ScorePos QUAD;
	private ScorePos QUIN;

	//Instanciações dos placares
	public Placar() {
		N1   = new ScorePos(1);
		N2   = new ScorePos(2);
		N3   = new ScorePos(3);
		N4   = new ScorePos(4);
		N5   = new ScorePos(5);
		N6   = new ScorePos(6);
		FULL = new ScorePos(7);
		SEQ  = new ScorePos(8);
		QUAD = new ScorePos(9);
		QUIN = new ScorePos(10);
	}

	//Seleciona a posição do placar correta
	public void add(int pos, int[] dadosArr) throws PlacarException {
		List<Integer> dados = Arrays.stream(dadosArr)
					    .boxed()
					    .collect(Collectors.toList());
		switch (pos) {
			case 1:
				adic1(dados);
				break;
			case 2:
				adic2(dados);
				break;
			case 3:
				adic3(dados);
				break;
			case 4:
				adic4(dados);
				break;
			case 5:
				adic5(dados);
				break;
			case 6:
				adic6(dados);
				break;
			case 7:
				adicFull(dados);
				break;
			case 8:
				adicSeq(dados);
				break;
			case 9:
				adicQuad(dados);
				break;
			case 10:
				adicQuin(dados);
				break;
			default:
				throw new PlacarException("Posição inválida no placar!");

		}
	}

	//Retorna a soma do placar
	public int getScore() {
		return N1.getVal()+
			N2.getVal()+
			N3.getVal()+
			N4.getVal()+
			N5.getVal()+
			N6.getVal()+
			FULL.getVal()+
			SEQ.getVal()+
			QUAD.getVal()+
			QUIN.getVal();
	}

	public String toString() {
		String retstring =
			  N1.toString() + "  |" +
			FULL.toString() + "  |" +
			  N4.toString() + "  \n"+
			"--------------------------\n"+
			  N2.toString() + "  |" +
			 SEQ.toString() + "  |" +
			  N5.toString() + "  \n"+
			"--------------------------\n"+
			  N3.toString() + "  |" +
			QUAD.toString() + "  |" +
			  N6.toString() + "  \n"+
			"--------------------------\n"+
			"        |" + QUIN.toString() + "  |\n"+
			"        +--------+\n";


		return retstring;
	}

	/*Cada função trata especialmente as posições dos placares*/
	private void adic1(List<Integer> dados) throws PlacarException {
		if (N1.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");

		long val = dados.stream()
				.filter(n -> n == 1)
				.count();

		N1.setVal((int)val);
	}

	private void adic2(List<Integer> dados) throws PlacarException {
		if (N2.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");
		long val = dados.stream()
				.filter(n -> n == 2)
				.count();

		N2.setVal((int)val * 2);
	}

	private void adic3(List<Integer> dados) throws PlacarException {
		if (N3.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");
		long val = dados.stream()
				.filter(n -> n == 3)
				.count();

		N3.setVal((int)val * 3);
	}

	private void adic4(List<Integer> dados) throws PlacarException {
		if (N4.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");
		long val = dados.stream()
				.filter(n -> n == 4)
				.count();

		N4.setVal((int)val * 4);
	}

	private void adic5(List<Integer> dados) throws PlacarException {
		if (N5.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");
		long val = dados.stream()
				.filter(n -> n == 5)
				.count();

		N5.setVal((int)val * 5);
	}

	private void adic6(List<Integer> dados) throws PlacarException {
		if (N6.getVal() != 0)
		throw new PlacarException("Já adicionou nessa casa do placar!");

		long val = dados.stream()
				.filter(n -> n == 6)
				.count();

		N6.setVal((int)val * 6);
	}

	private void adicFull(List<Integer> dados) throws PlacarException {
		if (FULL.getVal() != 0)
		throw new PlacarException("Já adicionou Full nesse jogo!");
		List<Integer> nums = dados.stream()
					.distinct()
					.collect(Collectors.toList());
		if (nums.size() != 2)
		throw new PlacarException("Full hand com mais de 2 números!");

		int numA = dados.stream()
				.filter( n -> n == nums.get(0))
				.collect(Collectors.toList())
				.size();

		int numB = dados.stream()
				.filter( n -> n == nums.get(1))
				.collect(Collectors.toList())
				.size();

		if ( (numA == 2 && numB == 3) || (numA == 3 && numB == 2)) {
			FULL.setVal(15);
		}

	}

	private void adicSeq(List<Integer> dados) throws PlacarException {
		if (SEQ.getVal() != 0)
		throw new PlacarException("Já adicionou Sequência nesse jogo!");
		List<Integer> sortedDices = dados.stream()
						.distinct()
						.sorted()
						.collect(Collectors.toList());

		int comparison = sortedDices.stream()
						.findFirst()
						.get().intValue();

		for ( Integer val : sortedDices) {
			if (comparison != val) {
				throw new PlacarException("Não é Sequência válida!");
			}
			comparison++;
		}
		SEQ.setVal(20);
	}

	private void adicQuad(List<Integer> dados) throws PlacarException {
		if (QUAD.getVal() != 0)
		throw new PlacarException("Já adicionou Quadra nesse jogo!");

		List<Integer> distinctNums = dados.stream()
						.distinct()
						.collect(Collectors.toList());

		List<Integer> quantityOfEachDistinct = distinctNums.stream()
				.map( n -> dados.stream()
						.filter( x -> x == n)
						.collect(Collectors.toList())
						.size() )
				.collect(Collectors.toList());

		if (quantityOfEachDistinct.contains(4) ) {
			QUAD.setVal(30);
		} else {
			throw new PlacarException("Não é uma Quadra válida!");
		}


	}

	private void adicQuin(List<Integer> dados) throws PlacarException {
		if (QUIN.getVal() != 0)
		throw new PlacarException("Já adicionou Quina nesse jogo!");
		List<Integer> distinctNums = dados.stream()
						.distinct()
						.collect(Collectors.toList());

		List<Integer> quantityOfEachDistinct = distinctNums.stream()
				.map( n -> dados.stream()
						.filter( x -> x == n)
						.collect(Collectors.toList())
						.size() )
				.collect(Collectors.toList());

		if (quantityOfEachDistinct.contains(5) ) {
			QUIN.setVal(40);
		} else {
			throw new PlacarException("Não é uma Quina válida!");
		}
	}

	/*Classe de exceção no caso de entrada inválida*/
	public class PlacarException extends Exception {
		public PlacarException (String s) {
			super(s);
		}

	}
}
