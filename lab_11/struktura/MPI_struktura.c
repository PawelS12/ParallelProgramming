#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

typedef struct {
    char name[20];    
    int age;                   
    float height;            
} Person;

int main(int argc, char** argv) {
    int rank, size, prev, next;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    prev = (rank - 1 + size) % size; 
    next = (rank + 1) % size;        

    Person person;

    int buffer_size;
    MPI_Pack_size(20, MPI_CHAR, MPI_COMM_WORLD, &buffer_size);
    int name_size = buffer_size;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &buffer_size);
    int age_size = buffer_size;
    MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &buffer_size);
    int height_size = buffer_size;

    buffer_size = name_size + age_size + height_size;
    char* buffer = (char*)malloc(buffer_size);

    if (rank == 0) {
        snprintf(person.name, 21, "Paweł");
        person.age = 21;
        person.height = 183.0f;

        printf("Proces %d inicjuje dane: name=%s, age=%d, height=%.2f\n", rank, person.name, person.age, person.height);

        int position = 0;
        MPI_Pack(person.name, 20, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&person.age, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&person.height, 1, MPI_FLOAT, buffer, buffer_size, &position, MPI_COMM_WORLD);

        printf("Proces %d wysyła dane do procesu %d\n", rank, next);
        MPI_Send(buffer, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, buffer_size, MPI_PACKED, prev, 0, MPI_COMM_WORLD, &status);

        position = 0;
        MPI_Unpack(buffer, buffer_size, &position, person.name, 20, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &person.age, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &person.height, 1, MPI_FLOAT, MPI_COMM_WORLD);

        printf("Proces %d odebrał dane: name=%s, age=%d, height=%.2f\n", rank, person.name, person.age, person.height);
    } else {
        MPI_Recv(buffer, buffer_size, MPI_PACKED, prev, 0, MPI_COMM_WORLD, &status);
        
        int position = 0;
        MPI_Unpack(buffer, buffer_size, &position, person.name, 20, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &person.age, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &person.height, 1, MPI_FLOAT, MPI_COMM_WORLD);

        printf("Proces %d odebrał dane: name=%s, age=%d, height=%.2f\n", rank, person.name, person.age, person.height);
        snprintf(person.name, 20, "Paweł_%d", rank);
        person.age += 1;
        person.height += 0.2;

        position = 0;
        MPI_Pack(person.name, 20, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&person.age, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&person.height, 1, MPI_FLOAT, buffer, buffer_size, &position, MPI_COMM_WORLD);

        if (rank != size - 1) {
            printf("Proces %d wysyła dane do procesu %d\n", rank, next);
            MPI_Send(buffer, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
        } else {
            printf("Proces %d wysyła dane do procesu %d\n", rank, next);
            MPI_Send(buffer, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
        }
    }

    free(buffer);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}