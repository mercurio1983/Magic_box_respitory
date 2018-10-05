#ifndef NODE_H
#define NODE_H

#include "image_lr.hpp"
//#include "rectangle.h"
//#include "polygon.h"
//#include "point.h"
//#include "circle.h"

#include <iostream>
using namespace std;
#include "queue4.h"


class image_lr;
class queue4;
typedef image_lr data1;

class Node {

	private:
		data1 data;
		Node * next;
	public:
		//constructor
		Node(); //not needed
		//constructor
		Node(data1 &input, Node * next_Node);
		//copy constructor
		Node(const Node & theNode);
    
		//destructor
		~Node();
	
		//methods
		
		const Node & operator=(const Node &n);
		
		inline const data1 & getObject() const {return data;}
		
		unsigned char* getObject_left();
		unsigned char* getObject_right();
		unsigned long getNum_left();
		unsigned long getNum_right();
		//void print(ostream &out) const; 
		friend class queue4;
};


#endif
