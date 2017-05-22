#include "stops_dictionary.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;


int main(int argc, char* argv[]){

	string infile_name, outfile_name;
	
	ifstream infile;
	ofstream outfile;

	infile_name=argv[1];
	outfile_name=argv[2];

	infile.open(infile_name);

	if(!infile){
		exit(EXIT_FAILURE);
	}

	Stops_Dictionary *sd = new Stops_Dictionary(infile);

	infile.close();
	sd->printInfo();

	sd->printNodeInfo(1);
	sd->printNodeInfo(1);
	sd->printNodeInfo(1);

	sd->save(outfile_name);

	free(sd);

	return 0;
}