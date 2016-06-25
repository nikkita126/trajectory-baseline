#include "tindex.h"

//using namespace btree;

//-------------------------
// Query

Query::Query(uint n, uint t, uint t_i, bool o_o){
	st_node=n;
	st_time=t;
	time_interval=t_i;
	origin_only=o_o;
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


size_t TIndex::getStartingIdIndex(uint s, size_t time_index){

	size_t s_index = tindex[s].prev_n_trajectories[time_index];

	return s_index;

}

size_t TIndex::getEndingIdIndex(uint s, size_t time_index){

	size_t e_index;

	if(time_index==tindex[s].n_times-1)
		e_index=tindex[s].n_ids-1;
	else
		e_index=tindex[s].prev_n_trajectories[time_index+1];


}

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

size_t TIndex::getTimeIndex(uint s, uint t){
	// s: stop, t: time

    size_t l=0, r=(size_t)tindex[s].n_times-1, m;

    while(l<r){ //bin search to find the index of time t in times_list
        
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

int TIndex::getStartingId(uint n_in, uint t_in, bool origin_only){
    /* argumentos: 
        * nodo inicial de la consulta
        * tiempo inicial de la consulta
        * flag para determinar si solo considerar pares (n,t) que inicien una trayectoria
        * lista de trayectorias
        * metodo de acceso a la lista
    */

    TList *tl = tlist;
    uint *list_of_times = tindex[n_in].times_list;
    uint times_list_size = tindex[n_in].n_times;


    // starting point
    auto l_b = lower_bound(list_of_times,list_of_times+times_list_size,t_in);
   
    // if there is no lower bound of t_in on the list, throw error message
    if(l_b=list_of_times+times_list_size){
        printf("ERROR, starting time is bigger than any other time in the list\n");
        return -1;
    }

     uint actual_starting_time=*l_b;


    //uint asdf=*l_b->second;

    //cout<<"lb: "<<l_b->first<<endl;

    //if(l_b->first >= t_fin){
    if(actual_starting_time > (t_in + DELTA_T)){
            //tiempo fuera de rango
            printf("There are no travels using (%u,%u)\n",n_in,t_in);
            return -1;
    }

    

    uint selected_index=l_b-list_of_times;
    printf("selected index: %d\n",selected_index);

    /*
    vector<uint> ids_vector;
    to_vector(l_b->second, ids_vector);

    if(origin_only){

        uint tam_lista_ids = ids_vector.size();

        uint l=0, r=tam_lista_ids-1, m, tray_id;
        uint first_node, first_time;
        pair<uint,uint> tmp_pair;

        while(l<r){
            
            m=l+(r-l)/2;
            tray_id = ids_vector[m];
            first_node=lista_trayectorias[tray_id][0].first;
            first_time=lista_trayectorias[tray_id][0].second;
            tmp_pair=make_pair(n_in,actual_starting_time);

            if(lista_trayectorias[tray_id][0] < tmp_pair){ // trayectorias "menores" que la buscada 
                l=m+1;

            }
            else
                r=m;

//            cout<<"l: "<<l<<" m: "<<m<<" r: "<<r<<endl;
        }
        return ids_vector[l];
    }
    else {

        // para trayectorias potenciales

    }*/

    return -1;

}

void loadListAndIndex(TList *tlist, ifstream &list_file, TIndex *tindex, ifstream &index_file){

	tlist = TList::load(list_file);

	tindex = TIndex::load(index_file,tlist);

}




