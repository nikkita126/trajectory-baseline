#include "distance_graph.h"
#include "utils.h"
#include <string>

void test_queries(Distance_Graph &dg){

	dg.printDistance(1,2);
	dg.printDistance(100,500);
	dg.printDistance(10456,4567);
	dg.printDistance(2,7);
	dg.printDistance(11194,194);
	dg.printDistance(11194,195);
	dg.printDistance(11196,1);
	dg.printDistance(11208,2766);
	dg.printDistance(11196,1385);

}



int main(int argc, char **argv){

	string encoded_dist_filename=argv[1];

	string separator(";");
	
	uint n_stops=11500;

	Distance_Graph *dg = new Distance_Graph(encoded_dist_filename,n_stops,separator);
	

	dg->printInfo();

	/** Leer archivo de tiempos y trayectorias */
	ifstream query_data_file;




	return 0;
}


