#ifndef IMAGE_LR_H
#define IMAGE_LR_H

//#include "image_numbers.hpp"

//typedef numbers_image data_size;

class image_lr
{
	enum { ARRAY_SIZE = 100 };
	private:
		int array_size; 
		const int array_size_max;
		unsigned long left_image_size;
		unsigned long right_image_size;
		unsigned char* left_image;
		unsigned char* right_image;
		
		
	public:
		/* constructor */
		image_lr(int array_size_set_ = ARRAY_SIZE);
		
		//copy constructor
		image_lr(const image_lr & image_item); //removes the implicit method definition
		
		//copy operator
		const image_lr & operator=(const image_lr & image_item);
		
		//image_lr(unsigned char* leftimage, unsigned char* rightimage,unsigned long size_left,unsigned long size_right);
		//image_lr(char leftimage, char rightimage,unsigned long size_left,unsigned long size_right);
		friend class queue4; //allows queue4 class to access the private members 
		
		/*destructor*/
		~image_lr();
		
		/*setters */ //applying the method overload technique
		void set_left_Value(unsigned char* left_image_1, unsigned long size_left);
		void set_right_Value(unsigned char* right_image_1, unsigned long size_right);
		void setValue(unsigned char* left_image_1, unsigned long size_left,unsigned char* right_image_1, unsigned long size_right);
		void set_item(unsigned char* left_image_1, unsigned long size_left,unsigned char* right_image_1, unsigned long size_right);
		//void setValue_left(char left_image_2, unsigned long size_left);
		//void setValue_right(char right_image_2, unsigned long size_right);
		//void setValue_left_unchar(unsigned char left_image_21,unsigned long size_left);
		//void setValue_right_unchar(unsigned char right_image_21,unsigned long size_right);
		//void setValue_left_char(char left_image_22,unsigned long size_left);
		//void setValue_right_char(char right_image_22,unsigned long size_right);
		void reallocate_dequeue();
				
		/*getters */
		unsigned char *getValue_left();
		unsigned char *getValue_right();
		unsigned long getValue_left_size();
		unsigned long getValue_right_size();
		unsigned char no_ptr_getValue_left();
		unsigned char no_ptr_getValue_right();
		unsigned long getSize_left() const;
		unsigned long getSize_right() const;
	
		inline int get_array_size() const {return array_size;}


};




#endif
