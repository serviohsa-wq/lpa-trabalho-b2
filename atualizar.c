#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atualizar.h"
#include "utils.h"

int lerDescricaoAtualizar(char descricao[61]) {
    char entrada[62];
    int resultado;

    resultado = lerLinha("Nova descricao (ate 60 caracteres): ",
                         entrada, sizeof(entrada));
    if (resultado != 1 || entrada[0] == '\0') {
        printf("Descricao invalida. Informe de 1 a 60 caracteres.\n");
        return 0;
    }

    strcpy(descricao, entrada);
    return 1;
}

int lerCategoriaAtualizar(int *categoria) {
    int resultado = lerInteiro("Nova categoria (1-Carro, 2-Moto): ", categoria);

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

    if (lerIdentificador(identificador) != 1) {
        printf("Identificador invalido. Use exatamente 7 letras ou numeros.\n");
        return 0;
    }

    indice = localizarVeiculo(veiculos, quantidade, identificador);
    if (indice < 0) {
        printf("Veiculo nao localizado.\n");
        return 0;
    }

    if (lerInteiro("Atualizar 1-Descricao, 2-Categoria, 3-Ambos, 0-Cancelar: ",
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
