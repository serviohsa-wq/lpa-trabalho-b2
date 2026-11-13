#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastrar.h"
#include "utils.h"

static int normalizarIdentificador(char identificador[8]) {
    size_t indice;

    if (strlen(identificador) != 7) {
        return 0;
    }

    for (indice = 0; indice < 7; indice++) {
        if (!isalnum((unsigned char)identificador[indice])) {
            return 0;
        }
        identificador[indice] = (char)toupper((unsigned char)identificador[indice]);
    }

    return 1;
}

static int identificadorJaExiste(const Veiculo *veiculos, int quantidade,
                                 const char *identificador) {
    int indice;

    for (indice = 0; indice < quantidade; indice++) {
        if (strcmp(veiculos[indice].identificador, identificador) == 0) {
            return 1;
        }
    }

    return 0;
}

static int ampliarColecao(Veiculo **veiculos, int *capacidade) {
    Veiculo *novaColecao;
    int novaCapacidade = *capacidade * 2;

    novaColecao = realloc(*veiculos, (size_t)novaCapacidade * sizeof(Veiculo));
    if (novaColecao == NULL) {
        return 0;
    }

    *veiculos = novaColecao;
    *capacidade = novaCapacidade;
    return 1;
}

int cadastrarVeiculo(Veiculo **veiculos, int *quantidade, int *capacidade,
                      int vagas[FILEIRAS][COLUNAS]) {
    Veiculo novoVeiculo;
    char identificador[9];
    int resultado;

    if (*quantidade == MAXIMO_VEICULOS) {
        printf("Cadastro recusado: estacionamento lotado.\n");
        return 0;
    }

    while (1) {
        resultado = lerLinha("Identificador (7 caracteres alfanumericos): ",
                             identificador, sizeof(identificador));
        if (resultado == 0) {
            return 0;
        }
        if (resultado < 0 || !normalizarIdentificador(identificador)) {
            printf("Identificador invalido. Use exatamente 7 letras ou numeros.\n");
        } else if (identificadorJaExiste(*veiculos, *quantidade, identificador)) {
            printf("Identificador ja cadastrado.\n");
        } else {
            break;
        }
    }

    strcpy(novoVeiculo.identificador, identificador);

    while (1) {
        resultado = lerLinha("Descricao (ate 60 caracteres): ", novoVeiculo.descricao,
                             sizeof(novoVeiculo.descricao));
        if (resultado == 0) {
            return 0;
        }
        if (resultado == 1 && novoVeiculo.descricao[0] != '\0') {
            break;
        }
        printf("Descricao invalida. Informe de 1 a 60 caracteres.\n");
    }

    do {
        resultado = lerInteiro("Categoria (1 - Carro, 2 - Moto): ", &novoVeiculo.categoria);
        if (resultado == 0) {
            return 0;
        }
        if (resultado != 1 || (novoVeiculo.categoria != 1 && novoVeiculo.categoria != 2)) {
            printf("Categoria invalida. Informe 1 ou 2.\n");
        }
    } while (resultado != 1 || (novoVeiculo.categoria != 1 && novoVeiculo.categoria != 2));

    do {
        resultado = lerInteiro("Fileira (1 a 4): ", &novoVeiculo.fileira);
        if (resultado == 0) {
            return 0;
        }
        if (resultado != 1 || novoVeiculo.fileira < 1 || novoVeiculo.fileira > FILEIRAS) {
            printf("Fileira invalida. Informe um valor de 1 a 4.\n");
        }
    } while (resultado != 1 || novoVeiculo.fileira < 1 || novoVeiculo.fileira > FILEIRAS);

    do {
        resultado = lerInteiro("Coluna (1 a 5): ", &novoVeiculo.coluna);
        if (resultado == 0) {
            return 0;
        }
        if (resultado != 1 || novoVeiculo.coluna < 1 || novoVeiculo.coluna > COLUNAS) {
            printf("Coluna invalida. Informe um valor de 1 a 5.\n");
        }
    } while (resultado != 1 || novoVeiculo.coluna < 1 || novoVeiculo.coluna > COLUNAS);

    if (vagas[novoVeiculo.fileira - 1][novoVeiculo.coluna - 1] == 1) {
        printf("Cadastro recusado: vaga ocupada.\n");
        return 0;
    }

    if (*quantidade == *capacidade && !ampliarColecao(veiculos, capacidade)) {
        printf("Cadastro cancelado: memoria insuficiente.\n");
        return 0;
    }

    (*veiculos)[*quantidade] = novoVeiculo;
    vagas[novoVeiculo.fileira - 1][novoVeiculo.coluna - 1] = 1;
    (*quantidade)++;

    printf("Veiculo %s cadastrado na fileira %d, coluna %d.\n",
           novoVeiculo.identificador, novoVeiculo.fileira, novoVeiculo.coluna);
    return 1;
}
