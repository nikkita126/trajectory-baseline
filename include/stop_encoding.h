#ifndef _STOP_ENCODING_H_
#define _STOP_ENCODING_H_

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "cppUtils.h"

using namespace std;


string checkStopName(string stop_name);
void createDictionary(map<string,int> &dictionary, ifstream &file,string separator);
void createReverseDictionary(map<string,int>&dictionary,map<int,string>&reverse_dictionary);
int getStopId(string stop_str, map<string,int> &dictionary);
int getDiscreteTimeInterval(string time_str, uint time_interval, int starting_day);


#endif