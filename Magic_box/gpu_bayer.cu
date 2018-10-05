#include "image.h"
#include "gpu_bayer.h"
#include <iostream>
#include <stdio.h>

// includes CUDA Runtime
#include <cuda.h>
#include <cuda_runtime.h>

// raw to rgb increases the width by 3 
#define RGB_width 3 

//using namespace cv;

__global__  void bayerRG(const unsigned char *in, unsigned char* out,int w,int h){
    int x =  ((blockIdx.x*blockDim.x)+ threadIdx.x);
    int y =  ((blockIdx.y*blockDim.y)+ threadIdx.y);

    //unsigned char r,g,b;        
    // 'R'

 		
    if((x %2 == 0) && (y %2 == 0)) {
    	out[y*w*RGB_width+x*RGB_width+0] = (in[y*w + x]);  // r
		out[y*w*RGB_width+x*RGB_width+1] = (in[y*w + x+1]+in[(y+1)*w+x])/2; //g
		out[y*w*RGB_width+x*RGB_width+2] = (in[(y+1)*w +x +1]); //b
    }
    // x is odd and y is even
    else if((x %2 == 1) && (y %2 == 0)){
    
		out[y*w*RGB_width+x*RGB_width+0] = (in[y*w + x+1]); // r 
		out[y*w*RGB_width+x*RGB_width+1] = (in[y*w + x]+in[(y+1)*w+x+1])/2; // g
		out[y*w*RGB_width+x*RGB_width+2] = (in[(y+1)*w +x]); // b
    }
    // x is even and y is odd
    else if((x %2 == 0) && (y %2 == 1)){
    
		out[y*w*RGB_width+x*RGB_width+0] = (in[(y+1)*w + x]); //r 
		out[y*w*RGB_width+x*RGB_width+1] = (in[y*w + x]+in[(y+1)*w+x+1])/2; //g 
		out[y*w*RGB_width+x*RGB_width+2] = (in[y*w +x +1]); //b
    }
    // x is odd and y is odd
    else if((x %2 == 1) && (y %2 == 1)){
    
		out[y*w*RGB_width+x*RGB_width+0] = (in[(y+1)*w + x+1]); //r
		out[y*w*RGB_width+x*RGB_width+1] = (in[y*w + x+1]+in[(y+1)*w+x])/2; //g
		out[y*w*RGB_width+x*RGB_width+2] = (in[y*w +x]); // b
    }
    
    //out[y*w+x+0] = (in[y*w + x]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x])/2; //(in[(y+1)*w +x +1]);
	//out[y*w+x+2] = (in[(y+1)*w +x +1]);
    
    /* block1 part2*/
    //out[y*w+x+5] = (in[y*w + 2+x]); 
	//out[y*w+x+4] = (in[y*w + 2+x+1]+in[(y+1)*w+2+x])/2;
    //out[y*w+x+3] = (in[(y+1)*w +2+x +1]);
    
    /* block1 part3*/
    //out[(y+3)*w+x+2] = (in[(y+2)*w + x]); 
	//out[(y+3)*w+x+1] = (in[(y+2)*w + x+1]+in[(y+3)*w+x])/2;
    //out[(y+3)*w+x+0] = (in[(y+3)*w +x +1]);
    
    /* block1 part4*/
    //out[(y+3)*w+x+7] = (in[(y+2)*w +2+ x]); 
	//out[(y+3)*w+x+6] = (in[(y+2)*w +2+ x+1]+in[(y+3)*w+2+x])/2;
    //out[(y+3)*w+x+5] = (in[(y+3)*w +2+x +1]);
    
    /* block1 part5*/
    //out[y*w+x+2] = (in[y*w + x-657]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x]-657)/2;
    //out[y*w+x+0] = (in[(y+1)*w +x +1-657]);
    
    /* block1 part6*/
    //out[y*w+x+2] = (in[y*w + x-657]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x]-657)/2;
    //out[y*w+x+0] = (in[(y+1)*w +x +1-657]);
    
    /* block1 part7*/
    //out[y*w+x+2] = (in[y*w + x-657]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x]-657)/2;
    //out[y*w+x+0] = (in[(y+1)*w +x +1-657]);
    
    /* block1 part8*/
    //out[y*w+x+2] = (in[y*w + x-657]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x]-657)/2;
    //out[y*w+x+0] = (in[(y+1)*w +x +1-657]);
    
    /* block1 part9*/
    //out[y*w+x+2] = (in[y*w + x-657]); 
	//out[y*w+x+1] = (in[y*w + x+1]+in[(y+1)*w+x]-657)/2;
    //out[y*w+x+0] = (in[(y+1)*w +x +1-657]);
    
    
}

gpu_bayer::gpu_bayer() : size(0),width(0),height(0)
{
	d_in_l=0;
	d_out_l=0; //private variables
	input_l = 0;
	output_l = 0;
	d_in_r=0;
	d_out_r=0; //private variables
	input_r = 0;
	output_r = 0;

	}

gpu_bayer::~gpu_bayer()
{
	//std::cout << "running delete function" << std::endl;
	//[] indicates it is an array of memory otherwise use delete only
	delete[] input_l;  
	delete[] output_l;
	delete[] input_r;  
	delete[] output_r;

}

void gpu_bayer::add_one_image(unsigned char* in_1)
{
		input_l = (unsigned char*)malloc(width*height*1*sizeof(unsigned char)); 
		output_l = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
		memcpy(input_l,in_1,size); //copy image to memory
}

void gpu_bayer::add_two_image(unsigned char* in_l,unsigned char* in_r)
{
		input_l = (unsigned char*)malloc(width*height*1*sizeof(unsigned char)); 
		output_l = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
		input_r = (unsigned char*)malloc(width*height*1*sizeof(unsigned char)); 
		output_r = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
		memcpy(input_l,in_l,size); //copy image to memory
		memcpy(input_r,in_r,size); //copy image to memory
}

unsigned char* gpu_bayer::get_one_image()
{
return output_l;
}

unsigned char* gpu_bayer::get_image_left(){

return output_l;
}

unsigned char* gpu_bayer::get_image_right()
{
return output_r;
}

void gpu_bayer::gpu_bayerRG1(int set_GPU){

	/* allocate to GPU */
	cudaSetDevice(set_GPU);
	cudaMalloc((void **) &d_in_l, size);
	cudaMalloc((void **) &d_out_l, 3*size);
	//dim3 DimBlock(1,1); //20172 blocks 16 threads	
	//dim3 DimBlock(1,2);
	//dim3 DimBlock(2,2);  
	dim3 DimBlock(2,4); 
	
	//if(access_gpu1 == 1){
		//cudaSetDevice(set_GPU);
		//cudaDeviceEnablePeerAccess(0,0); 
	cudaSetDevice(set_GPU);
	cudaMemcpy(d_in_l, input_l, size, cudaMemcpyHostToDevice); //copy from Host to Device memory
		
	//dim3 DimBlock(16,12); //1681 blocks 192 threads
    //dim3 DimBlock(8,12); //3362 blocks 92 threads
	dim3 DimGrid(width/DimBlock.x,height/DimBlock.y); 
	
	cudaSetDevice(set_GPU);
	bayerRG<<<DimGrid,DimBlock>>>(d_in_l,d_out_l,width,height);
	
	cudaSetDevice(set_GPU); 
	cudaMemcpy(output_l, d_out_l, 3*size, cudaMemcpyDeviceToHost); //copy from Device to Host memory
		
	cudaThreadSynchronize();
	//}
	//else{
	
	//printf("no access\n");
	//}
	
	cudaSetDevice(set_GPU);
	cudaFree(d_in_l); 
	cudaFree(d_out_l); 
	
	/* free GPU memory */
	

    

}


void gpu_bayer::gpu_bayerRG2(){
	
	
	
	/* allocate to GPU */
	cudaSetDevice(1);
	cudaMalloc((void **) &d_in_l, size);
	cudaMalloc((void **) &d_out_l, 3*size);
	
	cudaSetDevice(2);
	cudaMalloc((void **) &d_in_r, size);
	cudaMalloc((void **) &d_out_r, 3*size);
	
	dim3 DimBlock(1,1); //20172 blocks 16 threads
	
	//if(access_gpu1 == 1){
		//cudaSetDevice(1);
		//cudaDeviceEnablePeerAccess(0,0); 
	cudaSetDevice(1);
	cudaMemcpy(d_in_l, input_l, size, cudaMemcpyHostToDevice); //copy from Host to Device memory
	
	cudaSetDevice(2);	
	cudaMemcpy(d_in_r, input_r, size, cudaMemcpyHostToDevice); //copy from Host to Device memory
	
	
	//dim3 DimBlock(16,12); //1681 blocks 192 threads
		//dim3 DimBlock(8,12); //3362 blocks 92 threads
	dim3 DimGrid(width/DimBlock.x,height/DimBlock.y); 
	
	cudaSetDevice(1);
	bayerRG<<<DimGrid,DimBlock>>>(d_in_l,d_out_l,width,height);
	
	cudaSetDevice(2);	
	bayerRG<<<DimGrid,DimBlock>>>(d_in_r,d_out_r,width,height); 
	
	cudaSetDevice(1); 
	cudaMemcpy(output_l, d_out_l, 3*size, cudaMemcpyDeviceToHost); //copy from Device to Host memory
	
	cudaSetDevice(2);
	cudaMemcpy(output_r, d_out_r, 3*size, cudaMemcpyDeviceToHost); //copy from Device to Host memory
	
	cudaThreadSynchronize();
	//}
	//else{
	
	//printf("no access\n");
	//}
	
	cudaSetDevice(1);
	cudaFree(d_in_l); 
	cudaFree(d_out_l); 
	
	cudaSetDevice(2);
	cudaFree(d_in_r); 
	cudaFree(d_out_r);
	
	/* free GPU memory */
	

    

}






