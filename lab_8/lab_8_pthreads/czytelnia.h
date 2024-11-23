#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typów zmiennych ***/
typedef struct {
  int l_p; // liczba piszących
  int l_c; // liczba czytających
  pthread_mutex_t mutex; // mutex do wzajemnego wykluczania
  pthread_cond_t can_read;
  pthread_cond_t can_write;
} cz_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(cz_t* czytelnia_p);
void czytam(cz_t* czytelnia_p);
void pisze(cz_t* czytelnia_p);

int my_read_lock_lock(cz_t* czytelnia_p);
int my_read_lock_unlock(cz_t* czytelnia_p);
int my_write_lock_lock(cz_t* czytelnia_p);
int my_write_lock_unlock(cz_t* czytelnia_p);

#endif
