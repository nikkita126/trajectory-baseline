#ifndef _TLIST_H_
#define _TLIST_H_


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
#include "tlistreader.hpp"
#include "cppUtils.h"


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

	void create(TListReader &tdr){

		trips = tdr.trips;
		stops = tdr.stops;
		maxtime = tdr.maxtime;

		tlist = new Trajectory[trips];

		vector<uint> total_stops;
		vector<uint> total_times;

		for(uint i=0; i<trips; i++){
			auto traj_size = tdr.tlist[i].size();
			
			tlist[i].n_stops=traj_size;
			tlist[i].stops_list=NULL;
			tlist[i].times_list=NULL;
		
			total_stops.clear();
			total_times.clear();
	
			for(uint j=0;j<traj_size;j++){
				total_stops.push_back(tdr.tlist[i][j].first);
				total_times.push_back(tdr.tlist[i][j].second);
			}

			tlist[i].stops_list = new uint[tlist[i].n_stops];
			tlist[i].times_list = new uint[tlist[i].n_stops];

			copy(total_stops.begin(),total_stops.end(),tlist[i].stops_list);
			copy(total_times.begin(),total_times.end(),tlist[i].times_list);
		}


	}


	void save(ofstream &outfile){
		cds_utils::saveValue<TList>(outfile, this, 1);
		cds_utils::saveValue<Trajectory>(outfile,tlist,trips);

		for(uint i=0;i<trips;i++){
			cds_utils::saveValue<uint>(outfile,tlist[i].stops_list,tlist[i].n_stops);
			cds_utils::saveValue<uint>(outfile,tlist[i].times_list,tlist[i].n_stops);
		}
	}
	

	static TList* load(ifstream &infile){

		TList *td;

		td=cds_utils::loadValue<TList>(infile,1);

		td->tlist=cds_utils::loadValue<Trajectory>(infile,td->trips);

		for(uint i=0; i< td->trips; i++){
			td->tlist[i].stops_list=cds_utils::loadValue<uint>(infile,td->tlist[i].n_stops);
			td->tlist[i].times_list=cds_utils::loadValue<uint>(infile,td->tlist[i].n_stops);
		}

		return td;

	}

	void print(){
		cout<<"Lista de trayectorias generadas"<<endl;

		for(auto i=0;i<trips;i++){
		    for(auto j=0;j<tlist[i].n_stops;j++){
		        if(j) cout<<" ";
		        cout<<"("<<tlist[i].stops_list[j]<<","<<tlist[i].times_list[j]<<")";
		    }
		    cout<<endl;
		}

		cout<<"FIN!"<<endl;
	}

};

#endif
