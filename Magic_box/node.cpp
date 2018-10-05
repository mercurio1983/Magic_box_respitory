

#include <iostream>
using namespace std;
#include "node.h"
#include <cstdio>
#include <cstring>
#include <inttypes.h>

//constructor
Node::Node(){}

//constructor with 2 arguments
Node::Node(data1 &input, Node * next_Node): data(input), next(next_Node){}

//copy constructor to create a new Node
Node::Node(const Node & theNode){
	if(theNode.next == NULL){next = NULL;}
	else{next = new Node(*theNode.next);}
	}

Node::~Node(){
	//cout << "running the destructor in node"<< endl;
	// do not run this since it remove the entire queue recursivly
	//if(next != NULL){delete next;} 
	//delete data; //make sure to free memory
	}

unsigned char* Node::getObject_left() {return data.getValue_left();}
unsigned char* Node::getObject_right() {return data.getValue_right();}
unsigned long Node::getNum_left(){return data.getValue_left_size();}
unsigned long Node::getNum_right(){return data.getValue_right_size();}


//copy operator to enable Node2 = Node1
const Node & Node::operator=(const Node &n){
	
	if(this != &n){
	data = n.data;
	*next = *n.next;
	}
	return *this;
}

//void Node_::print(ostream &out) const {
	//out << data;
	//if(next != 0){
		//out << ", ";
		//next->print(out);
	
	//}
	
