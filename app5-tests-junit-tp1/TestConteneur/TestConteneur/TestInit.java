package test;

import testEtat.*;
import org.junit.*;
import static org.junit.Assert.*;

public class TestInit {

	private Conteneur C;

	// Objectif de test : creation d'un conteneur de capacite > 1
	// Resultat attendu : conteneur vide cree de la capacite passee en argument
	@Test
	public void capaciteSup1() {
		try {
			C = new Conteneur(5);

			assertNotNull(C);
			assertEquals(C.taille(), 0);
			assertEquals(C.capacite(), 5);
			assertTrue(C.estVide());
		}
		catch (Exception e) {
			fail();
			// on force le test a echouer si une exception est levee
		}
	}
}
