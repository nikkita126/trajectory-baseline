#ifndef _STOPS_DICTIONARY_H_
#define _STOPS_DICTIONARY_H_

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cmath>
#include <string>
#include <fstream>

#define MAX_NODES 11290

typedef unsigned int uint;

using namespace std;

class NodeInfo{
public:
	uint id;
	uint nameSize;
	char *name;
	double latitude;
	double longitude;

};



class Stops_Dictionary {
public:
	
	uint nStops;
	NodeInfo *dictionary;

	Stops_Dictionary();
	Stops_Dictionary(ifstream &f);
	//~Stops_Dictionary();


	int getDistance(uint i,uint j);
	void printDistance(uint i,uint j);
	void printInfo();
	void printNodeInfo(uint i);
	int save(string filename);
	int load(string filename);

};









#endif