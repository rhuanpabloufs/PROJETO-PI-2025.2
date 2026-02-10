#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int id;
    int altura;
    char nome[50];
    char medalha[50];
    char esporte[50];
} Atleta;
// struct de Atletas que guarda as informações necessárias para que se gere uma saída satisfatória.
int comparar(const void* atl1, const void* atl2){
    Atleta a1 = *(Atleta*) atl1;
    Atleta a2 = *(Atleta*) atl2;
    return a2.altura - a1.altura; 
}
// Função de Comparação decrescente das alturas para o qsort.
int EncontrarAltura(char* frase, int* id){
    int aspas = 0;
    int virgulas = 0;
    int altura = 0;
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

    // Proteção contra buffer negativo se o campo estiver vazio
    if (alturaTam > 0) alturaParam[alturaTam - 1] ='\0';
    else alturaParam[0] = '\0';

    if (idTam > 0) idParam[idTam - 1] = '\0';
    else idParam[0] = '\0';

    alturaParam[alturaTam - 1] ='\0';
    idParam[idTam - 1] = '\0';
    sscanf(idParam,"%d",id);
    // O sscanf retorna a quantidade de itens lidos com sucesso.
    // Só aceitamos se ele retornar 1.
    if((sscanf(alturaParam,"%d cm",&altura)) == 1){
        return altura;
    } else {
        return 0;
    }
}
// É um buscador de dados e separação de campos manual, utilizando das virgulas que separam os dados
// dentro do bios.csv para extrair o id e a altura de alguns atletas. 
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
                // encontrado servindo apenas para que nao seja iterado o Array inteiro, mesmo apos encontrado o atleta procurado.
            }
        }
    }
}
/* Função que abre o arquivo bios.csv e capta as frases que sao passadas como
parametros para a separação de campos, ocorrida na função anterior, e após isso preenche a altura
dos atletas alocados em um Array, que é gerado posteriormente */
void parserResults(char* frase, int* ano, int* id, char* nome, char* medalha, char* esporte){
    int aspas = 0;
    int virgulas = 0;
    int tamNome = 0;
    int tamMedalha = 0;
    char idP[10];
    int idTam = 0;
    int esporteTam = 0;
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
        if(virgulas == 8){
            esporte[esporteTam++] = frase[i+1];
        }
    }
    esporte[esporteTam - 1] = '\0';
    nome[tamNome - 1] = '\0';
    medalha[tamMedalha - 1] = '\0';
    idP[idTam - 1] = '\0';
    sscanf(idP,"%d",id);
}
/*Mesma ideia de separção manual de campos por virgulas, agora no results.csv, assim podemos captar nome, medalha ganhada, ID e esporte,
dados esses que preenche o Array dinamico de Atletas, para que possa ser respondido nome, medalha ganhada, e esporte participado, não apenas a altura*/
void MaiorAltura(int anoP){
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
        atleta.altura = 0;
        int ano;
        parserResults(frase,&ano,&atleta.id,atleta.nome,atleta.medalha,atleta.esporte);
        if(ano == anoP && atleta.medalha[0] != '\0'){
            atletas[tamanho++] = atleta;
        }
    }
    AbrirBios(atletas, tamanho);
    int (*cmp)(const void*, const void*) = comparar;
    if(tamanho > 0){
        qsort(atletas,tamanho,sizeof(Atleta),cmp);
        printf("O atleta de %s, %s, de altura %d cm, eh o medalhista mais alto das olimpiadas de %d, tendo ganhado uma medalha de %s.",atletas[0].esporte,atletas[0].nome,atletas[0].altura,anoP,atletas[0].medalha);
    } else {
        printf("Ano nao olimpico!");
    }
    free(atletas);

}
// Função core do programa, pega a frase o results.csv, aloca dinamicamente um vetor de Atletas, e preenche esses dados com a Função ParseResults
// Logos após, usa a bios para preencher a altura, utilizando no final um sort decrescente por altura, para deixar o atleta mais alto exatamente
// no primeiro espaço.
void MaiorAlturaHistoria(){ // acento no nome não compila
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
        atleta.altura = 0;
        int ano;
        parserResults(frase,&ano,&atleta.id,atleta.nome,atleta.medalha,atleta.esporte);
        if(atleta.medalha[0] != '\0'){
            atletas[tamanho++] = atleta;
        }
    }
    AbrirBios(atletas, tamanho);
    int (*cmp)(const void*, const void*) = comparar;
    qsort(atletas,tamanho,sizeof(Atleta),cmp);
    printf("O atleta de %s, %s eh o medalhista mais alto da historia, com altura de %d cm, tendo ganhado a medalha de %s.",atletas[0].esporte,atletas[0].nome,atletas[0].altura,atletas[0].medalha);
    free(atletas);
}
// Mesma função, mas sem o ano como parametro, o que permite iterar todo o arquivo em busca do medalhista mais alto.

// Substituí a main por uma função void para integrar no arquivo main
void resolver_maior_altura_medalhista() {
    int ano;
    printf("\n--- Questao: Maior Altura de Medalhista ---\n");
    printf("Digite o ano desejado ou digite qualquer outra coisa para toda historia: ");

    // Lógica original preservada
    if (scanf("%d", &ano)) {
        MaiorAltura(ano);
    } else {
        // Se entrou aqui, o usuário digitou algum outro texto
        // O scanf falhou e deixou o texto no buffer.
        // Precisamos limpar esse texto, para não bagunçar o menu da main
        char c;
        while ((c = getchar()) != '\n' && c != EOF);

        MaiorAlturaHistoria();
    }
}
