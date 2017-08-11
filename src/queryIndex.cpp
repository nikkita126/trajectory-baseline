#include "tindex.h"

using namespace std;

#define MAX_QUERIES 13000
#define MINUTES_SAMPLE 5

typedef struct{

    uint s_in;
    uint interval;
    uint t_in;
    uint t_end;
} ReachQuery;


void printUsage(){

	printf("\nUSAGE:\n ./useIndex dataset_name path/index/folder path/results/folder < path/query/file\n");

}

ReachQuery * readQueries(int *nqueries){

    ReachQuery *query_list = (ReachQuery *) malloc(MAX_QUERIES * sizeof(ReachQuery));
    int count=0;
    uint s_in, interval, t_in, t_end;

    while(EOF != scanf("%u %u %u %u", &s_in,&interval,&t_in, &t_end)){ //read until the end of a query file
        
        ReachQuery *q=&query_list[count];
        q->s_in=s_in;
        q->interval=interval;
        q->t_in=t_in;
        q->t_end=t_end;
        count++;
    }
    *nqueries=count;
    return query_list;
}

int processQuery(ReachQuery rq, TIndex &ti, btree_map<uint,QueryResult > &results_table){

    if(!ti.isInDataset(rq.s_in)){
        // stop not found in dataset
        return -1;
    }

    results_table.clear();

    int total_neighbors;

    //printf("DEBUGGING: s_in: %d interval: %d t_in: %d t_end: %d\n",rq.s_in, rq.interval,rq.t_in, rq.t_end);

    total_neighbors=ti.aggregatedReachability(rq.s_in, rq.interval,rq.t_in, rq.t_end, results_table);     

    return total_neighbors;
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

    uint s_in, t_in, t_end, t_interval;
    int total_neighbors, q_read, q_processed, q_success;
    btree_map<uint, QueryResult > results_table;
    
    printf("\nReading queries from query file...\n");

    ofstream query_results_file;    
    string output_file, query_type;
    

    q_read=0;
    q_processed=0;
    q_success=0;
    
    // reads from input file (redirected input when executing the program)
    ReachQuery *query_list=readQueries(&q_read);
    printf("\tDONE\n");
    printf("\t%d queries read\n", q_read);

    printf("\nProcessing...\n");

    int ten_perc=q_read/10;
 	while(q_processed<q_read){ //iterate over read queries
        if(!(q_processed%ten_perc))
            printf("\t%d queries processed...\n", q_processed);
        
        ReachQuery query = query_list[q_processed];
        total_neighbors=processQuery(query,*ti,results_table);

        //printf("DEBUGGING: results_table.size = %u\n", (uint)results_table.size());

        if(total_neighbors<1){
            q_processed++;
            continue;
        }

        output_file=results_folder+"/"+dataset_filename+"-"+to_string(query.s_in)+"-"+to_string(query.t_in)+"_"+to_string(query.t_end)+"-"+to_string(query.interval*MINUTES_SAMPLE)+"min.txt";
        query_results_file.open(output_file);
        //bool first_line=true;
        if(query_results_file){ // save query results to file
            for(auto it=results_table.begin();it!=results_table.end();it++){
                //if(first_line) first_line=false;
                //else query_results_file<<"\n";
                
                /* origin,destination,[starting_query_time,ending_query_time),interval*MINUTES_SAMPLE,time_sum*MINUTES_SAMPLE,trajectory_count,min_time*MINUTES_SAMPLE,max_time*MINUTES_SAMPLE */
                query_results_file<<query.s_in<<" "<<it->first<<" "<<query.t_in<<" "<<query.t_end<<" "<<query.interval*MINUTES_SAMPLE<<" "<<(it->second.time_sum)*MINUTES_SAMPLE<<" "<<it->second.trajectory_count<<" "<<(it->second.min_time)*MINUTES_SAMPLE<<" "<<(it->second.max_time)*MINUTES_SAMPLE<<"\n";
                
            }
            query_results_file.close();
        }
        else
            exit(EXIT_FAILURE);
   
        q_processed++; // processed queries
        q_success++;

    }

    printf("\tDONE.\nQueries read: %d\tQueries processed: %d\t Successful queries: %d\n", q_read, q_processed,q_success);
        
    return 0;

}