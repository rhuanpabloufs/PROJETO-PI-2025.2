#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
	char nome[100];
	char medalha[10];
	int ano;
} Atleta;
int contador = 0;
void pegarNomesMedalhistas(char* frase,char* nome, char* medalha){
	int aspas = 0;
	int numVirgulas = 0;
	char algo[150];
	int j = 0;
	for(int i = 0; i < strlen(frase); i++){
		if(frase[i] == '"'){
			aspas = !aspas;
		}
		if((frase[i]) == ',' && !aspas){
			numVirgulas++;
		}
		if(numVirgulas >= 4 && numVirgulas <= 5){
			algo[j++] = frase[i+1];
		}
	}
	algo[j == 0 ? j : j - 1] = '\0';
	if(algo[0] == ','){
		sscanf(algo,",%[^\n]", nome);
		medalha[0] = '\0';
	} else {
		sscanf(algo,"%[^,],%[^\n]",medalha,nome);
	}
}
void pegarAlturaMedalhistas(char* frase,char* nome, int* altura){
	int aspas = 0;
	char AlturaP[50];
	int numVirgulas = 0;
	int j = 0;
	int k = 0;
	for(int i = 0; i < strlen(frase); i++){
		if(frase[i] == '"'){
			aspas = !aspas;
		}
		if((frase[i]) == ',' && !aspas){
			numVirgulas++;
		}
		if(numVirgulas == 3){
			nome[j++] = frase[i+1];
		}
		if(numVirgulas == 8){
			AlturaP[k++] = frase[i];
		}
	}
	nome[j - 1] = '\0';
	AlturaP[k] = '\0';
	*altura = 0;
	nome[strcspn(nome,"•")] = ' ';
	sscanf(AlturaP, ",%d", altura);
}
int forzinho(char* nome,Atleta* atletas,int altura){
	for(int j = 0; j < contador; j++){
		if(!strcmp(nome, atletas[j].nome)){
			return altura;
		}
	}
	return 0;
}

int alturadosAtletas(Atleta atletas[]){
	int soma = 0;
	FILE* teste = fopen("bios.csv","r");
	char frase[1000];
	fgets(frase, 1000, teste);
	for(int i = 0; i < 1000; i++){
		char nome[100];
		int altura;
		fgets(frase, 1000, teste);
		pegarAlturaMedalhistas(frase,nome,&altura);
		soma += forzinho(nome,atletas,altura);
	}
	return soma;
}
int main(){
	Atleta atletas[1000];
	char frase[1000];
	FILE* teste = fopen("results.csv","r");
	fgets(frase,1000,teste);
	for(int i = 0; i < 1000;){
		fgets(frase,1000,teste);
		int ano;
		sscanf(frase,"%d",&ano);
		char nome[100];
		char medalha[10];
		pegarNomesMedalhistas(frase,nome,medalha);
		if(medalha[0] != '\0' && ano == 2012){
			strcpy(atletas[i].nome, nome);
			strcpy(atletas[i].medalha,medalha);
			atletas[i++].ano = ano;
			contador++;
		}
	}
	double altura = alturadosAtletas(atletas);
	printf("%.2lf", altura / contador);
	
	for(int i = 0; i < 1000; i++){
		printf("%s %s %d\n",atletas[i].medalha,atletas[i].nome, atletas[i].ano);
	}
}