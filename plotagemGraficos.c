// Arquivo para plotagem dos graficos das questoes evolucaoMulheres e evo_esportes_femininos
// INCLUSÃO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "olimpiadas.h"

// EVITAR REPETICAO DE CODIGO
// configuracao para que o compilador possa identificar o sistema operacional e ultilizar o comando correto
#ifdef _WIN32 // eh windows?
    #define POPEN _popen // define que _popen abre processos do gnuplot (padrao windows)
    #define PCLOSE _pclose // "  " _pclose 
#else
    #define POPEN popen // nao sendo windows, utiliza popen (padrao linux/mac) 
    #define PCLOSE pclose
#endif

// funcao para enviar dados para o gnuplot e evitar o uso de dois loops na outra funcao desse arquivo
void envio_dados_gnuplot(FILE* gp, void* lista, int qtd, int tipo, char* estacao) {
    // criacao de ponteiros utilizando casting para cada struct, ja que o void esta generico
    ResultadosEdicao* dados_mulheres = (ResultadosEdicao*) lista;
    EdicaoEsportes* dados_esportes = (EdicaoEsportes*) lista;

    // loop unico que coletara os dados da estacao especifica e enviara para o gnuplot
    for (int i = 0; i < qtd; i++) {
        int anoAtual = 0; //(ano ou anoDeOcorrencia)
        int qtdInteresse = 0; // (qtdEsportes ou qtdMulheres)
        char estacaoAtual[20];

        // se o tipo for 1, coleta dados da evoMulheres (anoDeOcorrencia e qtdMulheres)
        if (tipo == 1) { 
            anoAtual = dados_mulheres[i].anoDeOcorrencia;
            qtdInteresse = dados_mulheres[i].qtdMulheres;
            strcpy(estacaoAtual, dados_mulheres[i].estacao);
        } else { // "" 2, coleta dados da evo_esportes_femininos (ano e qtd_esportes_distintos)
            anoAtual = dados_esportes[i].ano;
            qtdInteresse = dados_esportes[i].qtd_esportes_distintos;
            strcpy(estacaoAtual, dados_esportes[i].estacao);
        }

        // Se a estacao da vez no loop for a que pedimos na funcao logo abaixo, os dados sao enviados para o gnuplot
        if (strstr(estacaoAtual, estacao) != NULL) {
            fprintf(gp, "%d %d\n", anoAtual, qtdInteresse);
        }
    }
    
    // Finaliza o bloco de dados para o Gnuplot
    fprintf(gp, "e\n");
}

// Funcao utilizada para plotar o grafico de evo_esportes_femininos
void plotar_grafico_evolucao(void* lista, int qtd, int grafico) {
    // grafico 1 -> evolucaoMulheres (struct ResultadosEdicao)
    // grafico 2 -> evo_esportes_mulheres (struct EdicaoEsportes)
    printf("\nGerando grafico com Gnuplot...\n");
    
    // POPEN abre um processo externo como foi definido
	// -persistant mantem a janela do grafico aberta
    // tratamos o gnu plot como um arquivo
    FILE *gp = POPEN("gnuplot -persistent", "w"); 

    if (gp) { // verifica se o gnuplot abriu sem problemas

        // criacao de ponteiros utilizando casting para cada struct, ja que o void esta generico
        ResultadosEdicao* dadosMulheres = (ResultadosEdicao*) lista;
        EdicaoEsportes* dadosEsportes = (EdicaoEsportes*) lista;

        // variaveis para evitar a repeticao de scanf's
        char tituloGrafico[100];
        char nomeEixoY[20];

        // se o grafico for o 1 (evolucaoMulheres), defino caracteristicas especificas dele
        if (grafico == 1){
            strcpy(tituloGrafico, "Evolucao da QtdMulheres");
            strcpy(nomeEixoY, "QtdMulheres");
        }
        
        else {
            strcpy(tituloGrafico, "Evolucao da Qtd Esportes com Mulheres");
            strcpy(nomeEixoY, "QtdEsportes");
        }

		// Configuracoes do grafico
        fprintf(gp, "set grid\n"); // adicao de grade ao grafico para melhor visualizacao
        
        fprintf(gp, "set title '%s'\n", tituloGrafico); // titulo
        fprintf(gp, "set xlabel 'Ano'\n"); // nome do eixo x  
        fprintf(gp, "set ylabel '%s'\n", nomeEixoY); // nome do eixo y
        fprintf(gp, "set key top left box\n"); // Adiciona uma legenda em formato de caixa para diferenciar verao e inverno

        // Configuracao das linhas 
        // plot -> comando para desenhar
		// '-' -> indica que os dados do grafico vao ser colocados a seguir
		// using 1:2 -> primeira coluna x e segunda coluna y
		// lc rgb 'cor' -> define a cor da linha
		// a virgula entre as linhas serve para separar os graficos, ja que os 
        fprintf(gp, "plot '-' using 1:2 title 'Jogos de Verao' with linespoints lw 2 lc rgb 'orange', \
                           '' using 1:2 title 'Jogos de Inverno' with linespoints lw 2 lc rgb 'blue'\n");

        // envio dados verao
        envio_dados_gnuplot(gp, lista, qtd, grafico, "Summer");

        // envio dados inverno
        envio_dados_gnuplot(gp, lista, qtd, grafico, "Winter");

        PCLOSE(gp); // fecha o pipe (comunicacao com o gnuplot)
        printf("Grafico gerado com sucesso!\n");
    } else {
        printf("ERRO: Gnuplot nao encontrado.\n");
    }
} 