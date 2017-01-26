#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


int main(int argc, char **argv){

	uint first_stop, last_stop, interval;
	int first_q_time;


	first_stop=atoi(argv[1]);
	last_stop=atoi(argv[2]);
	first_q_time=atoi(argv[3]);
	interval=atoi(argv[4]);

	ofstream query_file;

	string filename="s"+to_string(first_stop)+"-s"+to_string(last_stop)+"_t"+to_string(first_q_time)+"+"+to_string(interval)+".txt";

	string results_folder="/home/cathy/Magister/Tesis/trajectory-baseline/queries";

	string q_file=results_folder+"/"+filename;

	query_file.open(q_file);

	if(query_file){

		for(uint i=first_stop;i<=last_stop;i++){

			query_file<<i<<" "<<first_q_time<<" "<<interval<<" 1\n";

		}
		query_file.close();
	}
	else{
		exit(EXIT_FAILURE);
	}



	return 0;


}