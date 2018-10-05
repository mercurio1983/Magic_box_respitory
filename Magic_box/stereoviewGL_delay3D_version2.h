
#ifndef __STEREOVIEWGL_DELAY3D_H__
#define __STEREOVIEWGL_DELAY3D_H__

#define MAX_CAMERAS 8
#define NUM_BUFFERS 8
  
  unsigned long tid;	
  //struct idpost *que_image = NULL;
  float portion = 0.5;
  int mouse_x, mouse_y;

  int video = 0;
  /* camera settings */
  
  
  /* the while loop */
  static int done = 0;
  static int stop_flag = 0;
  uint32_t numCameras = 0;
  
  
  dc1394camera_t *cameras[MAX_CAMERAS];
  char *lfb=NULL;
  long format=0;

  /* Other declarations */
  
 
  
  
  
  /////////////////////////////////////////////////////////////////	
  //***************** The screen variables **********************//
  /////////////////////////////////////////////////////////////////  
  
  unsigned long width,height,height2, height3, width4, height4, width5, height5;
  unsigned long device_width,device_height;
  
  unsigned long delay_variable = 0;
  unsigned long delay_variable_old = 10; 
  
  unsigned long size;
  
  int drawVideo = 1;
  int choose12 = 1; //the setting for the delay "0" enable delay "1" disable delay
 

  
  
  // screen settings
  char fullscreen = 0;
  char resizable = 0;
  
  float mid = 1.0;
  float stretch = 1.0;
  
  /////////////////////////////////////////////////////////////////	
  //********** The time variables for measurement ***************//
  /////////////////////////////////////////////////////////////////
  
  struct timeval end_time; //for measuring the stop time
  struct timeval begin_time; // for measuring the start time
  struct timeval result_time; //for computing the result time 
  
  /////////////////////////////////////////////////////////////////	
  //********** The time variables for delay per frame ***********//
  /////////////////////////////////////////////////////////////////
  
  struct timeval end_delay; //for measuring the stop time
  struct timeval begin_delay; // for measuring the start time
  struct timeval result_delay; //for computing the result time 
  
  /////////////////////////////////////////////////////////////////	
  //********** The time measurement variables *******************//
  /////////////////////////////////////////////////////////////////
  char date_buffer[100];
  time_t current_time;
  struct timeval date; //for file logging
  
  
  struct timeval sequence_time;
  
  struct timeval begin_instruction;
  struct timeval begin_induction;
  struct timeval begin_stop_signal;
  struct timeval begin_test_movement;
  struct timeval begin_black_screen;
  struct timeval end_instruction;
  struct timeval end_induction;
  struct timeval end_stop_signal;
  struct timeval end_test_movement;
  struct timeval end_black_screen;
    
  unsigned int elapsed_ms_add1 = 0;
  unsigned int elapsed_s_add2 = 0;
  unsigned int elapsed_instruction= 0;
  unsigned int elapsed_induction = 0; //null the timer
  unsigned int elapsed_stop_signal =0;
  unsigned int elapsed_test_movement = 0;
  unsigned int elapsed_black_screen = 0;
  
  double sys_time = 27; //note that it is a measured value
  
  unsigned int store_result_time ;  
  unsigned int store_elapsed_time ; 
  
  int negative_value; //necessary time function variables
  int negative_value_2;
  
  /////////////////////////////////////////////////////////////////	
  //****************** The trial variables **********************//
  /////////////////////////////////////////////////////////////////
  
  unsigned int trial_number[101];
  unsigned int add_frames_number[101];
  int trial_mode = 0;
  unsigned int trial_key_set[101]; //trial key to answer
  unsigned int displacement[101];
  unsigned int instruction_set[101];
    
  /////////////////////////////////////////////////////////////////	
  //********** The time variables for automated paradigm ********//
  /////////////////////////////////////////////////////////////////
  
  unsigned int delay_enable = 0;
  unsigned int delay_on = 0;  //delay enabled or disabled
  unsigned int test_movement_time = 0;  //phase C the duration
  unsigned int number_of_loops = 1;  //number of loops
  unsigned int repetitions = 0;
  unsigned int stop_signal_time = 0; //phase B
  unsigned int induction_time = 0; // phase A
  unsigned int instruction_time = 0;
  unsigned int black_screen_time = 0;  //phase D reset time
    
  /////////////////////////////////////////////////////////////////	
  //********** The camera and images variables ******************//
  /////////////////////////////////////////////////////////////////

 
   
  int fps;
  int res;
  int color_coding;
  
  int bayer_setting;
  int Cameras_set;
  
    
  char *device_name=NULL;
  
  unsigned long frame_length;
  long frame_free;
  int frame=0;
  

  GLuint video_texture[2];	// This is a handle to our texture object
  SDL_Surface *screen;
  Uint8 *keys;
   
  uint8_t *rgb_image1;
  uint8_t *rgb_image2;
  dc1394video_frame_t *rgb_image11;
  dc1394video_frame_t *rgb_image12;
  
  unsigned char* image_left ;
  unsigned char* image_right; // uint16_t *rgbBuffer = malloc(w * h * 3); 
  unsigned char* image_left1;
  unsigned char* image_right1; // uint16_t *rgbBuffer = malloc(w * h * 3); 
 
  unsigned char* image_left2; //(unsigned char*)malloc(sizeof(unsigned char)); //(unsigned char*)malloc(sizeof(unsigned char));
  unsigned char* image_right2; //(unsigned char*)malloc(sizeof(unsigned char)); //(unsigned char*)malloc(sizeof(unsigned char));
  unsigned long* value_size_left1;
  unsigned long* value_size_right1;
  
  unsigned char* image_rgb1;
  unsigned char* image_rgb2;
  unsigned char image_test_left;
  unsigned char image_test_right;
  
  dc1394video_frame_t *rgb_image11;
  dc1394video_frame_t *rgb_image12;

  unsigned char value12;
  unsigned char value22;
  
  unsigned char* image_load_left;
  unsigned char* image_load_right;
  static unsigned char* image_storage_left;
  static unsigned char* image_storage_right;  
  uint32_t image_size = 0;
  uint32_t bytes_storage_left = 0;
  uint32_t bytes_storage_right = 0;
  //unsigned char *image_storage = NULL; 


  /////////////////////////////////////////////////////////////////	
  //***************** The file variables ************************//
  /////////////////////////////////////////////////////////////////

  char file_text[100];
  int file_data_index = 0;
  int file_data_time = 0;
  char outfile_name[150];
  
  FILE* outfile2 = NULL;
  FILE *infile = NULL;  //declaring the infile for reading the textfile
  FILE *outfile = NULL; //declaring the outfile for producing the textfile
  
  int set_empty_flag = 0; // to create a flag for an empty file
  char loop_found[20]; //for file operations
   
  /////////////////////////////////////////////////////////////////	
  //*************** The flags for automated paradigm*************//
  /////////////////////////////////////////////////////////////////
  int flag_1 = 0;
  int flag_2 = 0; 
  int flag_3 = 0;
  int flag_4 = 0; //set to 1 since paradigm is extended instruction
  
  int semaphore_flag = 0; //for starting and ending specific automated 
  //subfunctions like reset and increment step
  
  /////////////////////////////////////////////////////////////////	
  //*************** The delay buffer variables*******************//
  /////////////////////////////////////////////////////////////////
  
  
  
  unsigned int multiply = 10;
  unsigned int add_frames = 0; //to compute the number of frames to add for the queue
  unsigned int i_add = 0;
  int start_flag = 0;
  int start_flag2 = 0;
  CQueue * queue1 = NULL;
  unsigned int count_loops; // to fill the buffer
  unsigned int step_size = 30; //ms
  unsigned int increment_step;
  
  unsigned int total_bias = 80; //the intrinsic delay for this system is 80ms
  unsigned int system_bias; // the intrinsic delay subracted by computational delay
  
  unsigned int loop = 0; // to count the number of loops very important for trial
  int image_counter =0;
  unsigned int previous= 0;  
  int counting = 0;  
  int shift_delay = 0;
  int counter_i = 0;
  int manual_sync = 0; // to enable sync
  int delay_frame = 0; // to sync the screen
  unsigned int count_increment = 1;
  unsigned int computed_increment = 1;

  /////////////////////////////////////////////////////////////////	
  //**** The Nvidia variables for producing the 3D effect********//
  /////////////////////////////////////////////////////////////////
  
  // context for dealing with the stereo usb IR emitter
  struct nvstusb_context *nv_ctx = NULL;
  
  static int current_eye = 0;
  
  /////////////////////////////////////////////////////////////////	
  //********** The effect variables for the frame ***************//
  /////////////////////////////////////////////////////////////////
  
  //int start_and_freeze = 0; //to freeze the image to display same image
  int switch_camera = 0; // to switch camera pair
  
  
  /////////////////////////////////////////////////////////////////	
  //****************** The rendering variables ******************//
  /////////////////////////////////////////////////////////////////
  
  
  float zoom = 0;
  float move_image = 0;
  float move_image2 = 0;
  int frame_enable =0;
  float frame_zoom = 0;
  float frame_height = 0;
  float frame_width = 0;
  float frame_move = 0;
  float flip_horizontal=0;
  float flip_vertical = 0;
  float rotate = 0;
  //float black_screen = 0;	
//typedef struct rendering_parameters {
  //float zoom = 0;
  //float move_image = 0;
  //float move_image2 = 0;
  //int frame_enable =0;
  //float frame_zoom = 0;
  //float frame_height = 0;
  //float frame_width = 0;
  //float frame_move = 0;
  //float flip_horizontal=0;
  //float flip_vertical = 0;
  //float rotate = 0;
//} rendering_parameters;	
	
  /////////////////////////////////////////////////////////////////	
  //********************The thread variables*********************//
  /////////////////////////////////////////////////////////////////
  
  SDL_mutex *lock1;
  SDL_cond *cond1;
  SDL_mutex *lock2;
  SDL_cond *cond2;
  SDL_bool condition1 = SDL_FALSE;
  SDL_bool condition2 = SDL_FALSE;
  SDL_Thread* thread1;
  SDL_Thread* thread2;
  SDL_Thread* thread3;
  SDL_Thread* thread4;

  /////////////////////////////////////////////////////////////////	
  //********************** The function *************************//
  /////////////////////////////////////////////////////////////////
  int main_thread(void *arg);
  int keyboard_thread(void);
  uint32_t buffer(unsigned char *image,uint32_t bytes,int choice);
  void cleanup(uint32_t lnumCameras, dc1394camera_t **cam, char * fb,int i);
  void ConfigRefreshRate(struct nvstusb_context *ctx);
  //int elapsed_time(struct timeval *result,const struct timeval *start,const struct timeval *end);
  int elapsed_time_func(struct timeval *result,const struct timeval *start,const struct timeval *end);
  //uint32_t buffer(unsigned char *image,uint32_t bytes,int choice);
  int init_cameras(void);
  int run_camera(void *data);


#endif
