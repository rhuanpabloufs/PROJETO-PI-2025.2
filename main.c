#include <stdio.h>
#include <stdlib.h>
#include "olimpiadas.h"

int main() {
    printf("Iniciando o sistema das Olimpiadas: \n");

    int qtd_atletas = 0;

    Atleta* meus_atletas = ler_atletas("bios.csv", &qtd_atletas);

    if (meus_atletas != NULL) {
        // Teste: Imprimir o primeiro e o último para ver se leu certo
        printf("\nTeste dos dados \n");
        printf("Primeiro Atleta: ID %d | Nome: %s | Altura: %.2f\n",
                meus_atletas[0].id, meus_atletas[0].nome, meus_atletas[0].altura);

        printf("Ultimo Atleta..: ID %d | Nome: %s | Altura: %.2f\n",
                meus_atletas[qtd_atletas-1].id, meus_atletas[qtd_atletas-1].nome, meus_atletas[qtd_atletas-1].altura);

        // Limpeza de memória
        free(meus_atletas);
    }

    return 0;
}