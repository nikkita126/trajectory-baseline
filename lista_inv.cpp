#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "btree_set.h"
#include "btree_map.h"
#include "cppUtils.h"

#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/mapping_paraderos/trayectorias_codificadas_ordenadas.txt"
//#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/trayectorias_muestra.txt"

#define N_TRAYECTORIAS 100
#define N_NODOS 100
#define DELTA_T 1 /* ventana de espera, en intervalos */
#define INF 99999999
#define OUT_FOLDER "single_query_data"

using namespace btree;
using namespace std;

typedef struct columnas_tabla{

	uint suma;
	uint cant;
	uint min;
	uint max;

} columnas_tabla;


int main(){
	/* 
	vector< vector<pair<int,int> > > lista_trayectorias(N_TRAYECTORIAS);
	vector< vector<pair<int,int> > >::iterator it_trayectorias;
	*/
	btree_map<uint,vector<pair<uint,uint> > > lista_trayectorias;


	/*
	vector< vector<pair<int, vector<int> > > > indice(N_NODOS);
	vector< vector<pair<int, vector<int> > > >::iterator it_indice;
	*/

	btree_map<uint,btree_map<uint,btree_set<uint> > > indice;


	ifstream archivo_trayectorias;

	/* leer las trayectorias del archivo */
	archivo_trayectorias.open(IF_TRAYECTORIAS);

	string str_trayectoria;
	size_t parada_fin, tiempo_fin;
	int parada,tiempo;
	int cont_trayectorias;
    
    if(archivo_trayectorias){
		cout<<"Generando diccionario de trayectorias e índice"<<endl;
		cont_trayectorias=0;
    	while(getline(archivo_trayectorias,str_trayectoria)){
    		//cout<<str_trayectoria<<endl;
    		size_t inicio_punto=0;
    		while(true){
    			parada_fin=str_trayectoria.find(' ',inicio_punto);
    			//cout<<parada_fin<<endl;  	
				tiempo_fin=str_trayectoria.find(' ',parada_fin+1);
				  

				parada = stoi(str_trayectoria.substr(inicio_punto,(parada_fin - inicio_punto)));
	    		tiempo = stoi(str_trayectoria.substr(parada_fin+1,(tiempo_fin - (parada_fin+1))));

		    	inicio_punto=tiempo_fin+1;

		    	lista_trayectorias[cont_trayectorias].push_back(make_pair(parada,tiempo));

		    	/* AGREGAR AL ÍNDICE */

		    	indice[parada][tiempo].insert(cont_trayectorias);

		    	/* FIN AGREGAR AL ÍNDICE */

		    	if(tiempo_fin==string::npos)
					break;

    		} /* fin iteracion sobre una misma trayectoria */

			cont_trayectorias++;

    	}
    }
    else
    	exit(EXIT_FAILURE);

    archivo_trayectorias.close();

    /* RECORRER E IMPRIMIR TRAYECTORIAS */
   /* 
    cout<<"Lista de trayectorias generadas"<<endl;

    for(auto i=0;i<=cont_trayectorias;i++){
    	auto tam_trayectoria = lista_trayectorias[i].size();

    	for(auto j=0;j<tam_trayectoria;j++){
    		if(j) cout<<" ";
    		cout<<"("<<lista_trayectorias[i][j].first<<","<<lista_trayectorias[i][j].second<<")";
    	}
    	cout<<endl;
    }
	

	/* RECORRER E IMPRIMIR INDICE */
	/*int tam_ids,max_ids=0;
	int tam_tiempos,max_tiempos=0;

    for(auto i=indice.begin();i!=indice.end();i++){

    	cout<<"***** "<<i->first<<": *****"<<endl;

    	tam_tiempos=i->second.size();
    	if(tam_tiempos>max_tiempos) max_tiempos = tam_tiempos;

    	for(auto j=i->second.begin();j!=i->second.end();j++){
    		cout<<i->first<<"    "<<j->first<<":";
    		tam_ids=j->second.size();

    		if(tam_ids>max_ids) max_ids=tam_ids;

    		for(auto k=j->second.begin();k!=j->second.end();k++){
    			cout<<" "<<*k;
    		}
    		cout<<endl;

    	}
    }

    cout<<"# en lista mas larga de tiempos: "<<max_tiempos<<endl;
    cout<<"# en lista mas larga de ids: "<<max_ids<<endl;

*/
/*
    cout<<lista_trayectorias<<endl;
    cout<<"--------------"<<endl;
    cout<<indice<<endl;
    */

bool consultas = true;

if(consultas){


/* CONSULTAS DE TRAYECTORIAS EFECTIVAMENTE REALIZADAS PARA ACCESIBILIDAD */



    uint n_in, t_in, t_interval;

    vector<pair<int,int> > cola_puntos;

    btree_map<uint, columnas_tabla > tabla_resultados; /* columnas_tabla tienen 0's? */
  


 	while(true){

    	cout<<"CONSULTAS: \nEspecificar nodo inicial, tiempo inicial, radio (en intervalos): ";


    	cin>>n_in>>t_in>>t_interval;

    	cout<<"\n\t* Procesando: "<<n_in<<" "<<t_in<<" "<<t_interval<<endl;

    	if(!n_in && !t_in && !t_interval) break; /* el while cierra con input 0 0 0  */

    	if(n_in > indice.size()){ /* verificar que el paradero esté dentro de la lista */

    		cout<<"Paradero inexistente"<<endl;
    		continue;
    	}

    	cola_puntos.clear();
    	tabla_resultados.clear();

    	/* punto de inicio */

    	auto l_b = indice[n_in].lower_bound(t_in);

        cout<<"lb: "<<l_b->first<<endl;

    	//if(l_b->first >= t_fin){
    	if(l_b->first > (t_in + DELTA_T)){
    			//tiempo fuera de rango
    			cout<<"fuera de rango"<<endl;
    			continue;
    	}

    	auto starting_id = l_b->second.begin();

    	uint i = *starting_id;
    	uint tam_lista = lista_trayectorias.size();

        cout<<"____"<<tam_lista<<endl;
        cout<<"----"<<i<<" ---- "<<lista_trayectorias[i].begin()->first<<" ---- "<<lista_trayectorias[i].begin()->second<<endl;

    	// comienza en cualquier tiempo dentro del rango
    	//while(i<tam_lista && lista_trayectorias[i].begin()->first==n_in && lista_trayectorias[i].begin()->second < t_fin){
        int cont_destinos=0;

    	//comienza en el tiempo inicial dado o a lo más en una ventana posible, dado el tiempo de espera promedio
    	while(i<tam_lista && lista_trayectorias[i].begin()->first==n_in && lista_trayectorias[i].begin()->second <= t_in + DELTA_T){ // NO FUNCIONA
    	// recorrer lista de trayectorias hasta estar fuera de rango de tiempo
    		cout<<i<<endl;
    		uint tiempo_inicial_viaje=lista_trayectorias[i].begin()->second;

    		for(auto j=lista_trayectorias[i].begin();j!=lista_trayectorias[i].end();j+=2){
    			cout<<j->first<<" "<<j->second<<endl;
    			auto destino=j+1;
    			if(destino->second >= tiempo_inicial_viaje+t_interval)
    				break;

    			//si esta en rango, agregar a la tabla

    			auto it = tabla_resultados.find(destino->first);

				if (it == tabla_resultados.end()){
					tabla_resultados[destino->first].suma=0;
					tabla_resultados[destino->first].cant=0;
					tabla_resultados[destino->first].min=INF;
					tabla_resultados[destino->first].max=0;
				}

				uint tiempo_viaje=destino->second - tiempo_inicial_viaje;
    			tabla_resultados[destino->first].suma+=tiempo_viaje;
    			tabla_resultados[destino->first].cant++;

    			if(tiempo_viaje < tabla_resultados[destino->first].min)
    				tabla_resultados[destino->first].min = tiempo_viaje;

    			if(tiempo_viaje > tabla_resultados[destino->first].max)
    				tabla_resultados[destino->first].max = tiempo_viaje;
                cont_destinos++;



    		}


    		i++;


    	}

        cout<<"------"<<cont_destinos<<endl;

    	//cout<<n_in<<"\t"<<t_in<<"\t"<<t_fin<<endl;
    	//cout<<"NODO\tSUMA\tCANT\tMIN\tMAX"<<endl;

    	ofstream archivo_tabla;
    	string nombre_archivo=to_string(n_in)+"_"+to_string(t_in)+"_"+to_string(t_interval)+".csv";
    	archivo_tabla.open(nombre_archivo);


    	if(archivo_tabla){
    		for(auto it=tabla_resultados.begin();it!=tabla_resultados.end();it++){
    			/* origen,destino,[tiempoInicial,tiempoFinal),suma,contadorTray,tiempomin,tiempomax */
    			archivo_tabla<<n_in<<"\t"<<it->first<<"\t"<<t_in<<"\t"<<t_in+t_interval<<"\t"<<it->second.suma<<"\t"<<it->second.cant<<"\t"<<it->second.min<<"\t"<<it->second.max<<endl;

    		}
    	}
    	else
    		exit(EXIT_FAILURE);

    	archivo_tabla.close();
    

    }
}


bool guardar=false;

if(guardar){
/* GUARDAR Y CARGAR */

    ofstream out;

    out.open("diccionario.b",ios::binary);

    //cds_utils::saveValue<btree_map<uint,vector<pair<uint,uint> > > >(out,&lista_trayectorias,1);
    cds_utils::saveValue<int>(out,&cont_trayectorias,1);

    for(uint i=0;i<=cont_trayectorias;i++){
        int tam_trayectoria = lista_trayectorias[i].size();
        cds_utils::saveValue<int>(out,&tam_trayectoria,1);
       // cds_utils::saveValue<pair<uint,uint> >(out,&lista_trayectorias[i],tam_trayectoria);
    }

    out.close();
}

bool cargar=false;

if(cargar){


    btree_map<uint,vector<pair<uint,uint> > >  nueva_lista;

    ifstream in;
    in.open("diccionario.b");

    //nueva_lista=cds_utils::loadValue<btree_map<uint,vector<pair<uint,uint> > > >(in,1);
    int *nuevas_tray=cds_utils::loadValue<int>(in,1);

    for(uint i=0;i<=*nuevas_tray;i++){
        uint *nuevo_tam = cds_utils::loadValue<uint>(in,1);
       // nueva_lista[i]=cds_utils::loadValue<pair<uint,uint> >(in,*nuevo_tam);
    }

    //cout<<nueva_lista<<endl;

    in.close();
    cout<<"FIN!"<<endl;
}

	return 0;
}