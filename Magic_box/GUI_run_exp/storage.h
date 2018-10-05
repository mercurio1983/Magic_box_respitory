#ifndef STORAGE_H
#define STORAGE_H

#define SET_VALUE 1
//#define SET_STEP 2
//#define SYNC 3
//#define ASYNC 4
//#define DURATION 5
//#define NUMBER_OF 6
//#define RESET_TIME 7
//#define SET_SYNC 8
//#define TEST 9

#define INDUCTION 2
#define STOP_SIGNAL 3
#define TEST_MOVEMENT 4
#define BLACK_SCREEN 5


#include <iostream>
#include <wx/wx.h>

class storage {

	private:
		//for general input value
		wxString set_value; //for storing the information from the new window
		
		//for the setup
		wxString induction;
		wxString stop_signal;
		wxString test_movement;
		wxString black_screen;
		
		
		//for maximum values
		wxString induction_max;
		wxString stop_signal_max;
		wxString test_movement_max;
		wxString black_screen_max;
			
	public:
		//constructor
		storage();
		
		//set value for regular inputs
		void set_text_value(const wxString& text_value, int choice);
		void cpy_value_to_(int choice);
		
		void set_default();
			
		//get value for regular inputs
		wxString get_text_value(int choice) const;
		wxString get_max_value(int choice) const;
		//void set_sync();
		//void set_async();
		//void enable_test();
		//void disable_test();
		
		//to be able to copy objects with the attributes. 
		const storage& operator= (const storage& v);
		//set value for regular inputs

};
#endif
