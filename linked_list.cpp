#include <iostream>
#include <string>
using std::string;

struct node {
	std::string number;
	node *next;
};

class linked_list{

	node *start;

public:
	
	int len;
	linked_list(void);
	string get(int index);
	node *get_node(int index);
	void display_list(void);
	void test_length(void);

	void add(string number);
	void insert(string number,int index);
	void append(string number);

	void delete_first(void);
	void delete_index(int index);
	void delete_element(string number);

	void swap(int index1,int index2);
};

linked_list::linked_list(void){
	start =NULL;
	len = 0;
}

string linked_list::get(int index){



	if(index >= len){
		std::cout << "Get-index beyond list." << std::endl;
		throw;
	}

	if(index<0){
		std::cout<< "Get-index must be positive." << std::endl;
		throw;
	}
	int i;
	node *head=start;
	for(i=0;i<index;i++){
		head = head->next;
	}
	return head->number;
}

node * linked_list::get_node(int index){


	if(index >= len){
		std::cout << "Get-index beyond list." << std::endl;
		throw;
	}

	if(index<0){
		std::cout<< "Get-index must be positive." << std::endl;
		throw;
	}

	int i;
	node *head = start;
	for(i=0;i<index;i++){
		head = head->next;
	}

	return head;


}

void linked_list::test_length(void){

	int i= 0;
	node *temp;
	temp = start;

	while(temp){
		temp = temp->next;
		i++;
	}
	
	if(len != i){
		std::cout << "List length got missmatched." << std::endl;
		throw ;
	}
}


void linked_list::display_list(void){

	node *read_head = start;

	std::cout <<"[";

	while(read_head){
		std::cout<<" "<<read_head->number<<" ";

		if(read_head->next){
			std::cout << ",";
		}

		read_head = read_head->next;
	}
	std::cout <<"]"<<std::endl;
}

void linked_list::add(string number){

	node *new_node;
	new_node = new node;
	new_node->number= number;
	new_node->next = start;

	start = new_node;

	len++;
}

void linked_list::insert(string number,int index){

	if (index > len){
		throw "Insertion beyond list length.";
	}

	if(index == 0){
		add(number);
	} else {
		node *prev = new node;
		node *cur = new node;
		node *new_node = new node;
		
		cur = start;

		int i;
		for(i=0;i<index;i++){
			prev = cur;
			cur = cur->next;
		}

		new_node->number = number;
		prev->next = new_node;
		new_node->next = cur;

		len ++;
	}
}

void linked_list::append(string number){
	insert(number,len);
}

void linked_list::delete_first(void){

	node *temp;
	temp = start;
	start = start->next;
	delete temp;
	len --;
}


void linked_list::delete_index(int index){

	if(index>len){
		std::cout << "Deleting beyond list length." << std::endl;
		throw;
	}

	if(index<0){
		std::cout << "Index must be positive." << std::endl;
		throw;
	}

	if(index == 0){
		delete_first();
	} else {

		int i;
		node *cur;
		node *prev;

		cur = start;
		for(i=0;i<index;i++){
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		delete cur;
		len --;
	} 
}

void linked_list::delete_element(string number){

	int i=0;
	node *head =start;
	int found = 0;

	while(head&&(!found)){
		std::cout << "Checked at: " << i << std::endl;
		if (number == head->number){
			delete_index(i);
			found = 1;
		}
		std::cout << "found: " << found << std::endl;
		head = head->next;
		i++;
	}
}

void linked_list::swap(int index1,int index2){

	if(index1 < 0 || index2 < 0){
		std::cerr << "swaping index is smaller than 0."<<std::endl;
		throw;
	}

	if(index1 >= len || index2 >= len ) {
		std::cerr << "swapping index is beyond list. " << std::endl;
		throw;
	}

	if (index1 != index2){
		string buffer;
		node *node1,*node2;

		node1 = get_node(index1);
		node2 = get_node(index2);

		buffer = node1->number;
		node1->number = node2->number;
		node2->number = buffer;
	}
}

