#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
#include <math.h>
#include <map>


string lookup = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";


int find(char a){
	int j= 0;
	while(j<=lookup.size()&&lookup[j] != a){
		j++;
	}
	if(j<lookup.size()){
		return j;
	} else {
		cout << "trying to decode invalid string: " << a << endl;
		throw;
	}
}

int highest_bit(string a){
	int upper = 0;

	while((int)a[upper] == 49 && upper<a.size()){
		upper++;
	}
	return a.size()-upper;
}

int lt(string a,string b){

	int sig_bits_a = highest_bit(a);
	int sig_bits_b = highest_bit(b);

	if(sig_bits_a>sig_bits_b){
		return 1;
	} else if (sig_bits_b>sig_bits_a){
		return 0;
	} else {
		int i = 0;
		while(i<sig_bits_a&&a[a.size()-sig_bits_a+i] == b[b.size()-sig_bits_b+i]){
			i++;
		}

		if(i>=sig_bits_a){
			return 0;
		} else if(find(a[a.size()-sig_bits_a+i]) > find(b[b.size()-sig_bits_b+i])){
			return 1;
		} else {
			return 0;
		}
	}
}

