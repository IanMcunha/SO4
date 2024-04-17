# Projeto 1 - Sistemas Operacionais
## Escada Rolante

#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R: Em ambas as abordagens, utilizamos mecanismos de sincronização. Nas threads, o pthread_mutex_lock foi utilizado para garantir que somente uma thread pudesse acessar e modificar as variáveis compartilhadas em um dado momento. Nos processos, semáforos foram usados com a chamada sem_wait para bloquear o acesso à seção crítica, assegurando que apenas um processo por vez pudesse realizar mudanças no estado compartilhado da escada.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Isso foi conseguido mantendo uma variável de estado que registra a direção atual da escada rolante. Nas threads, antes de qualquer thread modificar a direção, ela verifica e adquire o bloqueio do mutex. Nos processos, antes de modificar a direção, o processo precisa adquirir o semáforo correspondente. Se a direção precisa ser alterada, a mudança só ocorre quando não há mais ninguém na direção anterior, garantindo que a direção só mude quando for seguro fazê-lo.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: A principal diferença entre as implementações usando threads e processos está na forma como a memória é compartilhada e na sobrecarga associada à criação e gestão dos trabalhadores. Threads compartilham o mesmo espaço de memória do processo pai, tornando a comunicação e sincronização mais diretas e com menos sobrecarga, já que não há necessidade de memória compartilhada IPC ou semáforos IPC. Processos, por outro lado, têm seu próprio espaço de memória, exigindo IPC para compartilhar estado, o que pode ser mais pesado em termos de performance. No contexto da simulação da escada rolante, as threads podem ser mais eficientes porque requerem menos recursos do sistema e têm menor latência na comunicação devido ao compartilhamento direto da memória. Além disso, criar e destruir threads geralmente tem menos sobrecarga do que fazer o mesmo com processos.

## Execução com processo (E_1)

## Execução com thread (E_1)
