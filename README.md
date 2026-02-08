# Sistema de Análise de Dados Olímpicos 🥉🥈🥇

Este projeto foi desenvolvido na disciplina de **Programação Imperativa** da **Universidade Federal  de Sergipe**, solicitado pelo professor **Kalil Araújo Bispo**. O software processa grandes bases de dados históricas das Olimpíadas (arquivos CSV) para gerar estatísticas e insights sobre atletas, medalhas e a evolução dos jogos.

## Funcionalidades do Sistema

O programa conta com um menu interativo no console que oferece as seguintes análises:

1.  **Média de Altura por Ano** (Módulo: `alturamediaporano.c`)
    * Calcula a altura média de todos os atletas medalhistas em um ano específico digitado pelo usuário.
2.  **Evolução da Participação Feminina** (Módulo: `evolucaoMulheres.c`)
    * Gera uma tabela cronológica exibindo a quantidade absoluta de mulheres em cada edição dos jogos.
3.  **Medalhista Mais Alto** (Módulo: `MaiorAlturaMedalhista.c`)
    * Identifica o atleta medalhista mais alto de uma edição específica ou de toda a história olímpica.
4.  **Diversidade de Esportes Femininos** (Módulo: `evo_esportes_femininos.c`)
    * Analisa o crescimento da quantidade de modalidades distintas que tiveram participação feminina ao longo dos anos.

---

## Organização dos arquivos
* `main.c`: Ponto de entrada, menu e gerenciamento de memória.
* `olimpiadas.h`: Cabeçalho (Header) que conecta todos os módulos.
* `csv_utils.c`: Biblioteca auxiliar para leitura de CSV.
* `*.c`: Arquivos com a lógica específica de cada questão.

---

## Como Compilar e Executar

### Pré-requisitos
* Compilador C (GCC) ou CMake.
* **Gnuplot:** É necessário ter o Gnuplot instalado e acessível via terminal (PATH) para gerar gráficos.
* **Importante:** Os arquivos de dados `bios.csv` e `results.csv` devem estar **na mesma pasta** do executável gerado.

### Opção 1: Compilação via Terminal (GCC)
Se você estiver usando o terminal (VS Code, PowerShell, Linux), execute o comando abaixo para compilar todos os módulos juntos:

```bash
gcc main.c csv_utils.c alturamediaporano.c evolucaoMulheres.c MaiorAlturaMedalhista.c evo_esportes_femininos.c plotagemGraficos.c -o olimpiadas
```

Para executar:
```bash
./olimpiadas
```

### Opção 2: Compilação via CMake (CLion)
O projeto já inclui um arquivo CMakeLists.txt. Basta abrir a pasta do projeto na IDE, recarregar o CMake e clicar no botão Run.

---
## Autores

* Renato Vasconcelos Campos Filho
* Rhuan Pablo Silva Santos
* Victor Gabriel Santos Alves
