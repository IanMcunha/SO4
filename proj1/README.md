# Projeto 1 - Sistemas Operacionais
## Escada Rolante

## Documentação código Processos: 
Descrição Geral
Este programa simula o funcionamento de uma escada rolante que atende pessoas subindo e descendo. O acesso é controlado para garantir que apenas uma pessoa utilize a escada por vez e que a direção da escada seja mudada conforme necessário, baseado na fila de pessoas esperando.

Estruturas de Dados
Pessoa: Estrutura que contém informações sobre o tempo de chegada (tempo) e a direção (direcao) da pessoa na escada rolante. A direção 0 indica subida e 1 indica descida.

FilaSubir e FilaDescer: Arrays que armazenam as pessoas esperando para subir ou descer, respectivamente.

Funções
escadaRolante(): Função principal que simula o funcionamento da escada. Ela percorre as filas de subida e descida, processando uma pessoa de cada vez de acordo com sua direção e tempo de chegada. A direção da escada é alternada conforme necessário, e o tempo de "saída" é atualizado a cada pessoa processada para refletir o tempo necessário para a próxima mudança de direção ou continuação do movimento.

Fluxo Principal (Função main)

Leitura do Arquivo de Entrada: O programa lê de um arquivo especificado pelo usuário que contém o número de pessoas e, para cada pessoa, o seu tempo de chegada e direção.

Processamento da Escada Rolante: As pessoas são adicionadas às filas correspondentes à sua direção. A função escadaRolante é então chamada para simular o funcionamento da escada, processando cada pessoa nas filas.

Saída: Ao final do processamento, o programa exibe o tempo total necessário para que todas as pessoas tenham usado a escada rolante.

###Considerações de Implementação
Sincronização: A implementação atual não requer sincronização entre threads ou processos, pois o programa opera de forma sequencial. No entanto, se a simulação fosse estendida para operar com múltiplas escadas em paralelo, mecanismos de sincronização (como semáforos ou mutexes) seriam necessários.

Eficiência: O programa é projetado para ser simples e direto, usando uma abordagem sequencial para processar as filas de pessoas. Isso é adequado para simulações pequenas a moderadas, mas pode ser ineficiente para um número muito grande de pessoas devido à natureza sequencial do processamento.

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

## 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R: 
Threads:

Para evitar que duas pessoas acessem a escada rolante simultaneamente, utilizei a sincronização através de threads com o uso de mutexes. No cenário onde se usam threads, um mutex é utilizado para controlar o acesso à seção crítica do código que manipula o estado compartilhado da escada rolante, como o tempo atual de saída (saida) e a direção atual (primeiro.direcao). O mutex garante que apenas uma thread (ou pessoa, neste contexto) pode executar a seção crítica do código por vez, o que evita condições de corrida e inconsistências no estado compartilhado.

Processos:

No código com processos, a estratégia não se foca explicitamente no controle de acesso simultâneo à escada por múltiplas pessoas, uma vez que o processo filho executa a função escadaRolante() de maneira sequencial. A função itera pelas filas de pessoas subindo e descendo, tratando uma pessoa de cada vez, garantindo que apenas uma pessoa (ou uma direção) seja processada num dado momento. Não há concorrência direta entre threads ou processos acessando a mesma função ao mesmo tempo, o que naturalmente evita colisões e condições de corrida.

## 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: 
Threads:

Para garantir que somente uma das direções da escada rolante esteja ativa por vez, o código verifica a direção da próxima pessoa na fila e decide se a escada deve continuar na mesma direção ou mudar. Isso é feito verificando a direção e o tempo de chegada das pessoas nas filas de subida e descida. A lógica inclui uma condição que só permite a mudança de direção se não houver mais ninguém esperando na direção atual ou se o próximo na direção oposta estiver agendado para um tempo posterior ao tempo de saída atual. Isso garante que a escada não mude de direção prematuramente, permitindo que todas as pessoas em uma direção específica usem a escada antes de mudar para a direção oposta.

Processos: 

A função escadaRolante() controla a direção da escada verificando a direção da próxima pessoa na fila que está pronta para usar a escada. Se a pessoa da frente na fila está indo para a direção oposta da última pessoa que usou a escada e já passou o tempo necessário para mudar de direção (determinado pela variável saida), a direção da escada é alterada. A direção é gerenciada pela variável primeiro.direcao, que é atualizada a cada iteração para refletir a pessoa que está atualmente usando a escada. Isso garante que a escada só opera em uma direção por vez, mudando apenas quando necessário e permitido pelas condições.

## 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: 
Implementação com Threads:

Vantagens: Utiliza menos recursos do sistema pois threads de um mesmo processo compartilham memória e estado. Isso torna a comunicação e a sincronização entre elas mais fácil e rápida.

Desvantagens: Erros e falhas em uma thread podem afetar todas as outras threads do mesmo processo, pois compartilham o mesmo espaço de memória.

Implementação com Processos:

Vantagens: Processos são isolados entre si, o que oferece maior segurança, pois falhas em um processo não afetam os outros.

Desvantagens: Comunicação entre processos é mais complexa e lenta do que entre threads, devido à necessidade de mecanismos IPC como pipes, sockets ou memória compartilhada. Além disso, processos têm maior overhead de criação e gerenciamento.

Eficiência na Solução do Problema:

A eficiência depende do contexto de uso:

Para ambientes que exigem alta segurança e isolamento, onde falhas em uma parte do sistema não devem comprometer todo o sistema, a implementação com processos pode ser mais adequada, apesar de menos eficiente em termos de uso de recursos.

Para a maioria das aplicações práticas deste problema, a implementação com threads tende a ser mais eficiente. Isso ocorre porque a sincronização e comunicação entre threads são mais rápidas e consomem menos recursos, o que é crucial em um sistema de tempo real como o controle de uma escada rolante.

## Comprovação de execução na aws: 

![Screenshot 2024-04-19 231424](https://github.com/IanMcunha/SO4/assets/101913171/0c46a754-208e-4f5c-a66a-c26e407e98f9)
![image](https://github.com/IanMcunha/SO4/assets/101913171/ea3b3c08-51a2-4bf0-8102-5e76a8887e5a)



