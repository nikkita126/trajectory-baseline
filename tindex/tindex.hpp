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

//using namespace btree;
using namespace std;


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
		//vector<uint> total_trajectories;
		vector<uint> total_prev_trajectories;
		vector<uint> total_ids;

		//vector<uint> curr_ids;

		tindex[0].n_times=0;
		tindex[0].n_ids=0;
		tindex[0].times_list=NULL;
		//tindex[0].n_trajectories=NULL;
		tindex[0].prev_n_trajectories=NULL;
		tindex[0].ids_list=NULL;


		for(uint i=1; i<=tlist->stops; i++){

			tindex[i].n_times=0;
			tindex[i].n_ids=0;
			tindex[i].times_list=NULL;
			//tindex[i].n_trajectories=NULL;
			tindex[i].prev_n_trajectories=NULL;
			tindex[i].ids_list=NULL;

			total_times.clear();
			//total_trajectories.clear();
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
				//total_trajectories.push_back(it->second.size());

				cont+=it->second.size();

			}

			tindex[i].n_times=index_reader[i].size();
			tindex[i].n_ids=total_ids.size();
			tindex[i].times_list=new uint[tindex[i].n_times];
			//tindex[i].n_trajectories=new uint[tindex[i].n_times];
			tindex[i].prev_n_trajectories=new uint[tindex[i].n_times];
			tindex[i].ids_list=new uint[tindex[i].n_ids];

			copy(total_times.begin(),total_times.end(),tindex[i].times_list);
			//copy(total_trajectories.begin(),total_trajectories.end(),tindex[i].n_trajectories);
			copy(total_prev_trajectories.begin(),total_prev_trajectories.end(),tindex[i].prev_n_trajectories);
			copy(total_ids.begin(),total_ids.end(),tindex[i].ids_list);

		}



	}

	void save(ofstream &outfile){
		cds_utils::saveValue<TIndex>(outfile, this, 1);
		cds_utils::saveValue<StopEventList>(outfile,tindex,tlist->stops+1);

		for(uint i=0;i<=tlist->stops;i++){
			cds_utils::saveValue<uint>(outfile,tindex[i].times_list,tindex[i].n_times);
			//cds_utils::saveValue<uint>(outfile,tindex[i].n_trajectories,tindex[i].n_times);
			cds_utils::saveValue<uint>(outfile,tindex[i].prev_n_trajectories,tindex[i].n_times);
			cds_utils::saveValue<uint>(outfile,tindex[i].ids_list,tindex[i].n_ids);
		}

	}

	void saveDataOnly(ofstream &outfile){

		for(uint i=0;i<=tlist->stops;i++){
			cds_utils::saveValue<uint>(outfile,tindex[i].times_list,tindex[i].n_times);
			//cds_utils::saveValue<uint>(outfile,tindex[i].n_trajectories,tindex[i].n_times);
			//cds_utils::saveValue<uint>(outfile,tindex[i].prev_n_trajectories,tindex[i].n_times);
			cds_utils::saveValue<uint>(outfile,tindex[i].ids_list,tindex[i].n_ids);
		}

	}

	static TIndex* load(ifstream &infile){

		TIndex *ti;

		ti=cds_utils::loadValue<TIndex>(infile,1);

		ti->tindex=cds_utils::loadValue<StopEventList>(infile,ti->tlist->stops);

		for(uint i=0;i<=ti->tlist->stops;i++){
			ti->tindex[i].times_list=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);
			//ti->tindex[i].n_trajectories=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);
			ti->tindex[i].prev_n_trajectories=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);
			ti->tindex[i].ids_list=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_ids);
		}
	}

	void printIdList(uint s, uint t){

		if(s>tlist->stops){
			cout<<"ERROR: paradero inexistente o dataset corrupto"<<endl;
			return;
		}

		int time_index=getTimeIndex(s,t);

		if(time_index==-1){
			cout<<"ERROR: tiempo no encontrado"<<endl;
			return;
		}

		cout<<"Printing trajectory ids including point ("<<s<<","<<t<<"):"<<endl;
		
		uint starting_index=tindex[s].prev_n_trajectories[time_index];
		uint ending_index;

		if(time_index==tindex[s].n_times-1)
			ending_index=tindex[s].n_ids-1;
		else
			ending_index=tindex[s].prev_n_trajectories[time_index+1];

		bool first=true;
		for(auto i=starting_index;i<ending_index;i++){

			if(!first) cout<<" ";
			else first=false;

			cout<<tindex[s].ids_list[i];
		}
		cout<<endl;
	}

private:
	int getTimeIndex(uint s, uint t){

	    uint l=0, r=tindex[s].n_times-1, m;
	    while(l<r){ //bin search to find time index in times_list
	        
	        m=l+(r-l)/2;

	        if(tindex[s].times_list[m]==t)
	        	break;

	        else if(tindex[s].times_list[m] < t) //time is smaller than the given one
	            l=m+1;
	        else
	            r=m;

	    }

	    if(tindex[s].times_list[m]!=t)
	    	return -1;

	    return m;
    }

};

#endif
