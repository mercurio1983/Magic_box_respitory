
#ifndef RUN_EXP_H
#define RUN_EXP_H

#include <wx/wx.h>
#include <wx/textdlg.h> // to get the text dialog working
#include <wx/numdlg.h> // to get the text dialog working
#include <wx/utils.h>
#include <wx/process.h>
#include <wx/textctrl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include "storage.h"
//#include "subprog.h"

class storage;
//class sub_prog;

class run_exp: public wxFrame, storage {
	
	private:
		wxString str2; 
	//	storage object;
	
	//storage *Comm;
		
	public:
		friend class subprog;
		
		//constructor
		run_exp(const wxString& title);
		
		//destructor
		~run_exp();
		
		void OnRun(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		
		void SetInduction(wxCommandEvent& event);
		void SetStop_signal(wxCommandEvent& event);
		void SetTest_movement(wxCommandEvent& event);
		void SetBlack_screen(wxCommandEvent& event);
		
		//void SetInc(wxCommandEvent& event);
		//void SetDur(wxCommandEvent& event);
		//void SetRes(wxCommandEvent& event);
		//void SetNum(wxCommandEvent& event);
		void print_value(wxCommandEvent& event);
		//void save_value(wxCommandEvent& event);
		//void Set_Sync(wxCommandEvent& event);
		//void Set_delay(wxCommandEvent& event);
		void Set_default(wxCommandEvent& WXUNUSED(event));
		//void OnOk(wxCommandEvent& event);
		
		//wxButton *set_test; //to make the buttons known in the functions
		//wxButton *sync; //to make the buttons known in the functions
		
		//void print_test(wxCommandEvent& WXUNUSED(event));
		//void Set_test(wxCommandEvent& WXUNUSED(event));
		
		wxGridSizer *grid_size;
		storage *object; 
		
		//sub_prog* SetStepSize_prog;	
		
		
		
		//DECLARE_EVENT_TABLE()
};



const int ID_RUN = 100; //save 


//const int ID_SET_DELAY = 102;

const int ID_INDUCTION = 103;
const int ID_STOP = 104;
const int ID_TEST = 105;
const int ID_BLACKSCREEN = 106;

//const int ID_INC = 103;
//const int ID_DUR = 104;
//const int ID_RES = 105;
//const int ID_NUM = 106;
const int ID_DEFAULT = 107; //save
const int ID_print = 108; //save

const int ID_OK_dialog = 111;

//const int ID_RUN_TEST = 112;
//const int ID_PRINT_TEST = 113;

#endif
