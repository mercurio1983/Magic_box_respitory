#include <iostream>
using namespace std;
#include <cstdlib>
#include <cmath>
#include "queue4.h"
//#include "bool1.h"



//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
//#include <iostream>

queue4::queue4(int q_size_) : q_max_size(q_size_), first(NULL)
{
	//first = NULL;
	last = NULL;
	q_size = 0;
}

queue4::~queue4(){
	Node * temp = new Node;
	while(first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
		}
}



queue4::queue4(const queue4 & q): q_max_size(100){
	//copy constructor 
	if(q.first == NULL){first = NULL;}
	else{first = new Node(*q.first);}
	}

const queue4 & queue4::operator=(const queue4 & q){
	//similiar to the list copy operator =
	if(first != NULL){delete first;}
	//need only to copy the first node
	if(q.first != NULL){first = new Node(*q.first);} 
	else{first = NULL;}
	return (*this);
	}

void queue4::set_left_item(unsigned char* left_image, unsigned long size_left){
	image_lr item;
	//cout << "running test on item\n" << endl;
	item.set_left_Value(left_image,size_left);
	//cout <<"test passed item\n"<< endl;
	enqueue4((item));	
	//cout << "test passed queue\n" << endl;
	}
	
void queue4::set_right_item(unsigned char* right_image, unsigned long size_right){
	image_lr item;
	//cout << "running test on item\n" << endl;
	item.set_right_Value(right_image,size_right);
	//cout <<"test passed item\n"<< endl;
	enqueue4((item));	
	//cout << "test passed queue\n" << endl;
	}	

void queue4::set_item(unsigned char* left_image, unsigned long size_left,unsigned char* right_image, unsigned long size_right){
	image_lr item;
	//cout << "running test on item\n" << endl;
	item.setValue(left_image,size_left,right_image,size_right);
	//cout <<"test passed item\n"<< endl;
	enqueue4((item));	
	//cout << "test passed queue\n" << endl;
	}

bool queue4::enqueue4(const image_lr &s){
	if (isfull()){
		cout << "the queue is full now" << endl;
		return false;} //chekc if the queue is full 
		
	else{ //else construct a new node
		Node * new1_node = new Node; //create a new node
		if (new1_node == NULL){ return 0;} //just to stop the add function
		new1_node->data = s; //set the attributes of the node
		new1_node->next = NULL; //set the next attribute of the node
		//new1_node(s,NULL);
		q_size++; //increment the size counter
		if(first == NULL){ //if the next pointer i null
			first = new1_node; //if the first node is empty then fill it
			}
		else{
			last->next = new1_node; //the next that is null gets an obj
			}
		last = new1_node; //pointing at the last obj	
		return 0; //just to stop the add function
		}	
	}


//void queue4::remove(const Vertex &v){
	
	////need a for loop to go through the entire queue
	//// the purpose is to place the objects after each other
	//// and do one entire loop, where the entire queue is checked
	////once.
	//image_lr *current_image_lr = new image_lr;
	//int count;
	//for(count = 0; count < q_size; count++){
		//pick((*current_image_lr));
		////since the class inherit the public properties then this is possible 
		////the positions must be withinn the difference of -1 to +1 thus 
		////one applies abs(pose-Vertex) < 1
		//if((fabs(current_image_lr->getXposition() - v.get_Xpose()) < 1) && (fabs(current_image_lr->getYposition() - v.get_Ypose()) < 1)){
			////then do nothing 
			//}
		//else{add(*current_image_lr); //just put the object last in the queue if the coordinate does not exist there
		//}
		//}
	//}

void queue4::clean_queue4(){
	if(isempty()){
		cout << "the queue is empty now" << endl;
		}
	else{
		Node * temp = new Node;
		while(!isempty())
		{
			temp = first;
			if(first->next == NULL){ last = NULL; }
			first = first->next;
			q_size--; //decrement the size counter
			delete temp;
			if (q_size == 0){last = NULL;} 
		}
		
	}
	
	
}

void queue4::dequeue4(){
	if (isempty()){
		cout << "the queue is empty now" << endl;
		
		} //check if the queue is empty
	else{
		//cout << "test1\n"<< endl;
		Node * temp = new Node; //set a temporary pointer to node
		//cout << "test2\n"<< endl;
		temp = first; //the temporary gets the first obj
		//cout << "test3\n"<< endl;
		//set last null if the last obj is going to be picked
		if(first->next == NULL){ last = NULL; } 
		//cout << "test4\n"<< endl;
		first = first->next; //overwrite the first with the next
	    //cout << "test5\n"<< endl;
	    q_size--; //decrement the size counter
	    //output_image_lr = temp->getObject(); //possible due to friend function //write to the output reference
		//cout << "test6\n"<< endl;
		delete temp; //make sure to delete the obj
		//cout << "test7\n"<< endl;
		
		if (q_size == 0){last = NULL;}
		
	}
		
	
}

//void queue4::dequeue4(image_lr &output_image_lr){
	//if (isempty()){} //check if the queue is empty
	//else{
		//Node * temp; //set a temporary pointer to node
		//temp = first; //the temporary gets the first obj
		
		////set last null if the last obj is going to be picked
		//if(first->next == NULL){ last = NULL; } 
		//first = first->next; //overwrite the first with the next
	    //q_size--; //decrement the size counter
	    //output_image_lr = temp->getObject(); //possible due to friend function //write to the output reference
		//delete temp; //make sure to delete the obj
		//if (q_size == 0){last = NULL;}
		
	//}
		
	
//}


bool queue4::isfull(){return q_size == q_max_size ? 1 : 0;}// ? true : false;}

bool queue4::isempty(){return first == 0 ? 1 : 0;}//true : false;}


//double queue4::area(){
	//image_lr *current_image_lr = new image_lr;
	//double area_sum;
	//int count;
	//for(count = 0; count < q_size; count++){
		//pick((current_image_lr));
		////since the class inherit the public properties then this is possible
		//area_sum += current_image_lr->area();
		//add((*current_image_lr)); //just put the object last in the queue if the coordinate does not exist there
		//}
	//return area_sum;	
	//}

//void queue4::print(){
	//image_lr *ptr_image_lr = new image_lr;
	////image_lr s;
	//int count;
	//for(count = 0; count < q_size; count++){
		//pick((*ptr_image_lr));
		////ptr_image_lr = &s;
		////since the class inherit the public properties then this is possible
		//ptr_image_lr->print();
		
		//add((*ptr_image_lr)); //just put the object last in the queue if the coordinate does not exist there
		//}
	//}

const image_lr& queue4::getValue(){return first->getObject();}
unsigned char* queue4::getValue_left(){return first->getObject_left();}
unsigned char* queue4::getValue_right(){return first->getObject_right();}	
unsigned long queue4::getNum_left(){return first->getNum_left();}
unsigned long queue4::getNum_right(){return first->getNum_right();}	

