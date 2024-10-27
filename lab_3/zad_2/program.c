#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define LICZBA_WATKOW 10

void *zadanie_watku(void *arg_wsk) {
    int id_watku = *((int *)arg_wsk);
    printf("Watek systemowy: %d | ID = %lu\n", id_watku, pthread_self());

    free(arg_wsk);
    pthread_exit(NULL);
}

int main() {
    pthread_t watki[LICZBA_WATKOW];

    for (int i = 0; i < LICZBA_WATKOW; i++) {
        int *id = malloc(sizeof(int)); 
        *id = i;
        pthread_create(&watki[i], NULL, zadanie_watku, id);
        //id = i; 
        //pthread_create(&watki[i], NULL, zadanie_watku, &id);
    }

    for (int i = 0; i < LICZBA_WATKOW; i++) {
        pthread_join(watki[i], NULL);
    }

    return 0;
}