#include "storage.h"

storage::storage():	induction_max(wxT("1200")),stop_signal_max(wxT("1200")),test_movement_max(wxT("1200")),	black_screen_max(wxT("1200")){
set_value= wxT("0");
induction= wxT("10");
stop_signal=wxT("2");
test_movement=wxT("3");
black_screen=wxT("5");	}

void storage::set_text_value(const wxString& text_value, int choice){
	if (choice == SET_VALUE){ set_value = text_value;}
	else if(choice == INDUCTION){ induction= text_value;}
	else if(choice == STOP_SIGNAL){ stop_signal= text_value;}
	else if(choice == TEST_MOVEMENT){ test_movement= text_value;}
	else if(choice == BLACK_SCREEN){ black_screen= text_value;}
	
	}
	
void storage::cpy_value_to_(int choice){
	if(choice == INDUCTION){ induction= set_value;}
	else if(choice == STOP_SIGNAL){ stop_signal= set_value;}
	else if(choice == TEST_MOVEMENT){ test_movement= set_value;}
	else if(choice == BLACK_SCREEN){ black_screen= set_value;}

	}
	
wxString storage::get_text_value(int choice) const {
	if (choice == SET_VALUE){return set_value;}
	else if(choice == INDUCTION){return induction;}
	else if(choice == STOP_SIGNAL){return stop_signal;}
	else if(choice == TEST_MOVEMENT){return test_movement;}
	else if(choice == BLACK_SCREEN){return black_screen;}
	else {return wxT("");}
}

wxString storage::get_max_value(int choice) const {
	if(choice == INDUCTION){return induction_max;}
	else if(choice == STOP_SIGNAL){return stop_signal_max;}
	else if(choice == TEST_MOVEMENT){return test_movement_max;}
	else if(choice == BLACK_SCREEN){return black_screen_max;}
	else {return wxT("");}
	
	
}

void storage::set_default(){
	induction = wxT("10"); //set step default
	stop_signal = wxT("2");	  //set delay that is async
	test_movement = wxT("3"); //no loops
	black_screen = wxT("5"); //set 1s
}		

const storage& storage::operator= (const storage& v){
	
	if (this != &v){
		set_value = v.set_value;
		induction = v.induction;
		induction = v.induction;
		test_movement = v.test_movement;
		black_screen = v.black_screen;
		}
	return *this;	
	}		
