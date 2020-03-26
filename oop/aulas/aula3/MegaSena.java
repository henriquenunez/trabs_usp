package Aula3;

import Exercises.EntradaTeclado;
import java.io.IOException;

public class MegaSena {

	public static void main(String[] args) {

		long seed;

		while(true)
		try{
			seed = EntradaTeclado.leInt();
			break;
		}catch(IOException e){
			System.out.println("Inserir inteiro plz");
		}		

		Random numerinho = new Random(seed, 60);

		for (int i = 0 ; i < 6 ; i++){
			System.out.print("Numero " + i);
			System.out.println(numerinho.getRandInt());
		}

	}

}
