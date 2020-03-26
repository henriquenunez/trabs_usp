//package Aula4;

import Exercises.EntradaTeclado;

/*Coisas simples em strings*/

public class Strings{

	private static long countOcurrences(String str, char ch){
		return str.chars()
			.filter(c -> c == ch)
			.count();
	}

	public static void main(String[] args){
		String a, b, vowels = "abcde";

		while(true)
		try{
			a = EntradaTeclado.leString();//abcde
			b = EntradaTeclado.leString();//ab
			break;
		}catch(Exception e){

		}

		System.out.println("String 1 UPPERCASE: " + a.toUpperCase());

		if (a.startsWith(b)) System.out.println("1 starts with 2");

		System.out.println("Number of As: " + countOcurrences(a.toUpperCase(), 'A'));
		System.out.println("Number of Es: " + countOcurrences(a.toUpperCase(), 'E'));
		System.out.println("Number of Is: " + countOcurrences(a.toUpperCase(), 'I'));
		System.out.println("Number of Os: " + countOcurrences(a.toUpperCase(), 'O'));
		System.out.println("Number of Us: " + countOcurrences(a.toUpperCase(), 'U'));


		}

	}

