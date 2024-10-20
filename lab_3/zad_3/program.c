#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define LICZBA_WATKOW 4

typedef struct {
    double in;
    double out;
    double wynik;
} struktura;

void * tworzenie_watkow (void * arg_wsk) {  
    struktura * dane = (struktura *)arg_wsk;
    dane->wynik = (dane->in + dane->out) / 2.0;
    
    return NULL;
}

int main() {
    pthread_t watki[LICZBA_WATKOW];
    struktura tab[LICZBA_WATKOW];
    double a = -5.0, b = 5.0;
    double suma = 0;
    double fragment = (b - a) / LICZBA_WATKOW;
    
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        tab[i].in = a + i * fragment;
        tab[i].out = a + (i + 1) * fragment;
        
        pthread_create(&watki[i], NULL, tworzenie_watkow, (void *)&tab[i]);
    }
    
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        pthread_join(watki[i], NULL);
    }
    
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        suma += tab[i].wynik;
    }
    
    printf("Suma: %.3f\n", suma);
}
