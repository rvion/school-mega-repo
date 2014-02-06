package test;

import testEtat.*;
import org.junit.*;
import static org.junit.Assert.*;

public class TestNonVide {

	private Conteneur C;
	private Object A1, A2, B1, B2;
	
	// Creation d'un conteneur partiellement rempli
	@Before
	public void creerConteneurNonVide() {
		try {
			C = new Conteneur(5);
        	A1 = new Object();
        	A2 = new Object();
        	B1 = new Object();
        	B2 = new Object();
        	C.ajouter(A1, B1);
        	C.ajouter(A2, B2);
		} catch (Exception e) {
			fail();
		}
	}

}
