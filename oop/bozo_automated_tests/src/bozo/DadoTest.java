package bozo;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class DadoTest {

	Dado _dice;
	
	@Before
	public void setUp() throws Exception {
		_dice = new Dado();
		_dice.randGenerator = new Random(43);
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testDadoInt() {
		_dice = new Dado(20);
		_dice.randGenerator = new Random(43);
	}

	@Test
	public void testGetLado() {
		int k;
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 2);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 2);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 1);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 2);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 3);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 6);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 5);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 5);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 2);
		_dice.rolar();
		k = _dice.getLado();
		
		assertEquals(k, 1);
		_dice.rolar();
		k = _dice.getLado();
		assertEquals(k, 3);
		
		_dice.rolar();
		k = _dice.getLado();
		assertEquals(k, 4);
	}

	@Test
	public void testToString() {
		//Expected dice for 2;
	String offsetString = new String("\033[7D\033[1B");
	String t1 =
				  "+-----+" + offsetString +
				  "|     |" + offsetString +
				  "|  *  |" + offsetString +
				  "|     |" + offsetString +
				  "+-----+" + offsetString;
	String t2 = 
				  "+-----+" + offsetString +
				  "|*    |" + offsetString +
				  "|     |" + offsetString +
				  "|    *|" + offsetString +
				  "+-----+" + offsetString;

	String t3 = 
				  "+-----+" + offsetString +
				  "|*    |" + offsetString +
				  "|  *  |" + offsetString +
				  "|    *|" + offsetString +
				  "+-----+" + offsetString;
  	String t4 = 
				  "+-----+" + offsetString +
				  "|*   *|" + offsetString +
				  "|     |" + offsetString +
				  "|*   *|" + offsetString +
				  "+-----+" + offsetString;

	String t5 = 
				  "+-----+" + offsetString +
				  "|*   *|" + offsetString +
				  "|  *  |" + offsetString +
				  "|*   *|" + offsetString +
				  "+-----+" + offsetString;
	String t6 = 
				  "+-----+" + offsetString +
				  "|*   *|" + offsetString +
				  "|*   *|" + offsetString +
				  "|*   *|" + offsetString +
				  "+-----+" + offsetString;
		
		String k;
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t2);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t2);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t1);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t2);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t3);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t6);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t5);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t5);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t2);
		_dice.rolar();
		k = _dice.toString();
		
		assertEquals(k, t1);
		_dice.rolar();
		k = _dice.toString();
		assertEquals(k, t3);
		
		_dice.rolar();
		k = _dice.toString();
		assertEquals(k, t4);
	
		_dice = new Dado(100);
		_dice.randGenerator = new Random(100);
		_dice.rolar();
		assertEquals(_dice.toString(), "Not Available");
	}

}
