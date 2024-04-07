#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PESSOAS 10000

// Estrutura para armazenar informações do passageiro
typedef struct {
    int tempoChegada;
    int direcao;
} Passageiro;

// Variáveis globais compartilhadas
int tempoFinal = 0;
int direcaoAtual = -1; // -1 indica que a escada está parada
pthread_mutex_t mutex;

// Função executada por cada thread
void* funcaoPassageiro(void* arg) {
    Passageiro* p = (Passageiro*)arg;

    // Simula o tempo de chegada
    sleep(p->tempoChegada);

    pthread_mutex_lock(&mutex);
    // Verifica a direção da escada e ajusta o tempo final
    if (direcaoAtual == -1 || direcaoAtual == p->direcao) {
        direcaoAtual = p->direcao;
        if (tempoFinal < p->tempoChegada) {
            tempoFinal = p->tempoChegada;
        }
        tempoFinal += 10; // Adiciona o tempo de travessia
    } else {
        // A escada precisa mudar de direção
        tempoFinal += (tempoFinal > p->tempoChegada) ? 10 : (p->tempoChegada - tempoFinal) + 10;
        direcaoAtual = p->direcao;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int numPassageiros;
    scanf("%d", &numPassageiros);

    Passageiro passageiros[MAX_PESSOAS];
    pthread_t threads[MAX_PESSOAS];
    pthread_mutex_init(&mutex, NULL);

    // Lê as informações de cada passageiro
    for (int i = 0; i < numPassageiros; i++) {
        scanf("%d %d", &passageiros[i].tempoChegada, &passageiros[i].direcao);
    }

    // Cria uma thread para cada passageiro
    for (int i = 0; i < numPassageiros; i++) {
        pthread_create(&threads[i], NULL, funcaoPassageiro, (void*)&passageiros[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < numPassageiros; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("O momento final de parada da escada rolante é %d\n", tempoFinal);

    pthread_mutex_destroy(&mutex);
    return 0;
}

