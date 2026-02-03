cmake_minimum_required(VERSION 3.20)
project(PROJETO_PI_2025_2 C)
set(CMAKE_C_STANDARD 99)

add_executable(olimpiadas_app
        main.c
        csv_utils.c
        bios.csv
        results.csv
        # evolucaoMulheres.c // Comentado por enquanto para rodar a única main que temos
        alturamediaporano.c
)
