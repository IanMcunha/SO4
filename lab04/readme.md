# Multiplicação Matriz-Vetor com Pthreads

Este programa realiza a multiplicação de uma matriz por um vetor usando a biblioteca pthread para paralelizar o cálculo. Cada thread calcula uma linha do resultado da multiplicação.

## Estrutura do Programa

O programa define uma matriz e um vetor de tamanho fixo, utilizando um número definido de threads para realizar a multiplicação. O resultado é armazenado em um vetor global `resultado`.

## Compilação e Execução

O código deve ser compilado com a flag `-pthread` para vincular a biblioteca pthread corretamente em um ambiente Red Hat na AWS.

Exemplo de compilação e execução:
```bash
gcc -pthread -o multMatrizVet multMatrizVet.c
./multMatrizVet
```

## Código

### Aqui está a estrutura básica do código:

Definição da Matriz e Vetor: A matriz e o vetor que serão multiplicados estão hard-coded no programa para simplificar a entrada de dados. 

Função de Thread: Cada thread executa esta função para calcular o resultado de uma linha da matriz multiplicada pelo vetor.

Criação de Threads: O programa cria uma thread para cada linha da matriz.

Sincronização de Threads: Após a criação, o programa espera a conclusão de todas as threads antes de prosseguir.

Impressão do Resultado: O programa imprime o vetor resultado após todas as threads terem completado o cálculo.
