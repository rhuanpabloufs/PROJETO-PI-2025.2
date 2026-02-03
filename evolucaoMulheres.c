// QUESTÃO RELACIONADA COM O ARQUIVO: Calcule a evolução da quantidade de mulheres em cada olimpíada

// INCLUSÃO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "olimpiadas.h"

// Criacao de uma estrutura para identificar genero ('F' ou 'M')
typedef struct {
    char sexo;
} Sexo;

/* 
Criação de uma estrutura que vai armazenar tipo de jogos (inverno/verão), 
o ano que ocorreu e conter um acumulador com a qtdMulheres
*/
typedef struct {
    char estacao[10];
    int anoDeOcorrencia;
    int qtdMulheres;
    // classificar ano por meio de código para ser possível de comparar adicionando 1 para verão e 2 para inverno
    int codigoEdicao; // Código único (ano * 10) + Estação
					// Exemplo, Rio 2016: 2016 * 10 + 1 (verão) = 20161
} ResultadosEdicao;

// Função auxiliar para verificar se uma edição já existe na lista
int buscar_ou_criar_edicao(ResultadosEdicao* lista, int* qtd_edicoes, int ano, const char* estacao, int codigo_unico) {
	for (int i = 0; i < *qtd_edicoes; i++) {
		// Código da edição.
		if (lista[i].codigoEdicao == codigo_unico) {
			return i; // Retorna o índice se já existe
		}
	}
	// Se não existe, cria uma nova
	int index = *qtd_edicoes;
	lista[index].anoDeOcorrencia = ano;
	strcpy(lista[index].estacao, estacao);
	lista[index].codigoEdicao = codigo_unico;
	lista[index].qtdMulheres = 0;
	(*qtd_edicoes)++;
	return index;
}

// Função de comparação usando a lógica de Victor (ordena pelo código numérico)
int comparar_edicoes(const void* a, const void* b) {
	ResultadosEdicao* r1 = (ResultadosEdicao*)a;
	ResultadosEdicao* r2 = (ResultadosEdicao*)b;
	// Ordenação simples de inteiros, o mlk é um gênio
	return r1->codigoEdicao - r2->codigoEdicao;
}

// adaptação da função criada em alturamediaporano.c
// colunaDesejada vai determinar qual a coluna que vamos extrair os dados
// função com mesmo nome mas argumentos diferentes do código de rhuan (ia dar conflito), por isso renomeei
int idAtleta_q17(char* frase, int colunaDesejada) {
	int aspas = 0;
	// virgulas
	int indiceID = 0;
	int coluna = 0;
	char idString[50];

	// loop para percorrer a frase ('\0' indica o final da frase)
	for(int i = 0; frase[i] != '\0'; i++) {
		// guardando o caracter atual pra nao precisar acessar frase[i] a todo momento
		// e ajudar na compreensao
		char charAtual = frase[i];

		if(charAtual == '"') { // checa se foram encontradas aspas
			aspas = !aspas;	//passa a ignorar virgulas que estejam dentro das aspas 
		}
		
		else if(frase[i] == ',' && !aspas) {
			
			if (coluna == colunaDesejada) { // quando chegamos na virgula da coluna desejada, retornamos o id
				idString[indiceID] = '\0'; // fecha a string obtida
				return atoi(idString); // retorna o id convertido para inteiro
			}
			coluna++; // passa pra proxima coluna se aquela ainda nao era a certa
			indiceID = 0; // volta a escrita do idString pra primeira posicao
		}
		
		else{

			if (coluna == colunaDesejada) { // checa se estamos na coluna certa
				if (isdigit(charAtual)) { // se o caractere for um numero...
					idString[indiceID++] = charAtual; // guardamos ele no idString, sempre aumentando o indice
				}
			}
		}
	}
	
	return 0;
}

// funcao para coletar sexo e edicao das olimpiadas
void pegarTexto(char* frase, int colunaDesejada, char* destino) {
    int aspas = 0;
    int coluna = 0; // semelhantes as da funcao anterior
    int indice = 0;
    destino[0] = '\0'; // inicializa o destino recebido (aponta para onde vamos enviar os textos)

	// percorre a frase do arquivo 
    for(int i = 0; frase[i] != '\0'; i++) {
        char charAtual = frase[i]; // armazena o ultimo caractere lido

        if(charAtual == '"') {
            aspas = !aspas;	// filtra quando estamos lendo textos dentro de aspas, para ignorar as virgulas internas
        }

        else if(charAtual == ',' && !aspas) { // verifica se chegamos a uma virgula e nao estamos em aspas
            if (coluna == colunaDesejada){
                destino[indice] = '\0'; // Fecha a string (funciona por ser ponteiro)
                return; // finaliza a funcao
            }
            coluna++;
            indice = 0; // Reinicia buffer
        }
        else {
            if (coluna == colunaDesejada) { // verifica se estamos na coluna certa
                // copia o caractere, se nao for aspas
                if(charAtual != '"') {
					destino[indice++] = charAtual;
            
				}
        	}
    
		}
	}
}

// FUNÇÃO PRINCIPAL PARA SER CHAMADA NA MAIN
void resolver_q17_evolucao_mulheres(Atleta* atletas, int qtd_total_atletas) {

	/* Qual a lógica que vou implementar:
	 * 1. Ler os dados para saber se é M ou F
	 * 2. Ler o results.csv para ver as participações
	 * 3. Se o ID em results.csv for de uma mulher, mulheres++ NAQUELE ANO
	 * 4. Usar o array ultimaEdicaoParticipada para garantir que não contemos a mesma pessoa mais de uma vez
	 */

	printf("\n--- Executando Codigo Questao 17 - Evolucao Mulheres ---\n");
	printf("Logica de ID unico (Ano + Estacao)...\n");

    // lista para conter os generos, que poderão ser acessados pelo athlete_id
    Sexo* listaGeneros = (Sexo*)calloc(200000, sizeof(Sexo));

	// ID -> Sexo
	char* sexo_por_id = (char*) calloc(200000, sizeof(char));
	for (int i = 0; i < qtd_total_atletas; i++) {
		int id = atletas[i].id;
		if (id < 200000) sexo_por_id[id] = atletas[i].sexo;
	}

    // dynamic binding de um array limpo (inicializado com zeros) que guarde o codigo do ultimo ano em que uma atleta participou das Olimpíadas pelo seu ID
    // isso foi feito para evitar a contagem de uma atleta mais de vez no mesmo ano
    int* ultimaEdicaoParticipada = (int*)calloc(200000, sizeof(int));

    // array para guardar os resultados de cada edição
    ResultadosEdicao* resultados = (ResultadosEdicao*)calloc(100, sizeof(ResultadosEdicao));
	int qtd_edicoes = 0;

	// abertura do arquivo results.csv
	FILE* file = fopen("results.csv", "r");
	if (!file) {
		printf("ERRO: results.csv nao encontrado.\n");
		free(sexo_por_id);
		free(ultimaEdicaoParticipada);
		free(resultados);
		return;
	}

	char linha[2048];
    char bufferGames[100]; // Para ler "1912 Summer Olympics"
    char bufferID[50];     // Para ler o ID
    char bufferEstacao[20]; // Para guardar só a estação ("Summer")

    fgets(linha, 2048, file); // Pula cabeçalho

    while (fgets(linha, 2048, file)) {

        // 1. Coluna 0 (Games) -> Ex: "1912 Summer Olympics"
        pegarTexto(linha, 0, bufferGames);

        // 2. Coluna 6 (athlete_id)
        pegarTexto(linha, 6, bufferID);
        int id_atleta = atoi(bufferID);

        // 3. Separar Ano e Estação de dentro do bufferGames
        int ano = 0;
        sscanf(bufferGames, "%d %s", &ano, bufferEstacao);

        // Validação e Contagem
        if (id_atleta > 0 && ano > 0 && id_atleta < 200000) {

            // Verifica se é mulher
            if (sexo_por_id[id_atleta] == 'F') {

                int sufixo = (strcmp(bufferEstacao, "Summer") == 0) ? 1 : 2;
                int codigo_unico = (ano * 10) + sufixo;

                if (ultimaEdicaoParticipada[id_atleta] != codigo_unico) {
                    int idx = buscar_ou_criar_edicao(resultados, &qtd_edicoes, ano, bufferEstacao, codigo_unico);
                    resultados[idx].qtdMulheres++;
                    ultimaEdicaoParticipada[id_atleta] = codigo_unico;
                }
            }
        }
    }
    fclose(file);

    // Ordenação e Exibição
    qsort(resultados, qtd_edicoes, sizeof(ResultadosEdicao), comparar_edicoes);

    printf("\n%-10s | %-8s | %s\n", "CODIGO", "ESTACAO", "QTD MULHERES");
    printf("-----------------------------------\n");
    for (int i = 0; i < qtd_edicoes; i++) {
        printf("%-10d | %-8s | %d\n",
                resultados[i].codigoEdicao,
                resultados[i].estacao,
                resultados[i].qtdMulheres);
    }

	// Minha memória, Victor, pelo amor de Deus!
    free(sexo_por_id);
    free(ultimaEdicaoParticipada);
    free(resultados);

	return;
}
