#include "utils.h"

string getFilename(string path){

	size_t pos=path.find_last_of("/\\"); // FIXME: makes assumption that theres a slash in path (might not always be like that)
	size_t extension_pos=path.find_first_of(".",pos);
	string filename;

	if(extension_pos!=string::npos){

		filename=path.substr(pos+1,extension_pos-(pos+1));
	}
	else
		filename=path.substr(pos+1);

	// printf("DEBUGGING: pos: %u, ext: %u, filename = %s\n", (uint)pos, (uint)extension_pos,filename.c_str());
	
	return filename;
}