#include "tlistreader.h"

TListReader::TListReader(){
	trips=0;
	stops=0;
	maxtime=0;
}

TListReader::TListReader(uint t, uint s, uint m){
	trips = t;
	stops = s;
	m = t;
}


void TListReader::addPoint(uint id, uint stop, uint time){
	// adds the point (stop,time) to the list identified by 'id'
	tlist[id].push_back(make_pair(stop,time));
}

void TListReader::setTrips(uint tr){
	trips=tr;
}

void TListReader::setStops(uint st){
	stops=st;
}

void TListReader::setMaxtime(uint mt){
	maxtime=mt;
}

// FOR DEBUGGING and using with small dataset sample
void TListReader::print(){

   // print all trajectories

	printf("List of trajectories: \n");

	for(auto i=0;i<trips;i++){
	    auto traj_size = tlist[i].size();

	    for(auto j=0;j<traj_size;j++){
	        if(j) printf(" ");
	        printf("(%u,%u)",tlist[i][j].first,tlist[i][j].second);
	    }
	    printf("\n");
	}
}
