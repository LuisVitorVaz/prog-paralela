#include <stdio.h>
#include <mpi.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int should_exit = 0;
int token = 0;
int num_nodes;
int counter = 0;

void* receiver_thread(void* arg) {
    int rank = *((int*)arg);

    while (!should_exit) {
        int received_token;
        MPI_Recv(&received_token, 1, MPI_INT, (rank - 1 + num_nodes) % num_nodes, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        pthread_mutex_lock(&mutex);
        token = received_token;
        pthread_mutex_unlock(&mutex);

        printf("Processo %d recebeu token: %d\n", rank, token);
    }

    pthread_exit(NULL);
}

void* sender_thread(void* arg) {
    int rank = *((int*)arg);

    while (!should_exit) {
        pthread_mutex_lock(&mutex);
        int local_token = token;
        int data_value = (rank * 1000) + counter;  // Valor a ser enviado, usando o rank e o contador
        counter++;
        pthread_mutex_unlock(&mutex);

        // Se o processo possuir o token, realize uma operação (por exemplo, incrementar)
        if (rank == local_token) {
            // Transmita o token para todos os outros processos
            for (int i = 0; i < num_nodes; i++) {
                if (i != rank) {
                    MPI_Send(&local_token, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
            }

            // Operação a ser realizada quando o processo possui o token
            printf("Processo %d realizou uma operacao com o token. Valor enviado: %d\n", rank, data_value);
        }

        // Passe o token para o próximo processo no anel lógico
        MPI_Send(&local_token, 1, MPI_INT, (rank + 1) % num_nodes, 0, MPI_COMM_WORLD);

        // Aguarde antes de verificar novamente
        sleep(1);
    }

    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int rank, size, max_nodes, ch = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    num_nodes = size; // Número de nós é o número total de processos.
    max_nodes = num_nodes - 1;

    if (rank == 0) {
        printf("Número de nós: %d\n", num_nodes);
        for (int i = 0; i < num_nodes; i++) {
            printf(" %d", i);
        }
        printf(" %d\n", 0);
    }

    // Barreira para garantir que todos os processos tenham alcançado este ponto antes de prosseguir
    MPI_Barrier(MPI_COMM_WORLD);

    pthread_t receiver_thread_id, sender_thread_id;

    // Crie as threads receiver e sender
    pthread_create(&receiver_thread_id, NULL, receiver_thread, (void*)&rank);
    pthread_create(&sender_thread_id, NULL, sender_thread, (void*)&rank);

    // Aguarde as threads terminarem
    pthread_join(receiver_thread_id, NULL);
    pthread_join(sender_thread_id, NULL);

    // Indique que as threads devem encerrar
    should_exit = 1;

    MPI_Finalize();

    return 0;
}
