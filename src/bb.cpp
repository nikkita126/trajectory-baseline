#include <cstdio>

using namespace std;


int main(){


	int array[10]={2,2,2,3,4,4,4,7,8,9};

	int t=1;
    size_t l=0, r=9, m;

    while(l<r){ //bin search to find the index of time t in times_list
        
        m=l+(r-l)/2;

       if(array[m] < t) //time is smaller than the given one
            l=m+1;
        else
            r=m;

    }

    /*
    if(tindex[s].times_list[l]!=t)
    	return -1;
    */


    printf("l: %d\n",(int)l);





	return 0;
}