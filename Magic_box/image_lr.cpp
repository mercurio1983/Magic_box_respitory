#include <iostream>
using namespace std;
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <inttypes.h>
#include "bool1.h"
#include "image_lr.hpp"



image_lr::image_lr(int array_size_set_) : array_size_max(array_size_set_)
{
	left_image = 0; //(unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	right_image = 0 ;//(unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	//for (int i = 0; i < ARRAY_SIZE; i++){
	left_image_size = 0;
	right_image_size = 0;
	array_size = 0;
	
}

//image_lr::image_lr(unsigned char* leftimage, unsigned char* rightimage,unsigned long size_left,unsigned long size_right){
//	setValue_left(leftimage,size_left);
//	setValue_right(rightimage,size_right);
//}

//image_lr::image_lr(char leftimage, char rightimage,unsigned long size_left,unsigned long size_right){
//	setValue_left(leftimage,size_left);
//	setValue_right(rightimage,size_right);
//}

image_lr::~image_lr(){
	//left_image_size = 0;
	//right_image_size = 0;
	//free(left_image);
	//free(right_image);
	//cout << "running the destructor in item"<< endl;
	
	//free(left_image);
	//free( right_image);
	if(left_image != NULL){
	delete[] left_image;}
	if(right_image != NULL){
	delete[] right_image;}
	//left_image = NULL; //(unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	//right_image = NULL; //(unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	
	}


	
void image_lr::set_item(unsigned char* left_image_1, unsigned long size_left,unsigned char* right_image_1, unsigned long size_right){
	//left_image=left_image_21;
		unsigned char *left_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
		//unsigned char *left_image_temp = new uint8_t[array_size+1];
		//printf("test0%d array not equal zero\n",c++);
		unsigned char *right_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
		//unsigned char *right_image_temp = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//for (int i=0;i<(array_size);i++){
			//printf("test0%d\n",c++);
			memcpy(left_image_temp,left_image,(left_image_size)); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
			//printf("test0%d\n",c++);
			memcpy(right_image_temp,right_image,(right_image_size));
			
		//}
		//printf("test0%d\n",c++);
		delete[] left_image;
		//printf("test0%d\n",c++);
		delete[] right_image;
		//printf("test0%d\n",c++);
		//left_image_size[array_size] = size_left;
		//right_image_size[array_size] = size_right;
		memcpy(left_image_temp+0,left_image_1,left_image_size); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		memcpy(right_image_temp+0,right_image_1,right_image_size);
		//printf("test0%d\n",c++);
	 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
	
		left_image = &(*(left_image_temp+0)); //points to the address of left_image_temp
		//printf("test01\n");
		right_image = &(*(right_image_temp+0)); //points to the address of right_image_temp
		
	
	//memcpy(left_image[], left_image_1, left_image_size);
	}  //{this->setValue_left_unchar(left_image_1,size_left);}

void image_lr::set_left_Value(unsigned char* left_image_1, unsigned long size_left){
	//left_image=left_image_21;
	//left_image = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	//left_image = left_image_1;
	//printf("test0%d\n",c++);
	if(array_size == 0){
		//printf("test0%d array = 0\n",c++);
		left_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size+1));
		//left_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		
		//right_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//left_image_size = new unsigned long[array_size+1];
		//printf("test0%d\n",c++);
	    //right_image_size = new unsigned long[array_size+1];
	    //printf("test0%d\n",c++);
		
		//printf("left_image_size is %lu\n",size_left);
		left_image_size = size_left;
		//printf("test0%d\n",c++);
		
		//printf("left_image_size is now %lu\n",left_image_size[0]);
		//printf("test0%d\n",c++);
		memcpy(left_image+0,left_image_1,left_image_size); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		
		//printf("test0%d\n",c++);
		}
	else{
		unsigned char *left_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//unsigned char *left_image_temp = new uint8_t[array_size+1];
		//printf("test0%d array not equal zero\n",c++);
		
		//unsigned char *right_image_temp = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//for (int i=0;i<(array_size);i++){
			//printf("test0%d\n",c++);
			memcpy(left_image_temp,left_image,(left_image_size)*(array_size)); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
			//printf("test0%d\n",c++);
			
			
		//}
		//printf("test0%d\n",c++);
		delete[] left_image;
		//printf("test0%d\n",c++);
		
		//printf("test0%d\n",c++);
		//left_image_size[array_size] = size_left;
		//right_image_size[array_size] = size_right;
		memcpy(left_image_temp+(array_size)*3,left_image_1,left_image_size); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		
		//printf("test0%d\n",c++);
	 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
	
		left_image = &(*(left_image_temp+0)); //points to the address of left_image_temp
		//printf("test01\n");
		
	//printf("test01\n");
	}
	//array_size += 3;
	array_size= 1;
	//printf("test01\n");
	//memcpy(left_image_temp[array_size],left_image_1,size_left);
	//memcpy(right_image_temp[array_size],right_image_1,size_right);
	//left_image_size = size_left;
	//left_image_temp[size_of_array] = left_image_1;
	
	//memcpy(left_image[], left_image_1, left_image_size);
	}  //{this->setValue_left_unchar(left_image_1,size_left);}

void image_lr::set_right_Value(unsigned char* right_image_1, unsigned long size_right){
	//left_image=left_image_21;
	


	//left_image = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	//left_image = left_image_1;
	//printf("test0%d\n",c++);
	if(array_size == 0){
		//printf("test0%d array = 0\n",c++);
		
		//left_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		right_image = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//right_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//left_image_size = new unsigned long[array_size+1];
		//printf("test0%d\n",c++);
	    //right_image_size = new unsigned long[array_size+1];
	    //printf("test0%d\n",c++);
		
		//printf("left_image_size is %lu\n",size_left);
		
		//printf("test0%d\n",c++);
		right_image_size = size_right;
		//printf("left_image_size is now %lu\n",left_image_size[0]);
		//printf("test0%d\n",c++);
		 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		memcpy(right_image+0,right_image_1,right_image_size);
		//printf("test0%d\n",c++);
		}
	else{
		
		//unsigned char *left_image_temp = new uint8_t[array_size+1];
		//printf("test0%d array not equal zero\n",c++);
		unsigned char *right_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//unsigned char *right_image_temp = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//for (int i=0;i<(array_size);i++){
			//printf("test0%d\n",c++);
			
			//printf("test0%d\n",c++);
			memcpy(right_image_temp,right_image,(right_image_size)*(array_size));
			
		//}
		//printf("test0%d\n",c++);
		
		//printf("test0%d\n",c++);
		delete[] right_image;
		//printf("test0%d\n",c++);
		//left_image_size[array_size] = size_left;
		//right_image_size[array_size] = size_right;
		 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		memcpy(right_image_temp+(array_size)*3,right_image_1,right_image_size);
		//printf("test0%d\n",c++);
	 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
	
		
		//printf("test01\n");
		right_image = &(*(right_image_temp+0)); //points to the address of right_image_temp
	//printf("test01\n");
	}
	//array_size += 3;
	array_size= 1;
	//printf("test01\n");
	//memcpy(left_image_temp[array_size],left_image_1,size_left);
	//memcpy(right_image_temp[array_size],right_image_1,size_right);
	//left_image_size = size_left;
	//left_image_temp[size_of_array] = left_image_1;
	
	//memcpy(left_image[], left_image_1, left_image_size);
	}  //{this->setValue_left_unchar(left_image_1,size_left);}

void image_lr::setValue(unsigned char* left_image_1, unsigned long size_left,unsigned char* right_image_1, unsigned long size_right){
	//left_image=left_image_21;
	


	//left_image = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t));
	//left_image = left_image_1;
	//printf("test0%d\n",c++);
	if(array_size == 0){
		//printf("test0%d array = 0\n",c++);
		left_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size+1));
		//left_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		right_image = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//right_image = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//left_image_size = new unsigned long[array_size+1];
		//printf("test0%d\n",c++);
	    //right_image_size = new unsigned long[array_size+1];
	    //printf("test0%d\n",c++);
		
		//printf("left_image_size is %lu\n",size_left);
		left_image_size = size_left;
		//printf("test0%d\n",c++);
		right_image_size = size_right;
		//printf("left_image_size is now %lu\n",left_image_size[0]);
		//printf("test0%d\n",c++);
		memcpy(left_image+0,left_image_1,left_image_size); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		memcpy(right_image+0,right_image_1,right_image_size);
		//printf("test0%d\n",c++);
		}
	else{
		unsigned char *left_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//unsigned char *left_image_temp = new uint8_t[array_size+1];
		//printf("test0%d array not equal zero\n",c++);
		unsigned char *right_image_temp = (unsigned char*)malloc(640 * 480 * 3 * sizeof(uint16_t)*(array_size+1));
		//unsigned char *right_image_temp = new uint8_t[array_size+1];
		//printf("test0%d\n",c++);
		//for (int i=0;i<(array_size);i++){
			//printf("test0%d\n",c++);
			memcpy(left_image_temp,left_image,(left_image_size)*(array_size)); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
			//printf("test0%d\n",c++);
			memcpy(right_image_temp,right_image,(right_image_size)*(array_size));
			
		//}
		//printf("test0%d\n",c++);
		delete[] left_image;
		//printf("test0%d\n",c++);
		delete[] right_image;
		//printf("test0%d\n",c++);
		//left_image_size[array_size] = size_left;
		//right_image_size[array_size] = size_right;
		memcpy(left_image_temp+(array_size)*3,left_image_1,left_image_size); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//printf("test0%d\n",c++);
		memcpy(right_image_temp+(array_size)*3,right_image_1,right_image_size);
		//printf("test0%d\n",c++);
	 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
	
		left_image = &(*(left_image_temp+0)); //points to the address of left_image_temp
		//printf("test01\n");
		right_image = &(*(right_image_temp+0)); //points to the address of right_image_temp
	//printf("test01\n");
	}
	//array_size += 3;
	array_size= 1;
	//printf("test01\n");
	//memcpy(left_image_temp[array_size],left_image_1,size_left);
	//memcpy(right_image_temp[array_size],right_image_1,size_right);
	//left_image_size = size_left;
	//left_image_temp[size_of_array] = left_image_1;
	
	//memcpy(left_image[], left_image_1, left_image_size);
	}  //{this->setValue_left_unchar(left_image_1,size_left);}


//void image_lr::setValue_left(char left_image_2, unsigned long size_left) //{this->setValue_left_char(left_image_2,size_left);}
//void image_lr::setValue_right(char right_image_2, unsigned long size_right) //{this->setValue_right_char(right_image_2,size_right);}
/*
void image_lr::setValue_left_unchar(unsigned char *left_image_21,unsigned long size_left){
	//left_image=left_image_21;
	left_image_size = size_left;
	memcpy(left_image, left_image_21, left_image_size);
	}
void image_lr::setValue_right_unchar(unsigned char *right_image_21,unsigned long size_right){
	right_image_size = size_right;
	memcpy(right_image, right_image_21, right_image_size);
	//right_image=right_image_21;
	}
void image_lr::setValue_left_char(char *left_image_22,unsigned long size_left){
	left_image_size = size_left;
	memcpy( left_image, (unsigned char)left_image_22, left_image_size);	
	//left_image=(unsigned char)left_image_22;
}
void image_lr::setValue_right_char(char *right_image_22,unsigned long size_right){
	right_image_size = size_right;
	memcpy(right_image, (unsigned char)right_image_22, right_image_size);
	//right_image=(unsigned char)right_image_22;
}*/

	 unsigned char *image_lr::getValue_left(){return (left_image+0);}
	 unsigned char *image_lr::getValue_right(){return (right_image+0);}
		 //unsigned char image_lr::no_ptr_getValue_left(){return (left_image+0);}
		 //unsigned char image_lr::no_ptr_getValue_right(){return (right_image+0);}
	 unsigned long image_lr::getValue_left_size() {return left_image_size;}
	 unsigned long image_lr::getValue_right_size() {return right_image_size;}
     unsigned long image_lr::getSize_left() const {return left_image_size;}
	 unsigned long image_lr::getSize_right() const {return right_image_size;}
//these functions are critical for queue or stack function.
//copy constructor that allows one to set image item; in a class

image_lr::image_lr(const image_lr & image_item) :array_size_max(100) {
	
	array_size = image_item.get_array_size(); //right_image_size
	left_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size));
	right_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size));
	//for (int i = 0; i < ARRAY_SIZE; i++){
	//left_image_size[i] = 0;
	//right_image_size[i] = 0;}
	left_image_size = image_item.getSize_left();
	right_image_size = image_item.getSize_right();
	memcpy(left_image,image_item.left_image,(left_image_size)*(array_size));
	memcpy(right_image,image_item.right_image,(right_image_size)*(array_size));
	} //removes the implicit method definition left_image_size

//copy operator that allows copying objects such as item1 = item2; in a class
const image_lr & image_lr::operator=(const image_lr & image_item){
	
	if(this != &image_item){
	delete[] left_image;
	delete[] right_image;
	array_size = image_item.get_array_size();
	left_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size));
	right_image = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)*(array_size));
	left_image_size = image_item.getSize_left();
	right_image_size = image_item.getSize_right();
	//data = &(image_item);
	//data->getValue_left();
	
	memcpy(left_image,image_item.left_image,left_image_size*(array_size));
	memcpy(right_image,image_item.right_image,right_image_size*(array_size));
	}
	return *this;
	}

void image_lr::reallocate_dequeue(){
		
	if(array_size < 1){
		
	
		}
	else{
		unsigned char *left_image_temp = (unsigned char*)malloc(640*480*3*sizeof(uint16_t)*(array_size-1));
		unsigned char *right_image_temp = (unsigned char*)malloc(640*480*3*sizeof(uint16_t)*(array_size-1));
		//unsigned char *left_image_temp = new uint8_t[array_size-1];
		//unsigned char *right_image_temp = new uint8_t[array_size-1];
		//for (int i=1; i<(array_size);i++){
			memcpy((left_image_temp),(left_image+3),(left_image_size)*(array_size-1)); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
			memcpy((right_image_temp),(right_image+3),(right_image_size)*(array_size-1));
		//}
		delete[] left_image;
		delete[] right_image;
		//left_image_size[array_size] = size_left;
		//right_image_size[array_size] = size_right;
		//memcpy(left_image_temp[array_size],left_image_1,size_left); //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
		//memcpy(right_image_temp[array_size],right_image_1,size_right);
		
	 //to copy entire allocation //left_image_temp = left_image; //gets the address of left image
	
		left_image = &(*(left_image_temp+0)); //points to the address of left_image_temp
		right_image = &(*(right_image_temp+0)); //points to the address of right_image_temp
		
		array_size--;
	}
	
	
	
	}
