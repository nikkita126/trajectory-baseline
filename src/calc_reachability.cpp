#include "distance_graph.h"


int main(int argc, char **argv){

	string encoded_dist_filename(argv[1]);

	string separator(";");
	uint n_stops=11500;

	Distance_Graph *dg = new Distance_Graph(encoded_dist_filename,n_stops,separator);


	printf("TOTAL_NODES: %d\nMINDIST: %d nodes: %d %d\nMAXNODE: %d\nZEROCOUNT: %d\n",dg->total_nodes,dg->mindist,dg->mindist_node_a,dg->mindist_node_b,dg->maxnode,dg->zerocount);

	/*for(int i=1;i<10;i++){
		printf("%d: ",(int)graph[i].size());

		for(auto j=graph[i].begin();j!=graph[i].end();j++){

			printf("%d %d %d\n",i,j->first,j->second);
		}
		printf("\n");

	}
	*/

	/*----- test queries ----*/

	dg->printDistance(1,2);
	dg->printDistance(100,500);
	dg->printDistance(10456,4567);
	dg->printDistance(2,7);
	dg->printDistance(11194,194);
	dg->printDistance(11194,195);
	dg->printDistance(11196,1);
	dg->printDistance(11208,2766);
	dg->printDistance(11196,1385);

	/*------------------------*/


	return 0;
}