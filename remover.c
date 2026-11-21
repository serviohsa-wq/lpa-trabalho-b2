#include <stdio.h>

#include "remover.h"
#include "utils.h"

int removerVeiculo(Veiculo *veiculos, int *quantidade,
                   int vagas[FILEIRAS][COLUNAS]) {
    char identificador[8];
    int resultado;
    int indice;
    int i;

    if (*quantidade == 0) {
        printf("Nenhum veiculo cadastrado para remover.\n");
        return 0;
    }

    resultado = lerIdentificador(identificador);

    if (resultado == 0) {
        return 0;
    }

    if (resultado == -1) {
        printf("Identificador invalido.\n");
        return 0;
    }

    indice = localizarVeiculo(veiculos, *quantidade, identificador);

    if (indice == -1) {
        printf("Veiculo nao encontrado.\n");
        return 0;
    }

    vagas[veiculos[indice].fileira - 1]
         [veiculos[indice].coluna - 1] = 0;

    for (i = indice; i < *quantidade - 1; i++) {
        veiculos[i] = veiculos[i + 1];
    }

    (*quantidade)--;

    printf("Veiculo %s removido com sucesso.\n", identificador);

    return 1;
}