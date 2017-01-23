#include "distance_graph.h"


int main(int argc, char **argv){

	ifstream encoded_distances;
	encoded_distances.open(argv[1]);

	if(!encoded_distances){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", argv[1]);
        exit(EXIT_FAILURE);
	}

	string separator(";");
	uint n_stops=11500;

	Distance_Graph *dg = new Distance_Graph(encoded_distances,n_stops,separator);

	encoded_distances.close();

	printf("TOTAL_NODES: %d\nMINDIST: %d nodes: %d %d\nMAXNODE: %d\nZEROCOUNT: %d\n",dg->total_nodes,dg->mindist,dg->mindist_node_a,dg->mindist_node_b,dg->maxnode,dg->zerocount);

	/*for(int i=1;i<10;i++){
		printf("%d: ",(int)graph[i].size());

		for(auto j=graph[i].begin();j!=graph[i].end();j++){

			printf("%d %d %d\n",i,j->first,j->second);
		}
		printf("\n");

	}
	*/


	dg->print_distance(1,2);
	dg->print_distance(100,500);
	dg->print_distance(10456,4567);
	dg->print_distance(2,7);




	return 0;
}