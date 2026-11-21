#ifndef UTILS_H
#define UTILS_H

#include "estacionamento.h"

int localizarVeiculo(const Veiculo *veiculos, int quantidade,
                            const char *identificador);
void descartarRestanteDaLinha(void);
int lerLinha(const char *mensagem, char *destino, size_t tamanho);
int lerInteiro(const char *mensagem, int *valor);
int lerIdentificador(char identificador[8]);

#endif