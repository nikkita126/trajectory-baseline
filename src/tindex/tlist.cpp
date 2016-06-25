#include "tlist.h"


void TList::create(TListReader &tdr){

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


void TList::save(ofstream &outfile){
	cds_utils::saveValue<TList>(outfile, this, 1);
	cds_utils::saveValue<Trajectory>(outfile,tlist,trips);

	for(uint i=0;i<trips;i++){
		cds_utils::saveValue<uint>(outfile,tlist[i].stops_list,tlist[i].n_stops);
		cds_utils::saveValue<uint>(outfile,tlist[i].times_list,tlist[i].n_stops);
	}
}

void TList::saveDataOnly(ofstream &outfile){
	for(uint i=0;i<trips;i++){
		cds_utils::saveValue<uint>(outfile,tlist[i].stops_list,tlist[i].n_stops);
		cds_utils::saveValue<uint>(outfile,tlist[i].times_list,tlist[i].n_stops);
	}
	
}


TList* TList::load(ifstream &infile){

	TList *td = new TList();

	td=cds_utils::loadValue<TList>(infile,1);

	td->tlist=cds_utils::loadValue<Trajectory>(infile,td->trips);

	for(uint i=0; i< td->trips; i++){
		td->tlist[i].stops_list=cds_utils::loadValue<uint>(infile,td->tlist[i].n_stops);
		td->tlist[i].times_list=cds_utils::loadValue<uint>(infile,td->tlist[i].n_stops);
	}

	return td;

}

void TList::print(){
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

void TList::print(uint id){
	cout<<"Trayectoria nro: "<<id<<endl;

    for(auto j=0;j<tlist[id].n_stops;j++){
        if(j) cout<<" ";
        cout<<"("<<tlist[id].stops_list[j]<<","<<tlist[id].times_list[j]<<")";
    }
    cout<<endl;
}

//----------------------------------------------------
// Added to the original file

string getFilename(string path){

	size_t pos=path.find_last_of("/\\"); // FIXME: makes assumption that theres a slash in path (might not always be like that)
	size_t extension_pos=path.find_first_of(".");
	string filename;

	if(extension_pos!=string::npos){

		filename=path.substr(pos+1,extension_pos-(pos+1));
	}
	else
		filename=path.substr(pos+1);

	
	return filename;
}