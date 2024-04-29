#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3 // Definir o número de threads igual ao número de linhas da matriz

// Definindo a matriz e o vetor para multiplicação
int matriz[NUM_THREADS][NUM_THREADS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int vetor[NUM_THREADS] = {1, 2, 3};
int resultado[NUM_THREADS] = {0};

// Função que cada thread executará
void* calcularProduto(void* arg) {
    int linha = *(int*)arg;
    for (int j = 0; j < NUM_THREADS; j++) {
        resultado[linha] += matriz[linha][j] * vetor[j];
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int linha[NUM_THREADS];

    // Criando uma thread para cada linha da matriz
    for (int i = 0; i < NUM_THREADS; i++) {
        linha[i] = i;
        pthread_create(&threads[i], NULL, calcularProduto, &linha[i]);
    }

    // Aguardando a conclusão de todas as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimindo o vetor resultado
    printf("O vetor resultado é: ");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    return 0;
}
