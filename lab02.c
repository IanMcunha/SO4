#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pid_t pid;
    char received_msg[100];

    // Cria um pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid > 0) { // Processo pai
        char msg[] = "Hello from parent!";
        close(fd[0]); // Fecha o lado de leitura do pipe
        write(fd[1], msg, sizeof(msg));
        close(fd[1]); // Fecha o lado de escrita do pipe
        wait(NULL);
    } else { // Processo filho
        close(fd[1]); // Fecha o lado de escrita do pipe
        read(fd[0], received_msg, sizeof(received_msg));
        printf("Received message: %s\n", received_msg);
        close(fd[0]); // Fecha o lado de leitura do pipe
    }

    return 0;
}
