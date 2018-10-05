#ifndef QUEUE_WRAPPER_H
#define QUEUE_WRAPPER_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef void CItem;
typedef void CNumber;
typedef void CQueue;


#ifdef __cplusplus
extern "C" {
#endif

/* Using number class of c++ */



CItem * new_item();
void set_item(CItem *item,unsigned char* i1, unsigned char* i2,unsigned long size1, unsigned long size2);
//void enqueue(const CQueue * queue1,const CItem *item, unsigned char* i1, unsigned char* i2, unsigned long size1, unsigned long size2);
unsigned char *get_item_left(const CItem *item);
unsigned char *get_item_right(const CItem *item);
unsigned long get_size_left(const CItem *item);
unsigned long get_size_right(const CItem *item);
void reallocate_dequeue(CItem *item);
void delete_item_image(CItem *item);
CQueue * new_queue();
//enqueue2(const CQueue * queue1,const CItem * item)
//void enqueue2(CQueue * queue1,const CItem * item);
//void dequeue2(CQueue * queue1,CItem * item);
//void enqueue2(const CQueue * queue1,const CItem * item);
void enqueue_left(CQueue * queue1, unsigned char* i1, unsigned long size1);
void enqueue_right(CQueue * queue1, unsigned char* i2, unsigned long size2);
void enqueue2(CQueue * queue1, unsigned char* i1, unsigned char* i2, unsigned long size1, unsigned long size2);
void dequeue2(CQueue * queue1);
//void enqueue3(CQueue * queue1,const CItem * item);
//void dequeue3( CQueue * queue1,CItem * item);

unsigned char *get_one_image(const CQueue * queue1);
unsigned char *get_image_left(const CQueue * queue1);
unsigned char *get_image_right(const CQueue * queue1);
unsigned long get_num_left(const CQueue * queue1);
unsigned long get_num_right(const CQueue * queue1);
void delete_queue(CQueue * queue1);
void clean_queue(CQueue * queue1);

int check_full(CQueue * queue1);
int check_empty(CQueue * queue1);

//void save_image_(unsigned char* i1);
//void save_image_(unsigned char* i1,char* input_name);
void save_image_(int width,int height,unsigned char* i1,char* input_name);
//unsigned char* gpu_bayer_(unsigned char* i1,unsigned long size,int width, int height);
void gpu_bayer_1(unsigned char* i1_1,unsigned char* i2_1,unsigned long size,int width, int height,int current_eye);
void gpu_bayer_2(unsigned char* i1_l,unsigned char* i1_r,unsigned char* i2_l,unsigned char* i2_r,unsigned long size,int width, int height);
//void delete_queue(CQueue * queue1);
/* Using queue class of c++ */


/*
CNumber * set_number(const CNumber *number,unsigned int i1, unsigned int i2);
unsigned int get_number_left(const CNumber *number);
unsigned int get_number_right(const CNumber *number);
void delete_number_image(CNumber *number);
*/
#ifdef __cplusplus
}
#endif



#endif
