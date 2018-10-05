#ifndef GPU_BAYER_H
#define GPU_BAYER_H

#include <iostream>
#include <stdio.h>

// includes CUDA Runtime
#include <cuda.h>



class gpu_bayer
{
	private:
		unsigned char *d_in_l, *d_out_l; //private variables
		unsigned char *d_in_r, *d_out_r; //private variables
		unsigned char *input_l, *output_l;
		unsigned char *input_r, *output_r;
		unsigned long size;
		int width;
		int height;
	public:
		/*constructor */
			gpu_bayer();
			
		/*destructor */
			~gpu_bayer();
		
		/* methods */

		/*setters */
			inline void set_size(unsigned long size_,int width_,int height_)
			{
			size=size_;
			width=width_;
			height=height_;
			}
			void add_one_image(unsigned char* i1_1);
		    void add_two_image(unsigned char* in_l,unsigned char* in_r);
		/*getters */
			unsigned char* get_one_image();
			unsigned char* get_image_left();
			unsigned char* get_image_right();
		/*other methods */
		    void gpu_bayerRG1(int current_eye);
			void gpu_bayerRG2();
			
		   

};




#endif
