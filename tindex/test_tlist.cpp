#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <chrono> // for timing
#include "btree_set.h"
#include "btree_map.h"
#include "cppUtils.h"
#include "tlist.hpp"
#include "tlistreader.hpp"
#include "tindex.hpp"

#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/mapping_paraderos/trayectorias_codificadas_ordenadas.txt"
//define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/trayectorias_muestra.txt"
//#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/modif_trayectorias_muestra.txt"

#define OUT_FOLDER "single_query_data"

using namespace std;

TListReader* readData(ifstream &infile){
	TListReader *t = new TListReader();

	string str_trayectoria;
	size_t parada_fin, tiempo_fin;
	uint parada,tiempo;
	uint cont_trayectorias;
	uint maxtime=0;

	btree_set<uint> stops;
    
    if(infile){
		cout<<"Creating ordered list of trajectories"<<endl;
		cont_trayectorias=0;
    	while(getline(infile,str_trayectoria)){
    		//cout<<str_trayectoria<<endl;
    		size_t inicio_punto=0;
    		while(true){
    			parada_fin=str_trayectoria.find(' ',inicio_punto);
    			//cout<<parada_fin<<endl;  	
				tiempo_fin=str_trayectoria.find(' ',parada_fin+1);
				  

				parada = stoi(str_trayectoria.substr(inicio_punto,(parada_fin - inicio_punto)));
	    		tiempo = stoi(str_trayectoria.substr(parada_fin+1,(tiempo_fin - (parada_fin+1))));

		    	inicio_punto=tiempo_fin+1;

		    	t->addPoint(cont_trayectorias,parada,tiempo);
		    	stops.insert(parada);
		    	if(tiempo>maxtime) maxtime=tiempo;

		    	//lista_trayectorias[cont_trayectorias].push_back(make_pair(parada,tiempo));

		    	/* AGREGAR AL ÍNDICE */

		    	//indice[parada][tiempo].insert(cont_trayectorias);

		    	/* FIN AGREGAR AL ÍNDICE */

		    	if(tiempo_fin==string::npos)
					break;

    		} /* fin iteracion sobre una misma trayectoria */
            //cout<<"tam lista: "<<lista_trayectorias.size()<<endl;
			cont_trayectorias++;

    	}
    }
    else
    	exit(EXIT_FAILURE);

    t->setTrips(cont_trayectorias);
    t->setStops(stops.size());
    t->setMaxtime(maxtime);

    return t;

}

int main(){

	TListReader *tdr;
	TList td;
	TIndex *new_tindex;
	TIndex tindex;

	ifstream infile;

	/* leer las trayectorias del archivo */
	infile.open(IF_TRAYECTORIAS);

	tdr=readData(infile);

    infile.close();

    //tdr->print();
	//printIndex(indice);

    td.create(*tdr);

    //td.print();

    ofstream f;
	f.open("test_tlist.b", ios::binary);
	td.save(f);
	f.close();

	/*ifstream if2;

	if2.open("test_tlist.b",ios::binary);
	TList *new_t;

	new_t=TList::load(if2);
	infile.close();

	new_t->print(0);

	//new_t->print(new_t->trips-1);
	
	*/
	

	tindex.create(td);

	tindex.printIdList(2,100);


	f.open("test_tindex.b",ios::binary);

	tindex.save(f);
	f.close();

	f.open("test_listindex.b",ios::binary | ios::app);
	td.save(f);
	tindex.save(f);
	f.close();

	f.open("test_tlist_do.b", ios::binary);
	td.saveDataOnly(f);
	f.close();



	f.open("test_tindex_do.b",ios::binary);

	tindex.saveDataOnly(f);
	f.close();

	f.open("test_listindex_do.b",ios::binary | ios::app);
	td.saveDataOnly(f);
	tindex.saveDataOnly(f);
	f.close();

	//------------------------
	ifstream if2;
	cout<<"Loading index..."<<endl;
	if2.open("test_tindex.b",ios::binary);
	


	new_tindex=TIndex::load(if2);
	if2.close();

	new_tindex->printIdList(2,100);

	//new_t->print(new_t->trips-1);



	cout<<"FIN!!"<<endl;


	return 0;
}