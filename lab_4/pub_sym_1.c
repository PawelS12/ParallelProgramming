#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ILE_MUSZE_WYPIC 33

int aktualna_l_kf; 
pthread_mutex_t mutex_kufle;

void do_something_else(int klient_id) {
    printf("\nKlient %d, czeka na kufel...\n", klient_id);
    usleep(50000); 
}

void *watek_klient(void *arg_wsk) {
    int moj_id = *((int *)arg_wsk);
    int i;

    printf("\nKlient %d, wchodzę do pubu\n", moj_id); 

    for (i = 0; i < ILE_MUSZE_WYPIC; i++) {
        printf("\nKlient %d, wybieram kufel\n", moj_id);

        // sekcja krytyczna | busy waiting
        int success = 0;
        do {
            pthread_mutex_lock(&mutex_kufle); 
            if (aktualna_l_kf > 0) {
                aktualna_l_kf--; 
                printf("\nKlient %d, pobrał kufel, pozostało kufli: %d\n", moj_id, aktualna_l_kf);
                success = 1; 
            }
            pthread_mutex_unlock(&mutex_kufle); 

            if (success == 0) {
                do_something_else(moj_id);
            }
        } while (success == 0);

        // Nalewanie z kranu
        printf("\nKlient %d, nalewam z kranu\n", moj_id);
        usleep(30000);

        // Picie piwa
        printf("\nKlient %d, pije\n", moj_id);
        nanosleep((struct timespec[]){{0, 50000000L}}, NULL);

        // Odłożenie kufla (bez synchronizacji)
        pthread_mutex_lock(&mutex_kufle);
        aktualna_l_kf++; 
        printf("\nKlient %d, odłożył kufel, dostępne kufle: %d\n", moj_id, aktualna_l_kf);
        pthread_mutex_unlock(&mutex_kufle);
    }

    printf("\nKlient %d, wychodzę z pubu\n", moj_id);

    return NULL;
}

int main(void) {
    pthread_t *tab_klient;
    int *tab_klient_id;

    int l_kl, poczatkowa_l_kf, i;

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: ");
    scanf("%d", &aktualna_l_kf);
    poczatkowa_l_kf = aktualna_l_kf;
    
    pthread_mutex_init(&mutex_kufle, NULL);

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++) {
        tab_klient_id[i] = i;
    }

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli %d\n", aktualna_l_kf);

    // Tworzenie wątków-klientów
    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }

    // Oczekiwanie na zakończenie pracy wątków
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }

    printf("\nZamykamy pub!\n");

    // Sprawdzenie końcowej liczby kufli
    if (aktualna_l_kf != poczatkowa_l_kf) {
        printf("\nBłąd: końcowa liczba kufli (%d) różni się od początkowej (%d)!\n", aktualna_l_kf, poczatkowa_l_kf);
    } else {
        printf("\nKońcowa liczba kufli (%d) rowna sie początkowej (%d)!\n", aktualna_l_kf, poczatkowa_l_kf);
    }

    pthread_mutex_destroy(&mutex_kufle);
    free(tab_klient);
    free(tab_klient_id);

    return 0;
}
