#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PESSOAS 10000

typedef struct {
    int tempo, direcao;
} Passageiro;

typedef struct {
    int tempoFinal;
    int direcaoAtual; // -1 indica que a escada está parada
    int contador[2]; // Contadores para pessoas esperando em cada direção [0] e [1]
    Passageiro fila[2][MAX_PESSOAS]; // Filas de espera para cada direção
    int fimFila[2]; // Aponta para o fim da fila em cada direção
} EstadoEscada;

pthread_mutex_t mutex;
sem_t semTempo, semDirecao;

void *processarPassageiro(void *arg) {
    Passageiro *p = (Passageiro *)arg;

    pthread_mutex_lock(&mutex);
    if (estado.direcaoAtual == -1 || estado.direcaoAtual == p->direcao) {
        // Processa imediatamente se estiver na mesma direção ou escada parada
        estado.direcaoAtual = p->direcao;
        estado.tempoFinal = p->tempo + 10; // Supõe processamento imediato
        estado.contador[p->direcao]++;
    } else {
        // Adiciona à fila de espera da direção oposta
        estado.fila[p->direcao][estado.fimFila[p->direcao]++] = *p;
    }
    pthread_mutex_unlock(&mutex);

    // Trabalha na fila pendente se necessário
    sem_wait(&semDirecao);
    if (estado.contador[estado.direcaoAtual] == 0) { // Ninguém na direção atual
        estado.direcaoAtual = 1 - estado.direcaoAtual; // Troca a direção
        for (int i = 0; i < estado.fimFila[estado.direcaoAtual]; i++) {
            sem_post(&semTempo);
            estado.tempoFinal += 10;
            estado.contador[estado.direcaoAtual]++;
        }
        estado.fimFila[estado.direcaoAtual] = 0; // Esvazia a fila
    }
    sem_post(&semDirecao);

    return NULL;
}

int main() {
    EstadoEscada estado = {0, -1, {0, 0}, {{{0, 0}}, {{0, 0}}}, {0, 0}};
    pthread_t threads[MAX_PESSOAS];
    Passageiro passageiros[MAX_PESSOAS];
    int numPassageiros;

    // Inicialização de semáforos e mutex
    sem_init(&semTempo, 0, 1);
    sem_init(&semDirecao, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Carregar passageiros
    for (int i = 0; i < numPassageiros; i++) {
        scanf("%d %d", &passageiros[i].tempo, &passageiros[i].direcao);
        pthread_create(&threads[i], NULL, processarPassageiro, &passageiros[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < numPassageiros; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("O momento final de parada da escada rolante é %d\n", estado.tempoFinal);

    // Limpeza de recursos
    sem_destroy(&semTempo);
    sem_destroy(&semDirecao);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

