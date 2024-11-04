#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include<math.h>

double funkcja ( double x );

typedef struct {
    int my_id;
    double a_local; 
    double b_local; 
    double dx;  
    double wynik;  
} Podobszar;

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w){
  double zakres_watku = (b - a) / l_w;
  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości
  Podobszar* podobszary = (Podobszar*)malloc(l_w * sizeof(Podobszar));
  pthread_t threads[l_w];

  // tworzenie wątków
  for (int i = 0; i < l_w; i++) {
        podobszary[i].my_id = i;
        podobszary[i].a_local = a + i * zakres_watku;
        if (i == l_w - 1) {
            podobszary[i].b_local = b; 
        } else {
            podobszary[i].b_local = podobszary[i].a_local + zakres_watku;
        }
        podobszary[i].dx = dx;
        podobszary[i].wynik = 0.0;

        pthread_create(&threads[i], NULL, calka_podobszar_w, (void*)&podobszary[i]);
    }

  // oczekiwanie na zakończenie pracy wątków
  for (int i = 0; i < l_w; i++) {
        pthread_join(threads[i], NULL);
        calka_suma_local += podobszary[i].wynik;
    }
    
  free(podobszary);
  return(calka_suma_local);
}

void* calka_podobszar_w(void* arg_wsk){

  // rozpakowanie danych przesłanych do wątku
  Podobszar* podobszar = (Podobszar*)arg_wsk;
   printf("\nWątek %d: a_local = %lf, b_local = %lf, dx = %lf\n", podobszar->my_id, podobszar->a_local, podobszar->b_local, podobszar->dx);
           
  // Obliczenie liczby trapezów w podprzedziale i dostosowanie dx
  int N_local = ceil((podobszar->b_local - podobszar->a_local) / podobszar->dx);
  double dx_adjust_local = (podobszar->b_local - podobszar->a_local) / N_local;
  
  double calka = 0.0;
  for (int i = 0; i < N_local; i++) {
      double x1 = podobszar->a_local + i * dx_adjust_local;
      calka += 0.5 * dx_adjust_local * (funkcja(x1) + funkcja(x1 + dx_adjust_local));
  }

  // Zapisanie wyniku całki w strukturze
  podobszar->wynik = calka;

    return NULL;
}
