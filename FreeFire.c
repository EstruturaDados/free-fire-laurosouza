#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura para representar um item na mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(const Item mochila[], int total);
void limparBuffer();

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n============================================\n");
        printf("        MOCHILA DO SOBREVIVENTE – NÍVEL NOVATO\n");
        printf("============================================\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// Função para adicionar um item na mochila
void inserirItem(Item mochila[], int *total) {
    if(*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== Adicionar Item ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma, munição, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochila[*total] = novo;
    (*total)++;
    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *total) {
    if(*total == 0) {
        printf("\nA mochila está vazia! Não há itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int indice = -1;
    for(int i = 0; i < *total; i++) {
        if(strcmp(mochila[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if(indice == -1) {
        printf("\nItem não encontrado.\n");
        return;
    }

    for(int i = indice; i < *total - 1; i++) {
        mochila[i] = mochila[i+1];
    }

    (*total)--;
    printf("\nItem removido com sucesso!\n");
}

// Função para listar todos os itens da mochila
void listarItens(const Item mochila[], int total) {
    printf("\n=========== ITENS NA MOCHILA ===========\n");
    if(total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for(int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i+1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
    printf("\n=========================================\n");
}

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}
