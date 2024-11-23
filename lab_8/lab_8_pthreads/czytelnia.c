#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include"czytelnia.h"

#ifdef MY_DEBUG
#define DEBUG_PRINT(fmt, args...) printf(fmt, ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

/*** Implementacja procedur interfejsu ***/
int my_read_lock_lock(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Czekaj, jeśli pisarz pisze
    while (cz_p->l_p > 0) {
        pthread_cond_wait(&cz_p->can_read, &cz_p->mutex);
    }

    cz_p->l_c++; // Zwiększamy liczbę czytających

    pthread_mutex_unlock(&cz_p->mutex);
    return 0;
}

int my_read_lock_unlock(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);
    
    cz_p->l_c--; // Zmniejszamy liczbę czytających

    // Jeśli nie ma już czytających, to sygnalizujemy pisarzowi, że może zacząć pisać
    if (cz_p->l_c == 0) {
        pthread_cond_signal(&cz_p->can_write);
    }

    pthread_mutex_unlock(&cz_p->mutex);
    return 0;
}

int my_write_lock_lock(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Czekaj, aż nie będzie czytelników ani innych pisarzy
    while (cz_p->l_c > 0 || cz_p->l_p > 0) {
        pthread_cond_wait(&cz_p->can_write, &cz_p->mutex);
    }

    cz_p->l_p++; // Zwiększamy liczbę piszących

    pthread_mutex_unlock(&cz_p->mutex);
    return 0;
}

int my_write_lock_unlock(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    cz_p->l_p--; // Zmniejszamy liczbę piszących

    // Po zakończeniu pisania sygnalizujemy czytelnikom i innym pisarzom
    pthread_cond_broadcast(&cz_p->can_read);
    pthread_cond_signal(&cz_p->can_write);

    pthread_mutex_unlock(&cz_p->mutex);
    return 0;
}

void inicjuj(cz_t* cz_p) {
    cz_p->l_p = 0;
    cz_p->l_c = 0;
    pthread_mutex_init(&cz_p->mutex, NULL);
    pthread_cond_init(&cz_p->can_read, NULL);
    pthread_cond_init(&cz_p->can_write, NULL);
}

void czytam(cz_t* cz_p) {
    DEBUG_PRINT("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
    
    // Sprawdzenie warunków poprawności
    //if (cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0) || cz_p->l_p < 0 || cz_p->l_c < 0) {
        //printf("Blad: Niepoprawna liczba czytelników (%d) lub pisarzy (%d)\n", cz_p->l_c, cz_p->l_p);
      //  exit(0);
    //}

    usleep(rand() % 3000000);
}

void pisze(cz_t* cz_p) {
    DEBUG_PRINT("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
    
    // Sprawdzenie warunków poprawności
    // if (cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0) || cz_p->l_p < 0 || cz_p->l_c < 0) {
      //  printf("Blad: Niepoprawna liczba czytelników (%d) lub pisarzy (%d)\n", cz_p->l_c, cz_p->l_p);
      //  exit(0);
    //}

    usleep(rand() % 3000000);
}
