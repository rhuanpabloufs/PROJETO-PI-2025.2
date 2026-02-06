cmake_minimum_required(VERSION 3.20)
project(PROJETO_PI_2025_2 C)
set(CMAKE_C_STANDARD 99)

add_executable(olimpiadas_app
        main.c
        csv_utils.c
        cmake-build-debug/bios.csv
        cmake-build-debug/results.csv
        evolucaoMulheres.c
        alturamediaporano.c
        MaiorAlturaMedalhista.c
        evo_esportes_femininos.c
)
