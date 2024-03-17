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

int threadFunction(void* argument) {
    printf("child thread entering\n");

    // Cast argument to int pointer and read the value
    int* shared_value = (int*)argument;
    printf("CHILD: shared value = %d\n", *shared_value);

    // Modify the value
    *shared_value = 20;

    printf("child thread exiting\n");
    return 0; 
}

int main() {
    void* stack;
    pid_t pid;
    int shared_value = 10;

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("Creating child thread\n");

    // Call the clone system call to create the child thread
    pid = clone(&threadFunction, (char*) stack + FIBER_STACK,
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

    printf("PARENT: shared value = %d\n", shared_value);

    // Free the stack
    free(stack);
    printf("Child thread returned and stack freed.\n");

    return 0; 
}
