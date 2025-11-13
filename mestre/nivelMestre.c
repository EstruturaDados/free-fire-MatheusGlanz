#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// -----------------------------------------------------------------------------
// Struct principal: representa cada componente da torre
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// -----------------------------------------------------------------------------
// Variáveis globais de contagem de comparações
// -----------------------------------------------------------------------------
int comparacoes = 0;

// -----------------------------------------------------------------------------
// Função utilitária: exibir todos os componentes
// -----------------------------------------------------------------------------
void mostrarComponentes(Componente lista[], int n) {
    printf("\n=== Componentes ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d) Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// -----------------------------------------------------------------------------
// Função: Bubble Sort (por nome)
// -----------------------------------------------------------------------------
void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Função: Insertion Sort (por tipo)
// -----------------------------------------------------------------------------
void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;

        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = chave;
    }
}

// -----------------------------------------------------------------------------
// Função: Selection Sort (por prioridade)
// -----------------------------------------------------------------------------
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[minIndex].prioridade)
                minIndex = j;
        }
        if (minIndex != i) {
            Componente temp = lista[i];
            lista[i] = lista[minIndex];
            lista[minIndex] = temp;
        }
    }
}

// -----------------------------------------------------------------------------
// Função: Busca binária (por nome)
// -----------------------------------------------------------------------------
int buscaBinariaPorNome(Componente lista[], int n, char nomeBusca[]) {
    int inicio = 0, fim = n - 1, meio;
    int compBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        compBinaria++;
        int cmp = strcmp(nomeBusca, lista[meio].nome);

        if (cmp == 0) {
            printf("\nComponente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                   lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            printf("Comparações (busca binária): %d\n", compBinaria);
            return meio;
        } else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nComponente '%s' não encontrado.\nComparações (busca binária): %d\n",
           nomeBusca, compBinaria);
    return -1;
}

// -----------------------------------------------------------------------------
// Função: medir tempo de execução de um algoritmo de ordenação
// -----------------------------------------------------------------------------
void medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n, char criterio[]) {
    Componente copia[MAX];
    memcpy(copia, lista, n * sizeof(Componente));

    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nOrdenação concluída por %s!\n", criterio);
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Comparações realizadas: %d\n", comparacoes);

    mostrarComponentes(copia, n);

    // Caso tenha sido ordenado por nome, permitir busca binária
    if (strcmp(criterio, "Bubble Sort (Nome)") == 0) {
        char nomeBusca[30];
        printf("\nDigite o nome do componente-chave para busca binária: ");
        fflush(stdin);
        fgets(nomeBusca, 30, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
        buscaBinariaPorNome(copia, n, nomeBusca);
    }
}

// -----------------------------------------------------------------------------
// Função: cadastrar componentes
// -----------------------------------------------------------------------------
void cadastrarComponentes(Componente lista[], int *n) {
    int qtd;
    printf("\nQuantos componentes deseja cadastrar (1 a 20)? ");
    scanf("%d", &qtd);
    if (qtd < 1 || qtd > 20) {
        printf("Quantidade inválida!\n");
        return;
    }

    *n = qtd;
    getchar(); // Limpar buffer

    for (int i = 0; i < qtd; i++) {
        printf("\n=== Cadastro do componente %d ===\n", i + 1);

        printf("Nome: ");
        fgets(lista[i].nome, 30, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(lista[i].tipo, 20, stdin);
        lista[i].tipo[strcspn(lista[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d", &lista[i].prioridade);
        getchar(); // limpar buffer
    }

    printf("\nCadastro concluído com sucesso!\n");
}

// -----------------------------------------------------------------------------
// Função principal (menu do jogo final)
// -----------------------------------------------------------------------------
int main() {
    Componente torre[MAX];
    int total = 0, opcao;

    printf("=== TORRE DE FUGA - MÓDULO ESTRATÉGICO ===\n");

    do {
        printf("\n==== MENU ====\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                cadastrarComponentes(torre, &total);
                break;
            case 2:
                mostrarComponentes(torre, total);
                break;
            case 3:
                medirTempo(bubbleSortNome, torre, total, "Bubble Sort (Nome)");
                break;
            case 4:
                medirTempo(insertionSortTipo, torre, total, "Insertion Sort (Tipo)");
                break;
            case 5:
                medirTempo(selectionSortPrioridade, torre, total, "Selection Sort (Prioridade)");
                break;
            case 6:
                printf("\nEncerrando o sistema... Boa sorte na fuga!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 6);

    return 0;
}
