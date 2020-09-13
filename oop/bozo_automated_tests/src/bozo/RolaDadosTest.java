package bozo;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class RolaDadosTest {

	RolaDados _nossosDados;
	
	@Before
	public void setUp() throws Exception {
		_nossosDados = new RolaDados(2);
		for(Object _umDado : _nossosDados.dados) {
			if(!(_umDado instanceof Dado)) throw new Exception("Something wrong");
			Dado _esseDado = (Dado) _umDado;
			_esseDado.randGenerator = new Random(42);
		}
	}

	@After
	public void tearDown() throws Exception {
	}
	
	@Test
	public void testRolaDados() {
	//	_nossosDados.
	}

	@Test
	public void testRolar() {
		_nossosDados.rolar();
	}

	@Test
	public void testRolarBooleanArray() {
		boolean[] which = {true, true};
		_nossosDados.rolar(which);
	}

	@Test(expected=Exception.class)
	public void testRolarBooleanArrayOutOfBoundaries() {
		boolean[] which = {false, true, true};
		_nossosDados.rolar(which);
	}
	
	@Test
	public void testRolarString() {
		_nossosDados.rolar("0 1");
	}
	
	@Test(expected=Exception.class)
	public void testRolarStringOutOfBoundaries() {
		_nossosDados.rolar("1 2 3");
	}

	@Test
	public void testToString() {
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
		_nossosDados.rolar();
		k = _nossosDados.toString();
	
		//From the random, we know that at this roll, both dices will be 2.
		assertEquals(k, "\n\n\n\n\n\n\n\n\033[8A"
				+ "0\033[1B\033[1D"
				+ t2
				+ "\033[9C\033[6A"//Walk right
				+ "1\033[1B\033[1D"
				+ t2
				+ "\033[9C\033[6A"//Walk right
				+ "\033[6B\n"); //last one
	}

}
