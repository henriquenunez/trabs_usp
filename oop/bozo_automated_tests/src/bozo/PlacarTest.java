package bozo;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import bozo.Placar.PlacarException;

public class PlacarTest {

	Placar _placar;
	
	@Before
	public void setUp() throws Exception {
		_placar = new Placar();
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testFullHand() {
		
		try {
			_placar = new Placar();
			_placar.add(7, new int[] {2, 2, 3, 3, 3} );
		} catch (Placar.PlacarException e) {}
		
		try {
			_placar = new Placar();
			_placar.add(7, new int[] {2, 2, 2, 3, 3} );
		} catch (Placar.PlacarException e) {}

	}

	@Test
	public void testAdd() {
		
		try {
			_placar.add(7, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Full hand com mais de 2 números!");
		}
		
		try {
			_placar.add(8, new int[] {1, 3, 1, 4, 1} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Não é Sequência válida!");
		}
		
		try {
			_placar.add(9, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Não é uma Quadra válida!");
		}
		
		try {
			_placar.add(10, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Não é uma Quina válida!");
		}

	}
/*
	@Test(expected=PlacarException.class)
	public void testInvalidPosition() throws PlacarException {
		_placar = new Placar();
		_placar.add(10, new int[] {1, 2, 3, 4, 5} );
	}*/

	@Test
	public void testInvalidPosition() {
		
		try {
			_placar.add(11, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Posição inválida no placar!");
		}
		
	}	
	
	@Test
	public void testReAdd() throws Placar.PlacarException {
		
		String k = "Já adicionou nessa casa do placar!";
	
		_placar.add(1, new int[] {1, 2, 3, 4, 5} );
		_placar.add(2, new int[] {1, 2, 3, 4, 5} );
		_placar.add(3, new int[] {1, 2, 3, 4, 5} );
		_placar.add(4, new int[] {1, 2, 3, 4, 5} );
		_placar.add(5, new int[] {1, 2, 3, 4, 5} );
		_placar.add(6, new int[] {1, 2, 3, 4, 6} );
		_placar.add(7, new int[] {5, 5, 2, 2, 2} );
		_placar.add(8, new int[] {1, 2, 3, 4, 5} );
		_placar.add(9, new int[] {4, 4, 4, 4, 5} );
		_placar.add(10, new int[] {6, 6, 6, 6, 6} );
	
		try {
			_placar.add(1, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(2, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(3, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(4, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(5, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(6, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), k);
		}
		
		try {
			_placar.add(7, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Já adicionou Full nesse jogo!");
		}
		
		try {
			_placar.add(8, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Já adicionou Sequência nesse jogo!");
		}
		
		try {
			_placar.add(9, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Já adicionou Quadra nesse jogo!");
		}
		
		try {
			_placar.add(10, new int[] {1, 2, 3, 4, 5} );
		} catch (Placar.PlacarException e) {
			assertEquals(e.getMessage(), "Já adicionou Quina nesse jogo!");
		}
	}
	
	@Test
	public void testGetScore() {

		try {
			_placar.add(1, new int[] {1, 2, 3, 4, 5} );
			_placar.add(2, new int[] {1, 2, 3, 4, 5} );
			_placar.add(3, new int[] {1, 2, 3, 4, 5} );
			_placar.add(4, new int[] {1, 2, 3, 4, 5} );
			_placar.add(5, new int[] {1, 2, 3, 4, 5} );
			_placar.add(6, new int[] {1, 2, 3, 4, 5} );
			_placar.add(7, new int[] {5, 5, 2, 2, 2} );
			_placar.add(8, new int[] {1, 2, 3, 4, 5} );
			_placar.add(9, new int[] {4, 4, 4, 4, 5} );
			_placar.add(10, new int[] {6, 6, 6, 6, 6} );	
		} catch (Placar.PlacarException e) { }
		
		int k = _placar.getScore();
		assertEquals(120, k);
	}

	@Test
	public void testToString() {
		
		try {
			_placar.add(1, new int[] {1, 2, 3, 4, 5} );
			_placar.add(2, new int[] {1, 2, 3, 4, 5} );
			_placar.add(3, new int[] {1, 2, 3, 4, 5} );
			_placar.add(4, new int[] {1, 2, 3, 4, 5} );
			_placar.add(5, new int[] {1, 2, 3, 4, 5} );
			_placar.add(6, new int[] {1, 2, 3, 4, 5} );
			_placar.add(7, new int[] {5, 5, 2, 2, 2} );
			_placar.add(8, new int[] {1, 2, 3, 4, 5} );
			_placar.add(9, new int[] {4, 4, 4, 4, 5} );
			_placar.add(10, new int[] {6, 6, 6, 6, 6} );	
		} catch (Placar.PlacarException e) {
			System.out.println("sla");
		}
		
		String k = _placar.toString();
		assertEquals(k, "   1    |  15    |   4    \n"
					  + "--------------------------\n"
					  + "   2    |  20    |   5    \n"
					  + "--------------------------\n"
					  + "   3    |  30    | ( 6)   \n"
					  + "--------------------------\n"
					  + "        |  40    |\n"
					  + "        +--------+\n");
	}

}
