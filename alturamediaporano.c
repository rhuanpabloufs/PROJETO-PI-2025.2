// ARQUIVO CORRESPONDENTE A QUESTAO 6:
// Para uma determinada edicao dos jogos olimpicos, calcule a altura media dos atletas medalhistas

// Inclusao das bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "olimpiadas.h"

int contador = 0;
int funcaoDeAjuda(int id, int altura, int atletas[], int tamanho){
	for(int i = 0; i < tamanho; i++){
		// O atleta precisa estar na lista E ter uma altura valida
		if(id == atletas[i] && altura > 0){
			contador++;
			return altura;
		}
	}
	return 0;
	/* Função que auxilia encontrarAlturas a não repetir alturas, ja que o array de atletas permite atletas repetidos
	essa função usa do fato de BIOS não se repetir, fazendo com que a altura de cada atleta so seja passada uma vez para soma total
	mesmo esse atleta estando mais vezes no Array principal */
}
int encontrarAlturas(char* frase,int atletas[], int tamanho){
	int aspas = 0;
	int virgulas = 0;
	char altura[20];
	int idTam = 0;
	char idP[20];
	int alturaTam = 0;
	int id = 0;
	int medida = 0;
	int len = strlen(frase);
	for(int i = 0; i < len; i++) {
		if(frase[i] == '"'){
			aspas = !aspas;	
		}
		if(frase[i] == ',' && !aspas) {
			virgulas++;
			continue; // pula a vírgula para não ficar no buffer
		}
		// Se nao eh virgula nem aspas, adiciona ao buffer correto
		if(virgulas == 7) {
			if(idTam < 19) idP[idTam++] = frase[i];
		}
		if(virgulas == 8) {
			if(alturaTam < 19) altura[alturaTam++] = frase[i];
		}
	}
	idP[idTam] = '\0';	// idP[-1] ERRO - Correção
	altura[alturaTam] = '\0';

	// Leitura segura
	if(idTam > 0) {
		sscanf(idP, "%d", &id);
	}

	// Leitura segura da altura
	if(alturaTam > 0 && sscanf(altura, "%d cm", &medida) == 1) {
		// medida lida ok
	} else {
		medida = 0;
	}
	return funcaoDeAjuda(id,medida,atletas,tamanho);
	/* Essa função permite retirar os IDs e alturas de cada atleta do arquivo bios.csv
	e torna-los dados manipulaveis, inicialmente utilizando a ideia de separar os campos buscados
	por meio das virgulas válidas, essas que não estão dentro de aspas, e apos isso lendo 
	diretamente desses campos separados, por meio de um sscanf */
}
int fraseBIOS(int atletas[], int tamanho){
	FILE* bios = fopen("bios.csv","r");
	if(!bios) return 0; // Seguranca se falhar abrir
	int soma = 0;
	char frase[2480];
    fgets(frase,2480,bios);
	while(fgets(frase,2480,bios) != NULL){
		soma += encontrarAlturas(frase,atletas,tamanho);
	}
	fclose(bios);
	return soma;
	// função separada para a leitura de bios e a passagem de cada linha de fgets como
	// parametro de encontrarAlturas.
}
int idAtleta(char* frase){
	int aspas = 0;
	int virgulas = 0;
	int medalhaTam = 0;
	int	idTam = 0;
	char medalha[50];
	char idP[20];
	int id = -1; // inicializa com valor invalido
	int len = strlen(frase);
	for(int i = 0; i < len; i++){ // o +1 pulava o ultimo char
		if(frase[i] == '"'){
			aspas = !aspas;	
		}
		if(frase[i] == ',' && !aspas){
			virgulas++;
			continue; // virgula era gravada dentro do id
		}
		if(virgulas == 4){
			if(medalhaTam < 49) medalha[medalhaTam++] = frase[i];
		}
		if(virgulas == 6){
			if(idTam < 19) idP[idTam++] = frase[i];
		}
	}
	medalha[medalhaTam] = '\0';
	idP[idTam] = '\0';

	// Verifica se tem medalha (nao eh vazia e nem NA)
	if(medalhaTam > 0 && strcmp(medalha, "NA") != 0){
		// Tenta converter o ID
		if(sscanf(idP, "%d", &id) == 1){
			return id;
		}
	}
	return -1;
	/* Função de separação de campos que funciona no mesmo modo da anterior,
	separando pelas virgulas validas, note que como so precisamos do id, a funcao
	separa em campos necessarios, verifica se o atleta é medalhista e retorna um id valido
	caso positivo, e ao contrario, retorna um id invalido que é tratado posteriomente. */
}
double encontrarMediaAltura(int ano){
	int* atletasMedal = malloc(100 * sizeof(int));
	int capacidade = 100;
	int tamanho = 0;
	FILE* results = fopen("results.csv","r");
	if (results == NULL) { // Correção: segurança caso arquivo falhe
		free(atletasMedal);
		return 0.0;
	}

	char frase[2480];
	fgets(frase,2480,results);

	while(fgets(frase,2480,results) != NULL){
		if(tamanho == capacidade){
			capacidade *= 2;
			// correção: uso de ponteiro temporário para evitar perda de dados
			int* temp = realloc(atletasMedal, capacidade * sizeof(int));
			if (temp == NULL) {
				free(atletasMedal);
				fclose(results);
				return 0.0;
			}
			atletasMedal = temp;
		}
		int anoParam = 0;
		// tenta ler normal ou com aspas para garantir
		if(frase[0] == '"') {
			sscanf(frase, "\"%d\"", &anoParam);
		} else {
			sscanf(frase, "%d", &anoParam);
		}
		if(anoParam == ano){
			int id = idAtleta(frase);
			if(id != -1){
				atletasMedal[tamanho++] = id;
			}
		}
	}

	fclose(results); // obrigatório fechar o arquivo
	// while que lê results inteiro, gera o array com os IDs de atletas medalhistas.
	int soma = fraseBIOS(atletasMedal,tamanho);
	// utilizando o array gerado, gera a soma de todas as alturas.

	free(atletasMedal); // Cuidando das memórias dos nossos computadores...
	if (contador == 0) {
		return 0.0;
	} else {
		return (double)soma / contador;
	}
	// o return com a media calculada.
}

// Resolvendo o problema de multiplas mains...
// Função agora será chamada na main
void resolver_q6_altura_media() {
	int ano;
	printf("\n--- Executando Questao 6 - Altura Media ---\n");
	printf("Digite o ano da Olimpiada (ex: 2016): ");

	// Permitir digitar o ano em vez de fixar
	if (scanf("%d", &ano) == 1) {
		// Zera o contador global antes de rodar
		extern int contador;
		contador = 0;

		printf("Calculando altura media para %d... (Aguarde)\n", ano);
		double media = encontrarMediaAltura(ano);

		if (media > 0) {
			printf("Resultado: %.2lf cm\n", media);
		} else {
			printf("Nenhum dado encontrado ou media eh 0.\n");
		}
	} else {
		char c;
		while ((c = getchar()) != '\n' && c != EOF);
	}
}
