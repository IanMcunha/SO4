#include <stdio.h>
#include <pthread.h>
#define MAXN 10000

int saida = 0;

typedef struct {
    int tempo;
    int direcao;
} Pessoa;

Pessoa filaSubida[MAXN];
int tamanhoFS = 0;
Pessoa filaDescida[MAXN];
int tamanhoFD = 0;
Pessoa primeiro;

void* escalador() {

    int indiceFS = 0, indiceFD = 0;

    while (indiceFS < tamanhoFS || indiceFD < tamanhoFD) {

        // subindo
        if (primeiro.direcao == 0) {

            // segue a mesma direção se o tempo de chegada for menor que o último tempo de saída ou se estiver imediatamente ao lado do anterior
            if ((indiceFS < tamanhoFS && (filaSubida[indiceFS].tempo <= saida) || (filaSubida[indiceFS].tempo > saida && filaSubida[indiceFS].tempo < filaDescida[indiceFD].tempo)) || indiceFD == tamanhoFD) {
                primeiro = filaSubida[indiceFS];               
                ++indiceFS;   

            // se o tempo de chegada for maior que o tempo de saída ou a fila estiver completamente usada 
            } else if (filaSubida[indiceFS].tempo > saida || indiceFS == tamanhoFS) {
                // muda a direção do escalador, considerando um novo tempo de chegada baseado no tempo de espera
                primeiro = filaDescida[indiceFD];
                if (saida > primeiro.tempo) primeiro.tempo = saida;
                ++indiceFD;

                // se o tempo de saída for maior que os seguintes
                int i = indiceFD;
                while (saida > filaDescida[i].tempo && i < tamanhoFD) {
                    filaDescida[i].tempo = saida;
                    ++i;
                }
            } 
        // descendo                              
        } else if (primeiro.direcao == 1) {

            // segue a mesma direção se o tempo de chegada for menor que o último tempo de saída ou se estiver imediatamente ao lado do anterior
            if ((indiceFD < tamanhoFD && filaDescida[indiceFD].tempo <= saida || (filaDescida[indiceFD].tempo > saida && filaDescida[indiceFD].tempo < filaSubida[indiceFS].tempo)) || indiceFS == tamanhoFS) {
                primeiro = filaDescida[indiceFD];      
                ++indiceFD;

            // se o tempo de chegada for maior que o tempo de saída ou a fila estiver completamente usada                                               
            } else if (filaDescida[indiceFD].tempo > saida || indiceFD == tamanhoFD) {
                // muda a direção do escalador, considerando um novo tempo de chegada baseado no tempo de espera
                primeiro = filaSubida[indiceFS];
                if (saida > primeiro.tempo) primeiro.tempo = saida;
                ++indiceFS;

                // se o tempo de saída for maior que os seguintes
                int i = indiceFS;
                while (saida > filaSubida[i].tempo && i < tamanhoFS) {
                    filaSubida[i].tempo = saida;
                    ++i;
                }                
            }
        }   
        saida = primeiro.tempo + 10;
    }
    return NULL;
}


int main() {
    pthread_t idThread;

    char caminhoArquivo[256];
    printf("Digite o caminho do arquivo de entrada (ex: ./input/E_58\\): ");
    scanf("%s", caminhoArquivo);

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int n;
    fscanf(arquivo, "%d", &n);

    for (int i = 0; i < n; ++i) {
        Pessoa p;
        fscanf(arquivo, "%d %d", &p.tempo, &p.direcao);
        if (i == 0) {
          primeiro = p;
        }
        if (p.direcao == 0) {
            filaSubida[tamanhoFS++] = p;
        } else {
            filaDescida[tamanhoFD++] = p;
        }
    }

    fclose(arquivo);

    pthread_create(&idThread, NULL, escalador, NULL);
    pthread_join(idThread, NULL);

    printf("Saida: %d\n", saida);
    return 0;
}
