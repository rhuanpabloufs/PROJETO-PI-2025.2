#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "olimpiadas.h"

// Lidando com as vírgulas e as aspas ("")
char* get_dado(char** cursor) {
    if (*cursor == NULL || **cursor == '\0') return NULL;
    char* start = *cursor;
    char* end = NULL;
    if (*start == '\"') {
        start++;
        end = strchr(start, '\"');
        if (end) {
            *end = '\0';
            *cursor = end + 1;
            if (**cursor == ',') (*cursor)++;
        }
    } else {
        end = strchr(start, ',');
        if (end) {
            *end = '\0';
            *cursor = end + 1;
        } else {
            size_t len = strlen(start);
            if (len > 0 && (start[len-1] == '\n' || start[len-1] == '\r')) start[len-1] = '\0';
            if (len > 1 && (start[len-2] == '\r')) start[len-2] = '\0';
            *cursor = start + strlen(start);
        }
    }
    return start;
}

// Alteração da função da Rhuan (alturamediaporano.c)
Atleta* ler_atletas(const char* nome_arquivo, int* qtd_total) {
    FILE* file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("ERRO: Nao abriu %s\n", nome_arquivo);
        *qtd_total = 0;
        return NULL;
    }

    char linha[1024];
    fgets(linha, 1024, file); // Pula o cabeçalho

    int capacidade = 1000;
    int contador = 0;
    Atleta* atletas = (Atleta*) malloc(capacidade * sizeof(Atleta));

    printf("Lendo %s...\n", nome_arquivo);

    while (fgets(linha, 1024, file)) {
        if (contador >= capacidade) {
            capacidade *= 2;
            atletas = (Atleta*) realloc(atletas, capacidade * sizeof(Atleta));
        }

        char* cursor = linha;
        char* dado;

        // Col 0: Roles (Ignorar por enquanto)
        get_dado(&cursor);

        // Col 1: Sexo (Salvar)
        dado = get_dado(&cursor);
        atletas[contador].sexo = (dado) ? dado[0] : '?';

        // Col 2: Full name (Usaremos o próximo)
        get_dado(&cursor);

        // Col 3: Used name (Salvar como Nome Principal)
        dado = get_dado(&cursor);
        if (dado) strncpy(atletas[contador].nome, dado, 99);
        else strcpy(atletas[contador].nome, "Desconhecido");

        // Col 4: Born (Ignorar por enquanto)
        get_dado(&cursor);
        // Col 5: Died (Ignorar)
        get_dado(&cursor);
        // Col 6: NOC (Ignorar)
        get_dado(&cursor);

        // Col 7: ID (Salvar)
        dado = get_dado(&cursor);
        atletas[contador].id = (dado) ? atoi(dado) : 0;

        // Col 8: Medidas (Ex: "170 cm / 60 kg")
        dado = get_dado(&cursor);
        atletas[contador].altura = 0.0f;
        atletas[contador].peso = 0.0f;

        // Lidando com as medidas...
        if (dado && strlen(dado) > 0 && strcmp(dado, "NA") != 0) {
            // Tenta ler os dois valores: "170 cm / 60 kg"
            float alt_temp, peso_temp;
            // Procura por "cm" e "kg" na string
            char* pos_cm = strstr(dado, " cm");
            char* pos_kg = strstr(dado, " kg");

            if (pos_cm) {
                atletas[contador].altura = atof(dado); // Pega o número antes do cm
            }
            if (pos_kg) {
                // Se tem barra, o peso está depois da barra
                char* pos_barra = strchr(dado, '/');
                if (pos_barra) {
                    atletas[contador].peso = atof(pos_barra + 1); // Lê depois da barra
                } else if (!pos_cm) {
                    // Se só tem kg e não tem cm (raro, mas precisamos tratar essa possibilidade também)
                    atletas[contador].peso = atof(dado);
                }
            }
        }

        contador++;
    }

    fclose(file);
    *qtd_total = contador;
    printf("Sucesso! Lidos %d atletas.\n", contador);
    return atletas;
}