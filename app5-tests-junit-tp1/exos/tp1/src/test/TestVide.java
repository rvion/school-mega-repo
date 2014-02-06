package test;

import testEtat.*;

import org.junit.*;

import static org.junit.Assert.*;

public class TestVide {

	private Conteneur C;

	// Creation d'un conteneur vide	
	@Before
	public void creerConteneurVide() {
		try {
			C = new Conteneur(10);
		} catch (Exception e) {
			fail();
		}
	}
	// Objectif de test : ajout d'un element dans un container vide
	// Resultat attendu : ajout possible et noveau couple clé valeur
	@Test
	public void ajouterVide() {
		try {
			Object A = new Object();
			Object B = new Object();
			C.ajouter(A, B);

			assertTrue(C.present(A));
			assertEquals(C.valeur(A), B);
			assertEquals(C.taille(), 1);
			assertEquals(C.capacite(), 10);
		}
		catch (Exception e) {
			fail();
		}
	}

	// Objectif de test : vérifier que estVide retourne vrai quand conteneur vide
	// Resultat attendu : estVide retourne vrai
	@Test
	public void estVideQuandVide() {
		try {
			assertTrue(C.estVide());
		}
		catch (Exception e) {
			fail();
		}
	}
	
	// Objectif de test : remise a zero d'un conteneur vide
	// Resultat attendu : remise a zero impossible, levee de l'exception ErreurConteneur
	@Test
	public void razVide() {
		try {
			C.raz();
			fail();
			// on force le test a echouer si aucune exception n'est levee
		} catch (ErreurConteneur e) {
			// si une exception de type ErreurConteneur est levee, le test reussit
			// on verifie que le conteneur n'a pas ete modifie
			assertEquals(C.taille(), 0);
			assertEquals(C.capacite(), 10);
			assertTrue(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	
	// Objectif de test : enlever un objet qui n'existe pas dans un container vide
	// Resultat attendu : rien ne se passe
	@Test
	public void removeFromVide() {
		try {
			Object A = new Object();
			C.retirer(A);
			assertEquals(C.taille(), 0);
			assertEquals(C.capacite(), 10);
			assertTrue(C.estVide());
			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}

}
