#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5
#define CAPACIDADE_INICIAL 2
#define MAXIMO_VEICULOS (FILEIRAS * COLUNAS)

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria; 
    int fileira;        
    int coluna;
} Veiculo;

#endif
