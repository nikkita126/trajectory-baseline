#include "tindex.h"
#include "tdictionary.h"
#include "btree_set.h"
#include "btree_map.h"
#include "cppUtils.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>


#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/mapping_paraderos/trayectorias_codificadas_ordenadas.txt"
//#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/trayectorias_muestra.txt"

#define N_TRAYECTORIAS 100
#define N_NODOS 100
#define DELTA_T 1 /* ventana de espera, en intervalos */
#define INF 99999999

using namespace btree;
using namespace std;


void TIndex::