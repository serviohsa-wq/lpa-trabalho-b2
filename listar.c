#include <stdio.h>

#include "listar.h"

void listarVeiculos(const Veiculo *veiculos, int quantidade) {
    if(quantidade == 0) {
        printf("Nenhum veiculo esta cadastrado no momento.\n");
        return;
    }

    printf("\n=== LISTA DE VEICULOS CADASTRADOS ===\n");
    for(int i = 0; i < quantidade; i++) {
        const char *categoria = veiculos[i].categoria == 1 ? "Carro" : "Moto";

        printf("----------------------------------------\n");
        printf("Veiculo %d:\n", i + 1);
        printf("Identificador: %s\n", veiculos[i].identificador);
        printf("Categoria: %s\n", categoria);
        printf("Descricao: %s\n", veiculos[i].descricao);
        printf("Posicao:Fileira %d, Coluna %d\n", veiculos[i].fileira, veiculos[i].coluna);
    }
    printf("----------------------------------------\n");
}