set -o errexit

export _IS_ENV_SET="true"

export _PROJECT_ROOT=".."
export _STRUCTURE_DIR=""$_PROJECT_ROOT"/structures"
export _RESULTS_DIR=""$_PROJECT_ROOT"/query_results"
export _DATASETS_DIR=""$_PROJECT_ROOT"/datasets"




### Seteo de horas para generar queries:
# TIEMPO = (12 * hora) + (minutos/5) + (288 * nro_dia)
# nro_dia: dia inicial dataset=0, dia siguiente=1, etc.
# INTERVALO = minutos/5 
#
# _T_IN: tiempo inicial de la query
# _T_END: tiempo final de la query
# _ITV: intervalo de la query
#



# viajes [20.00,20.30) lunes 15/04/2013, duracion 1 hora
#export _T_IN=$(( 12*20 + 288*7 ))
#export _T_END=$(( _T_IN + 6 ))
#export _ITV=12

export _T_IN=$(( 12*7 + 6 + 288*1 ))
export _T_END=$(( _T_IN + 12 ))
export _ITV=12