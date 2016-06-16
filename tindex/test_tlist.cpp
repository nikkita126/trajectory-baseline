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

//#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/mapping_paraderos/trayectorias_codificadas_ordenadas.txt"
//define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/trayectorias_muestra.txt"
#define IF_TRAYECTORIAS "/home/cathy/Magister/Tesis/baseline/modif_trayectorias_muestra.txt"

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

	auto t1 = std::chrono::high_resolution_clock::now();
	/* leer las trayectorias del archivo */
	infile.open(IF_TRAYECTORIAS);

	tdr=readData(infile);

    infile.close();
    auto t2 = std::chrono::high_resolution_clock::now();
    //tdr->print();
	//printIndex(indice);
	auto t3 = std::chrono::high_resolution_clock::now();
    td.create(*tdr);
	auto t4 = std::chrono::high_resolution_clock::now();
    //td.print();
	auto t5 = std::chrono::high_resolution_clock::now();
    ofstream f;
	f.open("test_tlist.b", ios::binary);
	td.save(f);
	f.close();
	auto t6 = std::chrono::high_resolution_clock::now();
		
	auto t7 = std::chrono::high_resolution_clock::now();
	tindex.create(td);
	auto t8 = std::chrono::high_resolution_clock::now();

	auto t9 = std::chrono::high_resolution_clock::now();
	tindex.printIdList(2,100);
	auto t10 = std::chrono::high_resolution_clock::now();


	auto t11 = std::chrono::high_resolution_clock::now();
	f.open("test_tindex.b",ios::binary);

	tindex.save(f);
	f.close();
	auto t12 = std::chrono::high_resolution_clock::now();

	auto t13 = std::chrono::high_resolution_clock::now();	
	f.open("test_listindex.b",ios::binary | ios::app);
	td.save(f);
	tindex.save(f);
	f.close();
	auto t14 = std::chrono::high_resolution_clock::now();

	auto t15 = std::chrono::high_resolution_clock::now();	
	f.open("test_tlist_do.b", ios::binary);
	td.saveDataOnly(f);
	f.close();
	auto t16 = std::chrono::high_resolution_clock::now();

	auto t17 = std::chrono::high_resolution_clock::now();
	f.open("test_tindex_do.b",ios::binary);

	tindex.saveDataOnly(f);
	f.close();
	auto t18 = std::chrono::high_resolution_clock::now();


	auto t19 = std::chrono::high_resolution_clock::now();	
	f.open("test_listindex_do.b",ios::binary | ios::app);
	td.saveDataOnly(f);
	tindex.saveDataOnly(f);
	f.close();
	auto t20 = std::chrono::high_resolution_clock::now();

	auto t21 = std::chrono::high_resolution_clock::now();
	ifstream if2;

	if2.open("test_tlist.b",ios::binary);
	TList *new_t;

	new_t=TList::load(if2);
	infile.close();
	auto t22 = std::chrono::high_resolution_clock::now();

	auto t23 = std::chrono::high_resolution_clock::now();
	new_t->print(0);
	auto t24 = std::chrono::high_resolution_clock::now();



	//------------------------
	

	ifstream if2;
	cout<<"Loading index..."<<endl;
	if2.open("test_tindex.b",ios::binary);
	


	new_tindex=TIndex::load(if2);
	if2.close();

	new_tindex->printIdList(2,100);

	new_t->print(new_t->trips-1);

	

	//-----------------------
	// TIMING

	// fractional duration: no duration_cast needed
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;    
 
 	cout<<"\n\n";
    cout << "TListReader creation: " << fp_ms.count() << " ms\n";

    fp_ms = t4 - t3;    
    cout << "TList creation: " << fp_ms.count() << " ms\n";

    fp_ms = t6 - t5;    
    cout << "TList saving: " << fp_ms.count() << " ms\n";

    fp_ms = t8 - t7;    
    cout << "TIndex creation: " << fp_ms.count() << " ms\n";

    fp_ms = t10 - t9;    
    cout << "TIndex traj id list printing: " << fp_ms.count() << " ms\n";

    fp_ms = t12 - t11;    
    cout << "TIndex saving: " << fp_ms.count() << " ms\n";

    fp_ms = t14 - t13;    
    cout << "TList + TIndex saving: " << fp_ms.count() << " ms\n";

    fp_ms = t16 - t15;    
    cout << "TList save data only: " << fp_ms.count() << " ms\n";

    fp_ms = t18 - t17;    
    cout << "TIndex save data only: " << fp_ms.count() << " ms\n";

    fp_ms = t20 - t19;    
    cout << "TList + TIndex save data only: " << fp_ms.count() << " ms\n";

    fp_ms = t22 - t21;    
    cout << "TList loading: " << fp_ms.count() << " ms\n";

    fp_ms = t24 - t23;    
    cout << "TList traj printing: " << fp_ms.count() << " ms\n";
	

	cout<<"FIN!!"<<endl;

	return 0;
}