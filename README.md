# Sistema de Gerenciamento de Estacionamento

**Disciplina:** Lógica de Programação e Algoritmos  
**Semestre:** 2º semestre — 2026/2  
**Trabalho:** Trabalho do 2º Bimestre  
**Linguagem:** C

## Integrantes

- **Sérvio Henrique Silva Alves** — GitHub: [@serviohsa-wq](https://github.com/serviohsa-wq)
- **Mateus Henrique Benício Magalhães dos Santos** — GitHub: [@MateusHBM](https://github.com/MateusHBM)

## 1. Cenário e escopo

O sistema simula o gerenciamento de um estacionamento com **4 fileiras e 5 colunas**, totalizando **20 vagas**. Por um menu executado no terminal, permite cadastrar veículos, consultar e atualizar seus dados, movimentá-los entre vagas, removê-los e visualizar a ocupação.

As vagas são representadas em uma matriz fixa, enquanto os dados dos veículos são mantidos em uma coleção alocada dinamicamente. O programa impede identificadores duplicados, cadastro em vagas ocupadas, movimentação para vagas indisponíveis e operações fora dos limites válidos. A categoria de cada veículo é **1 (carro)** ou **2 (moto)**.

**Limitações conhecidas:** os dados existem apenas durante a execução, sem salvamento em arquivo ou banco de dados; o estacionamento tem somente 20 vagas. Após a remoção de um veículo, a quantidade de registros diminui, mas a capacidade de memória já reservada não é reduzida automaticamente.

## 2. Funcionalidades e menu

| Opção | Operação | O que faz |
|---|---|---|
| 1 | Cadastrar veículo | Valida identificador, descrição, categoria e vaga; registra o veículo se a vaga estiver livre. |
| 2 | Consultar veículo | Busca pelo identificador e exibe seus dados. |
| 3 | Atualizar veículo | Altera a descrição, a categoria ou ambas; também permite cancelar. |
| 4 | Mover veículo | Altera a posição do veículo, liberando a vaga anterior. |
| 5 | Remover veículo | Exclui o registro e libera a vaga ocupada. |
| 6 | Listar veículos | Mostra os veículos atualmente cadastrados. |
| 7 | Exibir mapa | Mostra as 20 vagas, com `L` (livre) e `O` (ocupada). |
| 8 | Relatório de ocupação | Apresenta totais, percentual de ocupação e quantidades de carros e motos. |
| 0 | Encerrar | Termina o programa e libera a memória alocada. |

O menu exibido pelo programa é:

```text
=== ESTACIONAMENTO ===
1 - Cadastrar veiculo
2 - Consultar veiculo por identificador
3 - Atualizar descricao ou categoria
4 - Mover veiculo para outra vaga
5 - Remover veiculo
6 - Listar veiculos cadastrados
7 - Exibir mapa de vagas
8 - Exibir relatorio da ocupacao
0 - Encerrar
Escolha uma opcao:
```

### Regras de entrada

- **Identificador:** exatamente 7 caracteres alfanuméricos, convertidos para maiúsculas; não pode se repetir.
- **Descrição:** entre 1 e 60 caracteres.
- **Categoria:** `1` para carro ou `2` para moto.
- **Localização:** fileira de `1` a `4` e coluna de `1` a `5`.
- **Ocupação:** uma vaga não pode receber dois veículos; também não é possível mover um veículo para sua própria vaga.

## 3. Estruturas utilizadas

### 3.1. Matriz 4 × 5

A matriz `int vagas[FILEIRAS][COLUNAS]`, criada em `main.c`, armazena o estado de cada vaga: `0` significa livre e `1` significa ocupada. As constantes `FILEIRAS = 4` e `COLUNAS = 5` estão definidas em `estacionamento.h`. Como o usuário informa posições começando em 1, o programa subtrai 1 ao acessar os índices da matriz.

Exemplo de mapa inicialmente vazio:

```text
Mapa de vagas:
    C1 C2 C3 C4 C5
F1   L  L  L  L  L
F2   L  L  L  L  L
F3   L  L  L  L  L
F4   L  L  L  L  L
Legenda: L - Livre; O - Ocupada.
```

### 3.2. Estrutura `Veiculo`

Definida no arquivo `estacionamento.h`, a `struct` reúne os dados de cada veículo:

```c
typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;
```

Os vetores de caracteres incluem espaço para o caractere terminador `\0`. A categoria usa `1` para carro e `2` para moto; `fileira` e `coluna` indicam a localização do veículo.

### 3.3. Coleção dinâmica: quantidade e capacidade

Em `main.c`, um ponteiro `Veiculo *veiculos` recebe um bloco de memória criado com `malloc()`, inicialmente suficiente para **2 registros** (`CAPACIDADE_INICIAL = 2`). O sistema mantém dois contadores:

- **`quantidade`:** número de veículos efetivamente cadastrados. Começa em 0, aumenta no cadastro e diminui na remoção.
- **`capacidade`:** número de registros que cabem na memória atualmente reservada. Começa em 2.

Quando `quantidade == capacidade`, a função `ampliarColecao()`, em `cadastrar.c`, usa `realloc()` para **dobrar a capacidade** (2 → 4 → 8 → 16 → 32, se necessário). Apesar de a coleção poder reservar espaço para 32 registros, o limite físico continua sendo **20 veículos**, definido por `MAXIMO_VEICULOS`.

Ao remover um registro, `removerVeiculo()` desloca os elementos posteriores para manter a coleção contínua. Ao encerrar, `main()` chama `free(veiculos)`.

## 4. Organização e modularização

As implementações estão nos arquivos `.c`; os arquivos `.h` declaram as funções e compartilham definições. O arquivo `estacionamento.h` centraliza a `struct Veiculo` e as constantes utilizadas pelos demais módulos.

| Arquivo `.c` | Função(ões) e responsabilidade |
|---|---|
| `main.c` | `main()` — inicializa a matriz e a coleção, exibe o menu, chama as operações e libera a memória. |
| `cadastrar.c` | `cadastrarVeiculo()` — valida e cadastra veículos; `ampliarColecao()` — aumenta a memória reservada; auxiliares validam identificadores e duplicatas. |
| `consultar.c` | `consultarVeiculo()` — busca e apresenta os dados de um veículo. |
| `atualizar.c` | `atualizarVeiculo()` — atualiza descrição, categoria ou ambas; funções auxiliares validam os novos valores. |
| `mover.c` | `moverVeiculo()` — verifica o destino e atualiza a matriz e a posição registrada. |
| `remover.c` | `removerVeiculo()` — libera a vaga, compacta a coleção e diminui a quantidade. |
| `listar.c` | `listarVeiculos()` — mostra todos os registros existentes. |
| `mapa.c` | `mapaVeiculos()` — apresenta a matriz de ocupação. |
| `relatorio.c` | `gerarRelatorio()` — calcula vagas livres/ocupadas, percentual e totais por categoria. |
| `utils.c` | `localizarVeiculo()`, `lerLinha()`, `lerInteiro()`, `lerIdentificador()` e `descartarRestanteDaLinha()` — centralizam busca e tratamento de entradas. |

## 5. Compilação e execução

**Requisito:** compilador GCC instalado. Mantenha todos os arquivos `.c` e `.h` na mesma pasta, com os nomes originais (por exemplo, `estacionamento.h`, e não `estacionamento(1).h`).

Na pasta do projeto, compile **todos os arquivos `.c`**:

```bash
gcc -std=c11 -Wall -Wextra *.c -o estacionamento
```

Execute o programa:

- **Windows (PowerShell):** `./estacionamento.exe` ou `.\estacionamento.exe`
- **Linux:** `./estacionamento`

O programa exibirá o menu no terminal. Para encerrar, escolha a opção `0`.

## 6. Testes executados

Os testes abaixo foram realizados com os arquivos enviados, compilados com GCC e executados com entradas fornecidas ao programa pelo terminal. Os cenários foram executados de forma independente, começando com o estacionamento vazio. Em exemplos com vários passos, as operações foram feitas em sequência na mesma execução.

| Nº | Entrada / operação | Resultado esperado | Resultado observado | Situação |
|---|---|---|---|---|
| 1 | Cadastrar `ABC1234` na vaga F1/C1 e consultá-lo | Cadastro e consulta corretos | Confirmação do cadastro e dados do veículo exibidos | Aprovado |
| 2 | Cadastrar `ABC1234` e tentar repetir o identificador | Rejeitar identificador duplicado | Exibido `Identificador ja cadastrado.` | Aprovado |
| 3 | Cadastrar dois veículos na vaga F1/C1 | Recusar o segundo cadastro | Exibido `Cadastro recusado: vaga ocupada.` | Aprovado |
| 4 | Consultar identificador inexistente `XYZ9999` | Informar que não foi encontrado | Exibido `Veiculo nao localizado.` | Aprovado |
| 5 | Alterar descrição e categoria do veículo `ABC1234` | Salvar os dois novos valores | Consulta apresentou `Nova descricao` e categoria `Moto` | Aprovado |
| 6 | Mover `ABC1234` de F1/C1 para F2/C3 | Atualizar localização e liberar origem | Mensagem de sucesso e mapa com F2/C3 ocupada | Aprovado |
| 7 | Mover um veículo para uma vaga ocupada | Recusar movimentação | Exibida mensagem indicando destino ocupado | Aprovado |
| 8 | Remover `ABC1234` e consultar relatório | Remover registro e liberar vaga | Relatório mostrou 0 vagas ocupadas e 20 livres | Aprovado |
| 9 | Cadastrar um carro e uma moto; listar e gerar relatório | Exibir ambos e ocupação de 10% | Lista exibida; relatório mostrou 1 carro, 1 moto e 10,00% | Aprovado |
| 10 | Digitar opção numérica `9` no menu | Informar opção inválida | Exibida mensagem de opção inválida | Aprovado |
| 11 | Informar fileira `9` durante o cadastro e depois corrigir para `1` | Solicitar uma fileira válida | Exibida mensagem de fileira inválida; cadastro concluído após correção | Aprovado |
| 12 | Cadastrar 20 veículos em vagas distintas e tentar um 21º | Aceitar 20 cadastros e recusar o próximo | 20 cadastros realizados; exibido `Cadastro recusado: estacionamento lotado.` | Aprovado |

**Resultado:** 12 cenários aprovados nesta verificação. Os testes demonstram o comportamento observado para esses casos, mas não substituem uma verificação exaustiva de todas as entradas possíveis.

## 7. Distribuição das responsabilidades e integração das branches

### Sérvio Henrique Silva Alves

Responsável pela criação da estrutura inicial do projeto, incluindo os arquivos `utils.c`, `utils.h`, `main.c` e `estacionamento.h`. Também desenvolveu as funcionalidades de listagem e movimentação de veículos, visualização do mapa de vagas e geração do relatório de ocupação do estacionamento.

### Mateus Henrique Benício Magalhães dos Santos

Responsável pelo desenvolvimento das funcionalidades de cadastro, remoção, consulta e atualização dos dados dos veículos.

### Integração das Branches

Durante o desenvolvimento, foram criadas as seguintes branches para organizar a implementação das funcionalidades:

- `remover-veiculo`
- `atualizar-veiculos`
- `cadastrar-veiculo`
- `relatorio-ocupacao`
- `mover-veiculo`
- `listar-veiculos`
- `mapa-vagas`

Cada branch foi utilizada para desenvolver funcionalidades específicas do sistema, permitindo que os integrantes trabalhassem em diferentes partes do projeto.

Após a implementação das funcionalidades, as alterações eram enviadas ao repositório remoto utilizando o comando `git push origin <nome-da-branch>`. Em seguida, a integração com a branch principal (`main`) era realizada por meio do merge na interface do GitHub.

Para manter o ambiente local atualizado, eram utilizados os comandos `git status`, para verificar o estado dos arquivos e da branch atual, e `git pull`, para obter as atualizações do repositório remoto.

Esse processo permitiu organizar o desenvolvimento em módulos e integrar gradualmente as funcionalidades ao sistema principal.

## 8. Declarações individuais de autoria, uso de IA e referências

### Declaração de Autoria

O projeto foi desenvolvido de forma colaborativa pelos integrantes **Sérvio Henrique Silva Alves** e **Mateus Henrique Benício Magalhães dos Santos**, respeitando a divisão de responsabilidades apresentada anteriormente.

Cada integrante foi responsável pela concepção, desenvolvimento e implementação das funcionalidades atribuídas a si, contribuindo para a construção e integração do sistema.

### Uso de Inteligência Artificial

Foram utilizadas ferramentas de inteligência artificial como apoio ao desenvolvimento do projeto, principalmente para:

- Organização e revisão do código-fonte.
- Identificação e correção de possíveis falhas.
- Esclarecimento de dúvidas relacionadas à sintaxe da linguagem C.
- Orientação sobre comandos Git e gerenciamento de branches.
- Estruturação, revisão e elaboração do arquivo `README.md`.

As ferramentas foram utilizadas como recursos auxiliares, preservando a participação dos integrantes nas decisões e na implementação das funcionalidades.

### Referências Externas

- **Google Gemini:** consultas relacionadas à utilização de comandos Git e ao gerenciamento do repositório.
- **OpenAI ChatGPT:** auxílio na elaboração do `README.md`, organização e revisão do código-fonte.

### Declaração Individual

**Sérvio Henrique Silva Alves:** Declaro minha participação autoral no desenvolvimento das funcionalidades sob minha responsabilidade, conforme descrito na seção de distribuição de tarefas, e reconheço o uso das ferramentas de inteligência artificial nas atividades mencionadas.

**Mateus Henrique Benício Magalhães dos Santos:** Declaro minha participação autoral no desenvolvimento das funcionalidades sob minha responsabilidade, conforme descrito na seção de distribuição de tarefas, e reconheço o uso das ferramentas de inteligência artificial nas atividades mencionadas, quando aplicável.

## 9. Considerações finais

O projeto aplica conceitos de **matrizes, `struct`, ponteiros, alocação dinâmica, funções e modularização** a um problema de gerenciamento de estacionamento. O sistema mantém a correspondência entre o registro de cada veículo e a ocupação da matriz, permitindo operações de cadastro, consulta, atualização, movimentação, remoção e geração de relatórios durante a execução.
