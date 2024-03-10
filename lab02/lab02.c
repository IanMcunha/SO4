#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int fd1[2], fd2[2];  // Dois pipes: fd1 para pai -> filho, fd2 para filho -> pai
    pid_t pid;
    char parent_msg[BUFFER_SIZE] = "Hello from parent!";
    char child_msg[BUFFER_SIZE] = "Hello from child!";
    char read_buffer[BUFFER_SIZE];

    // Cria os pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Pipe Failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Processo pai
        close(fd1[0]); // Fecha lado de leitura do primeiro pipe no pai
        close(fd2[1]); // Fecha lado de escrita do segundo pipe no pai

        // Envia mensagem ao filho
        write(fd1[1], parent_msg, sizeof(parent_msg));
        printf("Pai: Mensagem enviada para o filho.\n");

        close(fd1[1]); // Fecha lado de escrita do primeiro pipe

        // Lê resposta do filho
        read(fd2[0], read_buffer, sizeof(read_buffer));
        printf("Pai: Resposta recebida do filho: %s\n", read_buffer);

        close(fd2[0]); // Fecha lado de leitura do segundo pipe

        wait(NULL); // Espera o processo filho terminar

    } else { // Processo filho
        close(fd1[1]); // Fecha lado de escrita do primeiro pipe no filho
        close(fd2[0]); // Fecha lado de leitura do segundo pipe no filho

        // Lê mensagem do pai
        read(fd1[0], read_buffer, sizeof(read_buffer));
        printf("Filho: Mensagem recebida do pai: %s\n", read_buffer);

        close(fd1[0]); // Fecha lado de leitura do primeiro pipe

        // Envia resposta para o pai
        write(fd2[1], child_msg, sizeof(child_msg));
        printf("Filho: Mensagem enviada para o pai.\n");

        close(fd2[1]); // Fecha lado de escrita do segundo pipe

        exit(0);
    }

    return 0;
}
