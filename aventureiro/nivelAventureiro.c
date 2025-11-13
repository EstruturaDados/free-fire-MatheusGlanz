#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------------------------------------------------------
// Structs básicas
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// -----------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS PARA COMPARAÇÕES (DESEMPENHO)
// -----------------------------------------------------------------------------
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// -----------------------------------------------------------------------------
// FUNÇÕES PARA MOCHILA COM VETOR (LISTA SEQUENCIAL)
// -----------------------------------------------------------------------------
#define TAM_MAX 10

// Inserir item no vetor
void inserirItemVetor(Item mochila[], int *total) {
    if (*total >= TAM_MAX) {
        printf("\n[Mochila Vetor] Cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n=== Inserir Item (Vetor) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", mochila[*total].nome);
    fflush(stdin);
    printf("Tipo: ");
    scanf(" %19[^\n]", mochila[*total].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;
    printf("Item adicionado com sucesso!\n");
}

// Remover item do vetor
void removerItemVetor(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n[Mochila Vetor] Vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Remover Item (Vetor) ===\n");
    fflush(stdin);
    printf("Nome do item: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Listar itens do vetor
void listarItensVetor(Item mochila[], int total) {
    printf("\n=== Itens (Vetor) ===\n");
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("%d) %s | %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    comparacoesSequencial = 0;

    printf("\n=== Buscar Item (Sequencial Vetor) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado: %s | %s | Qtd: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Item nao encontrado.\nComparacoes: %d\n", comparacoesSequencial);
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor(Item mochila[], int total) {
    Item temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome (Bubble Sort).\n");
}

// Busca binária no vetor (deve estar ordenado)
void buscarBinariaVetor(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item (Binaria Vetor) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", nomeBusca);

    int inicio = 0, fim = total - 1, meio;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado: %s | %s | Qtd: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparacoes (binaria): %d\n", comparacoesBinaria);
            return;
        } else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item nao encontrado.\nComparacoes (binaria): %d\n", comparacoesBinaria);
}

// -----------------------------------------------------------------------------
// FUNÇÕES PARA MOCHILA COM LISTA ENCADEADA
// -----------------------------------------------------------------------------

// Inserir item na lista
void inserirItemLista(No **inicio) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("\n=== Inserir Item (Lista) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", novo->dados.nome);
    fflush(stdin);
    printf("Tipo: ");
    scanf(" %19[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item adicionado na lista!\n");
}

// Remover item da lista
void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Remover Item (Lista) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", nomeBusca);

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL)
                *inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
}

// Listar itens da lista
void listarItensLista(No *inicio) {
    printf("\n=== Itens (Lista Encadeada) ===\n");
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    int i = 1;
    for (No *aux = inicio; aux != NULL; aux = aux->proximo) {
        printf("%d) %s | %s | Quantidade: %d\n",
               i++, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
    }
}

// Busca sequencial na lista
void buscarItemLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nomeBusca[30];
    comparacoesSequencial = 0;

    printf("\n=== Buscar Item (Lista Encadeada) ===\n");
    fflush(stdin);
    printf("Nome: ");
    scanf(" %29[^\n]", nomeBusca);

    for (No *aux = inicio; aux != NULL; aux = aux->proximo) {
        comparacoesSequencial++;
        if (strcmp(aux->dados.nome, nomeBusca) == 0) {
            printf("Item encontrado: %s | %s | Qtd: %d\n",
                   aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Item nao encontrado.\nComparacoes: %d\n", comparacoesSequencial);
}

// -----------------------------------------------------------------------------
// MENU PRINCIPAL
// -----------------------------------------------------------------------------
int main() {
    Item mochilaVetor[TAM_MAX];
    int totalVetor = 0;
    No *mochilaLista = NULL;
    int escolhaEstrutura, opcao;

    do {
        printf("\n=============================\n");
        printf("   SISTEMA DE MOCHILA\n");
        printf("=============================\n");
        printf("1. Usar Mochila (VETOR)\n");
        printf("2. Usar Mochila (LISTA ENCADEADA)\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolhaEstrutura);

        if (escolhaEstrutura == 1) {
            do {
                printf("\n--- MENU (VETOR) ---\n");
                printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Ordenar\n6. Buscar Binaria\n7. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(mochilaVetor, &totalVetor); break;
                    case 2: removerItemVetor(mochilaVetor, &totalVetor); break;
                    case 3: listarItensVetor(mochilaVetor, totalVetor); break;
                    case 4: buscarSequencialVetor(mochilaVetor, totalVetor); break;
                    case 5: ordenarVetor(mochilaVetor, totalVetor); break;
                    case 6: buscarBinariaVetor(mochilaVetor, totalVetor); break;
                    case 7: break;
                    default: printf("Opcao invalida!\n");
                }
            } while (opcao != 7);
        } 
        else if (escolhaEstrutura == 2) {
            do {
                printf("\n--- MENU (LISTA ENCADEADA) ---\n");
                printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar\n5. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(&mochilaLista); break;
                    case 2: removerItemLista(&mochilaLista); break;
                    case 3: listarItensLista(mochilaLista); break;
                    case 4: buscarItemLista(mochilaLista); break;
                    case 5: break;
                    default: printf("Opcao invalida!\n");
                }
            } while (opcao != 5);
        }

    } while (escolhaEstrutura != 3);

    printf("\nEncerrando o sistema...\n");
    return 0;
}
