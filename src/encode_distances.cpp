#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "cppUtils.h"
#include "stop_encoding.h"

#define SEPARATOR ";"

using namespace std;

void printUsage(){

	printf("\nUSAGE:\n ./encode_distances path/stop_names_and_codes_file.txt path/distances_file.txt path/encoded_distances_file.txt\n");

}

void encodeDistances(ifstream &trajectories_file, map<string,int> &dictionary, ofstream &encoded_distances_file){

	string line, encoded_line;
	size_t first_stop_end_pos, second_stop_end_pos;
	string first_stop_str, second_stop_str, dist_str;
	int first_stop_int,second_stop_int;
	int cont_dist;
	
	bool first_line=true;
	
	printf("\nEncoding distances... \n");
	cont_dist=0;

	while(getline(trajectories_file,line)){
		
		encoded_line="";
		if(first_line)
			first_line=false;
		else
			encoded_line+="\n";


	
		first_stop_end_pos=line.find(';',0);
		//if(first_stop_end_pos==string::npos)
		//	break;    	
		second_stop_end_pos=line.find(';',first_stop_end_pos+1);
    	


		first_stop_str = line.substr(0,(first_stop_end_pos - 0));
		second_stop_str = line.substr(first_stop_end_pos+1,(second_stop_end_pos - (first_stop_end_pos+1)));
		dist_str = line.substr(second_stop_end_pos+1);

		//cout<<first_stop_str<<" "<<second_stop_str<<endl;

		

		// buscar el codigo de first_stop_str en el mapa y reemplazalo
		
		//string tmp=checkStopName(first_stop_str); //UNNECESARY: it has been done directly in the dataset
		//it=dictionary.find(tmp);

		first_stop_int=getStopId(first_stop_str,dictionary);
		second_stop_int=getStopId(second_stop_str,dictionary);

		
		if(first_stop_int < 1 || second_stop_int < 1){ //stop ids start from 1
			printf("ERROR: stop '%s or %s' not found in dictionary. Stopping the process.\n",first_stop_str.c_str(),second_stop_str.c_str());
			exit(EXIT_FAILURE);
		}
		if(first_stop_int==second_stop_int){
			printf("Stop repetido: %d (%s), dist %s\n",first_stop_int,first_stop_str.c_str(),dist_str.c_str());
			continue;
		}

		encoded_line+= to_string(first_stop_int);
		encoded_line+= " ";
		encoded_line+= to_string(second_stop_int);
		encoded_line+= " ";
		encoded_line+= dist_str;


		//encoded_line+="\n";
		//cout<<encoded_line<<endl;
		encoded_distances_file<<encoded_line;
		cont_dist++;
	} // end of while that iterates over the file

	printf("\tDONE.\n %d distances encoded.\n",cont_dist);

}

int main(int argc, char* argv[]){

	int id_count;

	map<string,int> dictionary;
	

/*---------------------------------------------------*/
/* Dictionary creation */

	ifstream stops_names_and_codes;
	if (argc == 4){
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
/*	Encode distance data to ints */

	ifstream distances_file(argv[2]);
	ofstream encoded_distances_file(argv[3]);

	if (distances_file){
		//cout<<"Trying to read file: "<<argv[2]<<endl;
		encodeDistances(distances_file,dictionary,encoded_distances_file);
		distances_file.close();
		encoded_distances_file.close();
	}
	else{
		printf("ERROR: input distances file not found. Stopping the process.\n");
		printUsage();
		exit(EXIT_FAILURE);
	}


	return 0;

}
