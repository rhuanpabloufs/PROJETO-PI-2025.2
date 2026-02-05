#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
    int id;
    int altura;
    char nome[50];
    char medalha[50];
} Atleta;
int comparar(const void* atl1, const void* atl2){
    Atleta a1 = *(Atleta*) atl1;
    Atleta a2 = *(Atleta*) atl2;
    return a2.altura - a1.altura; 
}
int EncontrarAltura(char* frase, int* id){
    int aspas = 0;
    int virgulas = 0;
    int altura;
    int len = strlen(frase);
    char alturaParam[50];
    char idParam[50];
    int idTam = 0;
    int alturaTam = 0;
    for(int i = 0; i < len; i++){
        if(frase[i] == '"'){
            aspas = !aspas;
        }
        if(frase[i] == ',' && !aspas){
            virgulas++;
        }
        if(virgulas == 8){
            alturaParam[alturaTam++] = frase[i + 1];
        }
        if(virgulas == 7){
            idParam[idTam++] = frase[i+1];
        }
    }
    alturaParam[alturaTam - 1] ='\0';
    idParam[idTam - 1] = '\0';
    sscanf(idParam,"%d",id);
    if(sscanf(alturaParam,"%d cm",&altura)){
        return altura;
    } else {
        return 0;
    }
}
void AbrirBios(Atleta* atletas, int tamanho){
    FILE* bios = fopen("bios.csv","r");
    char frase[2000];
    fgets(frase,2000,bios);
    while(fgets(frase,2000,bios) != NULL){
        int id;
        int altura = EncontrarAltura(frase,&id);
        int encontrado = 0;
        for(int i = 0; i < tamanho && !encontrado; i++){
            if(id == atletas[i].id){
                atletas[i].altura = altura;
                encontrado = 1;
            }
        }
    }

}
void parserResults(char* frase, int* ano, int* id, char* nome, char* medalha){
    int aspas = 0;
    int virgulas = 0;
    int tamNome = 0;
    int tamMedalha = 0;
    char idP[10];
    int idTam = 0;
    int len = strlen(frase);
    sscanf(frase,"%d",ano);
    for(int i = 0; i < len; i++){
        if(frase[i] == '"'){
            aspas = !aspas;
        }
        if(frase[i] == ',' && !aspas){
            virgulas++;
        }
        if(virgulas == 4){
            medalha[tamMedalha++] = frase[i+1];
        }
        if(virgulas == 5){
            nome[tamNome++] = frase[i+1];
        }
        if(virgulas == 6){
            idP[idTam++] = frase[i+1];
        }
    }
    nome[tamNome - 1] = '\0';
    medalha[tamMedalha - 1] = '\0';
    idP[idTam - 1] = '\0';
    sscanf(idP,"%d",id);
}
int main(){
    FILE* results = fopen("results.csv","r");
    char frase[2000];
    int tamanho = 0;
    int capacidade = 100;
    Atleta* atletas = malloc(capacidade * sizeof(Atleta));
    fgets(frase,2000,results);
    while(fgets(frase,2000,results) != NULL){
        if(tamanho == capacidade){
            capacidade += 100;
            atletas = realloc(atletas, capacidade * sizeof(Atleta));
        }
        Atleta atleta;
        int ano;
        parserResults(frase,&ano,&atleta.id,atleta.nome,atleta.medalha);
        if(ano == 2012 && atleta.medalha[0] != '\0'){
            atletas[tamanho++] = atleta;
        }
    }
    AbrirBios(atletas, tamanho);
    int (*cmp)(const void*, const void*) = comparar;
    qsort(atletas,tamanho,sizeof(Atleta),cmp);
    printf("%s %s %d %d",atletas[0].nome,atletas[0].medalha,atletas[0].altura,atletas[0].id); 
}
