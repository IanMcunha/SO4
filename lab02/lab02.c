#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int fd[2]; // Pipe para comunicação de pai para filho
    pid_t pid;
    char parent_msg[BUFFER_SIZE] = "Hello from parent!";
    char read_buffer[BUFFER_SIZE];

    // Cria o pipe
    if (pipe(fd) == -1) {
        perror("Pipe Failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Processo pai
        close(fd[0]); // Fecha lado de leitura do pipe no pai
        // Envia mensagem ao filho
        write(fd[1], parent_msg, sizeof(parent_msg));
        printf("Pai: Mensagem enviada para o filho.\n");
        close(fd[1]); // Fecha lado de escrita do pipe
        wait(NULL); // Espera o processo filho terminar
        printf("Pai: Finalizando processo.\n");
    } else { // Processo filho
        close(fd[1]); // Fecha lado de escrita do pipe no filho
        // Lê mensagem do pai
        read(fd[0], read_buffer, sizeof(read_buffer));
        printf("Filho: Mensagem recebida do pai: %s\n", read_buffer);
        close(fd[0]); // Fecha lado de leitura do pipe
        printf("Filho: Finalizando processo.\n");
        exit(0);
    }

    return 0;
}
