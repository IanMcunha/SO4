#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TEMPO_TRAVESSIA 10 // Tempo que leva para atravessar a escada

void usarEscada(int id, int direcao) {
    printf("Pessoa %d quer ir na direção %d e está começando a usar a escada.\n", id, direcao);
    sleep(TEMPO_TRAVESSIA); // Simula o tempo para atravessar a escada
    printf("Pessoa %d terminou de usar a escada.\n", id);
}

int main() {
    pid_t pid;
    int n, ti, di;
    printf("Informe o número de pessoas: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Informe o momento e a direção para a pessoa %d: ", i + 1);
        scanf("%d %d", &ti, &di);

        pid = fork();

        if (pid == 0) { // Código executado pelo processo filho
            // Simula a espera até o momento de usar a escada
            sleep(ti);
            usarEscada(i + 1, di);
            exit(0); // Termina o processo filho
        } else if (pid > 0) { // Código executado pelo processo pai
            // O processo pai poderia esperar aqui com waitpid() se necessário
        } else {
            perror("fork falhou");
            exit(EXIT_FAILURE);
        }
    }

    // O processo pai espera todos os filhos terminarem
    while (n > 0) {
        wait(NULL);
        n--;
    }

    printf("Todas as pessoas terminaram de usar a escada.\n");
    return 0;
}

