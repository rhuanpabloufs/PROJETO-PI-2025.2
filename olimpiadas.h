#ifndef OLIMPIADAS_H
#define OLIMPIADAS_H

// Estrutura de um atleta
typedef struct {
    int id;               // ID do Atleta
    char nome[100];       // Nome
    char sexo;            // 'M' ou 'F'
    float altura;         // Em cm
    float peso;           // Em kg
} Atleta;

// Adicao para evitar repeticao
// Estrutura ResultadosEdicao trazida para que o olimpiadas.h possa "enxergar" e possamos definir a funcao de exibir graficos aqui
typedef struct {
    char estacao[10];
    int anoDeOcorrencia;
    int qtdMulheres;
    // classificar ano por meio de código para ser possível de comparar adicionando 1 para verão e 2 para inverno
    int codigoEdicao; // Código único (ano * 10) + Estação
					// Exemplo, Rio 2016: 2016 * 10 + 1 (verão) = 20161
} ResultadosEdicao;

// Estrutura para controlar os esportes por edição
typedef struct {
    int codigoEdicao;       // Seguindo a lógica criada anteriormente 20161 (Rio/Verão)
    char estacao[10];
    int ano;
    // Lista de nomes de esportes já contados nesta edição (matriz de strings)
    // Suporta até 200 esportes diferentes por edição (valor seguro)
    char esportes_vistos[200][50];
    int qtd_esportes_distintos;
} EdicaoEsportes;

Atleta* ler_atletas(const char* nome_arquivo, int* qtd_total);
char* get_dado(char** cursor); // função para leitura do arquivo criada no csv_utils
void resolver_q6_altura_media(); // Nova função criada
void resolver_q17_evolucao_mulheres(Atleta* atletas, int qtd_total_atletas); // Nova função para a Q17, que recebe o vetor carregado para cruzarmos os dados
void resolver_maior_altura_medalhista(); // Adicionando as funções novas da questão criada
void resolver_evo_esportes_femininos(Atleta* atletas, int qtd_total_atletas);
void plotar_grafico_evolucao(void* lista, int qtd_edicoes, int grafico); // adicionando funcao para plotar graficos

#endif //OLIMPIADAS_H