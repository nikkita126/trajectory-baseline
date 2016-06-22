#ifndef _TINDEX_H_
#define _TINDEX_H_

#include "tlist.hpp"
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


class StopEventList {
public:
	uint n_times;
	uint n_ids;

	uint *times_list;
	//uint *n_trajectories;
	uint *prev_n_trajectories;
	uint *ids_list;

};





#endif