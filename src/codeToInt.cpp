/* codeToInt.cpp
*	Transforms a trajectory file containing stop names and timestamps
*	into its encoded version (with ints)
*
*/


#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "cppUtils.h"
#include "stop_encoding.h"

#define STARTING_DATE_DAY 14
#define SEPARATOR ";"

using namespace std;

void printUsage(){

	printf("\nUSAGE:\n ./codeToInt path/stop_names_and_codes_file.txt path/trajectories_file.txt path/encoded_trajectories_file.txt time_interval(mins)\n");

}




void encodeTrajectories(ifstream &trajectories_file, map<string,int> &dictionary, ofstream &encoded_trajectories_file, uint time_interval){

	string line, encoded_line;
	size_t stop_end_pos, time_end_pos;
	string stop_str, time_str;
	int discrete_time_interval, starting_day;
	int stop_int;
	int cont_points,cont_traj;
	
	bool first_line=true;
	
	printf("\nEncoding trajectories... \n");
	cont_traj=0;

	while(getline(trajectories_file,line)){
		cont_traj++;
		size_t point_start=0; // point = pair (stop,time) 
		encoded_line="";
		cont_points=0;
		if(first_line)
			first_line=false;
		else
			encoded_line+="\n";


		while(true){
    		stop_end_pos=line.find(';',point_start);
			//if(stop_end_pos==string::npos)
			//	break;    	
			time_end_pos=line.find(';',stop_end_pos+1);
	    	


    		stop_str = line.substr(point_start,(stop_end_pos - point_start));
    		time_str = line.substr(stop_end_pos+1,(time_end_pos - (stop_end_pos+1)));

    		//cout<<stop_str<<" "<<time_str<<endl;

	    	point_start=time_end_pos+1; // update so the next iteration starts from the next point

    		

    		// buscar el codigo de stop_str en el mapa y reemplazalo
			
			//string tmp=checkStopName(stop_str); //UNNECESARY: it has been done directly in the dataset
    		//it=dictionary.find(tmp);

    		stop_int=getStopId(stop_str,dictionary);


    		// define discrete time interval
    		discrete_time_interval=getDiscreteTimeInterval(time_str,time_interval,STARTING_DATE_DAY);
    		
    		if(stop_int < 1){ //stop ids start from 1
    			printf("ERROR: stop '%s' not found in dictionary. Stopping the process.\n",stop_str.c_str());
				exit(EXIT_FAILURE);
			}


			if(cont_points)
				encoded_line+=" ";
			else
				cont_points++;

			encoded_line+= to_string(stop_int);
			encoded_line+= " ";
			encoded_line+= to_string(discrete_time_interval);

			if(time_end_pos==string::npos)
    			break;

		} // end of while that iterates over a line

		//encoded_line+="\n";
		//cout<<encoded_line<<endl;
		encoded_trajectories_file<<encoded_line;

	} // end of while that iterates over the file

	printf("\tDONE.\n %d trajectories encoded.",cont_traj);

}



int main(int argc, char* argv[]){

	int id_count;

	map<string,int> dictionary;
	

/*---------------------------------------------------*/
/* Dictionary creation */

	ifstream stops_names_and_codes;
	if (argc == 5){
		stops_names_and_codes.open(argv[1]);

		if(!stops_names_and_codes){
	        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[1]);
	        exit(EXIT_FAILURE);
    	}

    	string separator (SEPARATOR);
		createDictionary(dictionary,stops_names_and_codes,separator);
		stops_names_and_codes.close();
	}
	else{
		printUsage();
		exit(EXIT_FAILURE);
	}



/*-----------------------------------------------------*/
/*	Encode trajectory data to ints */

	ifstream trajectories_file(argv[2]);
	ofstream encoded_trajectories_file(argv[3]);
	uint time_interval=atoi(argv[4]);

	if (trajectories_file){
		//cout<<"Trying to read file: "<<argv[2]<<endl;
		encodeTrajectories(trajectories_file,dictionary,encoded_trajectories_file, time_interval);
		trajectories_file.close();
		encoded_trajectories_file.close();
	}
	else{
		printf("ERROR: input trajectories file not found. Stopping the process.\n");
		printUsage();
		exit(EXIT_FAILURE);
	}


	return 0;

}
