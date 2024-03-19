#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// Define o tamanho da pilha da nova thread como 64kB.
#define FIBER_STACK 1024*64

// Função que será executada pela nova thread.
int threadFunction(void* argument) {
    printf("Thread filha iniciando\n");

    // O argumento é um ponteiro para um valor inteiro compartilhado com o processo pai.
    int* shared_value = (int*)argument;

    // Incrementa o valor compartilhado.
    *shared_value += 1;

    printf("Thread filha incrementando o valor compartilhado para %d\n", *shared_value);

    printf("Thread filha encerrando\n");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    // Valor inicial compartilhado com a thread.
    int shared_value = 0;

    // Aloca memória para a pilha da nova thread.
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Criação da thread filha com valor compartilhado inicializado.
    printf("Criando thread filha com valor compartilhado %d\n", shared_value);

    // Chama a função clone para criar a thread filha, especificando as flags para compartilhamento de recursos.
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &shared_value);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Espera pela conclusão da thread filha.
    pid = waitpid(pid, 0, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Imprime o valor compartilhado após a execução da thread filha.
    printf("Processo pai: O valor compartilhado agora é %d\n", shared_value);

    // Libera a memória alocada para a pilha da thread filha.
    free(stack);
    printf("Thread filha retornou e a pilha foi liberada\n");

    return 0;
}
