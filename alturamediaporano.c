#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    char medalha[10];
    int ano;
} Atleta;

// ----------- FUNÇÃO PARA PEGAR NOMES E MEDALHAS -------------
void pegarNomesMedalhistas(char* frase,char* nome, char* medalha){
    int aspas = 0;
    int numVirgulas = 0;
    char algo[150];
    int j = 0;
    for(int i = 0; i < strlen(frase); i++){
        if(frase[i] == '"') aspas = !aspas;

        if(frase[i] == ',' && !aspas) numVirgulas++;

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

// ----------- FUNÇÃO PARA PEGAR ALTURA -------------
void pegarAlturaMedalhistas(char* frase,char* nome, int* altura){
    int aspas = 0;
    char AlturaP[50] = {0};   // inicializado
    int numVirgulas = 0;
    int j = 0;
    int k = 0;

    for(int i = 0; i < strlen(frase); i++){
        if(frase[i] == '"') aspas = !aspas;

        if(frase[i] == ',' && !aspas){
            numVirgulas++;
            continue;
        }

        if(numVirgulas == 3){
            nome[j++] = frase[i];
        }

        if(numVirgulas == 8){
            AlturaP[k++] = frase[i];   // corrigido: era altura[k] == frase[i]
        }
    }

    if(j > 0) nome[j-1] = '\0'; // remove vírgula final, se houver
    AlturaP[k] = '\0';

    sscanf(AlturaP, "%d", altura);  // corrigido: usar sscanf
}

// ----------- FUNÇÃO PARA SOMAR ALTURA DE UM ATLETA -------------
int forzinho(char* nome,Atleta* atletas,int n_atletas,int altura){
    for(int j = 0; j < n_atletas; j++){
        if(!strcmp(nome, atletas[j].nome)){
            return altura;
        }
    }
    return 0;
}

// ----------- FUNÇÃO PARA SOMAR TODAS AS ALTURAS -------------
int alturadosAtletas(Atleta* atletas, int n_atletas){
    int soma = 0;
    FILE* teste = fopen("bios.csv","r");
    if(!teste) return 0;

    char frase[1000];
    fgets(frase, 1000, teste); // ignora header

    while(fgets(frase, 1000, teste)){
        char nome[100];
        int altura;
        pegarAlturaMedalhistas(frase,nome,&altura);
        soma += forzinho(nome,atletas,n_atletas,altura);
    }

    fclose(teste);
    return soma;
}

// -------------------- MAIN DE TESTE ------------------------
int main(){
    Atleta atletas[100];
    int n_atletas = 0;

    char frase[1000];
    FILE* teste = fopen("results.csv","r");
    if(!teste){
        printf("Erro ao abrir results.csv\n");
        return 1;
    }

    fgets(frase,1000,teste); // ignora header

    while(fgets(frase,1000,teste)){
        int ano;                      // ✅ declarar ano
        sscanf(frase,"%d",&ano);      // ✅ passar endereço &ano

        char nome[100];
        char medalha[10];

        pegarNomesMedalhistas(frase,nome,medalha); // ✅ função correta

        if(medalha[0] != '\0'){ // ✅ corrigido: comparar com '\0', não ' \0'
            if(ano == 2012){
                strcpy(atletas[n_atletas].nome, nome);
                strcpy(atletas[n_atletas].medalha,medalha);
                atletas[n_atletas].ano = ano;
                n_atletas++;
            }
        }
    }

    fclose(teste);

    // imprime medalhistas de 2012
    for(int i = 0; i < n_atletas; i++){
        printf("%s %s %d\n",atletas[i].medalha,atletas[i].nome, atletas[i].ano);
    }

    // soma alturas dos medalhistas
    int soma_altura = alturadosAtletas(atletas,n_atletas);
    printf("Soma das alturas dos medalhistas de 2012: %d\n", soma_altura);

    return 0;
}
