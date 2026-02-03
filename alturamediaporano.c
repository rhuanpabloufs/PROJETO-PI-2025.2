#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "olimpiadas.h"

int contador = 0;
int funcaoDeAjuda(int id, int altura, int atletas[],int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(id == atletas[i] && altura != 0){
			contador++;
			// printf("%d %d\n",altura,id);
			return altura;
		}
	}
	return 0;
}
int encontrarAlturas(char* frase,int atletas[], int tamanho){
	int aspas = 0;
	int virgulas = 0;
	char altura[20];
	int j = 0;
	char idP[10];
	int k = 0;
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
			idP[j++] = frase[i+1];
		}
		if(virgulas == 8){
			altura[k++] = frase[i+1];
		}
	}
	idP[j - 1] = '\0';
	sscanf(idP,"%d",&id);
	altura[k == 0 ? k : k - 1] = '\0';
	if(!altura[0] != '\0' || !sscanf(altura,"%d cm",&medida)){
		medida = 0;
	}
	return funcaoDeAjuda(id,medida,atletas,tamanho);
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
}
int idAtleta(char* frase){
	int aspas = 0;
	int virgulas = 0;
	int j = 0;
	int k = 0;
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
			medalha[j++] = frase[i+1];
		}
		if(virgulas == 6){
			idP[k++] = frase[i + 1];
		}
	}
	medalha[j <= 0 ? j : j - 1] = '\0';
	idP[k - 1] = '\0';
	if(medalha[0] != '\0'){
		sscanf(idP,"%d",&id);
		return id;
	}
	return 0;
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
			if(id != 0){
				atletasMedal[tamanho++] = id;
			}
		}
	}
	int soma = fraseBIOS(atletasMedal,tamanho);
	return (double)soma / contador;
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

		printf("Calculando altura media para %d... (Lendo arquivos novamente)\n", ano);
		double media = encontrarMediaAltura(ano);

		if (media > 0) {
			printf("Resultado: %.2lf cm\n", media);
		} else {
			printf("Nenhum dado encontrado ou media é 0.\n");
		}
	}
}
