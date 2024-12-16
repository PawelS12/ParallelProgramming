#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
    int rank;     // ID
    int ranksent; // zmienna do danych odebranych
    int size;     // liczba procesów w komunikatorze
    int source;   // ID procesu źródła
    int dest;     // ID procesu docelowego
    int tag;      // tag wiadomości
    int i;  
    MPI_Status status;  //  struktura MPI używana do przechowywania informacji o odebranej wiadomości
    
    char hostname[256];     // Nazwa hosta bieżącego procesu
    char hostname_recv[256]; // Nazwa hosta odbierana przez proces 0

    MPI_Init( &argc, &argv ); // inicjalizuje środowisko MPI i uruchamia procesy
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // pobiera rangę (ID) bieżącego procesu w komunikatorze
    MPI_Comm_size( MPI_COMM_WORLD, &size ); // zwraca liczbę procesów w komunikatorze

    gethostname(hostname, 256);
    
    if(size > 1){
      
      if( rank != 0 ){ 
          dest=0; 
          tag=0; 
          MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD ); // wysyłanie do prcesu 0
          MPI_Send( hostname, 256, MPI_CHAR, dest, tag, MPI_COMM_WORLD ); // wysyłąnie nazwy hosta
      } else {
          for( i=1; i<size; i++ ) {   
              MPI_Recv( &ranksent, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status ); // odbieranie od reszty procesów
              MPI_Recv( hostname_recv, 256, MPI_CHAR, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status ); // odbieranie nazwy

              printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: %d, host: %s (i=%d)\n", status.MPI_SOURCE, ranksent, hostname_recv, i );
          }
      }
    } else{
        printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
    }

    MPI_Finalize(); 
    return(0);
}