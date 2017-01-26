#include "distance_graph.h"

class Time_Info{

	/* origin,destination,[starting_query_time,ending_query_time),time_sum,trajectory_count,min_time,max_time */
	public:
		uint s_orgn;
		uint s_dest;
		int t_in;
		int t_end;
		int t_sum;
		int traj_count;
		int min_time;
		int max_time;


		Time_Info(uint s_o, uint s_d, int t_i, int t_e, int t_s, int traj_c, int min_t, int max_t){

			s_orgn=s_o;
			s_dest=s_d;
			t_in=t_i;
			t_end=t_e;
			t_sum=t_s;
			traj_count=traj_c;
			min_time=min_t;
			max_time=max_t;

		}

};



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



int main(int argc, char **argv){

	string encoded_dist_filename(argv[1]);

	string separator(";");
	uint n_stops=11500;

	Distance_Graph *dg = new Distance_Graph(encoded_dist_filename,n_stops,separator);

	

	dg->printInfo();

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


	//Leer archivo de tiempos y trayectorias
	ifstream times_file;
	string infile_name=argv[2];

	times_file.open(infile_name);

	if(!times_file){
        printf("ERROR: %s file doesn't exist. Exiting now.\n", infile_name.c_str());
        exit(EXIT_FAILURE);
    }


	vector<Time_Info> times_vect;
	uint s_orgn, s_dest;
	int t_in, t_end, t_sum, traj_count, min_time, max_time;
	string line;

	while(getline(times_file,line)){

		sscanf(line.c_str(),"%u %u %d %d %d %d %d %d", &s_orgn,&s_dest, &t_in, &t_end, &t_sum, &traj_count, &min_time, &max_time);
		Time_Info *time_inf = new Time_Info(s_orgn,s_dest,t_in,t_end,t_sum,traj_count,min_time,max_time);

		times_vect.push_back(*time_inf);


	}

	times_file.close();

	float reach_min, reach_max, reach_mean, dist;
	float ac_min, ac_max, ac_mean;
	uint sum_min, sum_max, sum_mean,sum_traj,sum_dist,neighbour_stops;
	float min,max,mean;


	
	ac_min=0;
	ac_max=0;
	ac_mean=0;

	sum_min=0;
	sum_max=0;
	sum_mean=0;
	sum_traj=0;
	sum_dist=0;
	neighbour_stops=0;

	for(auto it=times_vect.begin();it!=times_vect.end();it++){

		//printf("%u %u %d %d %d %d %d %d\n",it->s_orgn,it->s_dest, it->t_in, it->t_end, it->t_sum, it->traj_count, it->min_time, it->max_time);
		dist=dg->getDistance(it->s_orgn,it->s_dest);
		/*min=dist*it->min_time*it->traj_count;
		max=dist*it->max_time*it->traj_count;
		mean=dist*(float)((float)it->t_sum/(float)it->traj_count)*it->traj_count;

		ac_min+=min;
		ac_max+=max;
		ac_mean+=mean;


		sum_min+=it->min_time*it->traj_count;
		sum_max+=it->max_time*it->traj_count;
		sum_mean+=(float)((float)it->t_sum/(float)it->traj_count)*it->traj_count;*/

		sum_dist+=dist;
		sum_traj+=it->traj_count;
		neighbour_stops++;


	}
	/*
	reach_min=ac_min/sum_min;
	reach_max=ac_max/sum_max;
	reach_mean=ac_mean/sum_mean;
	*/

	reach_min=(float)((float)sum_dist/(float)neighbour_stops);

	// guardar resultado (archivo?)

	//printf("Stop %d time %d to %d, Reach min: %f, reach max: %f, reach mean: %f\n",s_orgn,t_in,t_end,reach_min,reach_max,reach_mean);
	printf("Stop %d time %d to %d, traj count: %d, neighbour stops: %d, Reach dist: %f\n",s_orgn,t_in,t_end,sum_traj,neighbour_stops,reach_min);


	return 0;
}