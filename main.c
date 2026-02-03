#include <stdio.h>
#include <stdlib.h>
#include "olimpiadas.h"

int main() {
    printf("Iniciando o sistema das Olimpiadas: \n");

    int qtd_atletas = 0;
    Atleta* meus_atletas = ler_atletas("bios.csv", &qtd_atletas);
    void resolver_q6_altura_media();

    ler_atletas("bios.csv", &qtd_atletas);
    resolver_q6_altura_media(); // chamando a lógica da Q6

    return 0;
}