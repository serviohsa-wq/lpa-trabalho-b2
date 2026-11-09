#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "consultar.h"

static void descartarRestanteDaLinha(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

static int lerIdentificador(char identificador[8]) {
    char entrada[9];
    size_t comprimento;
    size_t indice;

    printf("Identificador (7 caracteres alfanumericos): ");
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    comprimento = strcspn(entrada, "\n");
    if (entrada[comprimento] != '\n') {
        descartarRestanteDaLinha();
        return -1;
    }
    entrada[comprimento] = '\0';

    if (comprimento != 7) {
        return -1;
    }

    for (indice = 0; indice < comprimento; indice++) {
        if (!isalnum((unsigned char)entrada[indice])) {
            return -1;
        }
        identificador[indice] = (char)toupper((unsigned char)entrada[indice]);
    }
    identificador[comprimento] = '\0';
    return 1;
}

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
