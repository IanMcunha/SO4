#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

#define MAX_PESSOAS 10000

typedef struct {
    int tempo, direcao;
} Passageiro;

typedef struct {
    int tempoFinal;
    int direcaoAtual; // -1 indica que a escada está parada
    int contador[2]; // Contadores para pessoas esperando em cada direção
    Passageiro fila[2][MAX_PESSOAS]; // Filas de espera para cada direção
    int fimFila[2]; // Indices para o fim da fila em cada direção
} EstadoEscada;

// Função que cada processo filho executará
void processarPassageiro(Passageiro p, EstadoEscada *estado, sem_t *semDir, sem_t *semTempo) {
    // Acesso crítico para verificar direção e tempo
    sem_wait(semDir);
    if (estado->direcaoAtual == -1 || estado->direcaoAtual == p.direcao) {
        estado->direcaoAtual = p.direcao;
        estado->tempoFinal = p.tempo + 10; // Incrementa o tempo final
        estado->contador[p.direcao]++;
    } else {
        // Adiciona à fila de espera da direção oposta
        estado->fila[1-p.direcao][estado->fimFila[1-p.direcao]++] = p;
    }
    sem_post(semDir);

    // Processa a fila pendente se necessário
    sem_wait(semTempo);
    if (estado->contador[estado->direcaoAtual] == 0) { // Ninguém na direção atual
        estado->direcaoAtual = 1 - estado->direcaoAtual; // Troca a direção
        for (int i = 0; i < estado->fimFila[estado->direcaoAtual]; i++) {
            estado->tempoFinal += 10;
            estado->contador[estado->direcaoAtual]++;
        }
        estado->fimFila[estado->direcaoAtual] = 0; // Esvazia a fila
    }
    sem_post(semTempo);
}

int main() {
    int shm_fd = shm_open("/estadoEscada", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(EstadoEscada));
    EstadoEscada *estado = mmap(NULL, sizeof(EstadoEscada), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    estado->tempoFinal = 0;
    estado->direcaoAtual = -1;
    memset(estado->contador, 0, sizeof(estado->contador));
    memset(estado->fimFila, 0, sizeof(estado->fimFila));

    sem_t *semDir = sem_open("/semDir", O_CREAT, 0666, 1);
    sem_t *semTempo = sem_open("/semTempo", O_CREAT, 0666, 1);

    Passageiro passageiros[MAX_PESSOAS];
    int numPassageiros;
    scanf("%d", &numPassageiros);

    for (int i = 0; i < numPassageiros; i++) {
        scanf("%d %d", &passageiros[i].tempo, &passageiros[i].direcao);
        if (fork() == 0) {
            processarPassageiro(passageiros[i], estado, semDir, semTempo);
            exit(0);
        }
    }

    while (wait(NULL) > 0); // Espera todos os processos filhos terminarem

    printf("O momento final de parada da escada rolante é %d\n", estado->tempoFinal);

    munmap(estado, sizeof(EstadoEscada));
    close(shm_fd);
    shm_unlink("/estadoEscada");
    sem_close(semDir);
    sem_unlink("/semDir");
    sem_close(semTempo);
    sem_unlink("/semTempo");

    return 0;
}



