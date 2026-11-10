#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.h" 
#include "cadastrar.h"
#include "consultar.h"

 
int main(void) {
    int opcao = 1; 
    int vagas[FILEIRAS][COLUNAS] = {0};
    Veiculo *veiculos = malloc(CAPACIDADE_INICIAL * sizeof(Veiculo));
    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;
    int caractere;

    if (veiculos == NULL) {
        printf("Erro: nao foi possivel reservar memoria inicial.\n");
        return 1;
    }

    while(opcao != 0) {
        printf("\n\n=== ESTACIONAMENTO ===\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Consultar veiculo por identificador\n");
        printf("3 - Atualizar descricao ou categoria\n");
        printf("4 - Mover veiculo para outra vaga\n");
        printf("5 - Remover veiculo\n");
        printf("6 - Listar veiculos cadastrados\n");
        printf("7 - Exibir mapa de vagas\n");
        printf("8 - Exibir relatorio da ocupacao\n");
        printf("0 - Encerrar\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            if (feof(stdin)) {
                break;
            }
            printf("Opcao invalida.\n");
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
            }
            continue;
        }
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }

        if (opcao == 1) {
            cadastrarVeiculo(&veiculos, &quantidade, &capacidade, vagas);
        } else if (opcao == 2) {
            consultarVeiculo(veiculos, quantidade);
        } else if (opcao != 0) {
            printf("Funcionalidade ainda nao implementada.\n");
        }

    }

    free(veiculos);
    return 0;
}
