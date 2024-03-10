# Laboratório 02 - Sistemas Operacionais

## Questão A

Sim, é possível identificar os trechos executados por pai e filho no primeiro exemplo de código. O trecho executado pelo processo filho é marcado pela condição else if (pid == 0), onde ele imprime que é o filho e executa o comando ls usando execlp. O processo pai executa o trecho no else final, onde espera pelo término do processo filho com wait(NULL) e depois imprime que o processo filho está completo.

## Questão B

Quanto ao segundo exemplo, serão criados 8 processos no total. Isso ocorre porque cada chamada a fork() duplica o número de processos existentes. Portanto, com três chamadas a fork(), o processo se duplica de 1 para 2, de 2 para 4, e de 4 para 8.

## Exercício

Para um exemplo onde processos pai e filho trocam mensagens, podemos usar um mecanismo simples de comunicação interprocesso, como pipes.
 
## Console da AWS rodando o programa:
<img src="https://i.imgur.com/G6U6Gzx.png" alt="Print AWS">
