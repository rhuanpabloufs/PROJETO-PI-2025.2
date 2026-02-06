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

Atleta* ler_atletas(const char* nome_arquivo, int* qtd_total);
char* get_dado(char** cursor); // função para leitura do arquivo criada no csv_utils
void resolver_q6_altura_media(); // Nova função criada
void resolver_q17_evolucao_mulheres(Atleta* atletas, int qtd_total_atletas); // Nova função para a Q17, que recebe o vetor carregado para cruzarmos os dados
void resolver_maior_altura_medalhista(); // Adicionando as funções novas da questão criada
void resolver_evo_esportes_femininos(Atleta* atletas, int qtd_total_atletas);

#endif //OLIMPIADAS_H