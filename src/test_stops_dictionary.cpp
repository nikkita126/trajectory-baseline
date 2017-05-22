#include "stops_dictionary.h"
#include <cstdlib>
#include <cstdio>

using namespace std;


int main(int argc, char *argv[]){


	char *filename = argv[1];

	Stops_Dictionary *sd = new Stops_Dictionary();

	sd->load(filename);

	printf("Distancia: %d\n",sd->getDistance(447,369));

	sd->printNodeInfo(447);
	sd->printNodeInfo(369);



	return 0;
}