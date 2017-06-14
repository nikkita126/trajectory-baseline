#include "stop_encoding.h"

string checkStopName(string stop_name){ //not necessary anymore

	string new_name;


	if(stop_name=="BAQUEDANO L1")
		new_name="BAQUEDANO";
	else if(stop_name=="BAQUEDANO L5")
		new_name="BAQUEDANO";
	else if(stop_name=="BARRANCAS - L5")
		new_name="BARRANCAS";
	else if(stop_name=="LA FLORIDA")
		new_name="BELLAVISTA DE LA FLORIDA";
	else if(stop_name=="BLANQUEADO - L5")
		new_name="BLANQUEADO";
	else if(stop_name=="AGRICOLA")
		new_name="CAMINO AGRICOLA";
	else if(stop_name=="CARLOS VALDOVINO")
		new_name="CARLOS VALDOVINOS";
	else if(stop_name=="CIUDAD DEL NI?O")
		new_name="CIUDAD DEL NINO";
	else if(stop_name=="COLON")
		new_name="CRISTOBAL COLON";
	else if(stop_name=="RICARDO CUMMING")
		new_name="CUMMING";
	else if(stop_name=="DEL SOL - L5")
		new_name="DEL SOL";
	else if(stop_name=="LA CISTERNA L4A")
		new_name="LA CISTERNA";
	else if(stop_name=="BILBAO")
		new_name="FRANCISCO BILBAO";
	else if(stop_name=="ROTONDA GRECIA")
		new_name="GRECIA";
	else if(stop_name=="GRUTA DE LOURDES - L5")
		new_name="GRUTA DE LOURDES";
	else if(stop_name=="HERNANDO DE MAGALLANES - L1")
		new_name="HERNANDO DE MAGALLANES";
	else if(stop_name=="LAGUNA SUR - L5")
		new_name="LAGUNA SUR";
	else if(stop_name=="LAS PARCELAS - L5")
		new_name="LAS PARCELAS";
	else if(stop_name=="LA CISTERNA L2")
		new_name="LA CISTERNA";
	else if(stop_name=="LOS DOMINICOS - L1")
		new_name="LOS DOMINICOS";
	else if(stop_name=="LO PRADO - L5")
		new_name="LO PRADO";
	else if(stop_name=="MANQUEHUE - L1")
		new_name="MANQUEHUE";
	else if(stop_name=="MIRADOR AZUL")
		new_name="MIRADOR";
	else if(stop_name=="MONTE TABOR - L5")
		new_name="MONTE TABOR";
	else if(stop_name=="?UBLE")
		new_name="NUBLE";
	else if(stop_name=="ROTONDA QUILIN")
		new_name="QUILIN";
	else if(stop_name=="PEDREROS")
		new_name="PEDRERO";
	else if(stop_name=="PLAZA EGA?A")
		new_name="PLAZA EGANA";
	else if(stop_name=="PLAZA MAIPU - L5")
		new_name="PLAZA MAIPU";
	else if(stop_name=="PUDAHUEL - L5")
		new_name="PUDAHUEL";
	else if(stop_name=="SANTA ANA L2")
		new_name="SANTA ANA";
	else if(stop_name=="SANTA ANA L5")
		new_name="SANTA ANA";
	else if(stop_name=="SANTIAGO BUERAS - L5")
		new_name="SANTIAGO BUERAS";
	else if(stop_name=="SAN JOSE DE LA ESTRELLA - L4")
		new_name="SAN JOSE DE LA ESTRELLA";
	else if(stop_name=="SAN PABLO L1")
		new_name="SAN PABLO";
	else if(stop_name=="SAN PABLO - L5")
		new_name="SAN PABLO";
	else if(stop_name=="SAN PABLO L5")
		new_name="SAN PABLO";
	else if(stop_name=="TOBALABA_L1")
		new_name="TOBALABA";
	else if(stop_name=="TOBALABA_L4")
		new_name="TOBALABA";
	else if(stop_name=="TOBALABA L1")
		new_name="TOBALABA";
	else if(stop_name=="TOBALABA L4")
		new_name="TOBALABA";
	else if(stop_name=="LATINO AMERICANA")
		new_name="UNION LATINO AMERICANA";
	else if(stop_name=="VICU?A MACKENA")
		new_name="VICUNA MACKENNA";
	else if(stop_name=="LOS HEROES L1")
		new_name="LOS HEROES";
	else if(stop_name=="LOS HEROES L2")
		new_name="LOS HEROES";
	else
		new_name=stop_name;


	return new_name;
}

void createDictionary(map<string,int> &dictionary, ifstream &file, string separator){

	map<string,int>::iterator it;
	size_t pos;
    string line,name,code_str;
    int code;

    if(file){
		printf("\nReading stops names and int codes, creating dictionary...\n");
    	while(getline(file,line)){

    		pos=line.find(separator);

    		if(pos==string::npos)
    			break;

    		name=line.substr(0,pos); 
    		code_str=line.substr(pos+1);
    		//cout<<"CODE STR: "<<code_str<<endl;
    		code=stoi(code_str);
		
			//cout<<name<<" "<<code<<endl;

			dictionary.insert(make_pair(name,code));
    	}
    	printf("\tDONE\n");
    }
    else
    	exit(EXIT_FAILURE);

}

int getStopId(string stop_str, map<string,int> &dictionary){
	/* returns the int id assigned to a stop name, if it exists
	or -1 otherwise */

	map<string,int>::iterator it;

	it=dictionary.find(stop_str);
			
	if(it!=dictionary.end()){
		return it->second;
	}


	return -1; 
}

int getDiscreteTimeInterval(string time_str, uint time_interval, int starting_day){

	// parse time_str to create discrete time points
		// string time_str format:
		//	YYYY-MM-DD hh:mm:ss

	int day, hour, min, interval;
	int intervals_per_day = (60*24)/time_interval;

	//printf("%s %s\n",stop_str.c_str(),time_str.c_str());

	day=stoi(time_str.substr(8,2));
	hour=stoi(time_str.substr(11,2));
	min=stoi(time_str.substr(14,2));

	interval=(day - starting_day)*intervals_per_day + (hour*60 + min)/time_interval;

	return interval;


}