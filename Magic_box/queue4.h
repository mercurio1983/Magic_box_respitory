#ifndef queue4_H
#define queue4_H

//#include "bool1.h"
#include "node.h"


class Node;
//class Rectangle;
//class Point;
//class Circle;
//class Polygon;

class queue4{
		//struct Node {image_lr image_lr_obj;struct Node * next;};
		enum { QUEUE_SIZE = 800 }; //7200 frames required for 2 min time shift (120 sec)x(60fps) 
	private:
	    int q_size;
	    const int q_max_size;
		Node * first;
		Node * last;
		//queue4(const queue4 & image_lrs) : q_max_size(0){} //dummy constructor does nothing but point to itself
		//queue4 & operator= (const queue4 & q){return *this;} //copy dummy operator does nothing but enables copy to itself
	public:
		
		queue4(int q_size_ = QUEUE_SIZE); /* constructor */
		
		//copy constructor for object2 inherits the properties from object1
		queue4(const queue4 & q);  
		
		//copy operator for moving the properties to similar object by equal sign object2 = object1
		const queue4 & operator=(const queue4 & q);
		//queue4(int queue4 &image_lrs); /* constructor */
	    ~queue4(); /* destructor */
	    
	   
	    const image_lr& getValue();	    
		bool enqueue4(const image_lr &s); /* setters */
		//void remove(const Vertex &v); /* getters */
		//void dequeue4(image_lr &output_image_lr); //just to check the data 
		void dequeue4(); //just to check the data 
		void clean_queue4(); //to clean the queue
		
		void set_left_item(unsigned char* left_image, unsigned long size_left);
		void set_right_item(unsigned char* right_image, unsigned long size_right);
		void set_item(unsigned char* left_image, unsigned long size_left,unsigned char* right_image, unsigned long size_right);
		bool isfull();
		bool isempty();
		//double area();
		//void print();
		
		unsigned char* getValue_left();
		unsigned char* getValue_right();
		unsigned long getNum_left();
		unsigned long getNum_right();	
	};


#endif
