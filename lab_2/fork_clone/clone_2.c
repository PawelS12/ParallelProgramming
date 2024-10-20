#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna = 0; 

#define ROZMIAR_STOSU 1024*64

int funkcja_watku(void* argument) {
    int* zmienna_lokalna = (int*) argument;

    for (int i = 0; i < 100000; i++) {
        zmienna_globalna++;
        (*zmienna_lokalna)++;
    }

    return 0;
}

int main() {
    void* stos;
    void* stos2;
    pid_t pid1, pid2;
    int lokalna1 = 0; 
    int lokalna2 = 0; 
    
    stos = malloc(ROZMIAR_STOSU);
    if (stos == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit(1);
    }
    
    stos2 = malloc(ROZMIAR_STOSU);
    if (stos2 == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit(1);
    }

    inicjuj_czas(); 

    pid1 = clone(&funkcja_watku, (void*)stos + ROZMIAR_STOSU, 
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &lokalna1);

    pid2 = clone(&funkcja_watku, (void*)stos2 + ROZMIAR_STOSU, 
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &lokalna2);

    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    drukuj_czas();

    printf("Wartosc zmiennej globalnej: %d\n", zmienna_globalna);
    printf("Wartosc zmiennej lokalnej 1: %d\n", lokalna1);
    printf("Wartosc zmiennej lokalnej 2: %d\n", lokalna2);

    free(stos); 
    free(stos2);
    
    return 0;
}
