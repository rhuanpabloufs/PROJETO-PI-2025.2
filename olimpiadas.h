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

#endif //OLIMPIADAS_H