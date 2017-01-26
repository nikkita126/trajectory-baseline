#include "distance_graph.h"


bool cmp(const ui &l,const ui &r)
{

    return l.first<r.first;
}


Distance_Graph::Distance_Graph(string encoded_dist_filename, uint n_stops, string separator){

	ifstream encoded_distances;
	encoded_distances.open(encoded_dist_filename);

	if(!encoded_distances){
        printf("\nERROR: %s file doesn't exist. Exiting now.\n", encoded_dist_filename.c_str());
        exit(EXIT_FAILURE);
	}



	//--------- Initialization --------//
	graph.assign(n_stops,vui());

	total_nodes=0;
	maxnode=0;
	mindist=INT_MAX;
	mindist_node_a=-1;
	mindist_node_b=-1;
	zerocount=0;

	//---------------------------------//
	
	string line;
	int stop_i,stop_j,dist,neighbors;

	while(getline(encoded_distances,line)){
		sscanf(line.c_str(),"%d %d %d\n",&stop_i,&stop_j,&dist);
		//printf("%d %d %d\n",stop_i,stop_j,dist);


		// POR QUÉ HAY PARES CON DISTANCIA 0???
		if(!dist) continue;

		neighbors=(int)graph[stop_i].size();
		//printf("%d!!!!\n",neighbors);
		bool push_dist=true;
		if(neighbors){

			auto l_b=lower_bound(graph[stop_i].begin(),graph[stop_i].end(),ui(stop_j,0),cmp);
			if(l_b->first==stop_j && l_b->second <= dist){
				//printf("no pushear\n");
				push_dist=false;
			}
		}
		else
			total_nodes++;

		neighbors=(int)graph[stop_j].size(); //neighbors of the other stop

		if(!neighbors)
			total_nodes++;

		if(push_dist){
			//printf("nodo nuevo\n");
			graph[stop_i].push_back(ui(stop_j,dist));
			graph[stop_j].push_back(ui(stop_i,dist));

			sort(graph[stop_i].begin(),graph[stop_i].end(),cmp);
			sort(graph[stop_j].begin(),graph[stop_j].end(),cmp);
			//printf("Updated: distance from %u to %u = %u\n",stop_i,stop_j,dist);

			if(dist<mindist){ // search for the smallest distance achievable
				mindist = dist;
				mindist_node_a=stop_i;
				mindist_node_b=stop_j;

			}

			if(!dist)
				zerocount++;

			if(stop_i>maxnode) maxnode=stop_i;
			if(stop_j>maxnode) maxnode=stop_j;
		}
	}


	encoded_distances.close();
}

int Distance_Graph::getDistance(uint i,uint j){

	auto l_b=lower_bound(graph[i].begin(),graph[i].end(),ui(j,0),cmp);

	if(l_b->first != j){
		//printf("l_b first: %u\n",l_b->first);
		
		return -1;
	}

	return l_b->second;

}

void Distance_Graph::printDistance(uint i, uint j){

	int d = getDistance(i,j);

	if(d==-1) {
		printf("pair (%u,%u) is not connected\n",i,j);
		return;
	}

	printf("distance from node %u to node %u: %d\n",i,j,d);


}

void Distance_Graph::printInfo(){

	printf("TOTAL_NODES: %d\nMINDIST: %d nodes: %d %d\nMAXNODE: %d\nZEROCOUNT: %d\n",total_nodes,mindist,mindist_node_a,mindist_node_b,maxnode,zerocount);
}