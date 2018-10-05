#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
#include <math.h>
#include <map>

int lt(string a,string b){


	if(a.size()>b.size()){
		return 1;
	} else if (b.size()>a.size()){
		return 0;
	} else {
		int i = 0;
		while(i<a.size()&&a[i] == b[i]){
			i++;
		}
		if(i>=a.size()){
			return 0;
		} else if((int)a[i] > (int)b[i]){
			return 1;
		} else {
			return 0;
		}
	}
}