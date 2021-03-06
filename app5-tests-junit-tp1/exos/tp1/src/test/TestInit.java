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
	// Objectif de test : creation d'un conteneur de capacite 0
	// Resultat attendu : conteneur ne se cré pas et une exception est lancée
	@Test
	public void capacite0Fail() {
		try {
			C = new Conteneur(0);
			fail();
		} catch (ErreurConteneur e) {
			// si une exception de type ErreurConteneur est levee, le test reussit
			// on verifie que le conteneur n'a pas ete modifie
			assertEquals(C, null);
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : creation d'un conteneur de capacite négative
	// Resultat attendu : conteneur ne se cré pas et une exception est lancée
	@Test
	public void capaciteNegFail() {
		try {
			C = new Conteneur(-5);
			fail();
		}
		catch (Exception e) {
		}
	}
}
