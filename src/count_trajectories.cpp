#include <cstdio>
#include "tindex.h"

using namespace std;

int main(int argc, char **argv){
	
	string dataset, dataset_filename, index_folder, results_folder;
	string tlist_filename, tindex_filename, query_filename;
	TList *tl;
	TIndex *ti;
	ifstream infile;
	ofstream outfile;
	string list_out_filename="", index_out_filename="";

	dataset=argv[1];
	index_folder=argv[2];
	dataset_filename=getFilename(dataset);
	//query_filename=getFilename(argv[4]);

	tlist_filename=index_folder+"/"+dataset_filename+".tlist";
	tindex_filename=index_folder+"/"+dataset_filename+".tindex";

	//printf("tlist_filename: %s tindex_filename: %s\n",tlist_filename.c_str(),tindex_filename.c_str());


	//-----------------------
	// Load tlist from file
	printf("\nLoading tlist from file %s ...\n",tlist_filename.c_str());
	infile.open(tlist_filename,ios::binary);

    if(!infile){
        printf("ERROR: %s file doesn't exist. Exiting now.\n", tlist_filename.c_str());
        exit(EXIT_FAILURE);
    }

	tl=TList::load(infile);
	infile.close();
	printf("\tDONE\n");
	

	//------------------------
	// Load tindex from file

	printf("\nLoading tindex from file %s ...\n",tindex_filename.c_str());
	infile.open(tindex_filename,ios::binary);

    if(!infile){
        printf("ERROR: %s file doesn't exist. Exiting now.\n", tindex_filename.c_str());
        exit(EXIT_FAILURE);
    }

	ti=TIndex::load(infile,tl);
	infile.close();
	printf("\tDONE\n");



	uint s_in, t_in, t_interval, origin_only;
    int err, q_read, q_processed;
    btree_map<uint, QueryResult > results_table;  
    

    results_table.clear();

    int catch_error;

    s_in=1;
    t_in=stoi(argv[3]);
    t_interval=stoi(argv[4]);


    for(int x=t_in;x<t_in+t_interval;x++){

    	catch_error=ti.startsInQuery(s_in, t_in, t_interval, results_table);

    	int cant = 0;

    	for(auto z=results_table.begin();z!=results_table.end();z++){



    		
    	}

	}

	return 0;

}