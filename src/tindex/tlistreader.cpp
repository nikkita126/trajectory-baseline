#include "tlistreader.h"


void TListReader::addPoint(uint id, uint stop, uint time){
	/* adds the point (stop,time) to the list identified by 'id'*/
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

void TListReader::print(){

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
