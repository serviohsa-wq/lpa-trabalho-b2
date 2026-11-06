#include <stdio.h>
#include <string.h>

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria; 
    int fileira;        
    int coluna;
} Veiculo;
 
int main() {
    int opcao = 1; // Inicializamos com 1 para o while executar pelo menos a primeira vez

    while(opcao != 0) {
        printf("\n\n=== ESTACIONAMENTO ===\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Consultar veiculo por identificador\n");
        printf("3 - Atualizar descricao ou categoria\n");
        printf("4 - Mover veiculo para outra vaga\n");
        printf("5 - Remover veiculo\n");
        printf("6 - Listar veiculos cadastrados\n");
        printf("7 - Exibir mapa de vagas\n");
        printf("8 - Exibir relatorio da ocupacao\n");
        printf("0 - Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Aqui depois entraremos com o switch/case para tratar cada opcao
    }

    return 0;
}