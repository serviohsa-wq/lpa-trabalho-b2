#include <stdio.h>
#include <string.h>

#include "consultar.h"
#include "utils.h"

int consultarVeiculo(const Veiculo *veiculos, int quantidade) {
    char identificador[8];
    int resultado;
    int indice;
    const char *categoria;

    resultado = lerIdentificador(identificador);
    if (resultado == 0) {
        return 0;
    }
    if (resultado < 0) {
        printf("Identificador invalido. Use exatamente 7 letras ou numeros.\n");
        return 0;
    }

    for (indice = 0; indice < quantidade; indice++) {
        if (strcmp(veiculos[indice].identificador, identificador) == 0) {
            categoria = veiculos[indice].categoria == 1 ? "Carro" : "Moto";
            printf("\nVeiculo encontrado:\n");
            printf("Identificador: %s\n", veiculos[indice].identificador);
            printf("Descricao: %s\n", veiculos[indice].descricao);
            printf("Categoria: %s\n", categoria);
            printf("Posicao: Fileira %d, Coluna %d\n",
                   veiculos[indice].fileira, veiculos[indice].coluna);
            return 1;
        }
    }

    printf("Veiculo nao localizado.\n");
    return 0;
}
