#include "tindex.h"

using namespace std;

typedef struct table_columns{

    uint suma;
    uint cant;
    uint min;
    uint max;

} table_columns;

void printUsage(){

	printf("\nUSAGE:\n ./useIndex dataset_name path/index/folder < path/query/file");

}



int main(int argc, char *argv[]){


	string dataset, dataset_filename, index_folder;
	string tlist_filename, tindex_filename, query_filename;
	TList *tl;
	TIndex *ti;
	ifstream infile;
	ofstream outfile;
	string list_out_filename="", index_out_filename="";

	if (argc!=4){
		printUsage();
		exit(EXIT_FAILURE);
	}

	dataset=argv[1];
	index_folder=argv[2];
	dataset_filename=getFilename(dataset);
	query_filename=getFilename(argv[3]);

	tlist_filename=index_folder+"/"+dataset_filename+".tlist";
	tindex_filename=index_folder+"/"+dataset_filename+".tindex";

	//printf("tlist_filename: %s tindex_filename: %s\n",tlist_filename.c_str(),tindex_filename.c_str());


	//-----------------------
	// Load tlist from file
	printf("\n Loading tlist from file %s ...",tlist_filename.c_str());
	infile.open(tlist_filename,ios::binary);
	tl=TList::load(infile);
	infile.close();
	printf(" DONE\n");
	

	//------------------------
	// Load tindex from file

	printf("\n Loading tindex from file %s ...",tindex_filename.c_str());
	infile.open(tindex_filename,ios::binary);
	ti=TIndex::load(infile,tl);
	infile.close();
	printf(" DONE\n");


	//------------------------
	// some test to check that the structures loaded correctly
	
	tl->print(0);
	ti->printIdList(2,100);

	tl->print(tl->trips-1);

	ti->printIdList(1,95);





	//------------------------
	// ACCESIBILITY QUERIES
	// (for *real* trajectories)

    uint n_in, t_in, t_interval, origin_only;

    vector<pair<int,int> > points_queue;

    btree_map<uint, QueryResult > results_table; /* table_columns tienen 0's? */
  
    print("Reading and executing queries from query file\n");

    // reads from input file
 	while(EOF != scanf("%u %u %u %u", &n_in,&t_in, &t_interval, &origin_only)){

    	//printf("QUERIES: \nSpecify starting node, starting time, interval ");

    	AccessibilityQuery aq;
    	int err;

    	err = readQuery()

        bool origin_only = true; /* CAMBIAR SI SE QUIERE INCORPORAR EN LA CONSULTA */

    	cin>>n_in>>t_in>>t_interval;

    	cout<<"\n\t* Procesando: "<<n_in<<" "<<t_in<<" "<<t_interval<<endl;

    	if(!n_in && !t_in && !t_interval) break; /* el while cierra con input 0 0 0  */

    	if(n_in > indice.size()){ /* verificar que el paradero esté dentro de la lista */

    		cout<<"Paradero inexistente"<<endl;
    		continue;
    	}

    	points_queue.clear();
    	results_table.clear();
//cout<<"tam lista: "<<lista_trayectorias.size()<<endl;
    	int starting_id = getStartingId(n_in, t_in, origin_only, lista_trayectorias, indice); //NO ES APROPIADO PARA ENCONTRAR TRAYECTORIAS QUE SOLO INICIAN EN (n_in,t_in)
//        cout<<"Starting id: "<<starting_id<<endl;
        //cout<<"tam lista: "<<lista_trayectorias.size()<<endl;
        if(starting_id == -1) continue; /* no se puede realizar la consulta */

    	uint i = starting_id;
    	uint tam_lista = lista_trayectorias.size();

//cout<<"____"<<tam_lista<<endl;
//        cout<<"----"<<i<<" ---- "<<lista_trayectorias[i].begin()->first<<" ---- "<<lista_trayectorias[i].begin()->second<<endl;

    	// comienza en cualquier tiempo dentro del rango

    	//while(i<tam_lista && lista_trayectorias[i].begin()->first==n_in && lista_trayectorias[i].begin()->second < t_fin){
        int cont_destinos=0;

    	//comienza en el tiempo inicial dado o a lo más en una ventana posible, dado el tiempo de espera promedio
    	while(i<tam_lista && lista_trayectorias[i].begin()->first==n_in && lista_trayectorias[i].begin()->second <= t_in + DELTA_T){ // NO FUNCIONA
    	// recorrer lista de trayectorias hasta estar fuera de rango de tiempo
 //   		cout<<"revisando trayectoria: "<<i<<endl;
    		uint tiempo_inicial_viaje=lista_trayectorias[i].begin()->second;

    		for(auto j=lista_trayectorias[i].begin();j!=lista_trayectorias[i].end();j+=2){
//    			cout<<j->first<<" "<<j->second<<endl;
    			auto destino=j+1;
    			if(destino->second >= tiempo_inicial_viaje+t_interval)
    				break;

    			//si esta en rango, agregar a la tabla

    			auto it = results_table.find(destino->first);

				if (it == results_table.end()){
					results_table[destino->first].suma=0;
					results_table[destino->first].cant=0;
					results_table[destino->first].min=INF;
					results_table[destino->first].max=0;
				}

				uint tiempo_viaje=destino->second - tiempo_inicial_viaje;
    			results_table[destino->first].suma+=tiempo_viaje;
    			results_table[destino->first].cant++;

    			if(tiempo_viaje < results_table[destino->first].min)
    				results_table[destino->first].min = tiempo_viaje;

    			if(tiempo_viaje > results_table[destino->first].max)
    				results_table[destino->first].max = tiempo_viaje;
                cont_destinos++;



    		}


    		i++;


    	}

//        cout<<"------"<<cont_destinos<<endl;

    	//cout<<n_in<<"\t"<<t_in<<"\t"<<t_fin<<endl;
    	//cout<<"NODO\tSUMA\tCANT\tMIN\tMAX"<<endl;

    	ofstream archivo_tabla;
        string folder_name=OUT_FOLDER;
    	string nombre_archivo=folder_name+"/"+to_string(n_in)+"_"+to_string(t_in)+"_"+to_string(t_interval)+".csv";
    	archivo_tabla.open(nombre_archivo);


    	if(archivo_tabla){
    		for(auto it=results_table.begin();it!=results_table.end();it++){
    			/* origen,destino,[tiempoInicial,tiempoFinal),suma,contadorTray,tiempomin,tiempomax */
    			archivo_tabla<<n_in<<"\t"<<it->first<<"\t"<<t_in<<"\t"<<t_in+t_interval<<"\t"<<it->second.suma<<"\t"<<it->second.cant<<"\t"<<it->second.min<<"\t"<<it->second.max<<endl;

    		}
    	}
    	else
    		exit(EXIT_FAILURE);

    	archivo_tabla.close();
    

    }
}



	return 0;
}