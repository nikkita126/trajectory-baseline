 
    /* CONSULTAS DE TRAYECTORIAS POTENCIALES PARA ACCESIBILIDAD */

    uint n_in, t_in, t_fin;
    uint delta_t=1; /* ventana de espera */
    vector<pair<int,int> > cola_puntos;

    btree_map<uint, btree_map<uint,uint> > tabla_resultados;

   


 while(true){

    	cout<<"Consultas\nEspecificar nodo inicial, tiempo inicial, tiempo final: ";


    	cin>>n_in>>t_in>>t_fin;

    	if(!n_in && !t_in && !t_fin) break; /* el while cierra con input 0 0 0  */

    	if(n_in > indice.size()){ /* verificar que el paradero esté dentro de la lista */

    		cout<<"Paradero inexistente"<<endl;
    		continue;
    	}

    	cola_puntos.clear();
    	tabla_resultados.clear();

    	cola_puntos.push_back(make_pair(n_in,t_in));

    	for(auto i=cola_puntos.begin();i!=cola_puntos.end();i++){

    		auto l_b = indice[i->first].lower_bound(i->second);
    		
    		//cout<<l_b->first<<endl;

    		if(l_b->first > i->second + delta_t){
    			//tiempo fuera de rango
    			continue;
    		}


    		for(auto j=l_b->second.begin();j!=l_b->second.end();j++){ /* recorrer lista de ids de tray */

    			//cout<<*j<<endl;
    			for(auto par=lista_trayectorias[*j].begin();par!=lista_trayectorias[*j].end();par++){

    				if(par->first == i->first && par->second==l_b->first){ /* tanto el nodo como el tiempo deben coincidir */

    					bool is_last=true;
    					if(par+1 !=lista_trayectorias[*j].end()){ /* si existe un siguiente par en la trayectoria */

    						cola_puntos.push_back(make_pair((par+1)->first,(par+1)->second)); /* lo encolo */
    						is_last=false;

    					}

    					if(par->first == 0)


    					break;

    				}
    			}

    		}



    	}








    }