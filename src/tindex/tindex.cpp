#include "tindex.h"

//using namespace btree;

//-----------------------
// QueryResult

QueryResult::QueryResult(){
	time_sum=0;
	trajectory_count=0;
	min_time=UINT_MAX; //from <climits>
	max_time=0;
}

//--------------------------

void TIndex::create(TList &tl){

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

void TIndex::save(ofstream &outfile){
	cds_utils::saveValue<TIndex>(outfile, this, 1);
	cds_utils::saveValue<StopEventList>(outfile,tindex,tlist->stops+1);

	for(uint i=0;i<=tlist->stops;i++){
		cds_utils::saveValue<uint>(outfile,tindex[i].times_list,tindex[i].n_times);
		//cds_utils::saveValue<uint>(outfile,tindex[i].n_trajectories,tindex[i].n_times);
		cds_utils::saveValue<uint>(outfile,tindex[i].prev_n_trajectories,tindex[i].n_times);
		cds_utils::saveValue<uint>(outfile,tindex[i].ids_list,tindex[i].n_ids);
	}

}

void TIndex::saveDataOnly(ofstream &outfile){

	for(uint i=0;i<=tlist->stops;i++){
		cds_utils::saveValue<uint>(outfile,tindex[i].times_list,tindex[i].n_times);
		//cds_utils::saveValue<uint>(outfile,tindex[i].n_trajectories,tindex[i].n_times);
		//cds_utils::saveValue<uint>(outfile,tindex[i].prev_n_trajectories,tindex[i].n_times);
		cds_utils::saveValue<uint>(outfile,tindex[i].ids_list,tindex[i].n_ids);
	}

}

TIndex* TIndex::load(ifstream &infile, TList *loaded_tlist){

	TIndex *ti = new TIndex();

	ti=cds_utils::loadValue<TIndex>(infile,1);

	ti->tlist = loaded_tlist;

	ti->tindex=cds_utils::loadValue<StopEventList>(infile,ti->tlist->stops+1);

	for(uint i=0;i<=ti->tlist->stops;i++){

		ti->tindex[i].times_list=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);

		//ti->tindex[i].n_trajectories=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);
		ti->tindex[i].prev_n_trajectories=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_times);
		ti->tindex[i].ids_list=cds_utils::loadValue<uint>(infile,ti->tindex[i].n_ids);
	}

	return ti;
}

uint TIndex::totalStops(){

	uint total = tlist->stops;
	return total;
}

uint TIndex::totalTrajectories(){

	uint total = tlist->trips;
	return total;
}


size_t TIndex::getStartingIdIndex(uint s, size_t time_index){

	size_t s_index = tindex[s].prev_n_trajectories[time_index];

	//printf("DEBUGGING: starting index: %u\n",(uint)s_index);

	return s_index;

}

size_t TIndex::getEndingIdIndex(uint s, size_t time_index){

	size_t e_index;

	if(time_index==tindex[s].n_times-1)
		e_index=tindex[s].n_ids-1;
	else{
		e_index=tindex[s].prev_n_trajectories[time_index+1]-1;
	}
	//printf("DEBUGGING: ending index: %u\n",(uint)e_index);

	return e_index;

}

/*void TIndex::print(){

	for (int i = 0; i < i; ++i)
	{
	
	}

}*/

void TIndex::printIdList(uint s, uint t){
	// s: stop, t: time

	if(s>tlist->stops){
		printf("ERROR: stop doesn't exist or dataset is corrupted\n");
		return;
	}

	size_t time_index=getTimeIndex(s,t);

	if(time_index==-1){
		printf("ERROR: time not found\n");
		return;
	}

	printf("Printing trajectory ids that include point (%u,%u): ", s,t);
	
	size_t starting_id_index=getStartingIdIndex(s,time_index);
	size_t ending_id_index=getEndingIdIndex(s,time_index);

	bool first=true;

	for(size_t i=starting_id_index;i<ending_id_index;i++){
		
		if(!first) printf(" ");
		else first=false;

		printf("%u",tindex[s].ids_list[i]);
	}

	printf("\n");
}

void TIndex::printIdList(uint s){

	size_t list_size=tindex[s].n_ids;

	for (size_t i = 0; i < list_size; i++){
		
		printf("%u ",tindex[s].ids_list[i]);
	}
	printf("\n");
}


void TIndex::printTimeList(uint s){

	size_t list_size=tindex[s].n_times;

	for (size_t i = 0; i < list_size; i++){
		
		printf("%u ",tindex[s].times_list[i]);
	}
	printf("\n");
}

void TIndex::printPrevTrajList(uint s){

	size_t list_size=tindex[s].n_times;

	for (size_t i = 0; i < list_size; i++){
		
		printf("%u ",tindex[s].prev_n_trajectories[i]);
	}
	printf("\n");
}

int TIndex::getTimeIndex(uint s, uint t){
	// s: stop, t: time
	// probado: esta bien esta busqueda 

    size_t l=0, r=(size_t)tindex[s].n_times-1, m;

    while(l<r){ //bin search to find the index of time t in times_list
        
        m=l+(r-l)/2;

       if(tindex[s].times_list[m] < t) //time is smaller than the given one
            l=m+1;
        else
            r=m;

    }

    /*
    if(tindex[s].times_list[l]!=t)
    	return -1;
    */


    return (int)l;
}

int TIndex::aggregatedReachability(uint s_in, uint interval, uint t_in, uint t_end, btree_map<uint, QueryResult > &results_table){
	// s_in: starting stop (node), interval: query buffer, t_in: starting time, t_end: ending time, results_table: structure to store query results
	// query finds destinations of trips that start in s_in within [t_ind,t_end), travelling for at most interval time instants

    int time_index_min = getTimeIndex(s_in,t_in); //indice del primer tiempo >= t_in
    int time_index_max = getTimeIndex(s_in,t_end); // indice del primer tiempo >= t_end
																							
    //printf("DEBUGGING: tiempo que devuelve: %d\n",tindex[s_in].times_list[time_index_min]);





    if(tindex[s_in].times_list[time_index_min] < t_in || tindex[s_in].times_list[time_index_min] >=t_end){
    	// UNCOMMENT IF DEBUGGING
		// ERROR: no times found in query range (todos los tiempos son menores que el tiempo inicial del rango)

        return -1;

    }



    //--------------------------------------
    // iteramos sobre los tiempos

    int destinations_cont=0;

    for(int time_index=time_index_min;time_index<time_index_max;time_index++){
    	int curr_time=tindex[s_in].times_list[time_index];

    
    // find the id of the smallest trajectory that *starts* in (s_in,curr_time)

	    uint starting_traj_id;
	   
	    size_t left_index=getStartingIdIndex(s_in,(size_t)time_index);
	    size_t right_index=getEndingIdIndex(s_in,(size_t)time_index);

		
	    uint l=left_index, r=right_index, m, traj_id;
	    uint traj_first_stop, traj_first_time;
	    pair<uint,uint> tmp_pair;

	    while(l<r){ // bin search to find starting trajectory id
	        
	        m=l+(r-l)/2;
	        traj_id = tindex[s_in].ids_list[m];
	        traj_first_stop=tlist->firstStop(traj_id);
	        traj_first_time=tlist->firstTime(traj_id);

	        //tmp_pair=make_pair(s_in,actual_starting_time);

	        if(traj_first_stop < s_in || (!(traj_first_stop>s_in) && traj_first_time<t_in) ){ // "smaller" trajectories than the ones of interest
	            l=m+1;

	        }
	        else
	            r=m;

	//            cout<<"l: "<<l<<" m: "<<m<<" r: "<<r<<endl;
	    }

	   	starting_traj_id=tindex[s_in].ids_list[l];
	   	uint starting_stop=tlist->firstStop(starting_traj_id);
	   	uint starting_time=tlist->firstTime(starting_traj_id);

	   	//printf("DEBUGGING: %\n");

	    //if(tlist->firstStop(starting_traj_id)!=s_in || tlist->firstTime(starting_traj_id)<t_in || tlist->firstTime(starting_traj_id)>=t_end){
	    if(starting_stop!=s_in || starting_time!=curr_time){
	    	
	    	//UNCOMMENT IF DEBUGGING
	    	//printf("There are no trips that start in (%u,%u)\n",s_in,t_in);

	    	continue; //probar con el siguiente tiempo
	    }
	    //---------------------------------------------


	    uint i=starting_traj_id;
	    uint ending_traj_id=tindex[s_in].ids_list[right_index];
	    size_t id_list_size=tlist->size();

	    // we iterate over TList's list of trajectories, taking advantage of the fact that they are sorted
	    //while(i<id_list_size && tlist->firstStop(i)==s_in && tlist->firstTime(i) >= t_in && tlist->firstTime(i)<t_end){ 
	    while(i<= ending_traj_id && tlist->firstStop(i)==s_in && tlist->firstTime(i) == curr_time){ 
	    	

	    	size_t traj_size=tlist->sizeOfTrajectory(i);

	        for(size_t j=1;j!=traj_size;j++){ //nos saltamos j=0 porque es el mismo nodo inicial, no hay viaje

	            size_t destination=j;
	            uint destination_time=tlist->timeAt(destination,i);

	            if(destination_time >= curr_time+interval) // comprueba que el tiempo del nodo visitado este dentro del rango
	                break;

	            // if the point is inside the query buffer, add to the results table
	            uint destination_stop = tlist->stopAt(destination,i);
	            auto it = results_table.find(destination_stop);

	            if (it == results_table.end()){
	            	
	            	QueryResult *qr = new QueryResult();
	                results_table.insert(make_pair(destination_stop,*qr));
	            }

	            uint travel_time=destination_time - curr_time + 1;
	            results_table[destination_stop].time_sum+=travel_time;
	            results_table[destination_stop].trajectory_count++;

	            if(travel_time < results_table[destination_stop].min_time)
	                results_table[destination_stop].min_time = travel_time;

	            if(travel_time > results_table[destination_stop].max_time)
	                results_table[destination_stop].max_time = travel_time;
	            
	            destinations_cont++;
	        }

	        i++;
	    }
	}

    return destinations_cont;

}

void loadListAndIndex(TList *tlist, ifstream &list_file, TIndex *tindex, ifstream &index_file){

	tlist = TList::load(list_file);

	tindex = TIndex::load(index_file,tlist);

}