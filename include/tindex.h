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

#define DELTA_T 0

using namespace std;

class Query {
public:
	uint st_node; //starting node
	uint st_time; //initial time
	uint time_interval;
	bool origin_only; // true for real trajectories, false for potential trajectories

	Query(uint n,uint t, uint t_i, bool o_o);
};

class QueryResult{
public:
    uint time_sum;
    uint trajectory_count;
    uint min_time;
    uint max_time;
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

	void create(TList &tl);

	void save(ofstream &outfile);

	void saveDataOnly(ofstream &outfile);

	static TIndex* load(ifstream &infile, TList *tlist);

	size_t getStartingIdIndex(uint s, size_t time_index);

	size_t getEndingIdIndex(uint s, size_t time_index);

	void printIdList(uint s, uint t);

	int getStartingId(uint n_in, uint t_in, bool origin_only);

private:
	size_t getTimeIndex(uint s, uint t);

};

	void loadListAndIndex(TList *tlist, ifstream &list_file, TIndex *tindex, ifstream &index_file);


#endif