#include "czytelnia.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(cz_t* cz_p) {
    cz_p->l_c++;
    return 0;
}

int my_read_lock_unlock(cz_t* cz_p) {
    cz_p->l_c--;
    return 0;
}

int my_write_lock_lock(cz_t* cz_p) {
    cz_p->l_p++;
    return 0;
}

int my_write_lock_unlock(cz_t* cz_p) {
    cz_p->l_p--;
    return 0;
}

void inicjuj(cz_t* cz_p) {
    cz_p->l_p = 0;
    cz_p->l_c = 0;
}

void czytam(cz_t* cz_p) {
#ifdef MY_DEBUG
    printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);

    if (cz_p->l_p > 0 || cz_p->l_p < 0 || cz_p->l_c < 0) {
        printf("Blad: Niepoprawna liczba czytelnikow lub pisarzy. l_c=%d, l_p=%d\n", cz_p->l_c, cz_p->l_p);
        exit(0);
    }
#endif
    usleep(rand() % 3000000);
}

void pisze(cz_t* cz_p) {
#ifdef MY_DEBUG
    printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);

    if (cz_p->l_p > 1 || cz_p->l_c > 0 || cz_p->l_p < 0 || cz_p->l_c < 0) {
        printf("Blad: Niepoprawna liczba czytelnikow lub pisarzy. l_c=%d, l_p=%d\n", cz_p->l_c, cz_p->l_p);
        exit(0);
    }
#endif
    usleep(rand() % 3000000);
}
