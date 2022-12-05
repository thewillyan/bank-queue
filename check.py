#!/usr/bin/env python3
import os

pasta_saidas_esperadas = "saidas-esperadas"
pasta_saida_produzidas = "saidas-prod"
tamanho_das_entradas = 20

for i in range(1, tamanho_das_entradas + 1):
    os.system("./src/bank  " + str(i))

    print(f"=============== Inicio do Diff da Entrada {i} ===================")
    if i < 10:
        os.system(
            "diff --unified=0 "
            + pasta_saidas_esperadas
            + "/saida-000"
            + str(i)
            + ".txt "
            + pasta_saida_produzidas
            + "/saida-000"
            + str(i)
            + ".txt"
        )
    elif i < 100:
        os.system(
            "diff --unified=0 "
            + pasta_saidas_esperadas
            + "/saida-00"
            + str(i)
            + ".txt "
            + pasta_saida_produzidas
            + "/saida-00"
            + str(i)
            + ".txt"
        )
    elif i < 1000:
        os.system(
            "diff --unified=0 "
            + pasta_saidas_esperadas
            + "/saida-0"
            + str(i)
            + ".txt "
            + pasta_saida_produzidas
            + "/saida-0"
            + str(i)
            + ".txt"
        )
    else:
        os.system(
            "diff --unified=0 "
            + pasta_saidas_esperadas
            + "/saida-"
            + str(i)
            + ".txt "
            + pasta_saida_produzidas
            + "/saida-"
            + str(i)
            + ".txt"
        )

    print(f"================= Fim do Diff da Entrada {i} ==================\n")
