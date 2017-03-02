#include "stop_encoding.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include "tindex.h"
#include "tlist.h"
#include <map>

using namespace std;


int main(int argc, char **argv){

	int day, hour, d_interval;
	int start_day=14, end_day=21;
	string hour_str, day_str;
	ifstream infile;
	TList *tl;

	string tlist_filename="/Users/huguito/Cathy/Tesis/trajectory-baseline/structures/sorted_transantiago_encoded_trips.tlist";


	printf("\nLoading tlist from file %s ...\n",tlist_filename.c_str());
	infile.open(tlist_filename,ios::binary);

    if(!infile){
        printf("ERROR: %s file doesn't exist. Exiting now.\n", tlist_filename.c_str());
        exit(EXIT_FAILURE);
    }

	tl=TList::load(infile);
	infile.close();
	printf("\tDONE\n");

	map<int,int> count;



	for(day=start_day;day<=end_day;day++){

		day_str=to_string(day);

		for(hour=0;hour<24;hour++){

			hour_str=to_string(hour);
			if(hour<10) hour_str="0"+hour_str;

			string date="2013-04-"+day_str+" "+hour_str+":00:00";

			d_interval=getDiscreteTimeInterval(date,5,14);

			count.insert(pair<int,int>(d_interval,0));

		}


	}


	//recorrer la TList y sumar al bucket (count)

	int tam=tl->trips;

	for(int i=0;i<tam;i++){

		int s_time=tl->firstTime(i);
		int aux=s_time%12;
		s_time=s_time-aux;

		count[s_time]++;
	}

	int total_trips=0;
	ofstream outfile;
	string out_filename="/Users/huguito/Cathy/Tesis/trajectory-baseline/other_extracted_data/trips_per_hour.csv";

	printf("\nSaving file %s ...\n",out_filename.c_str());
	outfile.open(out_filename);

    if(!outfile){
        printf("ERROR: %s file doesn't exist. Exiting now.\n", out_filename.c_str());
        exit(EXIT_FAILURE);
    }

    day=14;
    hour=0;
	for(auto it=count.begin();it!=count.end();it++){

		int hourly_trips=it->second;
		total_trips+=hourly_trips;
		string hourly_trips_str=to_string(hourly_trips);

		day_str=to_string(day);
		hour_str=to_string(hour);
		if(hour<10) hour_str="0"+hour_str;


		string results=day_str+",04,2013,"+hour_str+","+hourly_trips_str+"\n";

		outfile<<results;

		hour++;
		if(hour==24){
			hour=0;
			day++;
		}

	}

	outfile.close();
	printf("DONE!\n");

	printf("Total trips: %d\n",total_trips);

	return 0;
}



// cantidad de viajes por hora

//totales

//por paradero