#include "stops_dictionary.h"
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define earthRadiusKm 6371.0

using namespace std;

/* ---------------- To get euclidean distance between two stops ------------------ */
/*  Copied verbatim from http://stackoverflow.com/a/10205532 */


// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/* --------------------------------------------------------------------------------- */



Stops_Dictionary::Stops_Dictionary(){

	nStops=0;
	//dictionary= (NodeInfo *)malloc (MAX_NODES * sizeof(NodeInfo));
	dictionary=NULL;
}


Stops_Dictionary::Stops_Dictionary(ifstream &f){

	uint n=100;
	char separator;
	int i=1;
	uint id;
	uint nameSize;
		double latitude;
	double longitude;
	string name_str;

	nStops=0;

	dictionary = (NodeInfo *) malloc(MAX_NODES * sizeof(NodeInfo));
	//dictionary = (NodeInfo *) malloc(n * sizeof(NodeInfo));
	
	/* - Node 0 initialization - */
	dictionary[0].id=0;
	dictionary[0].nameSize=0;
	dictionary[0].name=NULL;
	dictionary[0].latitude=0;
	dictionary[0].longitude=0;
	/* ------------------------ */

	string line;


	while(getline(f,line)){

		//printf("Linea ql: %s\n",line.c_str());
		size_t start_pos=0,end_pos;

		end_pos=line.find(';',start_pos);
		//		cout<<start_pos<<" "<<end_pos<<endl;  		

		id = stoi(line.substr(start_pos,(end_pos-start_pos)));
		//printf("Id: %d\n",id);

		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		//				cout<<start_pos<<" "<<end_pos<<endl;  		

		name_str = line.substr(start_pos,(end_pos-start_pos));
		int len = name_str.size();
		/*char *name = (char *) malloc(len+1 * sizeof(char)); 
		name_str.copy(name,len);
		name_str[len] = '\0';*/

		nameSize = len;
				//printf("NAme: %s\n",name_str.c_str());


		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		latitude = stod(line.substr(start_pos,(end_pos-start_pos)));
				//printf("Lat: %f\n",latitude);


		start_pos=end_pos+1;
		end_pos=line.find(';',start_pos);
		longitude = stod(line.substr(start_pos,(end_pos-start_pos)));
		//printf("Lon: %f\n",longitude);

    	

		 /* end of iteration over the same trip */
		/*

		fscanf(f,"%u",&id)!=EOF){
		
		fscanf(f,"%*c",&separator);
		fscanf(f,"%[^;]",name);
		fscanf(f,"%*c",&separator);
		fscanf(f,"%lf",&latitude);
		fscanf(f,"%*c",&separator);
		fscanf(f,"%lf",&longitude);
		fscanf(f,"%c",&separator); // end of line (supposedly)
		*/

		//nameSize=strlen(name);
		//if(i==1) printf("This is the name that I read: %s\n",name);

		dictionary[i].id=id;
		dictionary[i].nameSize=nameSize;
		dictionary[i].name = (char *) malloc (nameSize * sizeof(char));
		name_str.copy(dictionary[i].name,nameSize);
		//strcpy(dictionary[i].name,name);
		//dictionary[i].name[]
		dictionary[i].latitude=latitude;
		dictionary[i].longitude=longitude;

		//if(i==1)
			//printf("Este es el nombre luego: %s\n",dictionary[i].name);
		i++;
		
		/*
		if(i>=n-2){
			n *=2;
			dictionary = (NodeInfo *) realloc(dictionary, n * sizeof(NodeInfo));
		}
		*/
		//	printf("HOLI CTM\n");

		//printf("Este es el nombre luego: %s\n",dictionary[1].name);

	}

	nStops=i;
	//printf("Este es el nombre: %s\n",dictionary[1].name);

}

int Stops_Dictionary::getDistance(uint i,uint j){

	int distance; //in meters

	double lat1 = dictionary[i].latitude;
	double lon1 = dictionary[i].longitude;
	double lat2 = dictionary[j].latitude;
	double lon2 = dictionary[j].longitude;

	double dist = distanceEarth(lat1,lon1,lat2,lon2);

	//printf("Distancia original: %f\n", dist);

	distance = (int)(dist * 1000);

	return distance;
}

void Stops_Dictionary::printDistance(uint i,uint j){

	// imprimit

}

void Stops_Dictionary::printInfo(){

	printf("Number of stops in dictionary: %u\n", nStops);
}


void Stops_Dictionary::printNodeInfo(uint i){

	printf("id: %u\n", dictionary[i].id);
	printf("name size: %u\n", dictionary[i].nameSize);
	printf("latitude: %f\n", dictionary[i].latitude);
	printf("longitude: %f\n", dictionary[i].longitude);
	printf("name: %s\n", dictionary[i].name);

}

int Stops_Dictionary::save(string filename){

	int file;

	if( (file = open(filename.c_str(), O_WRONLY|O_CREAT,S_IRWXG | S_IRWXU)) < 0) {
		printf("Cannot open file %s\n", filename.c_str());
		exit(0);
	}

	int write_err;

	//printf("Actual value of nStops: %u\n",nStops);
	write_err=write(file, &nStops, sizeof(uint));
	//printf("bytes written nstops: %d\n",write_err);

	NodeInfo *node = (NodeInfo *) malloc(1 * sizeof(NodeInfo));

	for (uint i=0;i<=nStops;i++){
		node = &(dictionary[i]);
		
		write_err=write(file,&(node->id),sizeof(uint));
		write_err=write(file,&(node->nameSize),sizeof(uint));
		write_err=write(file,node->name,node->nameSize*sizeof(char));
		//if(i==1)			printf("Nodes written name: %d name: %s and name: %s\n",write_err,node->name,dictionary[i].name);
		write_err=write(file,&(node->latitude),sizeof(double));
		write_err=write(file,&(node->longitude),sizeof(double));

	}
	close(file);
	//free(node);
	return 0;

	
}

int Stops_Dictionary::load(string filename){

	int file;

	if( (file = open(filename.c_str(), O_RDONLY)) < 0) { 
		printf("Cannot read file %s\n", filename.c_str());
		exit(0);
	}

	int read_err;

	read_err=read(file, &nStops, sizeof(uint));
	//printf("bytes read nstops: %d\n",read_err);
	printf("Number of nodes in dictionary: %u\n",nStops);

	dictionary = (NodeInfo *) malloc(nStops * sizeof(NodeInfo));

	NodeInfo *node = (NodeInfo *) malloc(1 * sizeof(NodeInfo));

	for (uint i=0;i<=nStops;i++){
		
		read_err=read(file,&(node->id),sizeof(uint));
		//printf("bytes read id: %d and id: %d\n",read_err,node->id);
		read_err=read(file,&(node->nameSize),sizeof(uint));
		//printf("bytes read namesize: %d\n",read_err);
		node->name = (char *) malloc(node->nameSize * sizeof(char));
		read_err=read(file,node->name,node->nameSize * sizeof(char));
		//printf("bytes read name: %d\n",read_err);
		read_err=read(file,&(node->latitude),sizeof(double));
		//printf("bytes read latitude: %d\n",read_err);
		read_err=read(file,&(node->longitude),sizeof(double));
		//printf("bytes read longitude: %d\n",read_err);

		dictionary[i] = *node;

	}
	close(file);

	free(node);
	return 0;

}
