#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]){

//char line[100];
	printf("test run c-program after call with argument");
	//int i;
	//for(i = 0; i<argc; i+=1){
    unsigned int delay_enable;
	unsigned int delay_on;  //delay enabled or disabled
	unsigned int induction;  //the induction time
	unsigned int stop_signal;  //the stop time
	unsigned int test_movement;  //test movement time
	unsigned int blackscreen; //black screen time
		  if (argc > 4){
	induction = (unsigned int)atoi(argv[1]); //step size
	stop_signal = (unsigned int)atoi(argv[2]);  //delay enabled or disabled
	test_movement = (unsigned int)atoi(argv[3]);  //the duration
	blackscreen = (unsigned int)atoi(argv[4]);  //number of loops
	//reset_time = (unsigned int)atoi(argv[5]);  //reset time
	//delay_on = (unsigned int)atoi(argv[6]);  //delay specified
	
	
	ofstream text_file("storing.txt",ios::app);
	text_file << induction << "\n" << stop_signal << "\n" << test_movement << "\n" << blackscreen << "\n" << endl;  
	text_file.close();
  //printf("step size is %u\n delay is %u\n duration is %u\n numer of loops are %u\n reset time is %u\n delay time is %u\n",step_size,delay_enable,duration,number_of_loops,reset_time,delay_on);	
  
		
		
		}	
	//if (argc > 2){printf(" %s",argv[2]);}	
	//if (argc > 1){printf(" %s",argv[1]);}	
	//else{printf("has no value");}
	//}
	//printf("\n");
	return 0;
}
