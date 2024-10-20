# kompilator c || definicja kompilatora, który ma być użyty 
CCOMP = gcc

# konsolidator || ustawienia linkera, który łączy pliki obiektowe aby stworzyć plik wykonywalny
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania || opcje do debugowania
# OPT = -g -DDEBUG -DPOMIAR_CZASU 
# wersja zoptymalizowana do mierzenia czasu || wersja zoptymalizowana, -O3 to wysoki poziom optymalizaji, natomiast DPOMIAR_CZASU to zdefiniowanie makra preprocesora
 OPT = -O3 -DPOMIAR_CZASU

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy || definicja głównego celu, używa linkera LOADER z opcją OPT aby z plików obiektowych stworzyć plik wykonywalny
moj_program: moj_program.o pomiar_czasu.o
	$(LOADER) $(OPT) moj_program.o pomiar_czasu.o -o moj_program $(LIB)

# jak uzyskac plik moj_program.o ? || definicja jak stworzyć plik moj_program.o, wymaga plików źródłowych .c i .h, używa kompilatora CCOMP do kompilacji z opcja OPT, tworząc plik obiektowy moj_program.o
moj_program.o: moj_program.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) moj_program.c

# to samo tylko dla pliku pomiar czasu
pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

# definicja clean który usuwa wszystkie pliku obiektowe oraz plik wykonywalny
clean:
	rm -f *.o moj_program
	

