#include "tindex.h"

using namespace std;

void printUsage(){

	printf("\nUSAGE:\n ./useIndex dataset_name path/index/folder path/results/folder < path/query/file\n");

}

int processQuery(uint s_in, uint t_in, uint t_interval, bool origin_only, TIndex &ti, btree_map<uint,QueryResult > &results_table){

    if(s_in > ti.totalStops()){ // check that stop id is on the list

        printf("\nERROR: stop %u not found in dataset\n", s_in);
        return -1;
    }

    results_table.clear();

    int catch_error;

    if(origin_only){

        catch_error=ti.startsInQuery(s_in, t_in, t_interval, results_table);

        if(catch_error==-1){
            printf("\nERROR: query %u,%u,%u, %s couldn't be executed\n",s_in,t_in,t_interval, origin_only ? "true": "false" );
            return -1;
        }      

    }
    else{
        // FIX-ME: AWAITING FOR includesQuery TO BE IMPLEMENTED
        /*
        catch_error=ti.includesQuery(s_in, t_in, t_interval, results_table)); // NOT IMPLEMENTED YET

        if(catch_error==-1){
            printf("ERROR: query %u,%u,%u, %s couldn't be executed\n",s_in,t_in,t_interval, origin_only ? "true": "false" );
            return -1;
        }  */
    }

    return 0;
}

int main(int argc, char *argv[]){


	string dataset, dataset_filename, index_folder, results_folder;
	string tlist_filename, tindex_filename, query_filename;
	TList *tl;
	TIndex *ti;
	ifstream infile;
	ofstream outfile;
	string list_out_filename="", index_out_filename="";

	if (argc!=4){
		printUsage();
		exit(EXIT_FAILURE);
	}

	dataset=argv[1];
	index_folder=argv[2];
	dataset_filename=getFilename(dataset);
    results_folder=argv[3];
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


	//------------------------
	// some test to check that the structures loaded correctly

    /*	
	tl->printTrajectory(0);
    printf("-------------\n");
	ti->printIdList(2,100);
printf("-------------\n");
	tl->printTrajectory(tl->trips-1);
    printf("-------------\n");

	ti->printIdList(1,97);
    printf("-------------\n");
    ti->printIdList(1);
    printf("-------------\n");
    ti->printTimeList(1);
    printf("-------------\n");
    ti->printPrevTrajList(1);
    printf("-------------\n");
    ti->printIdList(1,96);
    printf("-------------\n");
    */

	//------------------------
	// ACCESIBILITY QUERIES
	// (for *real* trajectories)

    uint s_in, t_in, t_interval, origin_only;
    int err, q_read, q_processed;
    btree_map<uint, QueryResult > results_table;  
    
    printf("\nReading and executing queries from query file...\n");

    ofstream query_results_file;    
    string output_file, query_type;
    

    q_read=0;
    q_processed=0;
    // reads from input file
 	while(EOF != scanf("%u %u %u %u", &s_in,&t_in, &t_interval, &origin_only)){ //read until the end of a query file
        
        //if(!s_in && !t_in && !t_interval && !origin_only) break; //read until 0 0 0 0

        q_read++; // read queries

        err=processQuery(s_in,t_in,t_interval,origin_only,*ti,results_table);

        //printf("DEBUGGING: results_table.size = %u\n", (uint)results_table.size());

        if(err==-1)
            continue;

        if(origin_only) query_type="R"; // indicates that query is on real trajectories only
        else query_type="P"; // indicates that query includes potential trajectories

        output_file=results_folder+"/"+dataset_filename+"-"+query_type+"-"+to_string(s_in)+"_"+to_string(t_in)+"-"+to_string(t_interval*5)+"min.txt";
        query_results_file.open(output_file);

        if(query_results_file){ // save query results to file
            for(auto it=results_table.begin();it!=results_table.end();it++){

                
                /* origin,destination,[starting_query_time,ending_query_time),time_sum,trajectory_count,min_time,max_time */
                query_results_file<<s_in<<" "<<it->first<<" "<<t_in<<" "<<t_in+t_interval<<" "<<(it->second.time_sum)*5<<" "<<it->second.trajectory_count<<" "<<(it->second.min_time)*5<<" "<<(it->second.max_time)*5<<endl;
                
            }
            query_results_file.close();
        }
        else
            exit(EXIT_FAILURE);
   
        q_processed++; // processed queries

    }

    printf("\tDONE.\nQueries read: %d\tQueries processed: %d\n", q_read, q_processed);
        
    return 0;

}