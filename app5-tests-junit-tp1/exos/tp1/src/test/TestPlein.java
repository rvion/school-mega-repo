package test;

import testEtat.*;

import org.junit.*;

import static org.junit.Assert.*;

public class TestPlein {

	private Conteneur C;
	private Object A1, A2, A3, A4, A5, B1, B2, B3, B4, B5;

	// Creation d'un conteneur plein
	@Before
	public void creerConteneurPlein() {
		try  {
			C = new Conteneur(5);
			A1 = new Object();
			A2 = new Object();
			A3 = new Object();
			A4 = new Object();
			A5 = new Object();
			B1 = new Object();
			B2 = new Object();
			B3 = new Object();
			B4 = new Object();
			B5 = new Object();
			C.ajouter(A1, B1);
			C.ajouter(A2, B2);
			C.ajouter(A3, B3);
			C.ajouter(A4, B4);
			C.ajouter(A5, B5);
		} catch (Exception e) {
			fail();
		}
	}

	// Objectif de test : vérifier que estVide retourne false quand conteneur plein
	// Resultat attendu : estVide retourne false
	@Test
	public void estVideQuandVide() {
		try {
			assertFalse(C.estVide());
		}
		catch (Exception e) {
			fail();
		}
	}

	// Objectif de test : ajout d'un element dont la cle est deja presente dans un conteneur plein
	// Resultat attendu : ajout possible et ancien couple de meme cle ecrase
	@Test
	public void ajouterPresentPlein() {
		try {
			Object B = new Object();
			C.ajouter(A2, B);

			assertTrue(C.present(A2));
			assertEquals(C.valeur(A2), B);
			assertEquals(C.taille(), 5);
			assertEquals(C.capacite(), 5);
		}
		catch (Exception e) {
			fail();
		}
	}
	// Objectif de test : ajout d'un element dont la cle n'est pas deja presente dans un conteneur plein	
	// Resultat attendu : ajout impossible, levée de l'exception DebordementConteneur
	@Test
	public void ajouterAbsentPlein() {
		try {
			Object B = new Object();
			Object A = new Object();
			C.ajouter(A, B);
			fail();
		} catch (DebordementConteneur e) {
			// si une exception de type ErreurConteneur est levee, le test reussit
			// on verifie que le conteneur n'a pas ete modifie
			assertEquals(C.taille(), 5);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : redimentionner un container plein
	// Resultat attendu : redimensionne un container en préservant ses valeurs
	@Test
	public void resizePlein() {
		try {
			C.redimensionner(20);
			assertEquals(C.taille(), 5);
			assertEquals(C.capacite(), 20);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertTrue(C.present(A2));
			assertTrue(C.present(A3));
			assertTrue(C.present(A4));
			assertTrue(C.present(A5));
			assertEquals(C.valeur(A1), B1);
			assertEquals(C.valeur(A2), B2);
			assertEquals(C.valeur(A3), B3);
			assertEquals(C.valeur(A4), B4);
			assertEquals(C.valeur(A5), B5);

			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : remise a zero d'un conteneur plein
	// Resultat attendu : remise a zero possible
	@Test
	public void razPlein() {
		try {
			C.raz();
			// on verifie que le conteneur n'a pas ete modifie
			assertEquals(C.taille(), 0);
			assertEquals(C.capacite(), 5);
			assertTrue(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : enlever un objet qui n'existe pas dans un container plein
	// Resultat attendu : rien ne se passe
	@Test
	public void removeNonExistantFromPlein() {
		try {
			Object A = new Object();
			C.retirer(A);
			assertEquals(C.taille(), 5);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertTrue(C.present(A2));
			assertTrue(C.present(A3));
			assertTrue(C.present(A4));
			assertTrue(C.present(A5));
			assertEquals(C.valeur(A1), B1);
			assertEquals(C.valeur(A2), B2);
			assertEquals(C.valeur(A3), B3);
			assertEquals(C.valeur(A4), B4);
			assertEquals(C.valeur(A5), B5);

			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : enlever un objet qui existe dans un container ni plein, ni vide
	// Resultat attendu : rien ne se passe
	@Test
	public void removeExistantFromPlein() {
		try {
			assertEquals(C.taille(), 5);
			assertEquals(C.capacite(), 5);
			C.retirer(A2);
			assertEquals(C.taille(), 4);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertFalse(C.present(A2));
			assertTrue(C.present(A3));
			assertTrue(C.present(A4));
			assertTrue(C.present(A5));
			assertEquals(C.valeur(A1), B1);
			assertEquals(C.valeur(A3), B3);
			assertEquals(C.valeur(A4), B4);
			assertEquals(C.valeur(A5), B5);
			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
}
