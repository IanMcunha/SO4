# Projeto 1 - Sistemas Operacionais
## Escada Rolante

## Documentação código Processos: 
Este código implementa um sistema de gerenciamento de tráfego de pessoas em uma escada rolante que suporta movimento em duas direções: subida e descida. As pessoas são organizadas em duas filas, uma para cada direção, e processadas conforme sua ordem de chegada e a direção atual da escada. O código utiliza a biblioteca pthread para gerenciar o fluxo de pessoas de forma concorrente, simulando o funcionamento da escada em um ambiente real.
### Estrutura do Código:
Definição de Estruturas:
Pessoa: Representa uma pessoa com atributos para o tempo de chegada na escada e a direcao desejada (0 para subida, 1 para descida).

filaSubida e filaDescida: Arrays que armazenam as pessoas esperando para subir ou descer.

tamanhoFS e tamanhoFD: Contadores para o número de pessoas em cada fila.

primeiro: Armazena a primeira pessoa a usar a escada, determinando a direção inicial.

Função escalador:
Controla o acesso à escada rolante e gerencia a sequência em que as pessoas usam a escada.
A função decide qual pessoa vai usar a escada com base em sua direção e tempo de chegada.
Implementa lógica para alternar a direção da escada quando necessário e garantir que o tempo de uso da escada seja respeitado.
Atualiza o tempo global saida, que representa o último momento de uso da escada.

Função main:
Abre e lê o arquivo de entrada que contém o número de pessoas e suas informações (tempo e direção).
Inicializa as filas de pessoas baseadas nas informações lidas.
Cria uma thread para executar a função escalador.
Aguarda a conclusão da thread e exibe o tempo final após todos usarem a escada.

### Lógica de Processamento:
Inicialização: O programa lê os dados de entrada e inicializa as filas de subida e descida com base nas direções desejadas das pessoas.
Processamento Concorrente: A função escalador é executada em uma thread separada para simular o funcionamento da escada rolante. Isso permite que o sistema opere de forma assíncrona e eficiente.
Gerenciamento de Direção: O programa verifica continuamente a direção atual da escada e a compara com a direção das pessoas na fila. Se a pessoa no início da fila corresponder à direção atual da escada, ela usará a escada. Caso contrário, a direção pode ser alterada se a outra fila tiver pessoas esperando e a escada estiver livre.
Atualização de Tempo: Cada uso da escada adiciona 10 segundos ao tempo global saida, que rastreia quando a escada foi usada pela última vez.

## Documentação código Threads:
Este programa simula a operação de uma escada rolante que acomoda pessoas subindo e descendo, utilizando threads para sincronizar o processo de maneira eficaz. O código é dividido em várias partes principais, incluindo definições de estruturas, lógica de processamento em uma thread e a leitura de dados de entrada.
### Estruturas Definidas:
Pessoa: Esta estrutura armazena informações cruciais sobre cada indivíduo que utiliza a escada rolante, incluindo o tempo de chegada e a direcao desejada (0 para subir, 1 para descer).
filaSubida e filaDescida: Dois arrays que armazenam as pessoas que desejam subir e descer, respectivamente.
Variáveis Globais:
saida: Mantém o tempo atualizado quando a última pessoa usou a escada.
primeiro: Registra a primeira pessoa na escada, ajudando a determinar a direção inicial da escada rolante.
Função escalador:
É a função principal que gerencia a lógica de como as pessoas usam a escada rolante.
Utiliza dois índices (indiceFS e indiceFD) para rastrear o progresso através das filas de subida e descida.
A lógica condicional dentro do loop verifica a direção da escada e decide se a pessoa atual pode proceder com base na sua direção e no tempo de chegada.
A direção da escada pode mudar se a próxima pessoa na fila oposta estiver esperando e a pessoa atual na fila ativa tiver um tempo de chegada posterior ao último tempo registrado de uso da escada.
Atualiza o tempo de saída após cada uso da escada, adicionando 10 segundos ao tempo da última pessoa que usou.
Função main:
Responsável por configurar o ambiente de execução, incluindo a leitura de entrada do arquivo especificado pelo usuário.
Inicializa as filas de pessoas e popula-as com dados do arquivo de entrada.
Cria uma thread para executar a função escalador e espera por sua conclusão para garantir que o programa não termine prematuramente.
Exibe o resultado final, que é o último tempo de saída registrado, indicando quando a escada foi usada pela última vez.
### Processamento e Sincronização:
A thread é usada para simular a operação contínua da escada rolante, permitindo que múltiplas pessoas sejam processadas simultaneamente de forma teórica.
O uso de pthread garante que o acesso aos recursos compartilhados seja sincronizado, evitando condições de corrida e garantindo que o tempo de saída seja consistentemente atualizado.

#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R: Em ambas as abordagens, utilizamos mecanismos de sincronização. Nas threads, o pthread_mutex_lock foi utilizado para garantir que somente uma thread pudesse acessar e modificar as variáveis compartilhadas em um dado momento. Nos processos, semáforos foram usados com a chamada sem_wait para bloquear o acesso à seção crítica, assegurando que apenas um processo por vez pudesse realizar mudanças no estado compartilhado da escada.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Isso foi conseguido mantendo uma variável de estado que registra a direção atual da escada rolante. Nas threads, antes de qualquer thread modificar a direção, ela verifica e adquire o bloqueio do mutex. Nos processos, antes de modificar a direção, o processo precisa adquirir o semáforo correspondente. Se a direção precisa ser alterada, a mudança só ocorre quando não há mais ninguém na direção anterior, garantindo que a direção só mude quando for seguro fazê-lo.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: A principal diferença entre as implementações usando threads e processos está na forma como a memória é compartilhada e na sobrecarga associada à criação e gestão dos trabalhadores. Threads compartilham o mesmo espaço de memória do processo pai, tornando a comunicação e sincronização mais diretas e com menos sobrecarga, já que não há necessidade de memória compartilhada IPC ou semáforos IPC. Processos, por outro lado, têm seu próprio espaço de memória, exigindo IPC para compartilhar estado, o que pode ser mais pesado em termos de performance. No contexto da simulação da escada rolante, as threads podem ser mais eficientes porque requerem menos recursos do sistema e têm menor latência na comunicação devido ao compartilhamento direto da memória. Além disso, criar e destruir threads geralmente tem menos sobrecarga do que fazer o mesmo com processos.

## Comprovação de execução na aws: 

![Screenshot 2024-04-19 231424](https://github.com/IanMcunha/SO4/assets/101913171/0c46a754-208e-4f5c-a66a-c26e407e98f9)


