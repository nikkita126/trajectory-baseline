#ifndef _DISTANCE_GRAPH_H_
#define _DISTANCE_GRAPH_H_


#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<uint> vu;
typedef pair<uint,int> ui;
typedef vector<ui> vui;

class Distance_Graph {
public:

	int total_nodes;
	int maxnode;
	int mindist;
	int mindist_node_a;
	int mindist_node_b;
	int zerocount;



	vector<vui> graph;




	Distance_Graph(string encoded_distances_filename, uint n_stops, string separator);
	~Distance_Graph();

	int getDistance(uint i,uint j);
	void printDistance(uint i,uint j);
	void printInfo();
	
};



#endif