#include <iostream>
#include <stdio.h>
#include <string>
#include "linked_list.cpp"
#include "compare.cpp"
#include <fstream>
using std::string;

int partition(linked_list list,int low_index,int high_index){

	string pivot = list.get(high_index);

	int i,j;
	j = low_index;
	for(i=low_index;i<high_index;i++){

		if(lt(pivot,list.get(i))){
			list.swap(i,j);
			j++;
		}

	}
	list.swap(j,high_index);
	return j;
}


void quicksort(linked_list list,int low_index= 0,int high_index= -2){

	if(high_index == -2){
		high_index = list.len-1;
	}


	if(low_index < high_index){
		int i = partition(list,low_index,high_index);

		quicksort(list,low_index,i-1);
		quicksort(list,i+1,high_index);

	}
}


linked_list read_new_adresses(linked_list list){

	std::ifstream new_block;
	new_block.open("new_block.csv");

	if(new_block.is_open()){
		string header;
		std::getline(new_block,header);
		int no_adresses = std::stoi(header);

		int i;
		string buffer;
		for(i=0;i<no_adresses;i++){
			std::getline(new_block,buffer);
			list.append(buffer);
		}

		return list;
	} else {
		std::cerr << "Missing input file new_block.csv" << std::endl;
		throw;
	}
}

void store(linked_list list){

	std::ifstream adress_database_old;
	adress_database_old.open("adress_database.csv",std::ios::in);

	if(!adress_database_old.is_open()){

		//There is no file yet, so just dumping everything.

		std::ofstream adress_database;
		adress_database.open("adress_database.csv",std::ios::out);
		int i = 0;
		for (i=0;i<list.len;i++){
			adress_database << list.get(i) << std::endl;
		}
		adress_database.close();


	} else {

		//There is already a file so a new file is created, that holds the updated content.
		//Old File is delted afterwards.

		std::ofstream adress_database_new;
		adress_database_new.open("adress_database.csv.tmp",std::ios::out|std::ios::trunc);

		if(adress_database_new.is_open()){

			int i = 0;
			string adress;

			while(!adress_database_old.eof() && i<list.len){

				std::getline(adress_database_old,adress);

				if(list.get(i) == adress) {
					i++;
					adress_database_new << adress << std::endl;
				} else if (lt(adress,list.get(i))){
					adress_database_new << list.get(i) << std::endl;
					adress_database_new << adress << std::endl;
					i++;
				} else {
					adress_database_new << adress << std::endl;
				}
			}

			adress_database_new.close();
			adress_database_old.close();


			remove("adress_database.csv");
			rename("adress_database.csv.tmp","adress_database.csv");

		} else {
			std::cerr << "Opening of new temporary database failed." << std::endl;
		}

	}
}


int main() {


	//Reading the file
	linked_list address_list;
	address_list =  read_new_adresses(address_list);

	//sorting the new adresses
	quicksort(address_list);

	std::cout << "Sorted." << std::endl;

	store(address_list);

	std::cout << "Stored in Database." << std::endl;


	return 0;
}

