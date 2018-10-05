#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "queue_Wrapper.h"
#include "bool1.h"
#include "queue4.h"
#include "image.h"
#include "image_lr.hpp"
#include "gpu_bayer.h"

extern "C" {
//#include <iostream>
//#include <queue>
//#include <new>


	
CItem * new_item(){
	
	image_lr *item = new image_lr();
	return (CItem *)item;
	}	

void set_item(CItem *item, unsigned char* i1, unsigned char* i2, unsigned long size1, unsigned long size2){
	
	image_lr *n1 = (image_lr *)item;
	n1->setValue(i1,size1,i2,size2);
 
	item =  (CItem *)n1;
	}	
	
unsigned char *get_item_left(const CItem *item){
	
	image_lr *n1 = (image_lr *)item;
	return n1->getValue_left();
	}	

unsigned char *get_item_right(const CItem *item){	
	
	image_lr *n1 = (image_lr *)item;
	return n1->getValue_right();
	
	}

unsigned long get_size_left(const CItem *item){
	
	
	//unsigned long value1;
	image_lr *n1 = (image_lr *)item;
	//value1 = n1->getValue_left_size();
	return n1->getValue_left_size();
	}	

unsigned long get_size_right(const CItem *item){	
	
	//unsigned long value2;
	image_lr *n1 = (image_lr *)item;
	//value2 = n1->getValue_right_size();	
	return n1->getValue_right_size();	
	
	}

void reallocate_dequeue(CItem *item){	
	
	image_lr *n1 = (image_lr *)item;
	n1->reallocate_dequeue();	
	//return (CItem *)n1; 
	item =  (CItem *)n1;
	}	
	
	
void delete_item_image(CItem *item){
	
	image_lr *n1 = (image_lr *)item;
	delete n1;
	
}

CQueue * new_queue(){
	queue4 *queue2 = new queue4(); //initiating queue
	return (CQueue *)queue2;
}

//void enqueue2(const CQueue * queue1,const CItem * item){
	//queue4 *que1 = (queue4*)queue1;
	//data1 *n1 = (data1*)item;
	//que1->enqueue4((*n1));
	//queue1 = (CQueue *)que1;
	////return (CQueue *)que1;
//}


void enqueue_left(CQueue * queue1, unsigned char* i1, unsigned long size1){
	//image_lr *n1 = (image_lr *)item; //creating a item object
	queue4 *que1 = (queue4*)queue1; //creating a queue object
	//n1->setValue(i1,size1,i2,size2); //storing values in object
	//que1->enqueue4((*n1)); //storing the object to the queue
	que1->set_left_item(i1,size1);
	queue1 = (CQueue *)que1; //transfering the object back to its orginal status
	//item =  (CItem *)n1;  //transfering the object back to its orginal status
	}

void enqueue_right(CQueue * queue1, unsigned char* i2, unsigned long size2){
	//image_lr *n1 = (image_lr *)item; //creating a item object
	queue4 *que1 = (queue4*)queue1; //creating a queue object
	//n1->setValue(i1,size1,i2,size2); //storing values in object
	//que1->enqueue4((*n1)); //storing the object to the queue
	que1->set_right_item(i2,size2);
	queue1 = (CQueue *)que1; //transfering the object back to its orginal status
	//item =  (CItem *)n1;  //transfering the object back to its orginal status
	}

void enqueue2(CQueue * queue1, unsigned char* i1, unsigned char* i2, unsigned long size1, unsigned long size2){
	//image_lr *n1 = (image_lr *)item; //creating a item object
	queue4 *que1 = (queue4*)queue1; //creating a queue object
	//n1->setValue(i1,size1,i2,size2); //storing values in object
	//que1->enqueue4((*n1)); //storing the object to the queue
	que1->set_item(i1,size1,i2,size2);
	queue1 = (CQueue *)que1; //transfering the object back to its orginal status
	//item =  (CItem *)n1;  //transfering the object back to its orginal status
	}

void dequeue2(CQueue * queue1){
	queue4 *que1 = (queue4*)queue1;
	//data1 *n1 = (data1*)item;
	que1->dequeue4();
	//n1->reallocate_dequeue(); //removing the object
	//item = (CItem *)n1;
	queue1 = (CQueue *)que1;
	//return (CQueue *)que1;
}
int check_full(CQueue * queue1){
	int check = 0;
	queue4 *que1 = (queue4 *)queue1;
	check = que1->isfull();
	return check;
}


int check_empty(CQueue * queue1){
	int check = 0;
	queue4 *que1 = (queue4 *)queue1;
	check = que1->isempty();
	return check;
}

unsigned char *get_one_image(const CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	return que1->getValue_left();
	}

unsigned char *get_image_left(const CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	return que1->getValue_left();
	}

unsigned char *get_image_right(const CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	return que1->getValue_right();
	}
	
unsigned long get_num_left(const CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	return que1->getNum_left();
	}

unsigned long get_num_right(const CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	return que1->getNum_right();
	}

void save_image_(int width,int height,unsigned char* i1,char* input_name){
	save_image(width,height,i1,input_name);
	
}


//CItem * new_bayer(){
	
	
	//return (CItem *)image_item;
//}



void gpu_bayer_2(unsigned char* i1_l,unsigned char* i1_r,unsigned char* i2_l,unsigned char* i2_r,unsigned long size,int width, int height){
	gpu_bayer *image_item = new gpu_bayer();
	image_item->set_size(size, width,  height);
	image_item->add_two_image(i1_l,i1_r);
	image_item->gpu_bayerRG2();
    memcpy(i2_l,image_item->get_image_left(),size*3);
    memcpy(i2_r,image_item->get_image_right(),size*3);
	delete image_item;
	//return image_item->get_image();	
	}

void gpu_bayer_1(unsigned char* i1_1,unsigned char* i2_1,unsigned long size,int width, int height,int current_eye){
	gpu_bayer *image_item = new gpu_bayer();
	image_item->set_size(size, width,  height);
	image_item->add_one_image(i1_1);
	image_item->gpu_bayerRG1(current_eye+1); //current_eye+1
    memcpy(i2_1,image_item->get_one_image(),size*3);
    //memcpy(i2_r,image_item->get_image_right(),size*3); 
	delete image_item;
	}

void delete_queue(CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	delete que1;
}

void clean_queue(CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	que1->clean_queue4();
	queue1 = (CQueue *)que1; 
	
}

}
