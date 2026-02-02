// QUESTÃO RELACIONADA COM O ARQUIVO: Calcule a evolução da quantidade de mulheres em cada olimpíada

// INCLUSÃO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    int codigoEdicao;
} ResultadosEdicao;

/* codigo a ser analisado
// utilização da função criada em alturamediaporano.c
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

int fraseBIOS(int atletas[], int tamanho){
	FILE* bios = fopen("bios.csv","r");
	int soma = 0;
	char frase[1000];
	while(fgets(frase,1000,bios) != NULL){
		soma += encontrarAlturas(frase,atletas,tamanho);
	}
	return soma;
}

int funcaoDeAjuda(int id, int altura, int atletas[],int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(id == atletas[i]){
			contador++;
			return altura;
		}
	}
	return 0;
}

int encontrarGenero(char* frase, Sexo generos[], int tamanho){
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
	if(altura[0] != '\0'){
		sscanf(altura,"%d",&medida);
	} else {
		medida = 0;
	}
	return funcaoDeAjuda(id,medida,atletas,tamanho);
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
*/

int main(){

    // lista para conter os generos, que poderão ser acessados pelo athlete_id
    Sexo* listaGeneros = (Sexo*)calloc(200000, sizeof(Sexo));

    // dynamic binding de um array limpo (inicializado com zeros) que guarde o codigo do ultimo ano em que uma atleta participou das Olimpíadas pelo seu ID
    // isso foi feito para evitar a contagem de uma atleta mais de vez no mesmo ano
    int* ultimaEdicaoParticipada = (int*)calloc(200000, sizeof(int));

    // array para guardar os resultados de cada edição
    ResultadosEdicao* resultados = (ResultadosEdicao*)calloc(100, sizeof(ResultadosEdicao));

    // abertura do arquivo bios.csv em modo de leitura
    FILE* bios = fopen("bios.csv", "r");

    // fechando o arquivo bios.csv
    fclose(bios);
    
    return 0;
}