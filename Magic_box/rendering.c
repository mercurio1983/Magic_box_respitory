#include "rendering.h"

#define PI_ 3.141592654



void SDLinit(int width, int height)
{

  glEnable( GL_TEXTURE_2D );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glViewport( 0, 0, width, height );
  glClear( GL_COLOR_BUFFER_BIT );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void initTexture(GLuint* tex, int num) //int w, int h)
{

  int i;
  
  //glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  //glEnable(GL_CULL_FACE);

  //glEnable(GL_TEXTURE_2D);

  for( i = 0; i<num;i++){
    glGenTextures(1, &tex[i]);
    glBindTexture(GL_TEXTURE_2D, tex[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glClear( GL_COLOR_BUFFER_BIT );
  }

}

//static 
void idle(void)
{
  usleep(1000); 
}

// new window size or exposure
//static 
void reshape(int width, int height)
{
  GLfloat h = (GLfloat) height / (GLfloat) width;

  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -40.0);
}

//to draw for one eye without extra drawing where there exist some more parameters to render by moving picture
//pixel zoom and flipping image
void center(GLint w, GLint h,int rotate,float zoom, float move_image,float flip_horizontal,float flip_vertical)
{
  //GLfloat p0,p1;
      //GLint def_height = 1080;
      //GLint max_height = 1080;
      GLfloat z = zoom;
	  GLfloat m = move_image;
	  GLfloat fh = flip_horizontal;
	  GLfloat fv = flip_vertical;
      GLfloat rh = 0.75; //rotate format 480 divided by 640
  
  //applies all the rendering variables such as pixel zoom, move picture and flipping picture
  if(rotate== 0){
	  
	  //the standard to start is the picture itself and then the where picture is binded
      glPushMatrix();
      glBegin(GL_QUADS);
      
      //applies a function to stretch for zoom effect	
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
	}
	else if(rotate == 90){
	      glPushMatrix();
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m-2*rh))); glVertex3f(0.0f, 0.0f, -1.0f);	
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+2*rh))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+2*rh))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m-2*rh))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
		}
	
	else if(rotate == 180){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
  }
    else if(rotate == 270){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+2*rh))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m-2*rh))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m-2*rh)));  glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+2*rh))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
	}
	  //glPushMatrix();
	  //glBegin(GL_QUADS);	
      //glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      //glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      //glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      //glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f(0.0f, ((GLfloat)max_height- (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      //glEnd();
      //glPopMatrix();
	  
	  //glPushMatrix();
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glEnd(); 
	          
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, (GLfloat)max_height, -1.0f);
	  //glVertex3f(0.0f, (GLfloat)max_height, -1.0f);
	  //glEnd(); 
	 
	  //glPopMatrix();
	  //glColor3f(1.0f, 1.0f, 1.0f); 
		
		
		
		

} 

//to apply for extra rendering for one eye that is one frame on top of the picture
void center_with_frame(GLint w, GLint h,int rotate,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image,float move_image2,float flip_horizontal,float flip_vertical){
	
	//rendering variables
	//GLfloat p0,p1;
    //GLint def_height = 1080;
    //GLint max_height = 1080;
    GLfloat z = zoom;
	GLfloat m = move_image;
	GLfloat fhm = move_image2; //move image when flipped
	GLfloat zf = frame_zoom;
	GLfloat zw = frame_width; 
	GLfloat zh = frame_height;
	GLfloat zm = frame_move;
	GLfloat fh = flip_horizontal;
	GLfloat fv = flip_vertical;
	GLfloat rh = 0.75; //rotate format 480 divided by 640
	//if(rotate== 90){ 
	//printf("%f\n",m);
    //printf("%f\n",fhm);
	//}
	//else if(rotate== 270){ 
	////printf("%f\n",m);
    ////printf("%f\n",fhm);
    //}
    if(rotate== 0){ 
      //binding the picture and rendering with picture move, picture zoom and rotation
      glPushMatrix(); 
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
	}
	else if(rotate == 90){
      
      
      glPushMatrix();
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m+fhm-2*rh-(-zf-zw+zm)/((GLfloat)w)))); glVertex3f(0.0f, 0.0f, -1.0f);	
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+fhm+2*rh-(-zf-zw+zm)/((GLfloat)w)))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+fhm+2*rh-(-zf-zw+zm)/((GLfloat)w)))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m+fhm-2*rh-(-zf-zw+zm)/((GLfloat)w)))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
		}
	
	else if(rotate == 180){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f-z+m+fh*(-fh+(2*z-2*m))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f+z+m+fh*(fh+(-2*z-2*m))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
  }
    else if(rotate == 270){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+fhm+2*rh))); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z+fv*(-fv+(2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m+fhm-2*rh))); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 1.0f+rh-z+m+fh*(-fh+(2*z-2*m+fhm-2*rh)));  glVertex3f((GLfloat)w,(GLfloat)h , -1.0f);
      glTexCoord2f(0.0f+z+fv*(fv+(-2*z)), 0.0f-rh+z+m+fh*(fh+(-2*z-2*m+fhm+2*rh))); glVertex3f(0.0f, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);	  
	  //glPushMatrix();
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glEnd(); 
	          
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, (GLfloat)max_height, -1.0f);
	  //glVertex3f(0.0f, (GLfloat)max_height, -1.0f);
	  //glEnd(); 
	 
	 // glPopMatrix();
	  //glColor3f(1.0f, 1.0f, 1.0f); 
		
		
		
		
	
	
	
	if((rotate == 0) || (rotate == 180)){
	
	//drawing the frame on top of the picture to create the illusion of one 2D picture
	glPushMatrix();
	glBegin(GL_QUADS);  //left vertical
	glColor3f(0.75f,0.75f,0.75f);
	
	glVertex3f(0.0f, 0.0f, -0.8f);
	glVertex3f(0.0f+zf+zw, 0.0f, -0.8f);
	glVertex3f(0.0f+zf+zw, (GLfloat)h, -0.8f);
	glVertex3f(0.0f, (GLfloat)h, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //right vertical
	glColor3f(0.75f,0.75f,0.75f); 
	glVertex3f((GLfloat)w-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, (GLfloat)h, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h, -0.8f);
	glEnd();
	glBegin(GL_QUADS); //top horizontal
	glColor3f(0.75f,0.75f,0.75f); 
	glVertex3f(0.0f+zf+zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, 0.0f+zf+zh+zm, -0.8f);
	glVertex3f(0.0f+zf+zw, 0.0f+zf+zh+zm, -0.8f);
	glEnd();	
		
	glBegin(GL_QUADS); //bottom horizontal
	glColor3f(0.75f,0.75f,0.75f);
	glVertex3f(0.0f+zf+zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h, -0.8f);
	glVertex3f(0.0f+zf+zw, (GLfloat)h, -0.8f);
	glEnd();
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if((rotate == 90) || (rotate == 270)){
	
	glPushMatrix();
	glBegin(GL_QUADS);  //left vertical
	glColor3f(0.75f,0.75f,0.75f);
	glVertex3f(0.0f, 0.0f+zf+zh, -0.8f);
	glVertex3f(0.0f+zf+zw+zm, 0.0f+zf+zh, -0.8f);
	glVertex3f(0.0f+zf+zw+zm, (GLfloat)h-zf-zh, -0.8f);
	glVertex3f(0.0f, (GLfloat)h-zf-zh, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //right vertical
	glColor3f(0.75f,0.75f,0.75f); 
	glVertex3f((GLfloat)w-zf-zw+zm, 0.0f+zf+zh, -0.8f);
	glVertex3f((GLfloat)w, 0.0f+zf+zh, -0.8f);
	glVertex3f((GLfloat)w, (GLfloat)h-zf-zh, -0.8f);
	glVertex3f((GLfloat)w-zf-zw+zm, (GLfloat)h-zf-zh, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //top horizontal
	glColor3f(0.75f,0.75f,0.75f); 
	glVertex3f(0.0f, 0.0f, -0.8f); 				//glVertex3f(0.0f+zf+zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, 0.0f, -0.8f); 		//glVertex3f((GLfloat)w-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, 0.0f+zf+zh, -0.8f); 	//glVertex3f((GLfloat)w-zf-zw, 0.0f+zf+zh, -0.8f);
	glVertex3f(0.0f, 0.0f+zf+zh, -0.8f); 		//glVertex3f(0.0f+zf+zw, 0.0f+zf+zh+zm, -0.8f);
	glEnd();	
		
	glBegin(GL_QUADS); //bottom horizontal
	glColor3f(0.75f,0.75f,0.75f);
	glVertex3f(0.0f, (GLfloat)h-zf-zh, -0.8f); 			//glVertex3f(0.0f+zf+zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w, (GLfloat)h-zf-zh, -0.8f); 	//glVertex3f((GLfloat)w-zf-zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w, (GLfloat)h, -0.8f); 			//glVertex3f((GLfloat)w-zf-zw, (GLfloat)h, -0.8f);
	glVertex3f(0.0f, (GLfloat)h, -0.8f); 				//glVertex3f(0.0f+zf+zw, (GLfloat)h, -0.8f);
	glEnd();
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	}
	
	
	
	
	
	}

//drawing the picture for left image
void left(GLint w, GLint h, float s, float portion, int f,float zoom, float move_image)
{
  //GLfloat p0,p1;
  GLint def_height = 1080;
  GLint max_height = 1080;
  //GLfloat border = 0.0; // part of image
  //GLfloat borderpx = 0.0*w; // part of image
  GLfloat z = zoom;
  GLfloat m = move_image;

  //if( s > 1.0)
    //{
      //p0 = (s -1.0)/2.0 + border;
      //p1 = 1.0 - (s -1.0)/2.0 - border;
      //// Draw a textured quad	
      //glPushMatrix();
      //glBegin(GL_QUADS);
      //glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((0.0f), 0.0f, -1.0f);
      //glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      //glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h , -1.0f);
      //glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((0.0f), (GLfloat)h, -1.0f);
      //glEnd();
      
      //glBegin(GL_QUADS);
      //glTexCoord2f(p0, portion); glVertex3f(0.0f+borderpx, (GLfloat)(portion*h), -1.0f);
      //glTexCoord2f(p1, portion); glVertex3f((GLfloat)(w/2-borderpx), (GLfloat)(portion*h), -1.0f);
      //glTexCoord2f(p1, 1.0f); glVertex3f((GLfloat)(w/2-borderpx), (GLfloat)h, -1.0f);
      //glTexCoord2f(p0, 1.0f); glVertex3f(0.0f+borderpx, (GLfloat)h, -1.0f);
      //glEnd();
	  //glPopMatrix();
    //}
  //if( s <= 1.0)
    //{
      //float pix = s*w/2.0;
      //p0 = w/2.0-pix; 
      //p1 = pix; 
      // Draw a textured quad
      /*glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, 0.0f); glVertex2f((GLfloat)p0, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f((GLfloat)p1, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1, (GLfloat)h );
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();*/
 if(f == 0){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h, -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f(0.0f, (GLfloat)h, -1.0f);
      glEnd();
	  glPopMatrix();
	  
  }
  else{
	    
	  glPushMatrix();
	  
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glEnd(); 
	  //glColor3f(1.0f, 1.0f, 1.0f); 
	  //printf("the height is %d\n",h);
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
      glEnd();
	  
	   //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w/2, (GLfloat)max_height, -1.0f);
	  //glVertex3f(0.0f, (GLfloat)max_height, -1.0f);
	  //glEnd(); 
	  glColor3f(1.0f, 1.0f, 1.0f); 
	  glPopMatrix();
	  
	  }
      // Remove this segemet to remove black borders
      /*glBegin(GL_QUADS); 
      glColor3f(0.0,0.0,0.0);     
      glVertex2f((0.0f), (portion*h));
      glVertex2f((GLfloat)w/2, (portion*h));
      glVertex2f((GLfloat)w/2, (GLfloat)h );
      glVertex2f((0.0f), (GLfloat)h );
      glColor3f(1.0,1.0,1.0);
      glEnd();*/

      /*
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, portion); glVertex2f((GLfloat)p0, (GLfloat)(portion*h));
      glTexCoord2f(1.0f, portion); glVertex2f((GLfloat)p1, (GLfloat)(portion*h));
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1, (GLfloat)h );
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();
	  */
      
    //}
  
}

//drawing the picture for right image with frame
void right_with_frame(GLint w, GLint h, float s, float portion, int f,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image)
{
  //GLfloat p0,p1;
  GLint def_height = 1080;
  GLint max_height = 1080;
  GLfloat z = zoom;
  GLfloat m = move_image;
  GLfloat zf = frame_zoom;
   GLfloat zw = frame_width; 
   GLfloat zh = frame_height;
   GLfloat zm = frame_move;
  //if( s > 1.0)
    //{
      //p0 = (s -1.0)/2.0;
      //p1 = 1.0 - (s -1.0)/2.0;
      //// Draw a textured quad	
      //glPushMatrix();
      //glBegin(GL_QUADS);
      //glTexCoord2f(0.0+z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      //glTexCoord2f(1.0-z, 0.0f+z+m); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      //glTexCoord2f(1.0-z, 1.0f-z+m); glVertex3f((GLfloat)w, (GLfloat)h, -1.0f);
      //glTexCoord2f(0.0+z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h ,-1.0f);
      //glEnd();
      //glPopMatrix();
      
      //glBegin(GL_QUADS);
      //glTexCoord2f(p0, portion); glVertex3f((GLfloat)w/2, (GLfloat)(h*portion),-1.0f);
      //glTexCoord2f(p1, portion); glVertex3f((GLfloat)w, (GLfloat)(h*portion),-1.0f);
      //glTexCoord2f(p1, 1.0f); glVertex3f((GLfloat)w,  (GLfloat)h ,-1.0f);
      //glTexCoord2f(p0, 1.0f); glVertex3f((GLfloat)w/2, (GLfloat)h ,-1.0f);
      //glEnd();
    //}
  if(f == 0){
      
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w, (GLfloat)max_height , -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)max_height , -1.0f);
      glEnd();
      glPopMatrix();
   }
   else{
	   
	  glPushMatrix();
	  glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height- (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      glEnd();
      glPopMatrix();
	  
	  glPushMatrix();
	  glBegin(GL_QUADS); //bottom horizontal
	  glColor3f(0.0f, 0.0f, 0.0f);  
	  glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
	  glVertex3f((GLfloat)w, 0.0f, -1.0f);
	  glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  glEnd(); 
	          
	  glBegin(GL_QUADS); //bottom horizontal
	  glColor3f(0.0f, 0.0f, 0.0f);  
	  glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  glVertex3f((GLfloat)w, (GLfloat)max_height, -1.0f);
	  glVertex3f((GLfloat)w/2, (GLfloat)max_height, -1.0f);
	  glEnd(); 
	 
	  glPopMatrix();
	  glColor3f(1.0f, 1.0f, 1.0f); 
	 }
      // Remove this segemet to remove black borders
      /*glBegin(GL_QUADS); 
      glColor3f(0.0,0.0,0.0);     
      glVertex2f((GLfloat)w/2, (portion*h));
      glVertex2f((GLfloat)w, (portion*h));
      glVertex2f((GLfloat)w, (GLfloat)h );
      glVertex2f((GLfloat)w/2, (GLfloat)h );
      glColor3f(1.0,1.0,1.0);
      glEnd();*/
		
	  	
		/*
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, portion); glVertex2f((GLfloat)p0, (GLfloat)(h*portion));
      glTexCoord2f(1.0f, portion); glVertex2f((GLfloat)p1, (GLfloat)(h*portion));
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1,  (GLfloat)h);
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();*/
    //}
    
       glPushMatrix();
	glBegin(GL_QUADS);  //left vertical
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)w/2, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2+zf+zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2+zf+zw, (GLfloat)h, -0.8f);
	glVertex3f((GLfloat)w/2, (GLfloat)h, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //right vertical
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)w-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, 0.0f, -0.8f);
	glVertex3f((GLfloat)w, (GLfloat)h, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //top horizontal
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)w/2+zf+zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, 0.0f+zf+zh+zm, -0.8f);
	glVertex3f((GLfloat)w/2+zf+zw, 0.0f+zf+zh+zm, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS); //bottom horizontal
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)w/2+zf+zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w-zf-zw, (GLfloat)h, -0.8f);
	glVertex3f((GLfloat)w/2+zf+zw, (GLfloat)h, -0.8f);
	glEnd();

	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
}

//drawing the picture for left image with frame
void left_with_frame(GLint w, GLint h, float s, float portion, int f,float zoom, float frame_zoom, float frame_width, float frame_height, float frame_move, float move_image)
{
  //GLfloat p0,p1;
  GLint def_height = 480;
  GLint max_height = 1024;
  //GLfloat border = 0.0; // part of image
  //GLfloat borderpx = 0.0*w; // part of image
  GLfloat z = zoom;
  GLfloat m = move_image;
  GLfloat zf = frame_zoom;
  GLfloat zw = frame_width; 
  GLfloat zh = frame_height;
  GLfloat zm = frame_move;
  //if( s > 1.0)
    //{
      //p0 = (s -1.0)/2.0 + border;
      //p1 = 1.0 - (s -1.0)/2.0 - border;
      //// Draw a textured quad	
      //glPushMatrix();
      //glBegin(GL_QUADS);
      //glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((0.0f), 0.0f, -1.0f);
      //glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      //glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h , -1.0f);
      //glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((0.0f), (GLfloat)h, -1.0f);
      //glEnd();
      
      //glBegin(GL_QUADS);
      //glTexCoord2f(p0, portion); glVertex3f(0.0f+borderpx, (GLfloat)(portion*h), -1.0f);
      //glTexCoord2f(p1, portion); glVertex3f((GLfloat)(w/2-borderpx), (GLfloat)(portion*h), -1.0f);
      //glTexCoord2f(p1, 1.0f); glVertex3f((GLfloat)(w/2-borderpx), (GLfloat)h, -1.0f);
      //glTexCoord2f(p0, 1.0f); glVertex3f(0.0f+borderpx, (GLfloat)h, -1.0f);
      //glEnd();
	  //glPopMatrix();
    //}
  //if( s <= 1.0)
    //{
      //float pix = s*w/2.0;
      //p0 = w/2.0-pix; 
      //p1 = pix; 
      // Draw a textured quad
      /*glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, 0.0f); glVertex2f((GLfloat)p0, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f((GLfloat)p1, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1, (GLfloat)h );
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();*/
      
      
  if(f == 0){
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h, -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f(0.0f, (GLfloat)h, -1.0f);
      glEnd();
	  glPopMatrix();
	  
  }
  else{
	    
	  glPushMatrix();
	  
	  glBegin(GL_QUADS); //bottom horizontal
	  glColor3f(0.0f, 0.0f, 0.0f);  
	  glVertex3f(0.0f, 0.0f, -1.0f);
	  glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
	  glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  glEnd(); 
	  glColor3f(1.0f, 1.0f, 1.0f); 
	  printf("the height is %d\n",h);
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
      glEnd();
	  
	   glBegin(GL_QUADS); //bottom horizontal
	  glColor3f(0.0f, 0.0f, 0.0f);  
	  glVertex3f(0.0f, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  glVertex3f((GLfloat)w/2, (GLfloat)max_height, -1.0f);
	  glVertex3f(0.0f, (GLfloat)max_height, -1.0f);
	  glEnd(); 
	  glColor3f(1.0f, 1.0f, 1.0f); 
	  glPopMatrix();
	  
	  }

	  
      // Remove this segemet to remove black borders
      /*glBegin(GL_QUADS); 
      glColor3f(0.0,0.0,0.0);     
      glVertex2f((0.0f), (portion*h));
      glVertex2f((GLfloat)w/2, (portion*h));
      glVertex2f((GLfloat)w/2, (GLfloat)h );
      glVertex2f((0.0f), (GLfloat)h );
      glColor3f(1.0,1.0,1.0);
      glEnd();*/

      /*
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, portion); glVertex2f((GLfloat)p0, (GLfloat)(portion*h));
      glTexCoord2f(1.0f, portion); glVertex2f((GLfloat)p1, (GLfloat)(portion*h));
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1, (GLfloat)h );
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();
	  */
      
    //}
    
    glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 0.0f, -0.8f);
	glVertex3f(0.0f+zf+zw, 0.0f, -0.8f);
	glVertex3f(0.0f+zf+zw, (GLfloat)h, -0.8f);
	glVertex3f(0.0f, (GLfloat)h, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)w/2, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, (GLfloat)h, -0.8f);
	glVertex3f((GLfloat)w/2, (GLfloat)h, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f+zf+zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, 0.0f, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, 0.0f+zf+zh+zm, -0.8f);
	glVertex3f(0.0f+zf+zw, 0.0f+zf+zh+zm, -0.8f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f+zf+zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, (GLfloat)h-zf-zh+zm, -0.8f);
	glVertex3f((GLfloat)w/2-zf-zw, (GLfloat)h, -0.8f);
	glVertex3f(0.0f+zf+zw, (GLfloat)h, -0.8f);
	glEnd();

	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
}

//drawing the picture for right image without frame
void right(GLint w, GLint h, float s, float portion, int f,float zoom, float move_image)
{
  //GLfloat p0,p1;
  GLint def_height = 1080;
  GLint max_height = 1080;
  GLfloat z = zoom;
  GLfloat m = move_image;
  if(f== 0){
      
      glPushMatrix();
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w, 0.0f, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w, (GLfloat)h , -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((GLfloat)w/2, (GLfloat)h , -1.0f);
      glEnd();
      glPopMatrix();
   }
   else{
	   
	  glPushMatrix();
	  glBegin(GL_QUADS);	
      glTexCoord2f(0.0f+z, 0.0f+z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 0.0f+z+m); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
      glTexCoord2f(1.0f-z, 1.0f-z+m); glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      glTexCoord2f(0.0f+z, 1.0f-z+m); glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height , -1.0f);
      glEnd();
      glPopMatrix();
	  
	  //glPushMatrix();
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f((GLfloat)w/2, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, 0.0f, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2, -1.0f);
	  //glEnd(); 
	          
	  //glBegin(GL_QUADS); //bottom horizontal
	  //glColor3f(0.0f, 0.0f, 0.0f);  
	  //glVertex3f((GLfloat)w/2, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, ((GLfloat)max_height - (GLfloat)def_height)/2+(GLfloat)def_height, -1.0f);
	  //glVertex3f((GLfloat)w, (GLfloat)max_height, -1.0f);
	  //glVertex3f((GLfloat)w/2, (GLfloat)max_height, -1.0f);
	  //glEnd(); 
	 
	 // glPopMatrix();
	  glColor3f(1.0f, 1.0f, 1.0f); 
	 }

      // Remove this segemet to remove black borders
      /*glBegin(GL_QUADS); 
      glColor3f(0.0,0.0,0.0);     
      glVertex2f((GLfloat)w/2, (portion*h));
      glVertex2f((GLfloat)w, (portion*h));
      glVertex2f((GLfloat)w, (GLfloat)h );
      glVertex2f((GLfloat)w/2, (GLfloat)h );
      glColor3f(1.0,1.0,1.0);
      glEnd();*/
		
	  	
		/*
      glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, portion); glVertex2f((GLfloat)p0, (GLfloat)(h*portion));
      glTexCoord2f(1.0f, portion); glVertex2f((GLfloat)p1, (GLfloat)(h*portion));
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)p1,  (GLfloat)h);
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)p0, (GLfloat)h );
      glEnd();*/
    }

//drawing the picture for one eye that is adapted for 3dvgl library with frame and applying a struct
void drawTexture_eye2_frame(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render){
  
  
  //int fullscreen;
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  //if(device_height < height){
	  //fullscreen = 1;
	//   } 
  //else{
	  //fullscreen = 0;
	 // }	   
	
  
 
   glBindTexture( GL_TEXTURE_2D, tex[0] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data); //frames[i]->image); 

  center_with_frame(width,height,render->rotate,render->zoom,render->frame_zoom, render->frame_width,  render->frame_height, render->frame_move, render->move_image, render->move_image2,render->flip_horizontal,render->flip_vertical);
  
  //glDisable(GL_TEXTURE_2D);	
	}

//drawing the picture for one eye that is adapted for 3dvgl library without frame and applying a struct
void drawTexture_eye2(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data ,rendering *render){
 

 // int fullscreen =0;
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  //if(device_height < height){
	  //fullscreen = 1;
	   //} 
  //else{
	  //fullscreen = 0;
	  //}	   
	
  
 
  //if (eye == 0){
   glBindTexture( GL_TEXTURE_2D, tex[0] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data); //frames[i]->image); 
  //}
  //else{
	//glBindTexture( GL_TEXTURE_2D, tex[1] );
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_right); //frames[i]->image);
	  //}
  center(width,height,render->rotate,render->zoom,render->move_image,render->flip_horizontal,render->flip_vertical);
  glDisable(GL_TEXTURE_2D);
  
}

//drawTexture(screen->w, screen->h, device_width, device_height, stretch, video_texture, frames[0]->image, frames[1]->image, portion);
//static 
//drawing regular left and right image without a frame
void drawTexture(int width, int height, int device_width, int device_height,float s, GLuint* tex, unsigned char* data_left, unsigned char* data_right, float portion,rendering *render)
{ 
  int fullscreen;
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  if(device_height < height){
	  fullscreen = 1;
	   } 
  else{
	  fullscreen = 0;
	  }	   
	
  
  glBindTexture( GL_TEXTURE_2D, tex[0] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_left); //frames[i]->image);
  left(width,height, s, portion,fullscreen,render->zoom, render->move_image);
  glBindTexture( GL_TEXTURE_2D, tex[1] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_right); //frames[i]->image);
  right(width,height, s, portion,fullscreen,render->zoom, render->move_image);
  
  glDisable(GL_TEXTURE_2D);
  
}

//drawing the left and right images with a frame
void drawTexture_with_frame(int width, int height, int device_width, int device_height,float s, GLuint* tex, unsigned char* data_left, unsigned char* data_right, float portion,rendering *render)
{
  int fullscreen;
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
    if(device_height < height){
	  fullscreen = 1;
	   } 
  else{
	  fullscreen = 0;
	  }	  
  
  glBindTexture( GL_TEXTURE_2D, tex[0] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_left); //frames[i]->image);
  left_with_frame(width,height, s, portion,fullscreen,render->zoom,render->frame_zoom, render->frame_width,  render->frame_height, render->frame_move, render->move_image);
  glBindTexture( GL_TEXTURE_2D, tex[1] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_right); //frames[i]->image);
  right_with_frame(width,height, s, portion,fullscreen,render->zoom,render->frame_zoom, render->frame_width,  render->frame_height, render->frame_move, render->move_image);
  
  glDisable(GL_TEXTURE_2D);
  
}

//(screen->w, screen->h, device_width, device_height, stretch, video_texture, frames[0]->image, frames[1]->image, portion);

//splitting up the cameras for four images that is rendered left cam1 pair1, left cam2 pair2, right cam3 pair1 and right cam4 pair2.  
void drawTexture_split(int width, int height, int device_width, int device_height, float s, GLuint* tex, unsigned char* data_left_cam1, unsigned char* data_right_cam1 , unsigned char* data_left_cam2, unsigned char* data_right_cam2, float portion)
{
  //int fullscreen;
  // take note that glTexCoord2f(width coordinate of pic, height coordinate of pic);
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;
  int left_border_split;
  int right_border_split;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  int number_of_images = 4;
  //int set_tex_value = 0;
  int count1;
  //for (count1= 0;count1<number_of_images;count1++){
  //  if (count1 < 2){
  //		}
  //  else{set_tex_value = 1;}
    
    
  //if(device_height < height){
	  ////fullscreen = 1;
	   //} 
  //else{
	  ////fullscreen = 0;
	  //}	  
    
	glBindTexture(GL_TEXTURE_2D,tex[0]);
	//glTexImage2D(GLenum  target,  GLint  level,  GLint  internalFormat,  GLsizei  width,  GLsizei  height,  GLint  border,  GLenum  format,  GLenum  type,  const GLvoid *  data);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_left_cam1);
	//glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGB,  device_width,  device_height,  0,  GL_RGB,  GL_UNSIGNED_BYTE, data_left);
	
	
	count1= 0;
	left_border_split = (width*count1)/number_of_images;
	right_border_split = width*1/number_of_images*(count1+1); //+24; //24 is 10% of 240 that is the half of 480 total width
	glBegin(GL_QUADS);	
      glTexCoord2f(0.2f, 0.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, 0.0f);
      glTexCoord2f(0.8f, 0.0f); glVertex2f((GLfloat)right_border_split, 0.0f);
      glTexCoord2f(0.8f, 1.0f); glVertex2f((GLfloat)right_border_split, (GLfloat)height);
      glTexCoord2f(0.2f, 1.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, (GLfloat)height);
    glEnd();
    
    /*
    glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f(width/2, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f(width/2, (GLfloat)height );
      glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, (GLfloat)height );
    glEnd();
    */    
    count1= 1;
    glBindTexture(GL_TEXTURE_2D,tex[1]);
	//glTexImage2D(GLenum  target,  GLint  level,  GLint  internalFormat,  GLsizei  width,  GLsizei  height,  GLint  border,  GLenum  format,  GLenum  type,  const GLvoid *  data);
	glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGB,  device_width,  device_height,  0,  GL_RGB,  GL_UNSIGNED_BYTE, data_left_cam2);
	
	
	left_border_split = (width*count1)/number_of_images; //+24; //24 is 10% of 240 that is the half of 480 total width
	right_border_split = width*1/number_of_images*(count1+1);
	glBegin(GL_QUADS);	
      glTexCoord2f(0.2f, 0.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, 0.0f);
      glTexCoord2f(0.8f, 0.0f); glVertex2f((GLfloat)right_border_split, 0.0f);
      glTexCoord2f(0.8f, 1.0f); glVertex2f((GLfloat)right_border_split, (GLfloat)height);
      glTexCoord2f(0.2f, 1.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, (GLfloat)height);
    glEnd();
    /*
    glBegin(GL_QUADS);	
      glTexCoord2f(0.0f, 0.0f); glVertex2f((GLfloat)width/2, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f((GLfloat)width, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f((GLfloat)width, (GLfloat)height );
      glTexCoord2f(0.0f, 1.0f); glVertex2f((GLfloat)width/2, (GLfloat)height );
    glEnd();
    */
    
    count1= 2;
    glBindTexture(GL_TEXTURE_2D,tex[2]);
	//glTexImage2D(GLenum  target,  GLint  level,  GLint  internalFormat,  GLsizei  width,  GLsizei  height,  GLint  border,  GLenum  format,  GLenum  type,  const GLvoid *  data);
	glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGB,  device_width,  device_height,  0,  GL_RGB,  GL_UNSIGNED_BYTE, data_right_cam1);
	
	
	left_border_split = (width*count1)/number_of_images;
	right_border_split = width*1/number_of_images*(count1+1); //-24; //24 is 10% of 240 that is the half of 480 total width
	glBegin(GL_QUADS);	
      glTexCoord2f(0.2f, 0.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, 0.0f);
      glTexCoord2f(0.8f, 0.0f); glVertex2f((GLfloat)right_border_split, 0.0f);
      glTexCoord2f(0.8f, 1.0f); glVertex2f((GLfloat)right_border_split, (GLfloat)height);
      glTexCoord2f(0.2f, 1.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, (GLfloat)height);
    glEnd();
    
    count1= 3;
    glBindTexture(GL_TEXTURE_2D,tex[3]);
	//glTexImage2D(GLenum  target,  GLint  level,  GLint  internalFormat,  GLsizei  width,  GLsizei  height,  GLint  border,  GLenum  format,  GLenum  type,  const GLvoid *  data);
	glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGB,  device_width,  device_height,  0,  GL_RGB,  GL_UNSIGNED_BYTE, data_right_cam2);
	
	
	left_border_split = (width*count1)/number_of_images; //-24; //24 is 10% of 240 that is the half of 480 total width
	right_border_split = width*1/number_of_images*(count1+1);
	glBegin(GL_QUADS);	
      glTexCoord2f(0.2f, 0.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, 0.0f);
      glTexCoord2f(0.8f, 0.0f); glVertex2f((GLfloat)right_border_split, 0.0f);
      glTexCoord2f(0.8f, 1.0f); glVertex2f((GLfloat)right_border_split, (GLfloat)height);
      glTexCoord2f(0.2f, 1.0f); glVertex2f((0.0f)+(GLfloat)left_border_split, (GLfloat)height);
    glEnd();
  
	
       
  }

//drawing for relugar left and right image
void drawTexture3(int width, int height, int device_width, int device_height,float s, GLuint* tex, unsigned char data_left, unsigned char data_right, float portion)
{
  int fullscreen;
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  if(device_height < height){
	  fullscreen = 1;
	   } 
  else{
	  fullscreen = 0;
	  }	  
  
  glBindTexture( GL_TEXTURE_2D, tex[0] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_left); //frames[i]->image);
  left(width,height, s, portion,fullscreen,0,0);
  glBindTexture( GL_TEXTURE_2D, tex[1] );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data_right); //frames[i]->image);
  right(width,height, s, portion,fullscreen,0,0);
  
  glDisable(GL_TEXTURE_2D);
  
}


void drawOverlayTexture(int width, int height, int device_width, int device_height, float s, GLuint* tex )
{
  int fullscreen;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glOrtho(0.0f, width, height, 0.0f, -1.0, 1.0f);
  glEnable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  if(device_height < height){
	  fullscreen = 1;
	   } 
  else{
	  fullscreen = 0;
	  }	    
  
  glBindTexture( GL_TEXTURE_2D, tex[0] );
  left(width,height, s, 0.0,fullscreen,0,0);
  glBindTexture( GL_TEXTURE_2D, tex[1] );
  right(width,height, s, 0.0,fullscreen,0,0);
  
}

void draw_point(int width, int height,float frame_zoom, float frame_width, float frame_height,float frame_move){
	
	
	GLfloat zf = frame_zoom;
	GLfloat zw = frame_width; 
	GLfloat zh = frame_height;
	GLfloat zm = frame_move;
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    
	glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity();
	
	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f); //mixing RGB color
	glPointSize(100.0f);
	//glBegin(GL_POINTS);
		//glVertex3f( (GLfloat)width-zf-zw+zm-50.0f,(GLfloat)height-zf-zh-50.0f,-0.3f);
	//glEnd();
	double i_angle = 0;
	int radius = 30;
	glBegin(GL_POLYGON);
		
		//for (double i= 0; i< 2*PI; i+= PI/6){
			//glVertex3f(cos(i)*radius, sin(i)*radius,-0.3f);}
			//glVertex3f( (GLfloat)width-zf-zw+zm-50.0f,(GLfloat)height-zf-zh-50.0f,-0.3f);
			
		//drawing a circle not soo smooth depends on the number of points
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle= PI_/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle= PI_*2/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*3/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*4/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*5/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*7/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*8/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*9/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*10/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		i_angle=PI_*11/6;
		glVertex3f(-(GLfloat)cos(i_angle)*radius+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)sin(i_angle)*radius+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		
		 
		//glVertex3f(-(GLfloat)polygonal_width+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)polygonal_height+(GLfloat)height-zf-zh-50.0f,-0.3f);//first vertex
		//glVertex3f((GLfloat)polygonal_width+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)polygonal_height+(GLfloat)height-zf-zh-50.0f,-0.3f);//second vertex
		//glVertex3f((GLfloat)polygonal_width*2+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)0+(GLfloat)height-zf-zh-50.0f,-0.3f);//third vertex
		//glVertex3f((GLfloat)polygonal_width+(GLfloat)width-zf-zw+zm-50.0f,-(GLfloat)polygonal_height+(GLfloat)height-zf-zh-50.0f,-0.3f);//fourth vertex
		//glVertex3f(-(GLfloat)polygonal_width+(GLfloat)width-zf-zw+zm-50.0f,-(GLfloat)polygonal_height+(GLfloat)height-zf-zh-50.0f,-0.3f);//fifth vertex
		//glVertex3f(-(GLfloat)polygonal_width*2+(GLfloat)width-zf-zw+zm-50.0f,(GLfloat)0+(GLfloat)height-zf-zh-50.0f,-0.3f);//sixth vertex
	
	glEnd();
	
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	} 


void drawsomething(int width, int height) {
	//Clear information from last draw
	//glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	
	int count1 = 0;
	int count2 = 0;
	int left_border_split = 0;
	int right_border_split = 0;
	int number_of_images = 4;
	int line_width = 6;
	int polygonal_height = 5;
	int polygonal_width = 4;
	//glEnable(GL_TEXTURE_2D);
  
    // Set Projection Matrix
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	//glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
	//upper_coordinate += resize_vertical;
	//lower_coordinate += resize_vertical;
	
	//stringstream converter_upper (stringstream::in | stringstream::out);
	//stringstream converter_lower (stringstream::in | stringstream::out);
	
	//converter_upper << upper_coordinate;
	//converter_lower << lower_coordinate;
	
//string upper_coord = converter_upper.str();
	//string lower_coord = converter_lower.str();
	
	//upper_coord = upper_coord.append("f");
	//lower_coord = lower_coord.append("f");
	
	//cout << upper_coord << endl;
	//cout << lower_coord << endl;
	
	//int2str(int new_upper_coordinate)
	//Trapezoid
	
	glPushMatrix();
	
	count1 = 1;
	left_border_split = (width*count1)/number_of_images-line_width/2; //24 is 10% of 240 that is the half of 480 total width
	right_border_split = (width*count1)/number_of_images+line_width/2; //24 is 10% of 240 that is the half of 480 total width
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)left_border_split, 0.0f, -0.8f);
	glVertex3f((GLfloat)right_border_split, 0.0f, -0.8f);
	glVertex3f((GLfloat)right_border_split, (GLfloat)height, -0.8f);
	glVertex3f((GLfloat)left_border_split, (GLfloat)height, -0.8f);
	glEnd();
	
	glColor3f(0.6f,0.6f,0.6f); //mixing RGB color
    count2 = 1;
    
	left_border_split = (width*count2)/number_of_images;
    glBegin(GL_POLYGON);//begin drawing of polygon
    glVertex3f(-(GLfloat)polygonal_width+(GLfloat)left_border_split,(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//first vertex
    glVertex3f((GLfloat)polygonal_width+(GLfloat)left_border_split,(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//second vertex
    glVertex3f((GLfloat)polygonal_width*2+(GLfloat)left_border_split,(GLfloat)0+(GLfloat)height*0.5,-0.3f);//third vertex
    glVertex3f((GLfloat)polygonal_width+(GLfloat)left_border_split,-(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//fourth vertex
    glVertex3f(-(GLfloat)polygonal_width+(GLfloat)left_border_split,-(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//fifth vertex
    glVertex3f(-(GLfloat)polygonal_width*2+(GLfloat)left_border_split,(GLfloat)0+(GLfloat)height*0.5,-0.3f);//sixth vertex
	glEnd();
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glPopMatrix();
	
	glPushMatrix();
	count2 = 3;
	left_border_split = (width*count2)/number_of_images-line_width/2; //24 is 10% of 240 that is the half of 480 total width
	right_border_split = (width*count2)/number_of_images+line_width/2; //24 is 10% of 240 that is the half of 480 total width
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex3f((GLfloat)left_border_split, 0.0f, -0.8f);
	glVertex3f((GLfloat)right_border_split, 0.0f, -0.8f);
	glVertex3f((GLfloat)right_border_split, (GLfloat)height, -0.8f);
	glVertex3f((GLfloat)left_border_split, (GLfloat)height, -0.8f);
	glEnd();
	
	 
	
	
	
	glColor3f(0.6f,0.6f,0.6f); //mixing RGB color
    count2 = 3;
	left_border_split = (width*count2)/number_of_images;
    glBegin(GL_POLYGON);//begin drawing of polygon
    glVertex3f(-(GLfloat)polygonal_width+(GLfloat)left_border_split,(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//first vertex
    glVertex3f((GLfloat)polygonal_width+(GLfloat)left_border_split,(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//second vertex
    glVertex3f((GLfloat)polygonal_width*2+(GLfloat)left_border_split,(GLfloat)0+(GLfloat)height*0.5,-0.3f);//third vertex
    glVertex3f((GLfloat)polygonal_width+(GLfloat)left_border_split,-(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//fourth vertex
    glVertex3f(-(GLfloat)polygonal_width+(GLfloat)left_border_split,-(GLfloat)polygonal_height+(GLfloat)height*0.5,-0.3f);//fifth vertex
    glVertex3f(-(GLfloat)polygonal_width*2+(GLfloat)left_border_split,(GLfloat)0+(GLfloat)height*0.5,-0.3f);//sixth vertex
	glEnd();
	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
	//glEnd(); //End quadrilateral coordinates
	
	//glBegin(GL_TRIANGLES); //Begin triangle coordinates
	//GLfloat parameter = -7.0f;
	
	
	//glEnd(); //End triangle coordinates
	
	//glutSwapBuffers(); //Send the 3D scene to the screen
}
void drawGrey_screen(int width, int height, int device_width, int device_height,rendering *render)
{
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;
  GLfloat zf = render->frame_zoom;
  GLfloat zw = render->frame_width; 
  GLfloat zh = render->frame_height;
  GLfloat zm = render->frame_move;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  glDisable(GL_TEXTURE_2D);
  
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  //glPushMatrix();
  //glColor3f(0.75f,0.75f,0.75f);
  //glBegin(GL_QUADS);	
  //glVertex3f(0.0f+zf+zw+zm, 0.0f+zf+zh, -0.9f);
  //glVertex3f((GLfloat)width-zf-zw+zm, 0.0f+zf+zh, -0.9f);
  //glVertex3f((GLfloat)width-zf-zw+zm, (GLfloat)height-zf-zh , -0.9f);
  //glVertex3f(0.0f+zf+zw+zm, (GLfloat)height-zf-zh , -0.9f);
  //glEnd();
  //glPopMatrix();
  //glColor3f(1.0f,1.0f,1.0f);
  
  glPushMatrix();
  glColor3f(0.75f,0.75f,0.75f);
  glBegin(GL_QUADS);	
  glVertex3f(0.0f, 0.0f, -0.9f);
  glVertex3f((GLfloat)width, 0.0f, -0.9f);
  glVertex3f((GLfloat)width, (GLfloat)height , -0.9f);
  glVertex3f(0.0f, (GLfloat)height , -0.9f);
  glEnd();
  glPopMatrix();
  glColor3f(1.0f,1.0f,1.0f);
  
  //glBindTexture( GL_TEXTURE_2D, tex[0] );
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data); //frames[i]->image);
  //draw(width,height);
  
  glEnable(GL_TEXTURE_2D);
  
}
 
void drawBlack_screen(int width, int height, int device_width, int device_height)
{
  //int i;
  //int frame_ready = 1;
  //GLfloat p0,p1;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glColor3f(0.0f, 0.0f, 0.0f);
  //glEnable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_2D);
  // Set Projection Matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  
  // Switch to Model View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_QUADS);	
  glVertex3f(0.0f, 0.0f, -0.9f);
  glVertex3f((GLfloat)width, 0.0f, -0.9f);
  glVertex3f((GLfloat)width, (GLfloat)height , -0.9f);
  glVertex3f(0.0f, (GLfloat)height , -0.9f);
  glEnd();
  glPopMatrix();
  glColor3f(1.0f,1.0f,1.0f);
  //glBindTexture( GL_TEXTURE_2D, tex[0] );
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, device_width,device_height,0, GL_RGB, GL_UNSIGNED_BYTE, data); //frames[i]->image);
  //draw(width,height);
  
 
  
}

void drawBlank(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


/* Function to print the string */
//GLvoid glPrintStereo( GLint w, GLint h, GLint x, GLint y, char *string, int set )
//{

  ////printf("w %d, h %d, x %d, y %d\n",w, h, x,y);
  //glPrint(w, h, x, y, string, set );
  //glPrint(w, h, (x+w/2), y, string, set );

//}

/* Here goes our drawing code */
int drawGLQuestion( GLvoid )
{
    /* These are to calculate our fps */
    //static GLint T0     = 0;
    //static GLint Frames = 0;

    /* Clear The Screen And The Depth Buffer */
    
  //
  //glColor3f( 1.0f , 1.0f , 1.0f );
  //glPrint((int) 640, (int) 480,  ( int ) (640/2),( int ) (480/2), "Is this question visibile and white?", 0 );

    /* Draw it to the screen */
    //SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
    /*Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }
    usleep(10000);*/

    return (int)true;
}


/*******************************************************************************************/

// function to build our font list 
void BuildFont( void )
{
  GLuint loop; // Loop variable               
  float cx;    // Holds Our X Character Coord 
  float cy;    // Holds Our Y Character Coord 

  // Creating 256 Display List 
  base  = glGenLists( 256 );
  // Select Our Font Texture 
  glBindTexture( GL_TEXTURE_2D, texture[0] );

  // Loop Through All 256 Lists 
  for ( loop = 0; loop < 256; loop++ )
    {
      /* NOTE:
       *  BMPs are stored with the top-leftmost pixel being the
       * last byte and the bottom-rightmost pixel being the first
       * byte. So an image that is displayed as
       *    1 0
       *    0 0
       * is represented data-wise like
       *    0 0
       *    0 1
       * And because SDL_LoadBMP loads the raw data without
       * translating to how it is thought of when viewed we need
       * to start at the bottom-right corner of the data and work
       * backwards to get everything properly. So the below code has
       * been modified to reflect this. Examine how this is done and
       * how the original tutorial is done to grasp the differences.
       *
       * As a side note BMPs are also stored as BGR instead of RGB
       * and that is why we load the texture using GL_BGR. It's
       * bass-ackwards I know but whattaya gonna do?
       */

      // X Position Of Current Character /
      cx = 1 - ( float )( loop % 16 ) / 16.0f;
      // Y Position Of Current Character /
      cy = 1 - ( float )( loop / 16 ) / 16.0f;

      // Start Building A List /
      glNewList( base + ( 255 - loop ), GL_COMPILE );
      // Use A Quad For Each Character /
      glBegin( GL_QUADS );
      // Texture Coord (Bottom Left) /
      glTexCoord2f( cx - 0.0625, cy );
      // Vertex Coord (Bottom Left) /
      //glVertex2i( 0, 0 );
      glVertex2i( 0, -32 );

      // Texture Coord (Bottom Right) /
      glTexCoord2f( cx, cy );
      // Vertex Coord (Bottom Right) /
      //glVertex2i( 32, 0 );
      glVertex2i( 0, 0 );

      // Texture Coord (Top Right) /
      glTexCoord2f( cx, cy - 0.0610f );
      // Vertex Coord (Top Right) /
      //glVertex2i( 32, 32 );
      glVertex2i( 32, 0 );

      // Texture Coord (Top Left) /
      glTexCoord2f( cx - 0.0610f, cy - 0.0610f);
      // Vertex Coord (Top Left) /
      //glVertex2i( 0, 32 );
      glVertex2i( 32, -32 );
      glEnd( );

      // Move To The Left Of The Character /
      glTranslated( 0, 32, 0 );
      glEndList( );
    }
}

// function to load in bitmap as a GL texture 
int LoadGLTextures()
{
  // Status indicator 
  //int Status = FALSE;
  bool status = false;

  // Create storage space for the texture 
  SDL_Surface *TextureImage[2];

  // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit 
  if ( ( TextureImage[0] = SDL_LoadBMP( "font2.bmp" ) ) && 
       ( TextureImage[1] = SDL_LoadBMP( "font.bmp" ) ) )
    {
	
      // Set the status to true 
      //Status = TRUE;
      status = true;

      // Create The Texture
      glGenTextures( NUM_TEXTURES, &texture[0] );

      // Load in texture 1
      // Typical Texture Generation Using Data From The Bitmap 
      glBindTexture( GL_TEXTURE_2D, texture[0] );

      // Generate The Texture
      glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
		    TextureImage[0]->h, 0, GL_BGR,
		    GL_UNSIGNED_BYTE, TextureImage[0]->pixels );
	    
      // Nearest Filtering
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

      // Load in texture 2
      // Typical Texture Generation Using Data From The Bitmap 
      glBindTexture( GL_TEXTURE_2D, texture[1] );

      // Linear Filtering 
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

      // Generate The Texture 
      glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[1]->w, TextureImage[1]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage[1]->pixels );
    }

  // Free up any memory we may have used 
  if ( TextureImage[0] )
    SDL_FreeSurface( TextureImage[0] );
  if ( TextureImage[1] )
    SDL_FreeSurface( TextureImage[1] );

  //return Status;
  return (int)status;
}

// general OpenGL initialization function /
int initGLfont( void )
{

  // Load in the textures 
  if ( !LoadGLTextures( ) )
    return (int)false;

    // Build our font list 
    BuildFont( );

    // Enable smooth shading 
    glShadeModel( GL_SMOOTH );

    // Set the background black 
    //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );

    // Depth buffer setup 
    glClearDepth( 1.0f );

    // The Type Of Depth Test To Do 
    glDepthFunc( GL_LEQUAL );

    // Select The Type Of Blending 
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    // Enable 2D Texture Mapping 
    glEnable( GL_TEXTURE_2D );
    
    return (int)true;
}

void KillFont( void )
{
  glDeleteLists( base, 256 ); // Delete All 256 Display Lists 

  return;
}

void glPrint( GLint w, GLint h, GLint x, GLint y, char *string, int set )
{
    if ( set > 1 )
		set = 1;

    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    // Re-enable Blending 
    glDisable( GL_BLEND );

    // Select our texture 
    glBindTexture( GL_TEXTURE_2D, texture[0] );

    // Disable depth testing 
    glDisable( GL_DEPTH_TEST );

    // Select The Projection Matrix 
    glMatrixMode( GL_PROJECTION );
    // Store The Projection Matrix 
    glPushMatrix( );

    // Reset The Projection Matrix 
    glLoadIdentity( );
    // Set Up An Ortho Screen 
    glOrtho( 0, w, 0, h, -1, 1 );

    // Select The Modelview Matrix 
    glMatrixMode( GL_MODELVIEW );
    // Stor the Modelview Matrix 
    glPushMatrix( );
    // Reset The Modelview Matrix 
    glLoadIdentity( );

    // Position The Text (0,0 - Bottom Left) 
    glTranslated( x, y, 0 );

    // Choose The Font Set (0 or 1) 
    glListBase( base - 32 + ( 128 * set ) );

    // Write The Text To The Screen 
    glCallLists( strlen( string ), GL_BYTE, string );

    // Select The Projection Matrix 
    glMatrixMode( GL_PROJECTION );
    // Restore The Old Projection Matrix 
    glPopMatrix( );

    // Select the Modelview Matrix 
    glMatrixMode( GL_MODELVIEW );
    // Restore the Old Projection Matrix 
    glPopMatrix( );

    // Re-enable Depth Testing 
    glEnable( GL_DEPTH_TEST );
}

void glPrintStereo( GLint w, GLint h, GLint x, GLint y, char *string, int set )
{

  //printf("w %d, h %d, x %d, y %d\n",w, h, x,y);
  glPrint(w, h, x, y, string, set );
  //glPrint(w, h, (x+w/2), y, string, set );

}

