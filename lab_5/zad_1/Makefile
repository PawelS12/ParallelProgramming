# Kompilator C
CCOMP = gcc

# Konsolidator
LOADER = gcc

# Opcje optymalizacji
# Wersja do debugowania
# OPT = -g -DDEBUG
# Wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -fopenmp

# Pliki nagłówkowe
INC = -I./include

# Biblioteki
LIB = -lm -lpthread

# Główne reguły
pthreads_suma: pthreads_suma.o lib/pomiar_czasu.o
	$(LOADER) $(OPT) pthreads_suma.o lib/pomiar_czasu.o -o pthreads_suma $(LIB)

# Kompilacja pliku pthreads_suma.o
pthreads_suma.o: pthreads_suma.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) pthreads_suma.c $(INC) 

# Kompilacja pliku lib/pomiar_czasu.o
lib/pomiar_czasu.o: lib/pomiar_czasu.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) lib/pomiar_czasu.c -o lib/pomiar_czasu.o $(INC)

# Czyszczenie plików obiektowych i wynikowych
clean:
	rm -f pthreads_suma.o lib/pomiar_czasu.o pthreads_suma

