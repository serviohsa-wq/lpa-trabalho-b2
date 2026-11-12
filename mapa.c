#include <stdio.h>

#include "mapa.h"

void mapaVeiculos(int vagas[FILEIRAS][COLUNAS]) {
    
    printf("Mapa de vagas:\n");
    printf("    C1 C2 C3 C4 C5\n");
    for(int i = 0; i < FILEIRAS; i++) {
        printf("F%d   ", i + 1);
        for(int j = 0; j < COLUNAS; j++) {
            if(vagas[i][j] == 0) {
                printf("L");
            } else {
                printf("O");
            }
            printf("  ");
        }
        printf("\n");
    }
    printf("Legenda: L - Livre; O - Ocupada.");
}