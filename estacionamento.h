#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria; 
    int fileira;        
    int coluna;
} Veiculo;

#endif