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
	
	// Objectif de test : vérifier que estVide retourne false quand conteneur ni plein, ni vide
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
	// Objectif de test : ajout d'un element dont la cle n'est pas deja presente dans un conteneur non plein
	// Resultat attendu : ajout possible
	@Test
	public void ajouterAbsentNonPlein() {
		try {
			Object B = new Object();
			Object A = new Object();
			C.ajouter(A, B);
			assertEquals(C.capacite(), 5);
			assertEquals(C.taille(), 3);
			assertFalse(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : ajout d'un element présent dans un conteneur non plein
	// Resultat attendu : ajout possible, ecrase la valeur précédente
	@Test
	public void ajouterPrésentNonPlein() {
		try {
			assertEquals(C.valeur(A1), B1);
			Object B = new Object();
			C.ajouter(A1, B);
			assertEquals(C.valeur(A1), B);
			assertEquals(C.taille(), 2);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : ajout des elements dont la valeur est deja presente associé à des clef non présentes
	// Resultat attendu : ajout possible
	@Test
	public void ajouterValPrésentsNonPlein() {
		try {
			Object Ax = new Object();
			Object Ay = new Object();
			C.ajouter(Ax, B1);
			C.ajouter(Ay, B1);
			assertFalse(C.estVide());
			assertEquals(C.taille(), 4);
			assertEquals(C.capacite(), 5);
			assertTrue(C.present(A1));
			assertTrue(C.present(Ax));
			assertTrue(C.present(Ay));
			assertEquals(C.valeur(A1), B1);
			assertEquals(C.valeur(Ax), B1);
			assertEquals(C.valeur(Ay), B1);

		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : redimentionner un container ni vide, ni plein
	// Resultat attendu : levee de l'exception ErreurConteneur
	@Test
	public void resizeNonVide() {
		try {
			C.redimensionner(20);
			fail();
			// on force le test a echouer si aucune exception n'est levee
		} catch (ErreurConteneur e) {
			// si une exception de type ErreurConteneur est levee, le test reussit
			// on verifie que le conteneur n'a pas ete modifie
			assertEquals(C.taille(), 2);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : remise a zero d'un conteneur ni plein, ni vide
	// Resultat attendu : remise a zero possible
	@Test
	public void razNonVide() {
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
	// Objectif de test : enlever un objet qui n'existe pas dans un container ni plein, ni vide
	// Resultat attendu : rien ne se passe
	@Test
	public void removeNonExistantFromNonPlein() {
		try {
			Object A = new Object();
			C.retirer(A);
			assertEquals(C.taille(), 2);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertTrue(C.present(A2));
			assertEquals(C.valeur(A1), B1);
			assertEquals(C.valeur(A2), B2);

			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}

	// Objectif de test : enlever un objet qui existe dans un container ni plein, ni vide
	// Resultat attendu : rien ne se passe
	@Test
	public void removeExistantFromNonPlein() {
		try {
			try	{
				assertEquals(C.taille(), 2);
			} catch (Exception e) {
				fail();
			}
			
			try	{
				C.retirer(A2);
			} catch (Exception e) {
				fail();
			}
			assertEquals(C.taille(), 1);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertFalse(C.present(A2));
			assertEquals(C.valeur(A1), B1);

			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
	// Objectif de test : recherche un objet qui n'existe pas
	// Resultat attendu : erreur
	@Test
	public void SearchNonExistantFromNonPlein() {
		try {
			Object Y = new Object();
			assertEquals(C.taille(), 2);
			Object X = C.valeur(Y);
			fail();
		} catch (ErreurConteneur e) {
			assertEquals(C.taille(), 2);
			assertEquals(C.capacite(), 5);
			assertFalse(C.estVide());
			assertTrue(C.present(A1));
			assertTrue(C.present(A2));
			// on force le test a echouer si aucune exception n'est levee
		} catch (Exception e) {
			fail();
			// si une exception d'un autre type est levee, le test echoue 
		}
	}
}
