#ifndef _TDICTIONARY_H_
#define _TDICTIONARY_H_


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

#define N_TRAYECTORIAS 100
#define N_NODOS 100
#define DELTA_T 1 /* ventana de espera, en intervalos */
#define INF 99999999

using namespace btree;
using namespace std;
using namespace cds_utils;

class TDictionary {
public:
	uint trips; /* number of trips (trajectories) */
	uint stops; /* total number of stops */
	uint maxtime;

	btree_map<uint,vector<pair<uint,uint> > > TList; /* list of trajectories */

	TDictionary(uint t, uint s, uint m){
		trips = t;
		stops = s;
		m = t;
	}

	void addPoint(uint id, uint stop, uint time){
		/* adds the point (stop,time) to the list identified by 'id'*/
		TList[id].push_back(make_pair(stop,time));

	}

	void save(ofstream &outfile){

	}

	static TDictionary* load(ifstream &infile){

	}

};

#endif