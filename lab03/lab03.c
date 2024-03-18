#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// 64kB stack
#define FIBER_STACK 1024*64

// The child thread will execute this function
int threadFunction(void* argument) {
    printf("Child thread entering\n");

    // O argumento é um ponteiro para um valor inteiro compartilhado com o processo pai
    int* shared_value = (int*)argument;

    // Incrementa o valor compartilhado
    *shared_value += 1;

    printf("Child thread incrementing shared value to %d\n", *shared_value);

    printf("Child thread exiting\n");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    int shared_value = 0; // Valor inicial compartilhado com a thread

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("Creating child thread with shared value %d\n", shared_value);

    // Call the clone system call to create the child thread
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &shared_value);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Wait for the child thread to exit
    pid = waitpid(pid, 0, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Print the shared value after the thread has exited
    printf("Parent process: Shared value is now %d\n", shared_value);

    // Free the stack
    free(stack);
    printf("Child thread returned and stack freed.\n");

    return 0;
}
