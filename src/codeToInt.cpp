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

#define TIME_INTERVAL 5 // minutes in the discrete time interval
#define STARTING_DATE_DAY 14
#define SEPARATOR ";"

using namespace std;

void printUsage(){

	printf("\nUSAGE:\n ./codeToInt path/stop_names_and_codes_file.txt path/trajectories_file.txt path/encoded_trajectories_file.txt\n");

}

string chequear_parada(string nombre_parada){ //not necessary anymore

	string nuevo_nombre;


	if(nombre_parada=="BAQUEDANO L1")
		nuevo_nombre="BAQUEDANO";
	else if(nombre_parada=="BAQUEDANO L5")
		nuevo_nombre="BAQUEDANO";
	else if(nombre_parada=="BARRANCAS - L5")
		nuevo_nombre="BARRANCAS";
	else if(nombre_parada=="LA FLORIDA")
		nuevo_nombre="BELLAVISTA DE LA FLORIDA";
	else if(nombre_parada=="BLANQUEADO - L5")
		nuevo_nombre="BLANQUEADO";
	else if(nombre_parada=="AGRICOLA")
		nuevo_nombre="CAMINO AGRICOLA";
	else if(nombre_parada=="CARLOS VALDOVINO")
		nuevo_nombre="CARLOS VALDOVINOS";
	else if(nombre_parada=="CIUDAD DEL NI?O")
		nuevo_nombre="CIUDAD DEL NINO";
	else if(nombre_parada=="COLON")
		nuevo_nombre="CRISTOBAL COLON";
	else if(nombre_parada=="RICARDO CUMMING")
		nuevo_nombre="CUMMING";
	else if(nombre_parada=="DEL SOL - L5")
		nuevo_nombre="DEL SOL";
	else if(nombre_parada=="LA CISTERNA L4A")
		nuevo_nombre="LA CISTERNA";
	else if(nombre_parada=="BILBAO")
		nuevo_nombre="FRANCISCO BILBAO";
	else if(nombre_parada=="ROTONDA GRECIA")
		nuevo_nombre="GRECIA";
	else if(nombre_parada=="GRUTA DE LOURDES - L5")
		nuevo_nombre="GRUTA DE LOURDES";
	else if(nombre_parada=="HERNANDO DE MAGALLANES - L1")
		nuevo_nombre="HERNANDO DE MAGALLANES";
	else if(nombre_parada=="LAGUNA SUR - L5")
		nuevo_nombre="LAGUNA SUR";
	else if(nombre_parada=="LAS PARCELAS - L5")
		nuevo_nombre="LAS PARCELAS";
	else if(nombre_parada=="LA CISTERNA L2")
		nuevo_nombre="LA CISTERNA";
	else if(nombre_parada=="LOS DOMINICOS - L1")
		nuevo_nombre="LOS DOMINICOS";
	else if(nombre_parada=="LO PRADO - L5")
		nuevo_nombre="LO PRADO";
	else if(nombre_parada=="MANQUEHUE - L1")
		nuevo_nombre="MANQUEHUE";
	else if(nombre_parada=="MIRADOR AZUL")
		nuevo_nombre="MIRADOR";
	else if(nombre_parada=="MONTE TABOR - L5")
		nuevo_nombre="MONTE TABOR";
	else if(nombre_parada=="?UBLE")
		nuevo_nombre="NUBLE";
	else if(nombre_parada=="ROTONDA QUILIN")
		nuevo_nombre="QUILIN";
	else if(nombre_parada=="PEDREROS")
		nuevo_nombre="PEDRERO";
	else if(nombre_parada=="PLAZA EGA?A")
		nuevo_nombre="PLAZA EGANA";
	else if(nombre_parada=="PLAZA MAIPU - L5")
		nuevo_nombre="PLAZA MAIPU";
	else if(nombre_parada=="PUDAHUEL - L5")
		nuevo_nombre="PUDAHUEL";
	else if(nombre_parada=="SANTA ANA L2")
		nuevo_nombre="SANTA ANA";
	else if(nombre_parada=="SANTA ANA L5")
		nuevo_nombre="SANTA ANA";
	else if(nombre_parada=="SANTIAGO BUERAS - L5")
		nuevo_nombre="SANTIAGO BUERAS";
	else if(nombre_parada=="SAN JOSE DE LA ESTRELLA - L4")
		nuevo_nombre="SAN JOSE DE LA ESTRELLA";
	else if(nombre_parada=="SAN PABLO L1")
		nuevo_nombre="SAN PABLO";
	else if(nombre_parada=="SAN PABLO - L5")
		nuevo_nombre="SAN PABLO";
	else if(nombre_parada=="SAN PABLO L5")
		nuevo_nombre="SAN PABLO";
	else if(nombre_parada=="TOBALABA_L1")
		nuevo_nombre="TOBALABA";
	else if(nombre_parada=="TOBALABA_L4")
		nuevo_nombre="TOBALABA";
	else if(nombre_parada=="TOBALABA L1")
		nuevo_nombre="TOBALABA";
	else if(nombre_parada=="TOBALABA L4")
		nuevo_nombre="TOBALABA";
	else if(nombre_parada=="LATINO AMERICANA")
		nuevo_nombre="UNION LATINO AMERICANA";
	else if(nombre_parada=="VICU?A MACKENA")
		nuevo_nombre="VICUNA MACKENNA";
	else if(nombre_parada=="LOS HEROES L1")
		nuevo_nombre="LOS HEROES";
	else if(nombre_parada=="LOS HEROES L2")
		nuevo_nombre="LOS HEROES";
	else
		nuevo_nombre=nombre_parada;


	return nuevo_nombre;
}

void readDictionary(map<string,int> &dictionary, ifstream &file){

	map<string,int>::iterator it;
	size_t pos;
    string line,name,code_str;
    int code;

    if(file){
		printf("\nReading stops names and int codes dictionary...\n");
    	while(getline(file,line)){

    		pos=line.find(SEPARATOR);

    		name=line.substr(0,pos); 
    		code_str=line.substr(pos+1);
    		code=stoi(code_str);
		
			//cout<<name<<" "<<code<<endl;

			dictionary.insert(make_pair(name,code));
    	}
    	printf("\tDONE\n");
    }
    else
    	exit(EXIT_FAILURE);

}

void encodeTrajectories(ifstream &trajectories_file, map<string,int> &dictionary, ofstream &encoded_trajectories_file){

	string line, encoded_line;
	size_t stop_end_pos, time_end_pos;
	string stop_str, time_str;
	int day,hour,min,interval;
	int stop_int;
	int cont_points,cont_traj;
	int intervals_per_day = (60*24)/TIME_INTERVAL;
	map<string,int>::iterator it;
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

    		// parse time_str to create discrete time points
				// string time_str format:
				//	YYYY-MM-DD hh:mm:ss

	    	//printf("%s %s\n",stop_str.c_str(),time_str.c_str());

    		day=stoi(time_str.substr(8,2));
    		hour=stoi(time_str.substr(11,2));
    		min=stoi(time_str.substr(14,2));

    		interval=(day - STARTING_DATE_DAY)*intervals_per_day + (hour*60 + min)/TIME_INTERVAL;

    		// buscar el codigo de stop_str en el mapa y reemplazalo
			
			//string tmp=chequear_parada(stop_str); //UNNECESARY: it has been done directly in the dataset
    		//it=dictionary.find(tmp);

    		it=dictionary.find(stop_str);
			
			if(it!=dictionary.end()){
				stop_int = it->second;
			}
			else{
				printf("ERROR: stop '%s' not found in dictionary. Stopping the process.\n",stop_str.c_str());
				exit(EXIT_FAILURE);
			}


			if(cont_points)
				encoded_line+=" ";
			else
				cont_points++;

			encoded_line+= to_string(stop_int);
			encoded_line+= " ";
			encoded_line+= to_string(interval);

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
	if (argc == 4){
		stops_names_and_codes.open(argv[1]);

		if(!stops_names_and_codes){
	        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[1]);
	        exit(EXIT_FAILURE);
    	}

		readDictionary(dictionary,stops_names_and_codes);
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

	if (trajectories_file){
		//cout<<"Trying to read file: "<<argv[2]<<endl;
		encodeTrajectories(trajectories_file,dictionary,encoded_trajectories_file);
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
