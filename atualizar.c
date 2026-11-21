#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atualizar.h"

void descartarRestanteDaLinhaAtualizar(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerLinhaAtualizar(const char *mensagem, char *destino, size_t tamanho) {
    size_t comprimento;

    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        return 0;
    }

    comprimento = strcspn(destino, "\n");
    if (destino[comprimento] != '\n') {
        descartarRestanteDaLinhaAtualizar();
        return -1;
    }

    destino[comprimento] = '\0';
    return 1;
}

int lerInteiroAtualizar(const char *mensagem, int *valor) {
    char linha[64];
    char *fim;
    long numero;
    int resultado;

    resultado = lerLinhaAtualizar(mensagem, linha, sizeof(linha));
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

int lerIdentificadorAtualizar(char identificador[8]) {
    char entrada[9];
    size_t comprimento;
    size_t indice;
    int resultado;

    resultado = lerLinhaAtualizar("Identificador (7 caracteres alfanumericos): ",
                         entrada, sizeof(entrada));
    if (resultado <= 0) {
        return resultado;
    }

    comprimento = strlen(entrada);
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

int localizarVeiculoAtualizar(const Veiculo *veiculos, int quantidade,
                            const char *identificador) {
    int indice;

    for (indice = 0; indice < quantidade; indice++) {
        if (strcmp(veiculos[indice].identificador, identificador) == 0) {
            return indice;
        }
    }

    return -1;
}

int lerDescricaoAtualizar(char descricao[61]) {
    char entrada[62];
    int resultado;

    resultado = lerLinhaAtualizar("Nova descricao (ate 60 caracteres): ",
                         entrada, sizeof(entrada));
    if (resultado != 1 || entrada[0] == '\0') {
        printf("Descricao invalida. Informe de 1 a 60 caracteres.\n");
        return 0;
    }

    strcpy(descricao, entrada);
    return 1;
}

int lerCategoriaAtualizar(int *categoria) {
    int resultado = lerInteiroAtualizar("Nova categoria (1-Carro, 2-Moto): ", categoria);

    if (resultado != 1 || (*categoria != 1 && *categoria != 2)) {
        printf("Categoria invalida. Informe 1 ou 2.\n");
        return 0;
    }

    return 1;
}

int atualizarVeiculo(Veiculo *veiculos, int quantidade) {
    char identificador[8];
    char novaDescricao[61];
    int novaCategoria;
    int escolha;
    int indice;

    if (quantidade == 0) {
        printf("Nao ha veiculos cadastrados para atualizar.\n");
        return 0;
    }

    if (lerIdentificadorAtualizar(identificador) != 1) {
        printf("Identificador invalido. Use exatamente 7 letras ou numeros.\n");
        return 0;
    }

    indice = localizarVeiculoAtualizar(veiculos, quantidade, identificador);
    if (indice < 0) {
        printf("Veiculo nao localizado.\n");
        return 0;
    }

    if (lerInteiroAtualizar("Atualizar 1-Descricao, 2-Categoria, 3-Ambos, 0-Cancelar: ",
                   &escolha) != 1 || escolha < 0 || escolha > 3) {
        printf("Opcao de atualizacao invalida.\n");
        return 0;
    }
    if (escolha == 0) {
        printf("Atualizacao cancelada.\n");
        return 0;
    }

    strcpy(novaDescricao, veiculos[indice].descricao);
    novaCategoria = veiculos[indice].categoria;

    if ((escolha == 1 || escolha == 3) && !lerDescricaoAtualizar(novaDescricao)) {
        return 0;
    }
    if ((escolha == 2 || escolha == 3) && !lerCategoriaAtualizar(&novaCategoria)) {
        return 0;
    }

    strcpy(veiculos[indice].descricao, novaDescricao);
    veiculos[indice].categoria = novaCategoria;
    printf("Veiculo %s atualizado com sucesso.\n", veiculos[indice].identificador);
    return 1;
}
