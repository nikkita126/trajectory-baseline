/* createIndex.cpp
*
*
*
*/
#include "tlist.h"
#include "tlistreader.h"
#include "tindex.h"
#include "utils.h"

using namespace std;

void printUsage(){

	printf("\nUSAGE:\n ./createIndex path/sorted_dataset.txt path/index/folder\n");

}

TListReader* readData(ifstream &infile){
	TListReader *t = new TListReader();

	string line;
	size_t stop_end_pos, time_end_pos;
	uint stop_int,time_int;
	uint cont_traj;
	uint maxtime=0;
	uint maxstop=0;

	btree_set<uint> stops;
    
    if(infile){
		
		cont_traj=0;
    	while(getline(infile,line)){
    		//cout<<line<<endl;
    		size_t point_start_pos=0;
    		while(true){
    			stop_end_pos=line.find(' ',point_start_pos);
    			//cout<<stop_end_pos<<endl;  	
				time_end_pos=line.find(' ',stop_end_pos+1);
				  

				stop_int = stoi(line.substr(point_start_pos,(stop_end_pos - point_start_pos)));
	    		time_int = stoi(line.substr(stop_end_pos+1,(time_end_pos - (stop_end_pos+1))));

		    	point_start_pos=time_end_pos+1;

		    	t->addPoint(cont_traj,stop_int,time_int);
		    	stops.insert(stop_int);
		    	if(time_int>maxtime) maxtime=time_int;

		    	if(time_end_pos==string::npos)
					break;

				if(stop_int>maxstop) maxstop=stop_int;

    		} /* end of iteration over the same trip */
            //cout<<"tam lista: "<<lista_trayectorias.size()<<endl;
			cont_traj++;

    	}
    }
    else
    	exit(EXIT_FAILURE);

    t->setTrips(cont_traj);
    t->setStops(maxstop);
    t->setMaxtime(maxtime);



    return t;

}


int main(int argc, char *argv[]){

	string dataset, dataset_filename, index_folder;
	TListReader *tlr;
	TList tl;
	TIndex ti;
	ifstream infile;
	ofstream outfile;
	string list_out_filename="", index_out_filename="";

	if (argc!=3){
		printUsage();
		exit(EXIT_FAILURE);
	}
	else {

		dataset=argv[1];
		index_folder=argv[2];
		dataset_filename=getFilename(dataset);
	}


	//--------------------
	// Parse input data and load it into ordered, auxiliar structure
	printf("\nReading data from dataset... \n");
	infile.open(dataset);

	if(!infile){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", dataset.c_str());
        exit(EXIT_FAILURE);
    }


	tlr=readData(infile);
    infile.close();
    printf("\tDONE\n");

    //--------------------
    // Create list structure of trajectories
    printf("\nCreating trajectory list...\n");
    tl.create(*tlr);
	printf("\tDONE\n");
	//--------------------
	// Create index
	printf("\nCreating trayectory index...\n");
	ti.create(tl);
	printf("\tDONE\n");
	//--------------------
	// Save list and index to disk

	printf("\nSaving data structures to disk...\n");
	list_out_filename=index_folder+"/"+dataset_filename+".tlist";
	outfile.open(list_out_filename,ios::binary);
	tl.save(outfile);
	outfile.close();

	index_out_filename=index_folder+"/"+dataset_filename+".tindex";
	outfile.open(index_out_filename,ios::binary);
	ti.save(outfile);
	outfile.close();
	printf("\tDONE\n");



	return 0;

}
