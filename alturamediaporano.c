#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "olimpiadas.h"

int contador = 0;
int funcaoDeAjuda(int id, int altura, int atletas[],int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(id == atletas[i] && altura != 0){
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
	char idP[10];
	int alturaTam = 0;
	int id;
	int medida;
	int len = strlen(frase);
	for(int i = 0; i + 1 < len; i++){
		if(frase[i] == '"'){
			aspas = !aspas;	
		}
		if(frase[i] == ',' && !aspas){
			virgulas++;
		}
		if(virgulas == 7){
			idP[idTam++] = frase[i+1]; // Mudança do nome da variável
		}
		if(virgulas == 8){
			altura[alturaTam++] = frase[i+1];
		}
	}
	idP[idTam - 1] = '\0';
	sscanf(idP,"%d",&id);
	altura[alturaTam == 0 ? alturaTam : alturaTam - 1] = '\0';
	if(!altura[0] != '\0' || !sscanf(altura,"%d cm",&medida)){
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
	int soma = 0;
	char frase[2480];
    fgets(frase,2480,bios);
	while(fgets(frase,2480,bios) != NULL){
		soma += encontrarAlturas(frase,atletas,tamanho);
	}
	return soma;
	// função separada para a leitura de bios e a passagem de cada linha de fgets como
	// parametro de encontrarAlturas.
}
int idAtleta(char* frase){
	int aspas = 0;
	int virgulas = 0;
	int medalhaTam = 0;
	int	idTam = 0;
	char medalha[10];
	char idP[10];
	int id;
	int len = strlen(frase);
	for(int i = 0; i + 1 < len; i++){
		if(frase[i] == '"'){
			aspas = !aspas;	
		}
		if(frase[i] == ',' && !aspas){
			virgulas++;
		}
		if(virgulas == 4){
			medalha[medalhaTam++] = frase[i+1];
		}
		if(virgulas == 6){
			idP[idTam++] = frase[i + 1];
		}
	}
	medalha[medalhaTam <= 0 ? medalhaTam : medalhaTam - 1] = '\0';
	idP[idTam - 1] = '\0';
	if(medalha[0] != '\0'){
		sscanf(idP,"%d",&id);
		return id;
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
	char frase[2480];
	fgets(frase,2480,results);
	while(fgets(frase,2480,results) != NULL){
		if(tamanho == capacidade){
			capacidade *= 2;
			atletasMedal = realloc(atletasMedal,capacidade * sizeof(int));
		}
		int anoParam;
		sscanf(frase,"%d",&anoParam);
		if(anoParam == ano){
			int id = idAtleta(frase);
			if(id != -1){
				atletasMedal[tamanho++] = id;
			}
		}
	}
	// while que lê results inteiro, gera o array com os IDs de atletas medalhistas.
	int soma = fraseBIOS(atletasMedal,tamanho);
	// utilizando o array gerado, gera a soma de todas as alturas.

	free(atletasMedal); // Cuidando das memórias dos nossos computadores...
	return (double)soma / contador;
	// o return com a media calculada.
}

// Resolvendo o problema de multiplas mains...
// Função agora será chamada na main
void resolver_q6_altura_media() {
	int ano;
	printf("\n--- Executando Questao 6 - Altura Media ---\n");
	printf("Digite o ano da Olimpiada (ex: 2016): ");
	printf(" ");

	// Permitir digitar o ano em vez de fixar
	if (scanf("%d", &ano) == 1) {
		// Zera o contador global antes de rodar
		extern int contador;
		contador = 0;

		printf("Calculando altura media para %d... (Lendo arquivos novamente)\n", ano);
		double media = encontrarMediaAltura(ano);

		if (media > 0) {
			printf("Resultado: %.2lf cm\n", media);
		} else {
			printf("Nenhum dado encontrado ou media eh 0.\n");
		}
	}
}
