# Projeto de Sistemas Operacionais

## Descrição

Este projeto faz parte da disciplina de Sistemas Operacionais da Universidade Presbiteriana Mackenzie. O objetivo é desenvolver um programa em C que simule a transferência de fundos entre duas contas utilizando chamadas de sistema para gerenciar processos concorrentes.

## Objetivos

1. Compreender o funcionamento do sistema operacional e sua comunicação com os dispositivos conectados.
2. Abordar o problema da concorrência.
3. Desenvolver um programa que consuma as chamadas de sistema do SO.
4. Utilizar de forma ótima as chamadas de sistema do SO.

## Requisitos

- O programa deve ser compilado e executado em um ambiente Linux.
- O código deve ser disponibilizado em um repositório público sem a necessidade de cadastro ou senha para acesso.
- Não deve haver dependências proprietárias para execução e compilação do programa.

## Compilação e Execução

## Documentação do Código

### Estrutura do Código

O programa é composto pelos seguintes elementos principais:

#### Declaração do Mutex:
- `pthread_mutex_t mutex;`
  - Utilizado para sincronizar o acesso às contas durante as transferências.

#### Inicialização e Destruição do Mutex:
- `pthread_mutex_init(&mutex, NULL);`
- `pthread_mutex_destroy(&mutex);`
  - O mutex é inicializado no início do `main` e destruído no final para garantir a limpeza dos recursos.

#### Função de Transferência:
- `int transferencia(void *arg)`
  - Executada pelos processos filhos criados pela chamada `clone`.
  - Realiza a transferência de fundos de `from` para `to` se houver saldo suficiente.
  - Utiliza `pthread_mutex_lock(&mutex);` e `pthread_mutex_unlock(&mutex);` para garantir que apenas uma transferência ocorra por vez.

## Explicação da Solução

O programa simula a transferência de fundos entre duas contas usando múltiplos processos filhos. Para evitar condições de corrida durante as transferências, foi utilizado um mutex para garantir que apenas uma transferência seja realizada por vez.

### Declaração e Inicialização do Mutex:

- Um mutex é declarado (`pthread_mutex_t mutex;`) e inicializado (`pthread_mutex_init(&mutex, NULL);`) no início do `main`.
- O mutex é destruído (`pthread_mutex_destroy(&mutex);`) no final do `main` para garantir a limpeza dos recursos.

### Função de Transferência:

- A função `transferencia` é responsável por realizar as transferências de forma segura, utilizando o mutex para sincronizar o acesso.
- Utiliza `pthread_mutex_lock(&mutex);` para bloquear o mutex antes de realizar a transferência e `pthread_mutex_unlock(&mutex);` para liberar o mutex após a transferência ser concluída.

### Criação dos Processos Filhos:

- Utilizamos a chamada `clone` para criar processos filhos que executam a função `transferencia`.
- Os processos filhos são criados dentro de um loop `for`, permitindo múltiplas transferências simultâneas.

### Sincronização das Transferências:

- Utilizamos um loop `for` adicional para esperar que todos os processos filhos terminem antes de liberar a memória e destruir o mutex.
- Isso garante que todas as transferências sejam concluídas antes que os recursos sejam liberados.

### Pré-requisitos

- Compilador GCC
- Sistema operacional Linux



