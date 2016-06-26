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
	printf("Printing list of trajectories...\n");

	for(auto i=0;i<trips;i++){
	    printTrajectory(i);
	}

	printf("DONE\n");
}

void TList::printTrajectory(uint id){
	printf("Trajectory num: %u\n",id);

    for(auto j=0;j<tlist[id].n_stops;j++){
        if(j) printf(" ");
        printf("(%u,%u)",tlist[id].stops_list[j],tlist[id].times_list[j]);
    }
    printf("\n");
}

size_t TList::size(){

	return (size_t)trips;
}

size_t TList::sizeOfTrajectory(uint traj_id){

	if(traj_id>trips)	// sanity check
		return 0;

	size_t traj_size=(size_t)tlist[traj_id].n_stops;

	return traj_size;
}

uint TList::firstStop(uint traj_id){

	if(traj_id>=trips)	// sanity check
		return 0;

	uint f_s=tlist[traj_id].stops_list[0];

	return f_s;
}

uint TList::firstTime(uint traj_id){

	if(traj_id>=trips)	// sanity check
		return 0;

	uint f_t=tlist[traj_id].times_list[0];

	return f_t;
}

uint TList::stopAt(size_t pos, uint traj_id){ 

	if(traj_id>=trips || pos>=tlist[traj_id].n_stops)
		return 0;

	return tlist[traj_id].stops_list[pos];
}

uint TList::timeAt(size_t pos, uint traj_id){ 

	if(traj_id>=trips || pos>=tlist[traj_id].n_stops)
		return 0;

	return tlist[traj_id].times_list[pos];
}

//----------------------------------------------------
// Added to the original file

string getFilename(string path){

	size_t pos=path.find_last_of("/\\"); // FIXME: makes assumption that theres a slash in path (might not always be like that)
	size_t extension_pos=path.find_first_of(".",pos);
	string filename;

	if(extension_pos!=string::npos){

		filename=path.substr(pos+1,extension_pos-(pos+1));
	}
	else
		filename=path.substr(pos+1);

	// printf("DEBUGGING: pos: %u, ext: %u, filename = %s\n", (uint)pos, (uint)extension_pos,filename.c_str());
	
	return filename;
}