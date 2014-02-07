public class TestRArray {

  // Objectif de test : creation d'un RArray vide de taille n strictement positive
  // Resultat attendu : RArray vide de taille n cree
  public static void testInitVide() {
    // RArray a = new RArray(-10);
    // RArray b = new RArray(-1);
    // RArray c = new RArray(0);
    RArray d = new RArray(1);
    RArray e = new RArray(10);
    RArray f = new RArray(100);
  }

  // test when size given is the same size 
  public static void testInitWithArraySimple(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    Object[] array = {obj1, obj2, obj3};
    RArray d = new RArray(array,3); 
  }

  // test when size given is bigger than array given
  public static void testInitWithArraySimple2(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    Object[] array = {obj1, obj2, obj3};
    RArray d = new RArray(array,10); 
  }

  // test when size given is smaller than array given
  public static void testInitWithArrayComplex(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    Object[] array = {obj1, obj2, obj3};
    RArray d = new RArray(array,2); 
  }

  public static void testScenarioSimple() {
    Object obj1 = new Object();
    Object obj2 = new Object();
    RArray a = new RArray(100);
    a.add(obj1);
    a.add(obj2);
  }

  public static void testScenarioDuplicates() {
    Object obj1 = new Object();
    RArray a = new RArray(10);
    a.add(obj1);
    a.add(obj1);
  }

  public static void testScenarioResize() {
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    Object obj4 = new Object();
    RArray a = new RArray(10);
    a.add(obj1);
    a.add(obj2);
    a.resize(20);
    a.add(obj3);
    a.add(obj4);
  }

  // resize while still empty
  public static void testScenarioResizeEmpty() {
    RArray a = new RArray(2);
    a.resize(3);
    a.resize(5);
    a.resize(15);
  }
  // resize when cap limit reached
  public static void testScenarioResizeAtCap() {
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    Object obj4 = new Object();
    Object obj5 = new Object();
    RArray a = new RArray(2);
    a.add(obj1);
    a.add(obj2);
    a.resize(20);
    a.add(obj1);
  }
  public static void testScenarioClear(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    Object obj3 = new Object();
    RArray a = new RArray(2);
    a.add(obj1);
    a.add(obj1);
    a.clear();
    a.add(obj1);
    a.add(obj2);
    a.clear();
    a.add(obj3);
  }

  public static void testScenarioAddRemoveCheckIndex(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    RArray a = new RArray(2);
    a.add(obj1);
    int idx = a.index(obj1);
    a.remove(obj1);
    int noidx = a.index(obj1);
  }

  public static void testScenarioAddCheckIndexRemoveCheckIndec(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    RArray a = new RArray(2);
    a.add(obj1);
    int idx = a.index(obj1);
    a.removeInd(idx);
    int noidx = a.index(obj1);
  }

  public static void testScenarioReplace(){
    Object obj1 = new Object();
    Object obj2 = new Object();
    RArray a = new RArray(2);
    a.add(obj1);
    a.replace(obj2,0);
  }

  public static void main(String[] args) {
    testInitVide();
    testInitWithArraySimple();
    testInitWithArraySimple2();
    testInitWithArrayComplex();
    testScenarioSimple();
    testScenarioDuplicates();
    testScenarioResize();
    testScenarioResizeAtCap();
    testScenarioAddCheckIndexRemoveCheckIndec();
    testScenarioAddRemoveCheckIndex();
    testScenarioReplace();
    testScenarioClear();
  }

}