#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"pomiar_czasu.h"
 
const int liczba = 100000;
// const int liczba = 10000000;

void inicjuj_czas();
double czas_C();
double czas_zegara();
double czas_CPU();

int main(){

  double a, b, c;
  int i,j,k,l;

  k = -50000;
  
  #ifdef POMIAR_CZASU
  double t1, t2;
  inicjuj_czas();
  #endif

  for(i=0;i<liczba;i++){

    printf("%d ",k+i);

  }
  printf("\n");
  printf("\n");
  
  #ifdef POMIAR_CZASU
  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",liczba);
  drukuj_czas();
  #endif

  a = 1.000001;
  
  #ifdef POMIAR_CZASU
  t1 = czas_zegara();
  t2 = czas_CPU();
  #endif
  
  for(i=0;i<liczba;i++){

    a = 1.000001*a+0.000001; 

  }
  
  #ifdef POMIAR_CZASU
  t1 = czas_zegara() - t1;
  t2 = czas_CPU() -t2;
  printf("\n");
  printf("Czas wykonania %d operacji arytmetycznych: \n",liczba);
  printf("Czas zegara: %lf\n", t1);
  printf("Czas CPU: %lf\n", t2);
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  #endif

  return 0;
}
