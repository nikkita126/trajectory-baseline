#ifndef _TLIST_H_
#define _TLIST_H_

#include "btree_set.h"
#include "btree_map.h"
#include "tlistreader.h"
#include "cppUtils.h"


#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <fstream>
#include <map>
#include <sstream>




//using namespace btree;
using namespace std;
//using namespace cds_utils;

class Trajectory {
public:
	uint n_stops;
	
	uint *stops_list; /* size: n_stops */
	uint *times_list; /* size: n_stops */

};

class TList {
public:
	uint trips; /* number of trips (trajectories) */
	uint stops; /* total number of stops */
	uint maxtime;

	Trajectory *tlist;

	void create(TListReader &tdr);

	void save(ofstream &outfile);

	void saveDataOnly(ofstream &outfile);
	

	static TList* load(ifstream &infile);

	void print();

	void print(uint id);

};

string getFilename(string path);

#endif
