#ifndef _TLISTREADER_H_
#define _TLISTREADER_H_


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


using namespace btree;
using namespace std;

class TListReader {
public:
	uint trips; /* number of trips (trajectories) */
	uint stops; /* total number of stops */
	uint maxtime;

	btree_map<uint,vector<pair<uint,uint> > > tlist; /* list of trajectories */

	TListReader();

	TListReader(uint t, uint s, uint m);

	void addPoint(uint id, uint stop, uint time);

	void setTrips(uint tr);

	void setStops(uint st);

	void setMaxtime(uint mt);

	void print();

};

#endif