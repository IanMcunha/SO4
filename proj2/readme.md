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
-Documentação do Código
-Estrutura do Código
-O programa é composto pelos seguintes elementos principais:

-Declaração do Mutex: pthread_mutex_t mutex;

-Utilizado para sincronizar o acesso às contas durante as transferências.
-Inicialização e Destruição do Mutex:

-pthread_mutex_init(&mutex, NULL);
-pthread_mutex_destroy(&mutex);
-O mutex é inicializado no início do main e destruído no final para garantir a limpeza dos recursos.
-Função de Transferência: int transferencia(void *arg)

-Executada pelos processos filhos criados pela chamada clone.
-Realiza a transferência de fundos de from para to se houver saldo suficiente.
-Utiliza pthread_mutex_lock(&mutex); e pthread_mutex_unlock(&mutex); para garantir que apenas uma transferência ocorra por vez.

### Pré-requisitos

- Compilador GCC
- Sistema operacional Linux

