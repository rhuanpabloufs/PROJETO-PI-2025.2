#include <stdio.h>
#include <stdlib.h>
#include "olimpiadas.h"

int main() {
    printf("Iniciando o sistema das Olimpiadas: \n");

    int qtd_atletas = 0;
    Atleta* meus_atletas = ler_atletas("bios.csv", &qtd_atletas);

    if (meus_atletas == NULL) {
        printf("ERRO: Nao foi possivel ler bios.csv.\n");
        return 1;
    }

    resolver_q6_altura_media(); // chamando a lógica da Q6
    resolver_q17_evolucao_mulheres(meus_atletas, qtd_atletas); // testando Q17

    free(meus_atletas);
    return 0;
}