#include <stdio.h>
#include <stdlib.h>
#include "olimpiadas.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    printf("===========================================\n");
    printf("      SISTEMA DE ANALISE OLIMPICA\n");
    printf("===========================================\n");

    // 1. CARREGAMENTO DA BASE DE DADOS
    // Algumas questões leem o arquivo sozinhos,
    // mas mantemos isso aqui para a Q17 e para validar o arquivo.
    int qtd_atletas = 0;
    Atleta* meus_atletas = ler_atletas("bios.csv", &qtd_atletas);

    if (meus_atletas == NULL) {
        printf("ERRO CRITICO: Nao foi possivel carregar 'bios.csv'.\n");
        printf("Verifique se o arquivo esta na pasta do executavel.\n");
    }

    // 2. MENU INTERATIVO
    int opcao = 0;

    while (1) {
        printf("\n\n------------------------------------------------");
        printf("\n               MENU PRINCIPAL                   ");
        printf("\n------------------------------------------------");
        printf("\n1. Altura Media (Por Ano)         ");
        printf("\n2. Evolucao Mulheres (Por Ano)    ");
        printf("\n3. Maior Altura Medalhista        ");
        printf("\n4. Esportes com Mulheres ao longo dos anos          "); // Nova questão
        printf("\n0. Sair");
        printf("\n------------------------------------------------");
        printf("\nEscolha uma opcao: ");

        // Leitura segura da opção
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida (digite um numero)!\n");
            limpar_buffer();
            continue;
        }

        if (opcao == 0) {
            printf("\nEncerrando o sistema...\n");
            break;
        }

        switch (opcao) {
            case 1:
                // Questão 6
                resolver_q6_altura_media();
                break;

            case 2:
                // Questão 17 (Usa os dados carregados na main)
                if (meus_atletas != NULL) {
                    resolver_q17_evolucao_mulheres(meus_atletas, qtd_atletas);
                } else {
                    printf("\nERRO: Base de dados nao carregada para esta questao.\n");
                }
                break;

            case 3:
                // Nova Questão
                resolver_maior_altura_medalhista();
                break;

            case 4:
                if (meus_atletas != NULL) {
                    resolver_evo_esportes_femininos(meus_atletas, qtd_atletas);
                } else {
                    printf("Base de dados nao carregada!\n");
                }
                break;

            default:
                printf("\nOpcao invalida! Tente entre 0 e 3.\n");
        }

        printf("\nPressione ENTER para voltar ao menu...");
        limpar_buffer();
        getchar(); // Pausa para ler o resultado
    }

    // 3. LIMPEZA DE MEMÓRIA
    if (meus_atletas != NULL) {
        free(meus_atletas);
    }

    return 0;
}