package bozo;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class RandomTest {

	Random _randInstance;
	
	@Before
	public void setUp() throws Exception {
		_randInstance = new Random(42);
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testRandom() {
		_randInstance = new Random();
	}
	
	@Test
	public void testGetIntRand() {
		int k;
		k = _randInstance.getIntRand(100);
		assertEquals(k, 30);
		k = _randInstance.getIntRand(100);
		assertEquals(k, 35);
		k = _randInstance.getIntRand(100);
		assertEquals(k, 71);
		k = _randInstance.getIntRand(100);
		assertEquals(k, 13);
		k = _randInstance.getIntRand(100);
		assertEquals(k, 34);
	}

}
