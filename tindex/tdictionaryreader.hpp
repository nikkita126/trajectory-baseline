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
//using namespace cds_utils;

class TListReader {
public:
	uint trips; /* number of trips (trajectories) */
	uint stops; /* total number of stops */
	uint maxtime;

	btree_map<uint,vector<pair<uint,uint> > > tlist; /* list of trajectories */

	TListReader(){
		trips=0;
		stops=0;
		maxtime=0;
	}

	TListReader(uint t, uint s, uint m){
		trips = t;
		stops = s;
		m = t;
	}

	void addPoint(uint id, uint stop, uint time){
		/* adds the point (stop,time) to the list identified by 'id'*/
		tlist[id].push_back(make_pair(stop,time));

	}

	void setTrips(uint tr){
		trips=tr;
	}

	void setStops(uint st){
		stops=st;
	}

	void setMaxtime(uint mt){
		maxtime=mt;
	}

	void print(){

	   /* RECORRER E IMPRIMIR TRAYECTORIAS */
    
		cout<<"Lista de trayectorias generadas"<<endl;

		for(auto i=0;i<trips;i++){
		    auto tam_trayectoria = tlist[i].size();

		    for(auto j=0;j<tam_trayectoria;j++){
		        if(j) cout<<" ";
		        cout<<"("<<tlist[i][j].first<<","<<tlist[i][j].second<<")";
		    }
		    cout<<endl;
		}
	}


};

#endif
