
#ifndef __RENDERING_H__
#define __RENDERING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* SDL and OpenGL */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL.h>

//rendering parameters done in struct
typedef struct rendering{
  float zoom;
  float move_image;
  float move_image2;
  int frame_enable;
  float frame_zoom;
  float frame_height;
  float frame_width;
  float frame_move;
  float flip_horizontal;
  float flip_vertical;
  float rotate;
} rendering;

#ifdef __cplusplus
extern "C" {
#endif

//#include "globals.h"

/* Setup our booleans */
//#define TRUE  1
//#define FALSE 0
#define true  1
#define false 0
typedef char bool;

/* Number of textures to load */
#define NUM_TEXTURES 2

/* This is our SDL surface */
//SDL_Surface *surface;

GLuint  base;                  /* Base Display List For The Font           */
GLuint  texture[NUM_TEXTURES]; /* Storage For Our Font Texture             */
//GLuint  loop;                  /* Generic Loop Variable                    */

	


void SDLinit(int width, int height);
void initTexture(GLuint* tex, int num);

// new window size or exposure
void reshape(int width, int height);
void idle(void);

//rendering
void center(GLint w, GLint h,int rotate,float zoom, float move_image,float flip_horizontal,float flip_vertical);
void center_with_frame(GLint w, GLint h,int rotate,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image,float move_image2,float flip_horizontal,float flip_vertical);
void left(GLint w, GLint h, float s, float portion,int f, float zoom, float move_image);
void right(GLint w, GLint h, float s, float portion,int f, float zoom, float move_image);
void left_with_frame(GLint w, GLint h, float s, float portion, int f,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image);
void right_with_frame(GLint w, GLint h, float s, float portion,int f,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image);

//set for 3dvgl library to draw center for each eye
void drawTexture_eye2(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render);
void drawTexture_eye2_frame(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render);

//set for left and right image
void drawTexture(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data_left, unsigned char* data_right , float portion,rendering *render);
void drawTexture_with_frame(int width, int height, int device_width, int device_height,float s, GLuint* tex, unsigned char* data_left, unsigned char* data_right, float portion,rendering *render);
void drawTexture3(int width, int height, int device_width, int device_height,float s, GLuint* tex, unsigned char data_left, unsigned char data_right, float portion);

//set for split view for 4 cameras
void drawTexture_split(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data_left_cam1, unsigned char* data_right_cam1 , unsigned char* data_left_cam2, unsigned char* data_right_cam2, float portion);

//to draw som extra on top of the picture
void drawsomething(int width, int height); 
void draw_point(int width, int height,float frame_zoom, float frame_width, float frame_height,float frame_move);
void drawOverlayTexture(int width, int height, int device_width, int device_height, float s, GLuint* tex);
void drawBlank(void);
void drawBlack_screen(int width, int height, int device_width, int device_height);
void drawGrey_screen(int width, int height, int device_width, int device_height,rendering *render);

// function to recover memory form our list of characters 
GLvoid KillFont( GLvoid ); //base

// function to load in bitmap as a GL texture 
int LoadGLTextures(); //texture

// function to build our font list 
GLvoid BuildFont( GLvoid ); // texture

/* general OpenGL initialization function */
int initGLfont( GLvoid );

/* Function to print the string */
GLvoid glPrint( GLint w, GLint h, GLint x, GLint y, char *string, int set ); //texture
GLvoid glPrintStereo( GLint w, GLint h, GLint x, GLint y, char *string, int set );

/* general OpenGL initialization function */
int initGLFont( GLvoid );

/* Here goes our drawing code */
int drawGLQuestion( GLvoid ); 

#ifdef __cplusplus
}
#endif

#endif
