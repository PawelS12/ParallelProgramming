#include <pthread.h>
#include <stdio.h>

static int liczba_watkow;       
static int licznik = 0;
static pthread_mutex_t muteks;  
static pthread_cond_t warunek;  

void bariera_init(int n) {
    liczba_watkow = n; 
    licznik = 0;     
    pthread_mutex_init(&muteks, NULL); 
    pthread_cond_init(&warunek, NULL);
}

void bariera(void) {
    static int generacja = 0; 
    int moja_generacja;

    pthread_mutex_lock(&muteks);

    moja_generacja = generacja; 
    licznik++;

    if (licznik == liczba_watkow) {
        licznik = 0;       
        generacja++;      
        pthread_cond_broadcast(&warunek); 
    } else {
        while (moja_generacja == generacja) {
            pthread_cond_wait(&warunek, &muteks);
        }
    }

    pthread_mutex_unlock(&muteks);
}
