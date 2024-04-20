#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define MAXN 10000

typedef struct {
    int tempo;
    int direcao;
} Pessoa;

Pessoa filaSubir[MAXN];
int tamanhoFS = 0;
Pessoa filaDescer[MAXN];
int tamanhoFD = 0;
Pessoa primeiro;

int escadaRolante() {
    int aux1 = 0, aux2 = 0, saida = 0;
    while (aux1 < tamanhoFS || aux2 < tamanhoFD) {
        if (primeiro.direcao == 0) {
            if ((aux1 < tamanhoFS && filaSubir[aux1].tempo <= saida) || (aux1 < tamanhoFS && filaSubir[aux1].tempo > saida && aux1 + 1 < tamanhoFS && filaSubir[aux1 + 1].tempo > saida) || aux2 >= tamanhoFD) {
                primeiro = filaSubir[aux1];
                ++aux1;
            } else if (aux2 < tamanhoFD) {
                primeiro = filaDescer[aux2];
                ++aux2;
            }
        } else {
            if ((aux2 < tamanhoFD && filaDescer[aux2].tempo <= saida) || (aux2 < tamanhoFD && filaDescer[aux2].tempo > saida && aux2 + 1 < tamanhoFD && filaDescer[aux2 + 1].tempo > saida) || aux1 >= tamanhoFS) {
                primeiro = filaDescer[aux2];
                ++aux2;
            } else if (aux1 < tamanhoFS) {
                primeiro = filaSubir[aux1];
                ++aux1;
            }
        }
        saida = primeiro.tempo + 10;
    }
    return saida;
}

int main() {
    char caminhoArquivo[256];
    printf("Digite o caminho do arquivo de entrada (ex: /home/ec2-user/SO04/SO4/proj1/input/E_58): ");
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
            filaSubir[tamanhoFS++] = p;
        } else {
            filaDescer[tamanhoFD++] = p;
        }
    }
    fclose(arquivo);

    int pid = fork(); // Cria um novo processo

    if (pid == 0) {
        // Processo filho
        int resultado = escadaRolante();
        printf("Saida no processo filho: %d\n", resultado);
        exit(0); // Termina o processo filho
    } else if (pid > 0) {
        // Processo pai
        wait(NULL); // Espera o processo filho terminar
        printf("Processo filho completou.\n");
    } else {
        // Falha ao criar o processo
        perror("Fork falhou");
        return 1;
    }

    return 0;
}
