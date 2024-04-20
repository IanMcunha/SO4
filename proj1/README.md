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

## 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R: 
Threads:

Para evitar que duas pessoas acessem a escada rolante simultaneamente, utilizei a sincronização através de threads com o uso de mutexes. No cenário onde se usam threads, um mutex é utilizado para controlar o acesso à seção crítica do código que manipula o estado compartilhado da escada rolante, como o tempo atual de saída (saida) e a direção atual (primeiro.direcao). O mutex garante que apenas uma thread (ou pessoa, neste contexto) pode executar a seção crítica do código por vez, o que evita condições de corrida e inconsistências no estado compartilhado.

Processos:

Neste código, não há concorrência real entre processos ou threads para acessar a escada rolante, já que o programa é executado de forma sequencial em um único processo. Portanto, o controle de acesso simultâneo à escada rolante não é necessário neste contexto específico. A função escadaRolante() gerencia o fluxo de pessoas virtualmente, simulando o acesso à escada rolante sem a necessidade de sincronização entre processos concorrentes, visto que não há paralelismo real envolvido.

## 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: 
Threads:

Para garantir que somente uma das direções da escada rolante esteja ativa por vez, o código verifica a direção da próxima pessoa na fila e decide se a escada deve continuar na mesma direção ou mudar. Isso é feito verificando a direção e o tempo de chegada das pessoas nas filas de subida e descida. A lógica inclui uma condição que só permite a mudança de direção se não houver mais ninguém esperando na direção atual ou se o próximo na direção oposta estiver agendado para um tempo posterior ao tempo de saída atual. Isso garante que a escada não mude de direção prematuramente, permitindo que todas as pessoas em uma direção específica usem a escada antes de mudar para a direção oposta.

Processos: 

O controle de direção na escada rolante é realizado verificando a direção (direcao) do primeiro objeto Pessoa e permitindo que pessoas na mesma direção continuem enquanto forem consecutivas e tiverem tempos de chegada que permitam. A mudança de direção ocorre quando não há mais pessoas para processar na direção atual ou quando uma pessoa da direção oposta tem um tempo de chegada que se torna o próximo na fila. Este comportamento é implementado pelas condições dentro dos blocos if que verificam a direção atual da escada e comparam os tempos de chegada das pessoas nas filas de subida e descida:

Se a direção atual for de subida (direcao == 0) e não houver mais pessoas que possam subir imediatamente (de acordo com o tempo), a direção pode mudar para descida se houver pessoas esperando para descer.
Vice-versa, se a direção atual for de descida (direcao == 1) e a situação for semelhante com pessoas esperando para subir.
Essas verificações são feitas na lógica que decide qual primeiro Pessoa deve ser o próximo a usar a escada, baseado no tempo de chegada (tempo) e na disponibilidade das filas.

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



