#include <stdio.h>

#include "relatorio.h"

void gerarRelatorio(const Veiculo *veiculos, int quantidade) {
    int carros = 0;
    int motos = 0;
    float percentualOcupacao = 0.0;

    for(int i = 0; i < quantidade; i++) {
        if(veiculos[i].categoria == 1) {
            carros++;
        } else {
            motos++;
        }
    }

    percentualOcupacao = ((float)quantidade / MAXIMO_VEICULOS) * 100.0f;

    printf("\nRelatorio de ocupacao:\n");
    printf("Total de vagas........: %d\n", MAXIMO_VEICULOS);
    printf("Vagas ocupadas........: %d\n", quantidade);
    printf("Vagas livres..........: %d\n", MAXIMO_VEICULOS - quantidade);
    printf("Percentual de ocupacao: %.2f%%\n", percentualOcupacao);
    printf("Quantidade de carros..: %d\n", carros);
    printf("Quantidade de motos...: %d\n\n", motos);
}