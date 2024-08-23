#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int meu_ranque, num_procs;
    int origem, destino = 0, etiq = 1;
    char mensagem[200];
    MPI_Status estado;

    /* Chamada inicial para o MPI */
    MPI_Init(&argc, &argv);
    
    /* Determina o ranque e número de processos em execução */
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    // retorna o número de processos em um comunicador MPI 
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Todos os processos com ranque diferente de 0 enviam uma mensagem */
    if (meu_ranque != 0) {
        sprintf(mensagem, "Processo %d está vivo!", meu_ranque);
        //MPI_Send envia a mensagem, especificando seu conteúdo, tamanho, tipo de dados, 
        //o processo de destino, a etiqueta e o comunicador a ser usado na comunicação.
        MPI_Send(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD);
    } else {
        // Processo com ranque 0 recebe mensagens
        for (origem = 1; origem < num_procs; origem++) {
            MPI_Recv(mensagem, 200, MPI_CHAR, origem, etiq, MPI_COMM_WORLD, &estado);
            printf("%s\n", mensagem);
        }
    }
    // extra
    int version, subversion;

    // Obtém a versão e subversão do MPI
    MPI_Get_version(&version, &subversion);

    printf("Versão do MPI: %d, Subversão: %d\n", version, subversion);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    // Obtém o nome do processador/nó
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Nome do processador/nó: %s\n", processor_name);

    MPI_Finalize();
    return 0;
}
