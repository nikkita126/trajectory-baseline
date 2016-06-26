#ifndef _TINDEX_H_
#define _TINDEX_H_

#include "tlist.h"
#include "btree_set.h"
#include "btree_map.h"
//#include "cppUtils.hpp"

#include <iostream>
#include <cstdio>
#include <cstddef>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <climits>

using namespace std;

class QueryResult{ //FIX-ME: should be in a sepparate header file (interface for upcoming structures) 
public:
    uint time_sum;
    uint trajectory_count;
    uint min_time;
    uint max_time;

    QueryResult();
};

class StopEventList {
public:
	uint n_times;
	uint n_ids;

	uint *times_list;
	//uint *n_trajectories;
	uint *prev_n_trajectories;
	uint *ids_list;

};

class TIndex{
public:
	TList *tlist;

	StopEventList *tindex; //size: tlist->stops(+1?)

	void create(TList &tl); // create a new index to access an existing TList

	void save(ofstream &outfile); // save structure to file

	void saveDataOnly(ofstream &outfile); // doesn't save the variables to reconstruct the index

	static TIndex* load(ifstream &infile, TList *tlist); // load structure from file

	int getTimeIndex(uint s, uint t); // get index of time t in the times_list associated to stop s

	size_t getStartingIdIndex(uint s, size_t time_index); // retrieve the starting index of the ids_list associated to time at position time_index in the times_list
	size_t getEndingIdIndex(uint s, size_t time_index); // idem, except that it's the ending index

	void printIdList(uint s, uint t); // print list of trajectory ids than include (s,t)
	void printIdList(uint s);
	void printTimeList(uint s);
	void printPrevTrajList(uint s);

	uint totalStops(); // return total stops included in tlist
	uint totalTrajectories(); // return number of trajectories in tlist 
	// query functions
	int startsInQuery(uint s_in, uint t_in, uint interval, btree_map<uint, QueryResult > &results_table); // accessibility query for real trajectories

	int includesQuery(uint s, uint t, uint interval, btree_map<uint, QueryResult > &results_table); // accessibility query for potential trajectories - NOT IMPLEMENTED YET

};

	void loadListAndIndex(TList *tlist, ifstream &list_file, TIndex *tindex, ifstream &index_file);


#endif