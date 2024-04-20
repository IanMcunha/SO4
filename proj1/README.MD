# Projeto 1 - Sistemas Operacionais
## Escada Rolante

## Documentação código Processos: 
Este código implementa um sistema de gerenciamento de tráfego de pessoas em uma escada rolante que suporta movimento em duas direções: subida e descida. As pessoas são organizadas em duas filas, uma para cada direção, e processadas conforme sua ordem de chegada e a direção atual da escada. O código utiliza a biblioteca pthread para gerenciar o fluxo de pessoas de forma concorrente, simulando o funcionamento da escada em um ambiente real.
Lógica de Processamento:
Inicialização: O programa lê os dados de entrada e inicializa as filas de subida e descida com base nas direções desejadas das pessoas.
Processamento Concorrente: A função escalador é executada em uma thread separada para simular o funcionamento da escada rolante. Isso permite que o sistema opere de forma assíncrona e eficiente.
Gerenciamento de Direção: O programa verifica continuamente a direção atual da escada e a compara com a direção das pessoas na fila. Se a pessoa no início da fila corresponder à direção atual da escada, ela usará a escada. Caso contrário, a direção pode ser alterada se a outra fila tiver pessoas esperando e a escada estiver livre.
Atualização de Tempo: Cada uso da escada adiciona 10 segundos ao tempo global saida, que rastreia quando a escada foi usada pela última vez.

## Documentação código Threads:


#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R: Em ambas as abordagens, utilizamos mecanismos de sincronização. Nas threads, o pthread_mutex_lock foi utilizado para garantir que somente uma thread pudesse acessar e modificar as variáveis compartilhadas em um dado momento. Nos processos, semáforos foram usados com a chamada sem_wait para bloquear o acesso à seção crítica, assegurando que apenas um processo por vez pudesse realizar mudanças no estado compartilhado da escada.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Isso foi conseguido mantendo uma variável de estado que registra a direção atual da escada rolante. Nas threads, antes de qualquer thread modificar a direção, ela verifica e adquire o bloqueio do mutex. Nos processos, antes de modificar a direção, o processo precisa adquirir o semáforo correspondente. Se a direção precisa ser alterada, a mudança só ocorre quando não há mais ninguém na direção anterior, garantindo que a direção só mude quando for seguro fazê-lo.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: A principal diferença entre as implementações usando threads e processos está na forma como a memória é compartilhada e na sobrecarga associada à criação e gestão dos trabalhadores. Threads compartilham o mesmo espaço de memória do processo pai, tornando a comunicação e sincronização mais diretas e com menos sobrecarga, já que não há necessidade de memória compartilhada IPC ou semáforos IPC. Processos, por outro lado, têm seu próprio espaço de memória, exigindo IPC para compartilhar estado, o que pode ser mais pesado em termos de performance. No contexto da simulação da escada rolante, as threads podem ser mais eficientes porque requerem menos recursos do sistema e têm menor latência na comunicação devido ao compartilhamento direto da memória. Além disso, criar e destruir threads geralmente tem menos sobrecarga do que fazer o mesmo com processos.

## Execução com processo (E_1)

## Execução com thread (E_1)
