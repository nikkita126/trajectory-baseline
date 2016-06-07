#ifndef _TINDEX_H_
#define _TINDEX_H_

#include "tlist.hpp"
#include "btree_set.h"
#include "btree_map.h"


#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

//using namespace btree;
using namespace std;

class StopEventList {
public:
	uint n_times;

	uint *times_list;
	uint *n_trajectories;
	uint *prev_n_trajectories;
	uint *ids_list;

};


class TIndex{
public:
	TList *tlist;

	StopEventList *tindex; //size: tlist->stops(+1?)



	void create(TList &tl){

		tlist = &tl;

		tindex = new StopEventList[tlist->stops+1];

		// load and order in auxiliar structure

		btree_map<uint,btree_map<uint,btree_set<uint> > > index_reader;
		uint s,t;

		for(uint i=0; i<tl.trips;i++){
			for(uint j=0;j<tl.tlist[i].n_stops;j++){
				s=tl.tlist[i].stops_list[j];
				t=tl.tlist[i].times_list[j];

				index_reader[s][t].insert(i);
			}

		}
		//-----------------

		vector<uint> total_times;
		vector<uint> total_trajectories;
		vector<uint> total_prev_trajectories;
		vector<uint> total_ids;

		//vector<uint> curr_ids;

		tindex[0].n_times=0;
		tindex[0].times_list=NULL;
		tindex[0].n_trajectories=NULL;
		tindex[0].prev_n_trajectories=NULL;
		tindex[0].ids_list=NULL;


		for(uint i=1; i<=tlist->stops; i++){

			tindex[i].n_times=0;
			tindex[i].times_list=NULL;
			tindex[i].n_trajectories=NULL;
			tindex[i].prev_n_trajectories=NULL;
			tindex[i].ids_list=NULL;

			total_times.clear();
			total_trajectories.clear();
			total_prev_trajectories.clear();
			total_ids.clear();

			uint cont=0;

			for(auto it=index_reader[i].begin(); it!=index_reader[i].end();it++){

				//curr_ids.clear();

				for(auto jt=it->second.begin();jt!=it->second.end();jt++){
					total_ids.push_back(*jt);
				}

				total_prev_trajectories.push_back(cont);
				total_times.push_back(it->first);
				total_trajectories.push_back(it->second.size());

				cont+=it->second.size();

			}

			tindex[i].n_times=index_reader[i].size();
			tindex[i].times_list=new uint[tindex[i].n_times];
			tindex[i].n_trajectories=new uint[tindex[i].n_times];
			tindex[i].prev_n_trajectories=new uint[tindex[i].n_times];
			tindex[i].ids_list=new uint[total_ids.size()];

			copy(total_times.begin(),total_times.end(),tindex[i].times_list);
			copy(total_trajectories.begin(),total_trajectories.end(),tindex[i].n_trajectories);
			copy(total_prev_trajectories.begin(),total_prev_trajectories.end(),tindex[i].prev_n_trajectories);
			copy(total_ids.begin(),total_ids.end(),tindex[i].ids_list);

		}



	}

	void save(ofstream &outfile);

	static TIndex* load(ifstream &infile);





};

#endif
