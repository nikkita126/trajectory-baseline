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

	Trajectory *tlist; // size: trips

	void create(TListReader &tdr); // copy ordered data (stored in a TListReader) into a TList

	void save(ofstream &outfile); // save structure to file

	void saveDataOnly(ofstream &outfile); // doesn't save variables needed to reconstruc the structure
	
	static TList* load(ifstream &infile); // load structure from file

	void print(); // print the complete TList - FOR DEBUGGING

	void printTrajectory(uint id); // print trajectory number id

	size_t size(); // return size of the TList (= number of trips)

	size_t sizeOfTrajectory(uint traj_id); // return size of trajectory number traj_id (= n_stops)

	uint firstStop(uint traj_id); // return first stop of trajectory traj_id

	uint firstTime(uint traj_id); // return time associated to first stop of trajectory traj_id

	uint stopAt(size_t pos, uint traj_id); //returns stop at index pos in traj_id's stops list

	uint timeAt(size_t pos, uint traj_id); //returns time at index pos in traj_id's times list
	
};

string getFilename(string path); // extract filename from a path - FIX-ME: should be in an interface header file

#endif
