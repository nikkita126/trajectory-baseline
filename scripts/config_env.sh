set -o errexit

export IS_ENV_SET="true"

export PROJECT_ROOT=".."
export STRUCTURE_DIR=""$PROJECT_ROOT"/structures"
export RESULTS_DIR=""$PROJECT_ROOT"/query_results"
export DATASETS_DIR=""$PROJECT_ROOT"/datasets"




### Seteo de horas para generar queries:
# TIEMPO = (12 * hora) + (minutos/5) + (288 * nro_dia)
# nro_dia: dia inicial dataset=0, dia siguiente=1, etc.
# INTERVALO = minutos/5 
#
# T_IN: tiempo inicial de la query
# T_END: tiempo final de la query
# ITV: intervalo de la query
#



# viajes [20.00,20.30) lunes 15/04/2013, duracion 1 hora
export T_IN=$(( 12*20 + 288*7 ))
export T_END=$(( T_IN + 6 ))
export ITV=12