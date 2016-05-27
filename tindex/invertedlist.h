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
#include "tdictionary.h"

#define N_TRAYECTORIAS 100
#define N_NODOS 100
#define DELTA_T 1 /* ventana de espera, en intervalos */
#define INF 99999999

using namespace btree;
using namespace std;




class InvertedList{
public:
	uint trips; /* number of trips (trajectories) */
	uint stops; /* total number of stops */
	uint maxtime;

	btree_map<uint,btree_map<uint,btree_set<uint> > > index;


	void create(TDictionary &td);

	void save(ofstream &outfile);

	static InvertedList* load(ifstream &infile);





};

#endif