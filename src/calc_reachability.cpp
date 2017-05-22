
#include "stops_dictionary.h"
#include "utils.h"
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
//#include <utility>

#define IN_STOP 1
#define END_STOP 11270


using namespace std;

class Reach_Pair_Info{

	/* origin,destination,[starting_query_time,ending_query_time),time_sum,trajectory_count,min_time,max_time */
	public:
		uint s_orgn;
		uint s_dest;
		int t_in;
		int t_end;
		int interval;
		int t_sum;
		int traj_count;
		int min_time;
		int max_time;


		Reach_Pair_Info(uint s_o, uint s_d, int t_i, int t_e, int inter, int t_s, int traj_c, int min_t, int max_t){

			s_orgn=s_o;
			s_dest=s_d;
			t_in=t_i;
			t_end=t_e;
			interval=inter;
			t_sum=t_s;
			traj_count=traj_c;
			min_time=min_t;
			max_time=max_t;

		}

};




void printUsage(){

	printf("\nUSAGE:\n ./calc_reachability <dictionary_structure> <query_results_folder> <dataset_name> <in_time> <end_time> <minute_buffer> <reachability_folder>\n");

}

/*
void test_queries(Distance_Graph &dg){

	dg.printDistance(1,2);
	dg.printDistance(100,500);
	dg.printDistance(10456,4567);
	dg.printDistance(2,7);
	dg.printDistance(11194,194);
	dg.printDistance(11194,195);
	dg.printDistance(11196,1);
	dg.printDistance(11208,2766);
	dg.printDistance(11196,1385);

}

*/

int main(int argc, char *argv[]){

	
	string dictionary_file=argv[1];


	Stops_Dictionary *sd = new Stops_Dictionary();

	sd->load(dictionary_file);

	//free(dictionary_file);

	//printf("Testeando. Distancia entre 447 y 369: %d\n", sd->getDistance(447,369));
	//sd->printNodeInfo(447);
	//sd->printInfo();



	/*for(int i=1;i<10;i++){
		printf("%d: ",(int)graph[i].size());

		for(auto j=graph[i].begin();j!=graph[i].end();j++){

			printf("%d %d %d\n",i,j->first,j->second);
		}
		printf("\n");

	}
	*/

	/*----- test queries ----*/
	//test_queries(*dg);
	/*------------------------*/

	// DESDE AQUI

	/** Leer archivo de tiempos y trayectorias */
	ifstream query_results_file;

	//FIXME: cambiar por "opciones" de ejecucion
	string query_results_folder=argv[2];
	string dataset_name=argv[3];
	string in_time_str=argv[4];
	string end_time_str=argv[5];
	string minute_buffer_str=argv[6];

	//printf("In time str: %s\n",in_time_str.c_str());

	uint in_stop=IN_STOP;
	uint end_stop=END_STOP;
	int in_time=atoi(in_time_str.c_str());
	int end_time=atoi(end_time_str.c_str());
	int minute_buffer=atoi(minute_buffer_str.c_str());

	if(end_stop<in_stop){
        printf("ERROR: end_stop id must be higher than in_stop id\n");
        exit(EXIT_FAILURE);
    }

    string out_data;
    out_data="current_stop,in_time,end_time,minute_buffer,total_trips,neighbour_stops,total_dist,max_dist,neighbour_dist_mean,";
    out_data+="reach_distTrips,reach_distTripsMintime,reach_distTripsMaxtime,reach_distTripsMeantime\n";

	/* Loop: from in_stop to end_stop, to loop through the files */


	/* For z-scores */

	vector<pair<int,float> > reach_dt_vec;
	int count_reach_dt=0;
	float sum_reach_dt=0;



    for(uint current_stop=in_stop;current_stop<=end_stop;current_stop++){

		string query_results_filename=query_results_folder+"/"+dataset_name+"-"+to_string(current_stop)+"-"+in_time_str+"_"+end_time_str+"-"+minute_buffer_str+"min.txt";

		query_results_file.open(query_results_filename);

		if(!query_results_file){
	        //printf("WARNING: %s file doesn't exist. Skipping.\n", query_results_filename.c_str());
	        query_results_file.close();
	        continue;
	        //exit(EXIT_FAILURE);
	    }

	    //sd->printNodeInfo(447);

		vector<Reach_Pair_Info> reach_pair_vect;
		uint s_orgn, s_dest;
		int t_in, t_end, interval, t_sum, traj_count, min_time, max_time;
		string line;

		while(getline(query_results_file,line)){

			sscanf(line.c_str(),"%u %u %d %d %d %d %d %d %d", &s_orgn,&s_dest, &t_in, &t_end, &interval,&t_sum, &traj_count, &min_time, &max_time);
			Reach_Pair_Info *reach_pair = new Reach_Pair_Info(s_orgn,s_dest,t_in,t_end,interval,t_sum,traj_count,min_time,max_time);

			reach_pair_vect.push_back(*reach_pair);
			free(reach_pair);
			//sd->printNodeInfo(447);

		}

		query_results_file.close();

		

		/* ---------------------------------- */


		/* Metrics */
		unsigned long long total_dist; //in case it gets too big
		uint total_trips, neighbour_stops, max_dist;
		float reach_distTrips, reach_distTripsMintime, reach_distTripsMaxtime, reach_distTripsMeantime;
		float neighbour_dist_mean;
		

		/* Aux variables */
		float sum_distTrips, sum_distTripsMintime, sum_distTripsMaxtime, sum_distTripsMeantime;
		uint sum_tripsMintime, sum_tripsMaxtime, sum_tripsMeantime, sum_dist;

		/* ----------------------------------- */

		total_trips=0;
		total_dist=0;
		neighbour_stops=0;
		max_dist=0;

		sum_distTrips=0;
		sum_distTripsMintime=0;
		sum_distTripsMaxtime=0;
		sum_distTripsMeantime=0;

		sum_tripsMintime=0;
		sum_tripsMaxtime=0;
		sum_tripsMeantime=0;
		sum_dist=0;




		for(auto it=reach_pair_vect.begin();it!=reach_pair_vect.end();it++){

			float distTrips,min,max,mean;
			int dist;

			//printf("%u %u %d %d %d %d %d %d\n",it->s_orgn,it->s_dest, it->t_in, it->t_end, it->t_sum, it->traj_count, it->min_time, it->max_time);
			
			dist=sd->getDistance(it->s_orgn,it->s_dest);
			/*
			if(it->s_orgn==447){
				sd->printNodeInfo(it->s_orgn);
				sd->printNodeInfo(it->s_dest);

			}
			*/

			//if(it->s_orgn==447) printf("Distancia %d entre %d - %d\n", dist,it->s_orgn,it->s_dest);

			if(dist>max_dist)
				max_dist=dist;

			distTrips=dist*it->traj_count;
			min=distTrips*it->min_time;
			max=distTrips*it->max_time;
			mean=distTrips*(float)((float)it->t_sum/(float)it->traj_count);


			sum_distTrips+=distTrips;
			sum_distTripsMintime+=min;
			sum_distTripsMaxtime+=max;
			sum_distTripsMeantime+=mean;


			sum_tripsMintime+=it->min_time*it->traj_count;
			sum_tripsMaxtime+=it->max_time*it->traj_count;
			sum_tripsMeantime+=(float)((float)it->t_sum/(float)it->traj_count)*it->traj_count;

			sum_dist+=dist;
			total_trips+=it->traj_count;
			total_dist+=distTrips;
			neighbour_stops++;

		} // fin iteracion sobre lineas de un mismo archivo

		// distancia maxima = max_dist
		
		// reachability without times
		reach_distTrips=(float)((float)total_dist/(float)total_trips);

		// reachability with times
		reach_distTripsMintime=sum_distTripsMintime/sum_tripsMintime;
		reach_distTripsMaxtime=sum_distTripsMaxtime/sum_tripsMaxtime;
		reach_distTripsMeantime=sum_distTripsMeantime/sum_tripsMeantime;

		// mean distance to visited neighbour stops
		neighbour_dist_mean=(float)((float)sum_dist/(float)neighbour_stops);
		
		// distancia ponderada por trayectorias
		// ponderan considerando el tiempo que me sobró


		/* load results into out string */
		out_data+=to_string(current_stop)+","+in_time_str+","+end_time_str+","+minute_buffer_str+","+to_string(total_trips)+","+to_string(neighbour_stops)+","+to_string(total_dist)+","+to_string(max_dist)+","+to_string(neighbour_dist_mean)+",";
    	out_data+=to_string(reach_distTrips)+","+to_string(reach_distTripsMintime)+","+to_string(reach_distTripsMaxtime)+","+to_string(reach_distTripsMeantime)+"\n";

    	reach_dt_vec.push_back(make_pair(current_stop,reach_distTrips)); //acumulate reachability in vector
    	sum_reach_dt+=reach_distTrips;
    	count_reach_dt++;

	}

	if(!count_reach_dt){
		printf("No files processed\n");
		return 0;
	}


	/* ------------------- END OF LOOP THROUGH THE FILES ----------------- */

	/* ------------------- SAVE REACHABILITY MEASURE DATA AS CSV ----------------- */


	printf("Saving data to CSV file...\n");
	ofstream outfile;

	string reachability_folder=argv[7];
	string out_filename=reachability_folder+"/Reach-"+dataset_name+"-"+to_string(in_stop)+"_"+to_string(end_stop)+"-"+in_time_str+"_"+end_time_str+"-"+minute_buffer_str+"min.csv";
	//set filename

	outfile.open(out_filename);

	if(!outfile){
		printf("ERROR: %s file couldn't be open. Exiting now.\n", out_filename.c_str());
		exit(EXIT_FAILURE);
	}


	outfile<<out_data;
	//printf("Stop %d time %d to %d, Reach min: %f, reach max: %f, reach mean: %f\n",s_orgn,t_in,t_end,reach_distTripsMintime,reach_distTripsMaxtime,reach_distTripsMeantime);
	/*printf("Stop %d time %d to %d\n\ttraj count: %d\n\tneighbour stops: %d\n\tdist mean: %f\n",s_orgn,t_in,t_end,total_trips,neighbour_stops,neighbour_dist_mean);
	printf("\nreach min: %f\treach max: %f\treach mean: %f\n",reach_distTripsMintime,reach_distTripsMaxtime,reach_distTripsMeantime);
	printf("\nSIN TIEMPOS: reach min: %f\n",a/total_trips);
*/

	outfile.close();


	printf("DONE\n");

	/* ------------------- END OF SAVING REACHABILTY MEASURES DATA ----------------- */

	/* ------------------- Z-SCORES CALCULATION ----------------- */


	printf("Calculating z-scores...\n");

	/* Z-SCORES */

	/* ---- STD DEV ---- */
	// count_reach_dt = nro archivos procesados (nodos con viajes iniciados en el rango)
	// sum_reach_dt = suma de los valores del reachability measure de todos los nodos
	//
	// std_dev(val) = raiz cuadrada( (sum(i=1...n) (val[i] - promedio(val)^2) / n )
	
	float mean_reach_dt = (float)(sum_reach_dt/count_reach_dt);

	float std_dev = 0;
	float var=0;
	for(auto it = reach_dt_vec.begin();it!=reach_dt_vec.end();it++ ){
		var += (it->second - mean_reach_dt) * (it->second - mean_reach_dt);
	}
	var /= count_reach_dt;
	std_dev = sqrt(var);


	/* ---- Z-SCORE ---- */
	// z(i) = ( val(i) - promedio(val) ) / std_dev(val)

	string out_data_z="stop,z_score\n";
	float z=0;


	for(auto it = reach_dt_vec.begin();it!=reach_dt_vec.end();it++ ){
		z=(float)((it->second - mean_reach_dt)/(std_dev));
		out_data_z+=to_string(it->first)+","+to_string(z)+"\n";
	}

	/* ------------------- SAVE Z-SCORES DATA ----------------- */


	ofstream outfile_z;

	string out_filename_z=reachability_folder+"/Z-"+dataset_name+"-"+to_string(in_stop)+"_"+to_string(end_stop)+"-"+in_time_str+"_"+end_time_str+"-"+minute_buffer_str+"min.csv";
	//set filename

	outfile_z.open(out_filename_z);

	if(!outfile_z){
		printf("ERROR: %s  file couldn't be open. Exiting now.\n", out_filename.c_str());
		exit(EXIT_FAILURE);
	}


	outfile_z<<out_data_z;
	outfile_z.close();


	printf("... DONE\n");
	return 0;


}