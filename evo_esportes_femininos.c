// QUESTAO RELACIONADA COM O ARQUIVO: Calcular quantos esportes distintos tiveram participação feminina em cada edição das Olimpíadas

// INCLUSAO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "olimpiadas.h"

// Função de Victor para pegar texto de uma coluna específica
void pegarTexto_reuso(char* frase, int colunaDesejada, char* destino) {
    int aspas = 0;
    int coluna = 0;
    int indice = 0;
    destino[0] = '\0';

    for(int i = 0; frase[i] != '\0'; i++) {
        char charAtual = frase[i];

        if(charAtual == '"') {
            aspas = !aspas;
        }
        else if(charAtual == ',' && !aspas) {
            if (coluna == colunaDesejada) {
                destino[indice] = '\0';
                return;
            }
            coluna++;
            indice = 0;
        }
        else {
            if (coluna == colunaDesejada) {
                if(charAtual != '"') {
                    destino[indice++] = charAtual;
                }
            }
        }
    }
    // Caso termine a linha na coluna desejada
    if (coluna == colunaDesejada) {
        destino[indice] = '\0';
    }
}


// Verifica se um esporte (string) já está na lista daquela edição
int esporte_ja_contado(EdicaoEsportes* edicao, char* nome_esporte) {
    for(int i = 0; i < edicao->qtd_esportes_distintos; i++) {
        if(strcmp(edicao->esportes_vistos[i], nome_esporte) == 0) {
            return 1; // Já existe
        }
    }
    return 0; // É novo
}

// Busca a edição na lista ou cria uma nova se não existir
int buscar_ou_criar_edicao_esp(EdicaoEsportes* lista, int* qtd, int codigo, int ano, char* estacao) {
    for(int i = 0; i < *qtd; i++) {
        if(lista[i].codigoEdicao == codigo) {
            return i;
        }
    }
    // Nova edição
    int idx = *qtd;
    lista[idx].codigoEdicao = codigo;
    lista[idx].ano = ano;
    strcpy(lista[idx].estacao, estacao);
    lista[idx].qtd_esportes_distintos = 0;
    (*qtd)++;
    return idx;
}

// Comparação para ordenar por ano (qsort)
int comparar_edicoes_esp(const void* a, const void* b) {
    return ((EdicaoEsportes*)a)->codigoEdicao - ((EdicaoEsportes*)b)->codigoEdicao;
}

// FUNÇÃO PRINCIPAL
void resolver_evo_esportes_femininos(Atleta* atletas, int qtd_total_atletas) {
    printf("\n--- CALCULO DE ESPORTES DISTINTOS COM MULHERES ---\n");
    printf("Processando dados...\n");

    // 1. Mapear Sexo na Memória (ID -> Sexo)
    // Isso evita ter que ler o bios.csv de novo
    char* sexo_por_id = (char*) calloc(200000, sizeof(char));
    for(int i = 0; i < qtd_total_atletas; i++) {
        if(atletas[i].id < 200000) {
            sexo_por_id[atletas[i].id] = atletas[i].sexo;
        }
    }

    // 2. Preparar Lista de Edições
    EdicaoEsportes* lista_edicoes = (EdicaoEsportes*) calloc(100, sizeof(EdicaoEsportes));
    int qtd_edicoes = 0;

    FILE* file = fopen("results.csv", "r");
    if(!file) {
        printf("ERRO: results.csv nao encontrado.\n");
        free(sexo_por_id);
        free(lista_edicoes);
        return;
    }

    char linha[2048];
    char bufferGames[100];
    char bufferID[50];
    char bufferEsporte[100];
    char bufferEstacao[20];
    int ano;

    fgets(linha, 2048, file); // Pula cabeçalho

    while(fgets(linha, 2048, file)) {

        // Coluna 6: ID do Atleta
        pegarTexto_reuso(linha, 6, bufferID);
        int id = atoi(bufferID);

        // Verifica se é Mulher ('F') e ID válido
        if(id > 0 && id < 200000 && sexo_por_id[id] == 'F') {

            // Coluna 0: Games (ex: "1912 Summer Olympics")
            pegarTexto_reuso(linha, 0, bufferGames);

            // Coluna 8: Discipline/Esporte (ex: "Swimming")
            pegarTexto_reuso(linha, 8, bufferEsporte);

            // Extrai ano e estação
            sscanf(bufferGames, "%d %s", &ano, bufferEstacao);

            if(ano > 0 && strlen(bufferEsporte) > 0) {
                int codigo = (ano * 10) + ((strcmp(bufferEstacao, "Summer") == 0) ? 1 : 2);

                // Pega a struct daquela edição
                int idx = buscar_ou_criar_edicao_esp(lista_edicoes, &qtd_edicoes, codigo, ano, bufferEstacao);

                // Se esse esporte AINDA NÃO foi contado nesta edição, adiciona na lista
                if(!esporte_ja_contado(&lista_edicoes[idx], bufferEsporte)) {
                    strcpy(lista_edicoes[idx].esportes_vistos[lista_edicoes[idx].qtd_esportes_distintos], bufferEsporte);
                    lista_edicoes[idx].qtd_esportes_distintos++;
                }
            }
        }
    }
    fclose(file);

    // 3. Ordenar e Exibir
    qsort(lista_edicoes, qtd_edicoes, sizeof(EdicaoEsportes), comparar_edicoes_esp);

    printf("\n%-6s | %-10s | %s\n", "ANO", "ESTACAO", "QTD ESPORTES (FEM)");
    printf("--------------------------------------\n");
    for(int i = 0; i < qtd_edicoes; i++) {
        printf("%-6d | %-10s | %d\n",
            lista_edicoes[i].ano,
            lista_edicoes[i].estacao,
            lista_edicoes[i].qtd_esportes_distintos);
    }

    int visualizarGrafico = 0;
    printf("\nDeseja ver o grafico da questao? (1 - sim / 0 - nao): ");
    scanf("%d", &visualizarGrafico);

    if (visualizarGrafico == 1){
        // chamada da funcao plotar grafico com 2, simbolizando o arquivo evo_esportes_femininos
        plotar_grafico_evolucao(lista_edicoes, qtd_edicoes, 2);
    }

    free(sexo_por_id);
    free(lista_edicoes);
}