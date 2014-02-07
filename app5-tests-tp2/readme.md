# App5 - Test Logiciel - Rémi Vion

## implemetation 1 :

    pas d'erreur trouvée

## implemetation 2 :

    Exception in thread "main" org.jmlspecs.jmlrac.runtime.JMLInvariantError: by method RArray.clear@post<File "RArray.refines-java", line 28, character 13>
        at RArray.checkInv$instance$RArray(RArray.refines-java:358)
        at RArray.clear(RArray.refines-java:803)
        at TestRArray.testScenarioClear(TestRArray.java:96)
        at TestRArray.main(TestRArray.java:143)

## implemetation 3 :

    pas d'erreur trouvée

## implemetation 4 :

    pas d'erreur trouvée

## implemetation 5 :

    pas d'erreur trouvée

## implemetation 6 :

    Exception in thread "main" org.jmlspecs.jmlrac.runtime.JMLInvariantError: by method RArray.removeInd@post<File "RArray.refines-java", line 73, character 13>
        at RArray.checkInv$instance$RArray(RArray.refines-java:359)
        at RArray.removeInd(RArray.refines-java:2274)
        at TestRArray.testScenarioAddCheckIndexRemoveCheckIndec(TestRArray.java:119)
        at TestRArray.main(TestRArray.java:140)
