#include <stdio.h>
#include <string.h>
#include "mover.h"
#include "cadastrar.h"
#include "utils.h"

int moverVeiculo(Veiculo *veiculos, int vagas[FILEIRAS][COLUNAS], int quantidade) {
    char identificador[9];
    int indiceVeiculo = -1;
    int resultado;
    int novaFileira, novaColuna;

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado para mover.\n");
        return 0;
    }

    do {
        print("Pressione Enter para cancelar.");
        resultado = lerIdentificador(identificador);
        if (resultado == 0) {
            return 0;
        }
        
        if (identificador[0] == '\0') {
            printf("Operacao cancelada.\n");
            return 0;
        }

        for (int i = 0; i < quantidade; i++) {
            if (strcmp(veiculos[i].identificador, identificador) == 0) {
                indiceVeiculo = i;
                break;
            }
        }

        if (indiceVeiculo == -1) {
            printf("Veiculo nao encontrado. Tente novamente.\n");
        }

    } while (indiceVeiculo == -1);

    printf("Veiculo encontrado na Fileira %d, Coluna %d.\n", 
           veiculos[indiceVeiculo].fileira, veiculos[indiceVeiculo].coluna);

    do {
        resultado = lerInteiro("Nova fileira (1 a 4): ", &novaFileira);
        if (resultado == 0) {
            return 0;
        }
        if (resultado != 1 || novaFileira < 1 || novaFileira > FILEIRAS) {
            printf("Fileira invalida. Informe um valor de 1 a 4.\n");
        }
    } while (resultado != 1 || novaFileira < 1 || novaFileira > FILEIRAS);

    do {
        resultado = lerInteiro("Nova coluna (1 a 5): ", &novaColuna);
        if (resultado == 0) {
            return 0;
        }
        if (resultado != 1 || novaColuna < 1 || novaColuna > COLUNAS) {
            printf("Coluna invalida. Informe um valor de 1 a 5.\n");
        }
    } while (resultado != 1 || novaColuna < 1 || novaColuna > COLUNAS);

    if (veiculos[indiceVeiculo].fileira == novaFileira && veiculos[indiceVeiculo].coluna == novaColuna) {
        printf("Movimentacao recusada: a vaga de destino e a vaga atual do veiculo sao a mesma.\n", novaFileira, novaColuna);
        return 0;
    }

    if (vagas[novaFileira - 1][novaColuna - 1] == 1) {
        printf("Movimentacao recusada: a vaga de destino (Fileira %d, Coluna %d) ja esta ocupada.\n", novaFileira, novaColuna);
        return 0;
    }

    int fileiraAntiga = veiculos[indiceVeiculo].fileira;
    int colunaAntiga = veiculos[indiceVeiculo].coluna;

    vagas[fileiraAntiga - 1][colunaAntiga - 1] = 0;

    vagas[novaFileira - 1][novaColuna - 1] = 1;

    veiculos[indiceVeiculo].fileira = novaFileira;
    veiculos[indiceVeiculo].coluna = novaColuna;

    printf("Sucesso! Veiculo %s movido para a Fileira %d, Coluna %d.\n", identificador, novaFileira, novaColuna);

    return 1;
}