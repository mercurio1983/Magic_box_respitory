/*drawTexture
 * 1394-Based Digital Camera Display Program
 *
 * Written by Martti Mercurio
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <time.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>

#define _GNU_SOURCE_
#include <getopt.h>
#include <stdint.h>
#include <inttypes.h>
#include <libavutil/avutil.h>
//#include "queue2.h"
#include "nvstusb.h"
//#include <gsl/gsl_math.h> // Shuffle function
//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_randist.h>
//#include <gsl/gsl_rng.h>
/* SDL and OpenGL */

#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include <SDL.h>

#include <SDL_thread.h>

//#include "SDL_opengl.h"

//#include "tools.h"
#include "dc1394/dc1394.h"
//#include "globals.h"
//#include "displayvideo.h"

#include "rendering.h"
#include "queue_Wrapper.h"
#include "conversion.h"
#include "stereoviewGL_delay3D.h"

//#include "loadTexture.h"

/* OpenGL defs*/

//extern "C" {
    
//}
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/extensions/Xvlib.h>
//#include <X11/keysym.h>

/* uncomment the following to drop frames to prevent delays */
//#define MAX_PORTS   4uint16_t
#define MAX_CAMERAS 8
#define NUM_BUFFERS 8

#define NUM_Q 2

// ok the following constant should be by right included thru in Xvlib.h 
#ifndef XV_YV12
#define XV_YV12 0x32315659
#endif 

#ifndef XV_YUY2 
#define XV_YUY2 0x32595559
#endif

#ifndef XV_UYVY
#define XV_UYVY 0x59565955
#endif

//SDL_mutex *lock1;
//SDL_cond *cond1;
//SDL_mutex *lock2;
//SDL_cond *cond2;
//SDL_bool condition1 = SDL_FALSE;
//SDL_bool condition2 = SDL_FALSE;

//SDL_Thread* thread1;
//SDL_Thread* thread2;
//SDL_Thread* buffer_thread3;
//SDL_Thread* rendering_thread;

//dc1394video_frame_t * to_buffer[4];
//dc1394video_frame_t * from_buffer[4];
//dc1394video_frame_t * frames[MAX_CAMERAS];



//GLuint  g_texture[2]; /* Storage For Our Font Texture             */

void cleanup(uint32_t lnumCameras, dc1394camera_t **cam, char * fb, int i) {
  //int i;
  //for (i=0; i < lnumCameras; i++) {
  dc1394_video_set_transmission(cam[i], DC1394_OFF); // sets the current operation mode to OFF
  dc1394_capture_stop(cam[i]); 
  //}
  if (fb != NULL)
  free( fb );

}




/*int questions(int num, SDL_Surface* screen){

  int h = (screen->h)-20;
  switch(num){
  case 0:
    glColor3f( 1.0f , 1.0f , 1.0f );
    glPrintStereo(screen->w, screen->h, 0 , h,     "A. Right now I feel..", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-20,  "   1. Extremely dissatisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-40,  "   2. Mostly dissatisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-60,  "   3. Moderately dissatisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-80,  "   4. Slightly dissatisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-100, "   5. Neither dissatisfied nor satisfied with my physical", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-120, "      appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-140, "   6. Slightly satisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-160, "   7. Moderately satisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-180, "   8. Mostly satisfied with my physical appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-200, "   9. Extremely satisfied with my physical appearance", 0 );    
    break;
  case 1:
    glColor3f( 1.0f , 0.0f , 0.0f );
    glPrintStereo(screen->w, screen->h, 0 , h,     "B. Right now I feel..", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-20,  "   1. Extremely dissatisfied with my virtual appearance", 0 );
    glPrintStereo(screen->w, screen->h, 0 , h-40,  "   2. Mostly dissatisfied with my mental appearance", 0 );
    //  default:
      
  }

}*/

void open_questions(SDL_Surface* screen,char* filename){
	 
	char text[70];
	char questions_with_count[70];
	char matrix[30][70];
	int counter = 0;
	int index4=0;	
	int index5=0;
	FILE *input_file = NULL;  //declaring the infile for reading the textfile
	int w = ((screen->w)/2)-120;
	if(input_file=fopen(filename,"r")){
			for (index5=0;index5<70;index5++){
					 text[index5] = 0;
					
				}
		//}
		while(!feof(input_file)){
			//fscanf(input_file,"%s",&questions);
			//questions +=" " +string
			//caracter = fgetc(input_file);
			if(fgets(text,100,input_file) != NULL){
					glPrintStereo(screen->w, screen->h, w-counter , (screen->h)/7, text, 0 );
				counter += 40;	
			}
		}
		fclose(input_file);
	}
}	

int main(int argc, char *argv[])
{
  //enabling threads in SDL 
  //in total there exist 4 threads
  XInitThreads();
  
  //creating struct for rendering parameters
  rendering *render;
  render = av_mallocz(sizeof(rendering));
  
  //Null all rendering parameters
  render->zoom = 0;
  render->move_image = 0;
  render->move_image2 = 0;
  render->frame_enable = 0;
  render->frame_zoom = 0;
  render->frame_height = 0;
  render->frame_width = 0;
  render->frame_move = 0;
  render->flip_horizontal = 0;
  render->flip_vertical = 0;
  render->rotate = 0;
  
  portion = 0.5;
  //bayer_setting = atoi(argv[1]); //0 indicates camera rgb conversion, 1 indicates gpu_bayer rgb and 2 dc1394 bayer rgb
  printf("bayer_setting %d \n",bayer_setting);
  Cameras_set = 0; // 0 indicates it is F031C Guppy Pro. 1 indicates stingray F046C
  
  //default settings for Guppy Pro this computer is not set for Stingray F046C
  Cameras_set = 0; // 0 indicates it is F031C Guppy Pro. 1 indicates stingray F046C
  bayer_setting = 1; //0 indicates camera rgb conversion, 1 indicates gpu_bayer rgb and 2 dc1394 bayer rgb
  fullscreen = 1; //set to fullscreen
  //if (argc > 2){
		//Cameras_set = atoi(argv[2]); // 0 indicates it is F031C Guppy Pro. 1 indicates stingray F046C
		
		//fullscreen = atoi(argv[3]);
	//}
  //else{
	  
	  //return 1;
	  //}
  
    
  //28 ms consist of zero delay and total bias consist of 80 ms thus system bias is 80 - 27
  system_bias=(total_bias - 28); // the intrinsic delay subracted by computational delay
 
  gettimeofday(&begin_time, NULL);
  //gettimeofday(&end_time, NULL);
  //unsigned long elapsed_microseconds=((unsigned long)end_time.tv_usec-(unsigned long)begin_time.tv_usec);

 
//  unsigned int step_size = 33; //step size

	

	/////////////////////////////////////////////////////////////////	
    //***************** Loading paradigm parameters ***************//
    /////////////////////////////////////////////////////////////////
	//An important variable to initialize the trial
    trial_mode = 0;	//trial mode to default as OFF


if (argc > 4){
	
	induction_time = (unsigned int)atoi(argv[1]); //step size
	stop_signal_time = (unsigned int)atoi(argv[2]);  //delay enabled or disabled
	test_movement_time = (unsigned int)atoi(argv[3]);  //the duration
	black_screen_time = (unsigned int)atoi(argv[4]);  //number of loops
	trial_mode = 1; //when GUI calls program trial mode is ON
	
  } 
  else if(argc <4){
	
	////To test the system  
	//induction_time = 1; //step size
	//stop_signal_time = 1;  //delay enabled or disabled
	//test_movement_time = 1;  //the duration
	//black_screen_time = 1;  //number of loops
	//trial_mode = 1; //when GUI calls program trial mode is ON  

  }
  number_of_loops = 0;  //the control for the number of frames that is going to be placed in the queue

  
 

  //increment_step = floor(((double)step_size)/sys_time); //compute the number of steps to take
  //fpos_t *read_pose;
 
    
    

	
	/////////////////////////////////////////////////////////////////	
    //***************** Loading rendering parameters **************//
    /////////////////////////////////////////////////////////////////
    //parameters are set in header file
	if(infile=fopen("save.txt","r")){ //first need to create and overwrite
	//while(!feof(infile)){
		fscanf(infile,"%f\n",&zoom);
		fscanf(infile,"%f\n",&move_image);
		fscanf(infile,"%f\n",&move_image2);
		fscanf(infile,"%d\n",&frame_enable);
		fscanf(infile,"%f\n",&frame_zoom);
		fscanf(infile,"%f\n",&frame_height);
		fscanf(infile,"%f\n",&frame_width);
		fscanf(infile,"%f\n",&frame_move);
		fscanf(infile,"%f\n",&flip_horizontal);
		fscanf(infile,"%f\n",&flip_vertical);
		fscanf(infile,"%f\n",&rotate);
	//}
	fclose(infile);}
	
	/////////////////////////////////////////////////////////////////	
    //***************** trial mode file parameters ****************//
    /////////////////////////////////////////////////////////////////
	
	if(trial_mode == 1){
		if(infile=fopen("trial.txt","r")){ //first need to create and overwrite
			//while(!feof(infile)){
			int j_index;
			for (j_index= 0;j_index<100;j_index++){
				trial_number[j_index] = 0;
				add_frames_number[j_index] = 0;
				displacement[j_index] = 0;
				trial_key_set[j_index] = 9;
			}
			char text[30];
			fscanf(infile,"%s",&text);
			printf("%s ",text);
			fscanf(infile,"%s",&text);	
			printf("%s",text);
			fscanf(infile,"%s\n",&text);	
			printf("%s\n",text);
			number_of_loops = 0;
			while(!feof(infile)){
				fscanf(infile,"%d",&trial_number[number_of_loops]);
				fscanf(infile,"%d",&add_frames_number[number_of_loops]);
				fscanf(infile,"%d\n",&displacement[number_of_loops]);
				number_of_loops += 1; //count the number of rows in the file
			}
			fclose(infile);
		}
	} 
	
  previous = delay_on;  
  
  
  
  //printf("%d\n",increment_step);

  
  
  // initialize communications with the usb emitter
    nv_ctx = nvstusb_init();
    if (nv_ctx == NULL) {
        fprintf(stderr, "Could not initialize NVIDIA 3D Vision IR emitter!\n");
        exit(0);
    }
  
  ConfigRefreshRate(nv_ctx);
  
  
  
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  printf("initiating mutex\n");
  
  lock1 = SDL_CreateMutex();
  cond1 = SDL_CreateCond();
  
  lock2 = SDL_CreateMutex();
  cond2 = SDL_CreateCond();
  printf("initiating camera\n");
  
  printf("initiating main thread\n");
  
  /////////////////////////////////////////////////////////////////	
  //********************** Running threads **********************//
  /////////////////////////////////////////////////////////////////
  
  image_storage_left = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_storage_right = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  thread1 = SDL_CreateThread(run_camera, "camera1"); //execute one camera thread1
  while(!condition1){printf("waiting1\n");}
  condition1 = SDL_FALSE;
  thread2 = SDL_CreateThread(run_camera, "camera2"); //execute one camera thread2
  while(!condition1){printf("waiting2\n");}
  //in main thread there exist another create thread that is the keyboard thread
  thread3 = SDL_CreateThread(main_thread,render); //execute one main thread3 
  
  //thread4 = SDL_CreateThread(keyboard_thread, "keyboard_thread");
  
  /////////////////////////////////////////////////////////////////	
  //********************* Wait for threads **********************//
  /////////////////////////////////////////////////////////////////
    
  
  
  SDL_WaitThread(thread3, NULL);
  
  stop_flag = 1;
  
  SDL_WaitThread(thread4, NULL);
  
  /////////////////////////////////////////////////////////////////	
  //********************* Clean up conditions********************//
  /////////////////////////////////////////////////////////////////
  
  //SDL_WaitThread(thread1, NULL);
  //SDL_WaitThread(thread2, NULL);
  
  SDL_KillThread(thread1);
  //SDL_KillThread(thread2);
  
  printf("cleaning upp cameras\n");
  dc1394_video_set_transmission(cameras[0], DC1394_OFF); // sets the current operation mode to OFF
  dc1394_capture_stop(cameras[0]); 
  dc1394_video_set_transmission(cameras[1], DC1394_OFF); // sets the current operation mode to OFF
  dc1394_capture_stop(cameras[1]); 
  if (lfb != NULL){free( lfb );}
  
  //cleanup(2,cameras,lfb, 0);
  //cleanup(2,cameras,lfb, 1);

  //SDL_KillThread(thread1);
  //SDL_KillThread(thread2);
  SDL_DestroyMutex(lock1);       
  SDL_DestroyMutex(lock2); 
  SDL_DestroyCond(cond2); 
  
  ////////////////////////////////////////////////////////////////	
  //***************** store rendering parameters ****************//
  ///////////////////////////////////////////////////////////////// 		
  
  outfile=fopen("save.txt","w"); //second need to read from the respective file
  fprintf(outfile,"%f\n",zoom);
  fprintf(outfile,"%f\n",move_image);
  fprintf(outfile,"%f\n",move_image2);
  fprintf(outfile,"%d\n",frame_enable);
  fprintf(outfile,"%f\n",frame_zoom);
  fprintf(outfile,"%f\n",frame_height);
  fprintf(outfile,"%f\n",frame_width);
  fprintf(outfile,"%f\n",frame_move);
  fprintf(outfile,"%f\n",flip_horizontal);
  fprintf(outfile,"%f\n",flip_vertical);
  fprintf(outfile,"%f\n",rotate);
  fclose(outfile);
  
  
  
  av_free(render);
  SDL_Quit();
  return 0;             /* ANSI C requires main to return int. */

}

 /////////////////////////////////////////////////////////////////	
 //******************* main function ***************************//
 /////////////////////////////////////////////////////////////////

 int main_thread(void *arg){
	 
  rendering *render = (rendering*)arg;	 
  int count_even = 2; //set to 2 for none of the used numbers
  int counting_passes = 0;
  printf("pass %d", ++counting_passes); //1 to check if the code passes through 1
  printf("initiating main thread\n");
  
  queue1 = new_queue();
  
 
  
  printf("pass %d", ++counting_passes); //2 to check if the code passes through 2
  SDL_Surface *screen;
  printf("pass %d", ++counting_passes); //3 to check if the code passes through 3
  //condition2 = SDL_TRUE;
  printf("pass %d", ++counting_passes); //4 to check if the code passes through 4
  //if (numCameras == 4){width = device_width *2;}
 // else{width=device_width*1;} //numCameras
  
  /////////////////////////////////////////////////////////////////	
  //******************* Setting up screen ***********************//
  /////////////////////////////////////////////////////////////////
  
  width=device_width*1;
  height=device_height;
  height2 = height*1024/device_height; //cancel original height and replace it with new height
  //height3 = height*900/580; //cancel original height and replace it with new height
  
  
  //for the resolutio of 640x480
  width4 = width*(640)/(388*2); //=388; //640; //1920x1080 //640x480
  height4 = height*480/290; //=290;//480;
  
  //for the resolution of 640x480 from 1280x1024
  width5 = width*1920/device_width; //640
  height5 = height*1080/device_height;
   
  printf("running subfunction\n");
  
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // Enable swap buffer for GL *new* 
  printf("pass %d", ++counting_passes); //5
  fullscreen = 1;
  if(fullscreen == 1){
		screen = SDL_SetVideoMode(width5, height5, 8, SDL_OPENGL|SDL_FULLSCREEN| SDL_HWACCEL );
		}
	else if(fullscreen == 0){
		screen = SDL_SetVideoMode(width5, height5, 8, SDL_OPENGL|SDL_RESIZABLE| SDL_HWACCEL );
		}
  
  //screen = SDL_SetVideoMode(1920, 1080, 16, SDL_OPENGL|SDL_RESIZABLE| SDL_HWACCEL ); 
  
  if ( ! screen ) {
    fprintf(stderr, "Couldn't set 640x480 GL video mode: %s\n", SDL_GetError());
    SDL_Quit(); 
    exit(2); 
  }
  SDL_WM_SetCaption("Gears", "gears");
  printf("pass %d", ++counting_passes); //6
  SDLinit(screen->w, screen->h);
  initTexture(video_texture,2); //initTexture(video_texture,2);
  reshape(screen->w, screen->h);
  done = 0;
  printf("pass %d\n", ++counting_passes); //7
  //initTexture(video_texture,4); //initTexture(video_texture,2);
  printf("passed subfunction\n");
  
  //start the keyboard thread

  if((bayer_setting == 1) || (bayer_setting == 2)){
	//fps = DC1394_FRAMERATE_MAX;
	//fps = DC1394_FRAMERATE_120;
	if(Cameras_set == 1){
		device_width=780; //640; //1920x1080 //640x480
		device_height=580;//480;	
		}
	else{
	device_width = 656;
	device_height = 492;
	}
  }
  else{
	  device_width=640;
	  device_height=480;
	  }
  
  /////////////////////////////////////////////////////////////////	
  //********* The allocating memory for image variables *********//
  /////////////////////////////////////////////////////////////////
  image_load_left = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_load_right = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_left = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_right= (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)); // uint16_t *rgbBuffer = malloc(w * h * 3); 
  image_left1 = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_right1= (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)); // uint16_t *rgbBuffer = malloc(w * h * 3); 
 
  image_left2 = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)); //(unsigned char*)malloc(sizeof(unsigned char)); //(unsigned char*)malloc(sizeof(unsigned char));
  image_right2= (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t)); //(unsigned char*)malloc(sizeof(unsigned char)); //(unsigned char*)malloc(sizeof(unsigned char));
  value_size_left1 = (unsigned long*)malloc(sizeof(uint16_t));
  value_size_right1 = (unsigned long*)malloc(sizeof(uint16_t));
 
  //unsigned int pwidth, pheight;
  //uint64_t numPixels = pheight * pwidth;
    
  //uint8_t *rgb_image1 = (uint8_t *)malloc(3*numPixels);
  rgb_image1 = (uint8_t *)malloc(3*device_width*device_height);
  rgb_image2 = (uint8_t *)malloc(3*device_width*device_height);
  image_rgb1 = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  image_rgb2 = (unsigned char*)malloc(640 * 480 * 3*sizeof(uint16_t));
  printf("starting keyboard thread\n");
  thread4 = SDL_CreateThread(keyboard_thread, "keyboard_thread");
  image_counter = 0; 
  int fill_queue = 0;
  current_eye = 0; //current_eye = 0
  SDL_Event event;
  choose12 = 1;
  
  while ( ! done ) {
	
	//global variables for control from keyboard thread and 
	//overwritting the struct since there is so many parameters to send 
	render->zoom=zoom; 
    render->move_image=move_image;
    render->move_image2=move_image2;
    render->frame_enable=frame_enable;
    render->frame_zoom=frame_zoom;
    render->frame_height=frame_height;
    render->frame_width=frame_width;
    render->frame_move=frame_move;
    render->flip_horizontal=flip_horizontal;
    render->flip_vertical=flip_vertical;
    render->rotate=rotate;  
	SDL_LockMutex(lock1);
    
  
  /////////////////////////////////////////////////////////////////	
  //************** Running SDL condition threads ****************//
  /////////////////////////////////////////////////////////////////
		if(current_eye == 0){
			SDL_CondSignal(cond1); //sent condition signal to camera thread1
			SDL_CondWait(cond1,lock1); //waiting for condition signal from camera thread1
			memcpy(image_load_right,image_storage_right,bytes_storage_right); //copied frames from camera thread1
			image_size = bytes_storage_right;
		}
		else if(current_eye == 1){
			SDL_CondSignal(cond2); //sent condition signal to camera thread2
			SDL_CondWait(cond2,lock1); //waiting for condition signal from camera thread2
			memcpy(image_load_left,image_storage_left,bytes_storage_left); //copied frames from camera thread2
			image_size = bytes_storage_left;	
			}
		
		//condition1 = SDL_FALSE;
		//condition2 = SDL_TRUE;
		
	
	//printf("passed lock2\n");
    gettimeofday(&end_time, NULL);
	negative_value = elapsed_time_func(&result_time,&end_time,&begin_time);	
	gettimeofday(&begin_time, NULL);
    
    //dc1394_get_image_size_from_video_mode(cameras[2],DC1394_VIDEO_MODE_640x480_YUV422,&pwidth,&pheight);
    //uint64_t numPixels = pheight * pwidth;
    //if(manual_sync == 1){
		//gettimeofday(&begin_delay, NULL);
		//result_delay.tv_usec = 0;
    //while(delay_frame > (result_delay.tv_usec)){
		
		//gettimeofday(&end_delay, NULL);
		//negative_value_2 = elapsed_time_func(&result_delay,&end_delay,&begin_delay);	
		
	//}
	//printf("the delay sync is %lu\n",result_delay.tv_usec);
	//}
    /////////////////////////////////////////////////////////////////	
	//* Running GPU image bayer converter from Raw8 to RGB8 *******//
	/////////////////////////////////////////////////////////////////
	if(bayer_setting == 1){
		if(numCameras < 2){
			//gpu_bayer_(frames[0]->image,rgb_image1,frames[0]->image_bytes,device_width,device_height);
			if(current_eye == 0){
				gpu_bayer_1(image_load_right,rgb_image2,image_size,device_width,device_height,current_eye);}
			else if(current_eye == 1){
				gpu_bayer_1(image_load_left,rgb_image1,image_size,device_width,device_height,current_eye);}	
			
			//gpu_bayer_2(frames[0]->image,rgb_image1,frames[0]->image_bytes,device_width,device_height,current_eye);
		}
	else{
			if(current_eye == 0){
				gpu_bayer_1(image_load_right,rgb_image2,image_size,device_width,device_height,current_eye);}
			else if(current_eye == 1){
				gpu_bayer_1(image_load_left,rgb_image1,image_size,device_width,device_height,current_eye);}
			//gpu_bayer_2(frames[0]->image,rgb_image1,frames[0]->image_bytes,device_width,device_height);
			//gpu_bayer_(frames[1]->image,rgb_image2,frames[1]->image_bytes,device_width,device_height);
		}
	}
	else if(bayer_setting == 2){
		if(numCameras < 2){
			//dc1394_bayer_decoding_8bit(image_load,rgb_image1,device_width,device_height,DC1394_COLOR_FILTER_RGGB,DC1394_BAYER_METHOD_SIMPLE); //NEREAST
			//dc1394_bayer_decoding_8bit(image_load,rgb_image2,device_width,device_height,DC1394_COLOR_FILTER_RGGB,DC1394_BAYER_METHOD_SIMPLE);//SIMPLE);	
		}
		else{
			//dc1394_bayer_decoding_8bit(image_load,rgb_image1,device_width,device_height,DC1394_COLOR_FILTER_RGGB,DC1394_BAYER_METHOD_SIMPLE); //NEREAST
			//dc1394_bayer_decoding_8bit(image_load,rgb_image2,device_width,device_height,DC1394_COLOR_FILTER_RGGB,DC1394_BAYER_METHOD_SIMPLE);//SIMPLE);
			}
	
	}
	
	
	
    elapsed_ms_add1 += (unsigned int)(result_time.tv_usec);
    elapsed_s_add2 += (unsigned int)(result_time.tv_sec);
   // elapsed_microseconds = 0;
	printf("milliseconds %lu and seconds %lu and number of frames %d ",result_time.tv_usec/1000,result_time.tv_sec,image_counter );
	
	if(result_time.tv_usec/1000 == 0){add_frames = 1;} //to avoid errors like setting the denominator zero
			
			else{			
			
			//add frames to the queue	
			//add_frames = delay_on/((unsigned int)result_time.tv_usec/1000);	//compute the number of frames to add
			//add_frames = (unsigned int)floor(((double)delay_on)/(sys_time));	//compute the number of frames to add
			//if((delay_on > 2000) && (!shift_delay)) {
				//add_frames = (unsigned int)floor(((double)delay_on-90)/(27.1029));	//compute the number of frames to add
		    //}
			//else 
			if (trial_mode == 1){
				add_frames = add_frames_number[loop];
			}
			else if(trial_mode == 0){	
				//if (delay_on >= 50){
					////add_frames = (unsigned int)floor(((double)delay_on-95.63)/(23.1029));	//compute the number of frames to add
					////add_frames = (unsigned int)floor(((double)delay_on-45)/(16.7));	//compute the number of frames to add
					////add_frames = (unsigned int)floor(((double)delay_on-33.4382)/(14.0836));	//compute the number of frames to add
					//add_frames = (unsigned int)round(((double)delay_on*0.0727)-(3.0586)); // a function to correct the delay
					////add_frames = (unsigned int)(((double)delay_on*2)/100-1)*3+0;
				//}
				//else{add_frames = 0;}
			}
			//compute the milliseconds for each incrementation for phase B
			//computed_increment = (int)floor((double)(increment_time*1000)/(double)add_frames); 
			//if (computed_increment == 0){computed_increment = 1;} // to avoid errors
			}
			
	printf("and number of frames to add is %u and the delay is on %u\n",add_frames,delay_on);
	//printf("milliseconds %lu and seconds %lu\n",elapsed_ms_add1/1000,elapsed_s_add2);

	//}
    if( drawVideo == 1)
     {
	
	/////////////////////////////////////////////////////////////////	
	//********** The automated sequence for running the GUI *******//
	/////////////////////////////////////////////////////////////////
	
	if ((trial_mode == 1) && (done == 0)){
	//Make use of binary 0 0 0 sequence of numbers are 1 1 1 that is 9 different choices
	//edit the flip_horizontal for displacement directly
	flip_horizontal=displacement[loop];
	render->flip_horizontal=displacement[loop];
	//Sequence1 start part A
	
	if (((!flag_1) && (!flag_2)) && (!flag_3)){
		 gettimeofday(&begin_induction, NULL);	 //To set different flags after each sequence
		 flag_3 = 1; //next binary 0 0 1
		 flag_2 = 0;
		 flag_1 = 0;
		 //queue1 = new_queue();	
	} //Sequence2 measure time of part A in seconds
	else if(((!flag_1) && (!flag_2)) && flag_3){
		 gettimeofday(&end_induction, NULL);	 //To set different flags after each sequence
		 elapsed_time_func(&sequence_time,&end_induction,&begin_induction);
		 elapsed_induction = (unsigned int)sequence_time.tv_sec;
		 //printf("induction phase A\n");
		 //printf("induction time is %u \n",elapsed_induction);
		 if((induction_time) <= elapsed_induction){
			flag_3 = 0; //next binary 0 1 0 if the initial time has past
			flag_2 = 1;
			flag_1 = 0;
		 }
	} //Sequence3 start part B
	else if(((!flag_1) && (flag_2)) && (!flag_3)){
			gettimeofday(&begin_stop_signal,NULL);   //To set different flags after each sequence
			flag_3 = 1; //next binary 0 1 1
			flag_2 = 1;
			flag_1 = 0;
	} //Sequence4 measure time of part B in seconds
	else if(((!flag_1) && (flag_2)) && (flag_3)){
		 gettimeofday(&end_stop_signal, NULL);	 //To set different flags after each sequence
		 elapsed_time_func(&sequence_time,&end_stop_signal,&begin_stop_signal);
		 elapsed_stop_signal = (unsigned int)sequence_time.tv_sec;
		 //printf("stop time phase B\n");
		 //printf("stop time is %u \n",elapsed_stop_signal);
		 if((stop_signal_time) <= elapsed_stop_signal){
			flag_3 = 0; //next binary 1 0 0
			flag_2 = 0;
			flag_1 = 1;
		 }
	} //Sequence5 start part C
	else if(((flag_1) && (!flag_2)) && (!flag_3)){
			gettimeofday(&begin_test_movement, NULL);   //To set different flags after each sequence
			flag_3 = 1; //next binary 1 0 1
			flag_2 = 0;
			flag_1 = 1;
	} //Sequence6 measure time of part C in seconds
	else if(((flag_1) && (!flag_2)) && flag_3){
		 gettimeofday(&end_test_movement, NULL);	 //To set different flags after each sequence
		 elapsed_time_func(&sequence_time,&end_test_movement,&begin_test_movement);
		 elapsed_test_movement = (unsigned int)sequence_time.tv_sec;
		 //printf("test movement phase C\n");
		 //printf("test movement time is %u \n",elapsed_test_movement);
		 if((test_movement_time) <= elapsed_test_movement){
			flag_3 = 0; //next binary 1 1 0
			flag_2 = 1;
			flag_1 = 1;
		 }
	} //Sequence7 start part D
	else if(((flag_1) && (flag_2)) && (!flag_3)){
		gettimeofday(&begin_black_screen, NULL);     //To set different flags after each sequence
		flag_1 = 1;
		flag_2 = 1; 
		flag_3 = 1; 	
		} //Sequence8 measure time in part D in seconds	
	else if(((flag_1) && (flag_2)) && flag_3){
		gettimeofday(&end_black_screen, NULL);	 //To set different flags after each sequence
		elapsed_time_func(&sequence_time,&end_black_screen,&begin_black_screen);
		elapsed_black_screen = (unsigned int)sequence_time.tv_sec;
		//printf("black screen phase D\n");
		//printf("black screen time is %u \n",elapsed_black_screen);
		if((black_screen_time) <= elapsed_black_screen){ 
			loop++;
			flip_horizontal=displacement[loop];
			render->flip_horizontal=displacement[loop];
			if (loop == (number_of_loops)){
			done = 1;
			//delay_enable = 0; //to disable the automation
			}
			else{
				flag_1 = 0; //do another loop again. Begin at the beginning again
				flag_2 = 0; 
				flag_3 = 0;
				start_flag2 = 0;
				KillFont(); 
				clean_queue(queue1); //clean queue such that it is empty
				image_counter = 0; //set image counter to zero
				fill_queue = 0; //queue flag do not draw if queue is empty
				//SDL_Delay(1000); //wait 1000ms
				count_increment = 1; //reset
				} 
		
			}
		}
	//printf("number of loops is %d and last loop is %d\n",loop-1,(number_of_loops-1));
	}
		 
	if(((choose12 == 0) && (!trial_mode)) || ((((flag_1) && (!flag_2)) && (trial_mode == 1)) && (!done))) {
	//if(((choose12 == 0) && (!delay_enable)) || ( && delay_enable)) && {		
			

				
			//printf("%d\n",count_loops);
			
			/////////////////////////////////////////////////////////////////	
			//********************* enqueue the images ********************//
			/////////////////////////////////////////////////////////////////

				if (switch_camera == 1){
				
					//enqueue(queue1, frames[2]->image, frames[3]->image,frames[2]->image_bytes,frames[3]->image_bytes);
					//image_counter++;
				}
				else if(add_frames > 0){
					if(numCameras < 2){
						if((bayer_setting == 1) || (bayer_setting == 2)){
							if(current_eye == 0){
								count_even = 1; 
								//enqueue_right(queue1, rgb_image1,image_size*3);
							}
							else if((current_eye == 1) && (count_even == 1)){
								//enqueue2(queue1, rgb_image1,image_size*3);
								enqueue2(queue1,rgb_image1,rgb_image2,image_size*3,image_size*3);
								//if(image_counter > 1){
								fill_queue = 1;
								//}
								count_even = 0; 
							}
						}
						else{
							if(current_eye == 0){
								//enqueue_right(queue1, image_load,image_size);
								count_even = 1; 
								}
							else if((current_eye == 1) && (count_even == 1)){
								//enqueue2(queue1, image_load,image_size);
								enqueue2(queue1,image_load_left,image_load_right,image_size,image_size);	
								fill_queue = 1;
								count_even = 0;
								}						
							}
					}
					else{
						if((bayer_setting == 1) || (bayer_setting == 2)){
							if(current_eye == 0){
								count_even = 1; 
								//enqueue_right(queue1, rgb_image1,image_size*3);
							}
							else if((current_eye == 1) && (count_even == 1)){
								enqueue2(queue1,rgb_image1,rgb_image2,image_size*3,image_size*3);
								//enqueue2(queue1, rgb_image1,image_size*3);
								fill_queue = 1;
								count_even = 0;
								}
						}
						else{
							if(current_eye == 0){
								count_even = 1;
								//enqueue_right(queue1, image_load,image_size);
								}
							else if((current_eye == 1) && (count_even == 1)){
								enqueue2(queue1,image_load_left,image_load_right,image_size,image_size);
								fill_queue = 1;
								//enqueue2(queue1, image_load,image_size);	
								count_even = 0;
								}
						}
						}	
					//
					//enqueue(queue1, frames[0]->image, frames[1]->image,frames[0]->image_bytes,frames[1]->image_bytes);
					
					//printf("test1\n");
					//enqueue(queue1, rgb_image1, rgb_image2,frames[0]->image_bytes,frames[1]->image_bytes);
					//printf("test1_passed\n");
					if((current_eye == 1) && (count_even == 0)){
					image_counter++;}	
				}
				
			
			
			if((fill_queue == 1)){ // && (image_counter > (add_frames))){
			//if(image_counter == add_frames){
			//printf("test display\n");
			if (frame_enable == 1){
				
				if(current_eye == 1){
					//void drawTexture_eye3_frame(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render);
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), render);
				}
					//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);}
				else if(current_eye == 0){
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_right(queue1), render);
					//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_right(queue1), rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);
					}
				//drawTexture_with_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), get_image_right(queue1), 1,zoom, frame_zoom, frame_width, frame_height, frame_move, move_image);
				}
			else {
				if(current_eye == 1){
					drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), render);}
				else if(current_eye == 0) {
					drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_right(queue1), render);
					}
				}
			if((!flag_1) && (flag_2) && (trial_mode == 1)){
				draw_point(screen->w, screen->h,frame_zoom, frame_width, frame_height,frame_move);
			}
			}
			else if(add_frames == 0){
				if (frame_enable == 1){
				
				if(current_eye == 1){
					//void drawTexture_eye3_frame(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render);
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image1, render);
				}
					//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);}
				else if(current_eye == 0){
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image2, render);
					//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_right(queue1), rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);
					}
				//drawTexture_with_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, get_image_left(queue1), get_image_right(queue1), 1,zoom, frame_zoom, frame_width, frame_height, frame_move, move_image);
				}
			else {
				if(current_eye == 1){
					drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image1, render);}
				else if(current_eye == 0) {
					drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image2, render);
					}
				}
			
			}
			/////////////////////////////////////////////////////////////////	
			//************* commented reallocate frame code ***************//
			/////////////////////////////////////////////////////////////////
			//if the reference for the number of frames that is the control is minimized then start removing images 			
			//if ((!delay_enable) || ((flag_1) && (!flag_2))){ 
				if((current_eye == 1) && (count_even == 0)){
				if((add_frames) < image_counter){
						//if(image_counter > delay_variable){
						//reallocate the images that is to remove from the queue more than one 
						//reallocate_dequeue(item);
						if((current_eye == 1) && (count_even == 0)){
						dequeue2(queue1);
						//count backwards when removing images
						image_counter--;}//
						if(image_counter ==0){
						fill_queue = 0;
						}
					}
				
				//to be able to remove frames if they are above target value of frames
			    
					if((add_frames) < image_counter){
						//if(image_counter > delay_variable){
						//reallocate the images that is to remove from the queue more than one 
						//reallocate_dequeue(item);
						if((current_eye == 1) && (count_even == 0)){
						dequeue2(queue1);
						//count backwards when removing images
						image_counter--;}
						if(image_counter ==0){
						fill_queue = 0;
						}
					
					}
				}
				//}
			//else if ((!flag_1) && (flag_2)) {
				
				
				//count_increment += (unsigned int)(result_time.tv_usec/1000);
				//printf("the current time for increment is %u and the target time is %u\n",count_increment,computed_increment); 
				//if (count_increment < computed_increment){
					//if((current_eye == 1) && (count_even == 0)){
					//dequeue2(queue1); // to keep the delay constant constant
					//// the reason is to keep the frames constant.
					//image_counter--; // decrement the counter, since it is incremented above
					//}
					//if(image_counter ==0){
						//fill_queue = 0;
						//}
					
				//}
				//else{
					////reset the counter and do not dequeue will automatically increase the queue size
					//count_increment = 0; 	
				//}	
		    //}
	
	
	}

	//run reset_time	
    else if(((choose12 == 1) && (!trial_mode)) || (((((!flag_1) && (!flag_2)) || ((!flag_1) && (flag_2))) && (trial_mode == 1)) && (!done))) {
		
			gettimeofday(&begin_time, NULL);
			if (switch_camera == 1){
			if (frame_enable == 1){
			
				}
			else {
					}
			}
			else{ 
			if (frame_enable == 1){
				if((bayer_setting == 1) || (bayer_setting == 2)){
					if(current_eye == 1){
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image1, render);
					
					}
					else if(current_eye == 0){
					drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image2, render);
					
					
					}
				}
				else{
					if(numCameras < 2){
						if(current_eye == 1){
						drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, render);}
						//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);}
						else if(current_eye == 0){
						drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_right, render);}
						//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_right, rotate,zoom, frame_zoom, frame_width, frame_height, frame_move, move_image,move_image2,flip_horizontal,flip_vertical);}
					} 
					else{
						if(current_eye == 1){
						drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, render);}
						//drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, rotate,zoom, frame_zoom, frame_width, frame_height, frame_move,move_image,move_image2,flip_horizontal,flip_vertical);}
						else if(current_eye == 0){
						drawTexture_eye2_frame(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_right, render);}
						}	
				} 
				
				}
			else {
				if((bayer_setting == 1) || (bayer_setting == 2)){
					
					if(current_eye == 1){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image1, render);}
						else if(current_eye == 0){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, rgb_image2, render);}
					
					}
				else{
					if(numCameras < 2){
						
						
						if(current_eye == 1){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, render);}
						else if(current_eye == 0){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_right, render);}
						}
					else{
						
						//rintf("processing the image\n");
						
						if(current_eye == 1){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_left, render);}
						else if(current_eye == 0){
							drawTexture_eye2(screen->w, screen->h, device_width, device_height, stretch, video_texture, image_load_right, render);}
						
						}
				}		
			}	
				if((!flag_1) && (flag_2) && (trial_mode == 1)){
					draw_point(screen->w, screen->h,frame_zoom, frame_width, frame_height,frame_move);
				}
				}
			//add_frames = 0;
			delay_on = 0; //set the delay on 0 ms
			
			
			
			//remove items as long as the image_buffer has images stored
			if(image_counter > 0){
			//if(image_counter > delay_variable){
				//reallocate_dequeue(item);
				if((current_eye == 1) && (count_even == 0)){
				dequeue2(queue1);
				image_counter--;}
				if(image_counter ==0){
						fill_queue = 0;
						}
				}
			
			


      }
      
    else if((flag_1) && (flag_2) && (trial_mode == 1) && (!done)){
				//////////////////////////////////////////////////////////////
				//******************Initializing font***********************//
				//////////////////////////////////////////////////////////////
				if(start_flag2 == 0){
					//glDeleteTextures( NUM_TEXTURES, &video_texture[0] );
					initGLfont(); //initialize the fonts for openGL
					start_flag2 = 1;
				}
				drawGrey_screen(screen->w, screen->h, device_width, device_height,render);
				open_questions(screen,"grey_screen_text.txt");
				
		}
    else{
      drawBlack_screen(screen->w, screen->h, device_width, device_height);
       //drawBlack_screen(screen->w, screen->h, device_width, device_height);
      }
    }//end for if-statement draw video
    while ( SDL_PollEvent(&event) ) {
      switch(event.type) {
      case SDL_VIDEORESIZE:
			screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,SDL_OPENGL|SDL_RESIZABLE);
			if ( screen ) {
				reshape(screen->w, screen->h);
			} 
			else {
				//Uh oh, we couldn't set the new video mode?? /;
			}
			break;
	

			}
   
	} 
  //SDL_GL_SwapBuffers();
   nvstusb_swap(nv_ctx, (enum_eye)current_eye, SDL_GL_SwapBuffers);
   current_eye = (current_eye + 1) % 2;
   SDL_UnlockMutex(lock1);
  } 
  //cleanup(numCameras,cameras,lfb);
  if((numCameras > 1) && (bayer_setting != 0)){
	save_image_(device_width,device_height,rgb_image1,"Image_left_rgb.jpg");
	save_image_(device_width,device_height,rgb_image2,"Image_right_rgb.jpg");
	}
  nvstusb_deinit(nv_ctx);
  delete_queue(queue1);
  
  queue1 = NULL;
   
  // Clean up our textures
  glDeleteTextures( NUM_TEXTURES, &video_texture[0] );
  //glDeleteTextures( 2, &overlay_texture[0] );
  //initGLFont();
  done = 0;
  
  if(trial_mode ==1){
  
  gettimeofday(&date, NULL);
  current_time = date.tv_sec;
  strftime(date_buffer,100,"%Y-%m-%d-%H:%M",localtime(&current_time));
  //printf("The text is %s\n",date_buffer);
  sprintf(outfile_name,"data-%s",date_buffer);
  outfile2=fopen(outfile_name,"w"); //second need to read from the respective file
  //outfile2=fopen("trial_answer","w"); //second need to read from the respective file
  fprintf(outfile2,"trial frames displaced answer\n");
  int i_index;
	for(i_index = 0; i_index < (number_of_loops); i_index++){
		fprintf(outfile2,"%d	",trial_number[i_index]);
		fprintf(outfile2,"%d	",add_frames_number[i_index]);
		fprintf(outfile2,"%d	",displacement[i_index]);
		fprintf(outfile2,"%d\n",trial_key_set[i_index]);
		//if(trial_key_set[i_index] == 1){
			//fprintf(outfile2,"yes\n");
		//}
		//else if(trial_key_set[i_index] == 2){
			//fprintf(outfile2,"no\n");
		//}
		//else if(trial_key_set[i_index] == 0){
			//fprintf(outfile2,"no answer\n");
		//}
	}
	fclose(outfile2);
  }
  
   
  
  return 0;
  }

    /////////////////////////////////////////////////////////////////	
	//******************* Time function ***************************//
	/////////////////////////////////////////////////////////////////

//to compute the amount of elapsed time correctly 
int elapsed_time_func(struct timeval *result,const struct timeval *start,const struct timeval *end){
	struct timeval *start_temp, *end_temp;
	
	start_temp = (struct timeval*)malloc(sizeof(struct timeval));
	end_temp = (struct timeval*)malloc(sizeof(struct timeval));
	*start_temp = *start;
	*end_temp = *end;
	if(start_temp->tv_usec < end_temp->tv_usec){
		int numberofsec = (start_temp->tv_usec- end_temp->tv_usec)/1000000 +1;
		end_temp->tv_usec -= 1000000 * numberofsec;
		end_temp->tv_sec += numberofsec;
		}
	if (start_temp->tv_usec - end_temp->tv_usec > 1000000){
		int numberofsec = (end_temp->tv_usec- start_temp->tv_usec)/1000000;
		end_temp->tv_usec += 1000000 * numberofsec;
		end_temp->tv_sec += numberofsec;
		}	
	
	result->tv_sec = start_temp->tv_sec - end_temp->tv_sec;
	result->tv_usec = start_temp->tv_usec - end_temp->tv_usec;
	
	return start_temp->tv_usec < end_temp->tv_usec;
	} 

    /////////////////////////////////////////////////////////////////	
	//************** Camera function for threads*******************//
	/////////////////////////////////////////////////////////////////

int run_camera(void *data){
 
  char* name = (char*)data;
  
  int  i, j;
  //name = "camera1" where index [6] is the number
  if(name[6] == '1'){i = 0;} //initiate camera 1
  else if(name[6] == '2'){i = 1;} //initiate camera 2
  /* declarations for libdc1394 */
  dc1394error_t err;  
  //dc1394camera_t *cameras[MAX_CAMERAS];
  dc1394video_frame_t * frames[MAX_CAMERAS];
  dc1394_t * d;
  dc1394camera_list_t * list;
 
  //char *lfb=NULL;
  
  //dc1394featureset_t features;
  //dc1394video_frame_t * frames[MAX_CAMERAS];
  /* declarations for video1394 */
  



  
  //cleanup(numCameras,cameras,lfb,i);

  //bool video = false;
  

  //res = DC1394_VIDEO_MODE_FORMAT7_0;SDL_Delay(Uint32 ms)
  //fps = DC1394_FRAMERATE_60; //DC1394_FRAMERATE_30;
  
  //printf("fps is %d",fps);
  //fps = DC1394_FRAMERATE_60;
  //res = DC1394_VIDEO_MODE_640x480_RGB8; //YUV422; //RGB8;
  //res = DC1394_VIDEO_MODE_640x480_YUV422; //YUV422; //RGB8;
 if((bayer_setting == 1) || (bayer_setting == 2)){
	//fps = DC1394_FRAMERATE_MAX;
	//fps = DC1394_FRAMERATE_120;
	fps = DC1394_FRAMERATE_MAX;
	res = DC1394_VIDEO_MODE_FORMAT7_0;//DC1394_VIDEO_MODE_640x480_RGB8; //DC1394_VIDEO_MODE_800x600_RGB8;//
	color_coding = DC1394_COLOR_CODING_RAW8; //DC1394_COLOR_CODING_YUV422;
	if(Cameras_set == 1){
		device_width=780; //640; //1920x1080 //640x480
		device_height=580;//480;	
		}
	else{
	device_width = 656;
	device_height = 492;
	}
  }
  else{
	  
	  fps = DC1394_FRAMERATE_60;
	  res = DC1394_VIDEO_MODE_640x480_RGB8; //YUV422; //RGB8;
	  device_width=640;
	  device_height=480;
	  }
  //device_width=640; //1920x1080 //640x480
  //device_height=480;
  //device_width = 1292;
  //device_height = 964;
  
  //
  //device_width=388; //640; //1920x1080 //640x480
  //device_height=290;//480;
  //format=XV_YUY2;
  format=XV_UYVY; //for YUV422 mode
  //format=XV_YV12;
  // Camera setup
  char *device_name=NULL;

  d = dc1394_new();
  if (!d)
    return 1;
  err=dc1394_camera_enumerate(d, &list);
  DC1394_ERR_RTN(err,"Failed to enumerate cameras");

  if (list->num == 0) {
    dc1394_log_error("No cameras found");
    return 1;
  }

  j = 0;
  //for (i = 0; i < list->num; i++) {
    if (j >= MAX_CAMERAS){}
      //break;
    cameras[i] = dc1394_camera_new (d, list->ids[i].guid);
    if (!cameras[i]) {
      dc1394_log_warning("Failed to initialize camera with guid %llx", list->ids[i].guid);
      //continue;
    }
    //j++;
  //}
  numCameras = 2;
  dc1394_camera_free_list (list);

  if (numCameras == 0) {
    dc1394_log_error("No cameras found");
    exit (1);
  } 

  /* setup cameras for capture */
  //for (i = 0; i < numCameras; i++) {
    // Set speed to 800 Mbits/s
    err= dc1394_video_set_operation_mode(cameras[i], DC1394_OPERATION_MODE_1394B); 
    err=dc1394_video_set_iso_speed(cameras[i], DC1394_ISO_SPEED_800); //DC1394_ISO_SPEED_800);
    DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not set ISO speed");
    if((bayer_setting == 1) || (bayer_setting == 2)){
		err=dc1394_format7_set_color_coding(cameras[i] ,res ,color_coding);
		DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not set color coding");
	}
	err=dc1394_video_set_mode(cameras[i], res);
    DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not set video mode");
	if(bayer_setting == 0){
    err=dc1394_video_set_framerate(cameras[i], fps);
    DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not set framerate");
	}
    err=dc1394_capture_setup(cameras[i],1, DC1394_CAPTURE_FLAGS_DEFAULT);
    DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not setup camera-\nmake sure that the video mode and framerate are\nsupported by your camera");

    err=dc1394_video_set_transmission(cameras[i], DC1394_ON);
    DC1394_ERR_CLN_RTN(err,cleanup(numCameras,cameras,lfb,i),"Could not start camera iso transmission");

    // Camera settings 
    int setting = 1;
    if(setting == 1){
		//setting shorter shutter time to increase speed
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_SHUTTER,500); 
		//err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_SHUTTER,500); //800
		//err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_SHUTTER,1400);
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_BRIGHTNESS,800);
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_EXPOSURE,150);
		err = dc1394_feature_whitebalance_set_value(cameras[i],500,400);
	}
	else{	
    //err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_SHUTTER,800);
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_SHUTTER,1400);
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_BRIGHTNESS,800);
		err = dc1394_feature_set_value(cameras[i],DC1394_FEATURE_EXPOSURE,150);
		err = dc1394_feature_whitebalance_set_value(cameras[i],500,400);
	}
  //}
  
  fflush(stdout);
  if (numCameras < 1) {
    perror("no cameras found :(\n");
    cleanup(numCameras,cameras,lfb,i);
    exit(-1);
  }

  
  switch(format){
  case XV_YV12:
    //set_frame_length(device_width*device_height*3/2, numCameras);
    //void set_frame_length(unsigned long size, int numCameras)
    size = device_width*device_height*3/2;
    frame_length=size;
    dc1394_log_debug("Setting frame size to %ld kb",size/1024);
    frame_free=0;
    //    frame_buffer = malloc( size * numCameras);
    lfb = malloc(size * numCameras);
    break;
  case XV_YUY2:
  case XV_UYVY:
    //set_frame_length(device_width*device_height*2, numCameras);
    size = device_width*device_height*3/2;
    frame_length=size;
    dc1394_log_debug("Setting frame size to %ld kb",size/1024);
    frame_free=0;
    //frame_buffer = malloc( size * n
    lfb = malloc( size * numCameras);

    break;
  default:
    dc1394_log_error("Unknown format set (internal error)");
    exit(255);
  }
  
  
	
	//dc1394video_frame_t * frame_from_camera1[2];
	//while (!condition2){ }
	//int start_flag2 = 0;
	while(stop_flag == 0){
		SDL_LockMutex(lock1); //locked the mutex and starting the cameras
		if (dc1394_capture_dequeue(cameras[i], DC1394_CAPTURE_POLICY_WAIT, &frames[i])!=DC1394_SUCCESS)
			dc1394_log_error("Failed to capture from camera %d", 0);
        
        
       	//applying gear principle to let the main_thread have access to the varible every even time 
		//applying gear principle to let the run_camera1 have access to the varible every odd time 
		
		//buffer(frames[0]->image,frames[0]->image_bytes,1);
		
		
		
		if(name[6] == '1'){
			memcpy(image_storage_left,frames[i]->image,frames[i]->image_bytes); //copied frame to main thread
			bytes_storage_left = frames[i]->image_bytes;//copied bytes to main thread

			} //initiate camera 1
		
		else if(name[6] == '2'){
			// Doing the critical tasks
			memcpy(image_storage_right,frames[i]->image,frames[i]->image_bytes); //copied frame to main thread
			bytes_storage_right = frames[i]->image_bytes; //copied bytes to main thread
			} //initiate camera 2	
		
		
		
		
		//SDL_LockMutex(lock1);
		//SDL_CondSignal(cond1);
		//SDL_UnlockMutex(lock1);
		
		//condition2 = SDL_FALSE;
		if (frames[i]){
			dc1394_capture_enqueue(cameras[i], frames[i]);
			
			//dc1394_capture_enqueue (cameras[1], frames[current_eye]);
		}
		//while(condition2){}
		condition1 = SDL_TRUE;
		if(name[6] == '1'){
		SDL_CondSignal(cond1); //sent condition signal to main thread
		SDL_CondWait(cond1,lock1); //waiting for condition signal from main thread
		}
		else if(name[6] == '2'){
		SDL_CondSignal(cond2); //sent condition signal to main thread
		SDL_CondWait(cond2,lock1); //waiting for condition signal from main thread
		}
		SDL_UnlockMutex(lock1); //unlocked mutex and passed wait function in run camera
		}
	
	//cleanup(numCameras,cameras,lfb, i);
	
	//if (stop_flag == 1){
		////if stop flag is entered then clean the cameras and set the stop flag for the while loop
		//done = 1;       
      //cleanup(numCameras,cameras,lfb, i);
		
		//}
	
	
	return 0;
	}
	
   /////////////////////////////////////////////////////////////////	
   //************ Keyboard function for threads*******************//
   /////////////////////////////////////////////////////////////////

int keyboard_thread(void){
	//SDL_Init(0);
	SDL_Event event;
	while(!done){
	 	
	   while ( SDL_PollEvent(&event) ) {
      switch(event.type) {
    	case SDL_KEYDOWN:
			
			switch(event.key.keysym.sym){
	 			//case SDLK_d:
					//choose12 = 0;
					//break;
			    case SDLK_KP2:
						if(trial_mode == 1){
							//answer is valid if withinn testmovement phase or black screen phase
							if(((flag_1) && (!flag_2)) || ((flag_1) && (flag_2))){
								trial_key_set[loop] = 1; //key settings for yes
							}
						}
					break;
				case SDLK_y:
						if(trial_mode == 1){
							//answer is valid if withinn testmovement phase or black screen phase
							//if(((flag_1) && (!flag_2)) || ((flag_1) && (flag_2))){
							//	trial_key_set[loop] = 1; //key settings for yes
							//}
						}
						else{
							if(flip_horizontal == 0){
								flip_horizontal = 1;
								//printf("manual sync on\n");
								}
							else{
								flip_horizontal = 0;
								}
						} 	
					break;
				
					

				
				
				case SDLK_KP1:
						if(trial_mode == 1){
							//answer is valid if withinn testmovement phase or black screen phase
							if(((flag_1) && (!flag_2)) || ((flag_1) && (flag_2))){
								trial_key_set[loop] = 0; //key settings for no
							}
						}
						else{
							//frame_height -= 3; //remove 0.1 if frame_zoom is larger than zero
						}
				break;	
					
					
				//case SDLK_u:
					//if(flip_vertical == 0){
						//flip_vertical = 1;
						//}
					//else{
						//flip_vertical = 0;
					//}
					//break;
					case SDLK_f:
						if(trial_mode == 0){
						choose12 = 1;}
						//if (choose12 == 3){choose12 = 0;}
						break;
					//case SDLK_a:
					    //if(trial_mode == 0){
						//delay_on += 50; //add 50 ms
						//}
						//else{
							//if(black_screen == 0 ){black_screen =1;}
							//else{black_screen = 0;}
							//}
						//delay_variable += 1;
						//break;
					case SDLK_r:
						if(trial_mode == 0){
							if(multiply > 1){
								delay_on /= multiply;
								//multiply /= 10; //remove 50 ms
								printf("the multiplicator is now %u\n",multiply);}
							}
						break;
					case SDLK_t:
						if(trial_mode == 0){
							//multiply *= 10; //remove 50 ms
							delay_on *= multiply;
							printf("the multiplicator is now %u\n",multiply);
						}
						break;	
					//case SDLK_s:
						////if(trial_mode == 0){
							////if(delay_on > 0){delay_on -= 50; //remove 50 ms
								////}
							////}
						//break;
						//case SDLK_n:
						//if( drawVideo == 1)
						//drawVideo = 0;
						//else
						//drawVideo = 1;
						//break;
					case SDLK_z:
						//if(zoom > 0){zoom -= 0.001; //remove 0.1 if zoom is larger than zero
						//}
						if(trial_mode == 0){
							if(flip_horizontal == 0){
								move_image -= 0.01;}
							else if(flip_horizontal == 1){
								move_image2 -=0.01;}
						}
						break;
					case SDLK_x:
						if(trial_mode == 0){
							if(flip_horizontal == 0){
								move_image +=0.01;}
							else if(flip_horizontal == 1){
								move_image2 +=0.01;}
						}
						break;
					case SDLK_c:
						//if(zoom > 0){zoom -= 0.01; //remove 0.1 if zoom is larger than zero
		
						//}
						if(trial_mode == 0){
							zoom -= 0.01;
							}
						
						break;
					case SDLK_v:
						if(trial_mode == 0){
							zoom +=0.01;
						}
						break;
					//case SDLK_b:
						//zoom = 0; //cancel zoom !! directly and pull it back to its original status
						//break;
					case SDLK_g:
						if(trial_mode == 0){
							if( frame_enable == 1) //too enable the frame
								{frame_enable = 0;
								frame_zoom = 0; //to reset the values 
								frame_height = 0;
								frame_width = 0;
								frame_move = 0;}
							else{
								frame_enable = 1;}
							}
						break;
					case SDLK_h:
						if(trial_mode == 0){
							frame_width -= 3; //remove 0.1 if frame_zoom is larger than zero
						}
						//frame_zoom -= 0.001;
						break;
					case SDLK_j:
						if(trial_mode == 0){
							frame_width +=3;
						}
						break;
					
		
						//frame_zoom -= 0.001;
					
					case SDLK_m:
						if(trial_mode == 0){
							frame_height +=3;
						}
						break;
					case SDLK_k:
						if(trial_mode == 0){
							if(frame_zoom > 0){frame_zoom -= 3; //remove 0.1 if frame_zoom is larger than zero
		
							}
						}
						//frame_zoom -= 0.01;
						break;
					case SDLK_l:
						if(trial_mode == 0){
							frame_zoom +=3;
						}
						break;
					case SDLK_o:
						if(trial_mode == 0){
							frame_move -= 3; //remove 0.1 if frame_zoom is larger than zero
						}
						//frame_zoom -= 0.01;
						break;
					case SDLK_p:
						if(trial_mode == 0){
							frame_move +=3;
						}
						break;
					case SDLK_i:
						if(trial_mode == 0){
							if( shift_delay == 1)
								shift_delay = 0;
							else{
								shift_delay = 1;}
						}
						break;
					case SDLK_w:
						if(trial_mode == 0){
							if( rotate >= 270){
								rotate = 0;}
							else{
								rotate += 90;
							}
						}
						//if( switch_camera == 1){
						//switch_camera = 0;}
						//else{
						//switch_camera = 1;
	  
						//}
						break;
					case SDL_QUIT:
						done = 1;
					    
						break;
					//default:
					 
						//break;
				
				
				
	//if(event.type == SDL_MOUSEBUTTONDOWN){
		//if(event.button.button == SDL_BUTTON_LEFT){
			////do_something();
			//SDL_GetMouseState(&mouse_x, &mouse_y);
			//portion = (float)mouse_y/((float)screen->h);
			//printf("%f\n", portion);
		//}
      //}
      //drawTexture
    }
     
    keys = SDL_GetKeyState(NULL);
    
    if ( keys[SDLK_ESCAPE] ) {
      done = 1;
      
    }
   	
		//if ( keys[SDLK_0] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 1000; //1s
				//add_frames = 10;
			//}
			//}
		//if ( keys[SDLK_1] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 100; //100ms
				//add_frames = 11;
				//}
			//}
		//if ( keys[SDLK_2] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 150; //200ms
				//add_frames = 12;
				//}
			//}
		//if ( keys[SDLK_3] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 200; //300ms
				//add_frames = 13;
				//}
			//}
		//if ( keys[SDLK_4] ) {
			 //if(trial_mode == 0){
				////stretch = mid; 
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 250; //400ms
				//add_frames = 14;
				//}
			//}
		//if ( keys[SDLK_5] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 300; //500ms
				//add_frames = 5;
				//}
			//}
		//if ( keys[SDLK_6] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 350; //600ms
				//add_frames = 6;
				//}
			//}
		//if ( keys[SDLK_7] ) {
			 //if(trial_mode == 0){
				////stretch = mid;
				////printf("Strech 1.0: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 400; //700ms
				//add_frames = 7;
				//}
			//}
		//if ( keys[SDLK_8] ) {
			 //if(trial_mode == 0){
				////stretch = 0.8*mid;
				////printf("Strech 0.8: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 450; //800ms
				//add_frames = 8;
				//}
			//}
		//if ( keys[SDLK_9] ) {
			 //if(trial_mode == 0){
				////stretch = 0.9*mid;
				////printf("Strech 0.9: %f\n", stretch);
				//choose12 = 0;
				////delay_on = 500; //900ms
				//add_frames = 9;
				//}
			//}
		//if ( keys[SDLK_1] ) {
		//stretch = 1.1*mid;
		//printf("Strech 1.1: %f\n", stretch);
		//}
		//if ( keys[SDLK_2] ) {
		//stretch = 1.2*mid;
		//printf("Strech 1.2: %f\n", stretch);
		//}
		if ( keys[SDLK_UP] ) {
			stretch = 1.0;
			mid = stretch;
			printf("Reset to 1.0");
			}
		if ( keys[SDLK_DOWN] ) {
			mid = stretch;
			printf("Normal is: %f\n", mid);
			}
		if ( keys[SDLK_LEFT] ) {
			stretch = stretch + 0.01;
			}
		if ( keys[SDLK_RIGHT] ) { 
			stretch = stretch - 0.01;
			}
		if ( keys[SDLK_q] ) {
			if((numCameras > 1) && (bayer_setting != 0)){
		
				}
			//SDL_WaitThread(thread1, NULL);
			//SDL_DestroyMutex(lock1);
			done = 1;      
			//cleanup(numCameras,cameras,lfb);
			}
		}	
	}
	
	
	}
	return 0;
}
	
	

   /////////////////////////////////////////////////////////////////	
   //*************** 3dvgl setup for refresh *********************//
   /////////////////////////////////////////////////////////////////
 
void ConfigRefreshRate(struct nvstusb_context *ctx) {
        Display *display = XOpenDisplay(0);
        double display_num = DefaultScreen(display);
        XF86VidModeModeLine mode_line;
        int pixel_clk = 0;
        XF86VidModeGetModeLine(display, display_num, &pixel_clk, &mode_line);
        double frame_rate = (double) pixel_clk * 1000.0 / mode_line.htotal / mode_line.vtotal;
        printf("Detected refresh rate of %f Hz.\n", frame_rate);
        nvstusb_set_rate(ctx, frame_rate);
    }
