# -------------- #
# -- Makefile -- #
# -------------- #

OBJ = contourNR.o filterNR.o gauss.o histogramNR.o lutNR.o main.o morphoNR.o mutil.o noise.o nrutil.o random.o test.o test_contourNR.o test_filterNR.o test_morphoNR.o
HEADER = contourNR.h def.h filterNR.h gauss.h histogramNR.h lutNR.h morphoNR.h mutil.h my_paths.h noise.h nrutil.h random.h test.h test_contourNR.h test_filterNR.h test_morphoNR.h

tp: $(OBJ) $(HEADER)
	gcc -o tp $(OBJ) -lm

contourNR.o: contourNR.c $(HEADER)
	gcc -c contourNR.c

filterNR.o: filterNR.c $(HEADER)
	gcc -c filterNR.c

gauss.o: gauss.c $(HEADER)
	gcc -c gauss.c

histogramNR.o: histogramNR.c $(HEADER)
	gcc -c histogramNR.c

lutNR.o: lutNR.c $(HEADER)
	gcc -c lutNR.c

main.o: main.c $(HEADER)
	gcc -c main.c

morphoNR.o: morphoNR.c $(HEADER)
	gcc -c morphoNR.c

mutil.o: mutil.c $(HEADER)
	gcc -c mutil.c

noise.o: noise.c $(HEADER)
	gcc -c noise.c

nrutil.o: nrutil.c $(HEADER)
	gcc -c nrutil.c

random.o: random.c $(HEADER)
	gcc -c random.c

test.o: test.c $(HEADER)
	gcc -c test.c

test_contourNR.o: test_contourNR.c $(HEADER)
	gcc -c test_contourNR.c

test_filterNR.o: test_filterNR.c $(HEADER)
	gcc -c test_filterNR.c

test_morphoNR.o: test_morphoNR.c $(HEADER)
	gcc -c test_morphoNR.c

clean:
	rm -f $(OBJ)
	rm -f tp
