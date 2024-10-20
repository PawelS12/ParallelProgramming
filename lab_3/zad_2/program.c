#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define LICZBA_WATKOW 10

void * zadanie_watku (void * arg_wsk) {
    int id_watku = *((int *)arg_wsk);
    printf("Watek systemowy: %d | ID = %lu\n", id_watku, pthread_self());
    
    pthread_exit(NULL);
}

int main() {
    pthread_t watki[LICZBA_WATKOW];
    int id[LICZBA_WATKOW];

    for (int i = 0; i < LICZBA_WATKOW; i++) {
        id[i] = i;
        pthread_create(&watki[i], NULL, zadanie_watku, &id[i]);
        // pthread_create(&watki[i], NULL, zadanie_watku, &i); - niepoprawnie
        // ta sama zmienna i dla wszystkich wątków przez co gdy dany wątek ją odczytuje może ona już mieć inną wartość
    }
    
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        pthread_join(watki[i], NULL);
    }
    
}
