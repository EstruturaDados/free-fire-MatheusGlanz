#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------------------------------------------
// Struct que representa cada item da mochila
// --------------------------------------------------------------------------------------
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// --------------------------------------------------------------------------------------
// Funcao: inserirItem
// Descricao: cadastra um novo item na mochila
// --------------------------------------------------------------------------------------
void inserirItem(struct Item mochila[], int *totalItens) {
    if (*totalItens >= 10) {
        printf("\n Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");
    fflush(stdin);
    printf("Nome do item: ");
    scanf(" %29[^\n]", mochila[*totalItens].nome);

    fflush(stdin);
    printf("Tipo (ex: Arma, Municao, Cura): ");
    scanf(" %19[^\n]", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;
    printf("\n Item adicionado com sucesso!\n");
}

// --------------------------------------------------------------------------------------
// Funcao: removerItem
// Descricao: remove um item da mochila pelo nome
// --------------------------------------------------------------------------------------
void removerItem(struct Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\n Mochila vazia! Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Remover Item ===\n");
    fflush(stdin);
    printf("Informe o nome do item que deseja remover: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("\n Item removido com sucesso!\n");
            return;
        }
    }

    printf("\n Item nao encontrado.\n");
}

// --------------------------------------------------------------------------------------
// Funcao: listarItens
// Descricao: exibe todos os itens atualmente cadastrados na mochila
// --------------------------------------------------------------------------------------
void listarItens(struct Item mochila[], int totalItens) {
    printf("\n=== Itens na Mochila ===\n");
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
                   i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

// --------------------------------------------------------------------------------------
// Funcao: buscarItem
// Descricao: busca sequencialmente um item pelo nome
// --------------------------------------------------------------------------------------
void buscarItem(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\n Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item ===\n");
    fflush(stdin);
    printf("Digite o nome do item: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n Item nao encontrado.\n");
}

// --------------------------------------------------------------------------------------
// Funcao principal (menu do jogo)
// --------------------------------------------------------------------------------------
int main() {
    struct Item mochila[10];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA DO JOGADOR =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &totalItens); listarItens(mochila, totalItens); break;
            case 2: removerItem(mochila, &totalItens); listarItens(mochila, totalItens); break;
            case 3: listarItens(mochila, totalItens); break;
            case 4: buscarItem(mochila, totalItens); break;
            case 5: printf("\n Saindo do sistema...\n"); break;
            default: printf("\n Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
