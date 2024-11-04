# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -Wno-unused-result

# pliki naglowkowe
INC = -I./include -I.

# biblioteki
LIB = -L./lib -L. -lm -lpthread

# zaleznosci i komendy


all: clean obliczanie_calki

obliczanie_calki: obliczanie_calki.o dekompozycja_petli.o dekompozycja_obszaru.o lib/pomiar_czasu.o
	$(LOADER) $(OPT) obliczanie_calki.o lib/pomiar_czasu.o dekompozycja_petli.o dekompozycja_obszaru.o -o obliczanie_calki $(LIB)

obliczanie_calki.o: obliczanie_calki.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) obliczanie_calki.c $(INC) 

dekompozycja_petli.o: dekompozycja_petli.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) dekompozycja_petli.c $(INC) 

dekompozycja_obszaru.o: dekompozycja_obszaru.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) dekompozycja_obszaru.c $(INC) 
	
lib/pomiar_czasu.o: lib/pomiar_czasu.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) lib/pomiar_czasu.c -o lib/pomiar_czasu.o $(INC)
	
clean:
	rm -f *.o obliczanie_calki
