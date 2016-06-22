#ifndef _INVLIST_H_
#define _INVLIST_H_


#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "btree_set.h"
#include "btree_map.h"

#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/mapping_paraderos/trayectorias_codificadas_ordenadas.txt"
//#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/trayectorias_muestra.txt"

#define N_TRAYECTORIAS 100
#define N_NODOS 100
#define DELTA_T 1 /* ventana de espera, en intervalos */
#define INF 99999999

using namespace btree;
using namespace std;

typedef struct columnas_tabla{

	uint suma;
	uint cant;
	uint min;
	uint max;

} columnas_tabla;


