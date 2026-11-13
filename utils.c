#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils.h"

void descartarRestanteDaLinha(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerLinha(const char *mensagem, char *destino, size_t tamanho) {
    size_t comprimento;

    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        return 0;
    }

    comprimento = strcspn(destino, "\n");
    if (destino[comprimento] == '\n') {
        destino[comprimento] = '\0';
    } else {
        descartarRestanteDaLinha();
        return -1;
    }

    return 1;
}

int lerInteiro(const char *mensagem, int *valor) {
    char linha[64];
    char *fim;
    long numero;
    int resultado;

    resultado = lerLinha(mensagem, linha, sizeof(linha));
    if (resultado <= 0) {
        return resultado;
    }

    numero = strtol(linha, &fim, 10);
    if (*linha == '\0' || *fim != '\0') {
        return -1;
    }

    *valor = (int)numero;
    return 1;
}

int lerIdentificador(char identificador[8]) {
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