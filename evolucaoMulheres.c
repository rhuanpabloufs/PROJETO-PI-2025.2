// QUESTÃO RELACIONADA COM O ARQUIVO: Calcule a evolução da quantidade de mulheres em cada olimpíada

// INCLUSÃO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Criacao de uma estrutura para identificar genero ('F' ou 'M')
typedef struct {
    char sexo;
} Sexo;

// VER OPCAO DE UNIFICAR AS FUNCOES

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

// adaptação da função criada em alturamediaporano.c
// colunaDesejada vai determinar qual a coluna que vamos extrair os dados
int idAtleta(char* frase, int colunaDesejada){
	int aspas = 0;
	// virgulas
	int indiceID = 0;
	int coluna = 0;
	char idString[50];

	// loop para percorrer a frase ('\0' indica o final da frase)
	for(int i = 0; frase[i] != '\0'; i++){
		// guardando o caracter atual pra nao precisar acessar frase[i] a todo momento
		// e ajudar na compreensao
		char charAtual = frase[i];

		if(charAtual == '"'){ // checa se foram encontradas aspas
			aspas = !aspas;	//passa a ignorar virgulas que estejam dentro das aspas 
		}
		
		else if(frase[i] == ',' && !aspas){ 
			
			if (coluna == colunaDesejada){ // quando chegamos na virgula da coluna desejada, retornamos o id
				idString[indiceID] = '\0'; // fecha a string obtida
				return atoi(idString); // retorna o id convertido para inteiro
			}
			coluna++; // passa pra proxima coluna se aquela ainda nao era a certa
			indiceID = 0; // volta a escrita do idString pra primeira posicao
		}
		
		else{

			if (coluna == colunaDesejada){ // checa se estamos na coluna certa
				if (isdigit(charAtual)){ // se o caractere for um numero...
					idString[indiceID++] = charAtual; // guardamos ele no idString, sempre aumentando o indice
				}
			}
		}
	}
	
	return 0;
}

// funcao para coletar sexo e edicao das olimpiadas
void pegarTexto(char* frase, int colunaDesejada, char* destino){
    int aspas = 0;
    int coluna = 0; // semelhantes as da funcao anterior
    int indice = 0;
    destino[0] = '\0'; // inicializa o destino recebido (aponta para onde vamos enviar os textos)

	// percorre a frase do arquivo 
    for(int i = 0; frase[i] != '\0'; i++){
        char charAtual = frase[i]; // armazena o ultimo caractere lido

        if(charAtual == '"'){
            aspas = !aspas;	// filtra quando estamos lendo textos dentro de aspas, para ignorar as virgulas internas
        }

        else if(charAtual == ',' && !aspas){ // verifica se chegamos a uma virgula e nao estamos em aspas
            if (coluna == colunaDesejada){
                destino[indice] = '\0'; // Fecha a string (funciona por ser ponteiro)
                return; // finaliza a funcao
            }
            coluna++;
            indice = 0; // Reinicia buffer
        }
        else {
            if (coluna == colunaDesejada){ // verifica se estamos na coluna certa
                // copia o caractere, se nao for aspas
                if(charAtual != '"') {
					destino[indice++] = charAtual;
            
				}
        	}
    
		}
	}
}

int main(){

	// ADAPTAR A MAIN AS DUAS NOVAS FUNCOES

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
