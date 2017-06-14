#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "stop_encoding.h"

#define STARTING_DATE_DAY 14
#define SEPARATOR ";"

using namespace std;

typedef vector<uint> vu;
typedef pair<uint,int> ui;
typedef vector<ui> vui;

vector<vui> distance_graph(11285);

bool cmp(const ui &l,const ui &r)
{

    return l.first<r.first;
}

int getDistance(uint i,uint j){

	auto l_b=lower_bound(distance_graph[i].begin(),distance_graph[i].end(),ui(j,0),cmp);

	if(l_b->first != j){
		//printf("l_b first: %u\n",l_b->first);
		
		return -1;
	}

	return l_b->second;

}


int main(int argc, char* argv[]){

	int id_count;

	map<string,int> dictionary; // dict (code,int id)


	

/*---------------------------------------------------*/
/* Dictionary creation */

	ifstream stops_names_and_codes;

	stops_names_and_codes.open(argv[1]);

	if(!stops_names_and_codes){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[1]);
        exit(EXIT_FAILURE);
	}

	string separator (SEPARATOR);
	createDictionary(dictionary,stops_names_and_codes,separator);
	stops_names_and_codes.close();

/*-------------------------*/
	/* Leer distancias*/

	ifstream distances_file;
	string line;
	int cant_dist;
	string cant_str,s_i_str,s_e_str,recorrido,distroute_str,disteuclid_str;
	int s_i,s_e;
	int distroute,disteuclid;
	size_t start_pos,end_pos;

	distances_file.open(argv[2]);

	if(!distances_file){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[1]);
        exit(EXIT_FAILURE);
	}

	int curr_origin=0,curr_dest=0;
	int dist_moda=0,cant_etapas;
	int pares_distintos=0;

	while(getline(distances_file,line)){


		/* ---------  LEER PARÁMETROS --------- */

		start_pos=0;
		end_pos=line.find(' ',start_pos);
		if(end_pos==string::npos){
			break;
		}

		cant_dist=stoi(line.substr(start_pos,(end_pos-start_pos)));

		//-----
		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		s_i_str=line.substr(start_pos,(end_pos-start_pos));

		s_i=getStopId(s_i_str,dictionary);

		//------

		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		s_e_str=line.substr(start_pos,(end_pos-start_pos));

		s_e=getStopId(s_e_str,dictionary);

		//------

		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);

		if(start_pos == end_pos)
			recorrido="NULL";
		else {
		recorrido=line.substr(start_pos,(end_pos-start_pos));
		}

		//------

		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		distroute=stoi(line.substr(start_pos,(end_pos-start_pos)));

		//------

		start_pos=end_pos+1;
		end_pos=line.find('\n',start_pos);
		disteuclid=stoi(line.substr(start_pos,(end_pos-start_pos)));



		//cout<<"LEÍ: "<<to_string(cant_dist)<<" "<<s_i<<" "<<s_e<<" "<<recorrido<<" "<<to_string(distroute)<<" "<<to_string(disteuclid)<<endl;

		if(s_i!=curr_origin){
			
			if(curr_origin){

				distance_graph[curr_origin].push_back(ui(curr_dest,dist_moda));
				//cout<<">> PUSH 1: "<<curr_origin<<" "<<curr_dest<<" "<<dist_moda<<endl;

			}

			sort(distance_graph[curr_origin].begin(),distance_graph[curr_origin].end(),cmp);

			dist_moda=0;
			cant_etapas=0;

			curr_origin=s_i;
			curr_dest=s_e;


		}


		else {

			if(s_e!=curr_dest){

				// ESTO NO ESTÁ RESULTANDO!!!

				distance_graph[curr_origin].push_back(ui(curr_dest,dist_moda));
				//cout<<">> PUSH 2: "<<curr_origin<<" "<<curr_dest<<" "<<dist_moda<<endl;

				curr_dest=s_e;

				dist_moda=0;
				cant_etapas=0;
				pares_distintos++;


			}

		}


		// CASO NORMAL
		if(cant_dist>cant_etapas){

			//cout<<"Cant dist: "<<cant_dist<<" Cant etapas: "<<cant_etapas<<endl;

			cant_etapas=cant_dist;
			dist_moda=distroute;
		}
		else if(cant_dist==cant_etapas){

			if(distroute>dist_moda)
				dist_moda=distroute;
		}


	} // fin lectura archivo distances_file

	distances_file.close();

	/* PUSH del último par */
	distance_graph[curr_origin].push_back(ui(curr_dest,dist_moda));
	sort(distance_graph[curr_origin].begin(),distance_graph[curr_origin].end(),cmp);
	/* --------------------- */


	/*
	int tam_g=distance_graph.size();

	cout<<"Tam de grafo: "<<tam_g<<endl;

	for(int i=0;i<tam_g;i++){

		int tam_lista=distance_graph[i].size();

		if(tam_lista){

			for(auto it=distance_graph[i].begin();it!=distance_graph[i].end();it++){

				cout<<i<<" -> "<<it->first<<": "<<it->second<<" , ";

			}
			cout<<endl;






		}

	} */



	/* REVISAR QUÉ PARES DE STOPS EN EL DATASET DE TRAYECTORIAS NO TIENEN DISTANCIAS VÁLIDAS */

	ifstream trajectories_file;

	trajectories_file.open(argv[3]);

	if(!trajectories_file){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    size_t s_i_end_pos,s_e_end_pos,time_end_pos;
    int dist_par;
    int cont_traj=0;
    int total_pares=0,no_encontrados=0;

    while(getline(trajectories_file,line)){

    	size_t point_start_pos=0;
    		while(true){
    			s_i_end_pos=line.find(' ',point_start_pos);
    			//cout<<stop_end_pos<<endl;  	
				time_end_pos=line.find(' ',s_i_end_pos+1);
				  

				s_i = stoi(line.substr(point_start_pos,(s_i_end_pos - point_start_pos)));

		    	point_start_pos=time_end_pos+1;
		    	s_e_end_pos=line.find(' ',point_start_pos);
    			//cout<<stop_end_pos<<endl;  	
				time_end_pos=line.find(' ',s_e_end_pos+1);

				s_e = stoi(line.substr(point_start_pos,(s_e_end_pos - point_start_pos)));

				point_start_pos=time_end_pos+1;
				dist_par = getDistance(s_i,s_e);

				if(dist_par==-1){

					//cout<<"DISTANCE NOT FOUND: "<<s_i<<" "<<s_e<<" (traj "<<cont_traj<<")"<<endl;
					cout<<"NO ENCONTRADOS: "<<no_encontrados++<<" (traj: "<<cont_traj<<")"<<endl;
				}


				total_pares++;
		    	if(time_end_pos==string::npos)
					break;

    		} /* end of iteration over the same trip */
            //cout<<"tam lista: "<<lista_trayectorias.size()<<endl;
			cout<<"TOTAL TRAYS: "<<cont_traj++<<endl;

    }

	trajectories_file.close();

	cout<<endl<<endl<<"RESUMEN:"<<endl<<"pares distintos: "<<pares_distintos<<endl<<"total pares: "<<total_pares<<endl<<"no encontrados: "<<no_encontrados<<endl;

	return 0;
}

