#include "run_exp_3.h"
//#include "subprog.h"

//#include "Communication.h"


/*BEGIN_EVENT_TABLE(run_exp,wxFrame)
//EVT_COMMAND (ID_TEXT,wxEVT_COMMAND_TEXT_UPDATED,run_exp::save_value)
EVT_COMMAND (ID_OK_dialog,wxEVT_COMMAND_BUTTON_CLICKED,run_exp::save_value)
END_EVENT_TABLE()*/

run_exp::run_exp(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxPoint(600,350), wxSize(220,300))
{
	//default_ = 1; //set default flag
	//set_default(); // the values to default
	//wxPanel *panel = new wxPanel(this,-1);
	//object = new storage; 
	wxMenuBar* menubar = new wxMenuBar;
	//wxMenu* file = new wxMenu;
	wxString input;
	SetMenuBar(menubar);
	
	//The alignments
	wxBoxSizer *vbox1 = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer *hbox1 = new wxBoxSizer(wxEXPAND);
	

	
	//The buttons for use
	wxButton *run = new wxButton(this,ID_RUN,wxT("&Run"));
	//sync = new wxButton(this,ID_SYNC,wxT("&sync"));
	//wxButton *set_delay_on = new wxButton(this,ID_SET_DELAY,wxT("&Set delay"));
	wxButton *instruction1 = new wxButton(this,ID_INSTRUCTION,wxT("&Instruction"));
	wxButton *induction1 = new wxButton(this,ID_INDUCTION,wxT("&Induction"));
	wxButton *stop = new wxButton(this,ID_STOP,wxT("&Stop signal"));
	wxButton *test = new wxButton(this,ID_TEST,wxT("&Test movement"));
	wxButton *blackscreen = new wxButton(this,ID_BLACKSCREEN,wxT("&Blackscreen"));
    //set_test = new wxButton(this,ID_RUN_TEST,wxT("&test disabled"));
	//wxButton *print_test = new wxButton(this,ID_PRINT_TEST,wxT("&print test"));
	wxButton *print_value = new wxButton(this,ID_print,wxT("&Print"));
	wxButton *default_ = new wxButton(this,ID_DEFAULT,wxT("&Set default"));
	wxButton *quit = new wxButton(this,wxID_EXIT,wxT("&Quit"));
	
	/*
	//To align with the panel
	hbox1->Add(new wxPanel(panel, -1));
	vbox1->Add(hbox1, 1, wxEXPAND);
	
	//To align the buttons 
	vbox2->Add(run);
	vbox2->Add(sync);
	vbox2->Add(async);
	vbox2->Add(quit);
	
	//Specify the space for the alignments
	*/
	//vbox1->Add(vbox2, 0, wxALIGN_RIGHT| wxRIGHT | wxLEFT);
	grid_size = new wxGridSizer(4,2,2,2);
	grid_size->Add(run,0,wxEXPAND);
	//grid_size->Add(set_test,0,wxEXPAND);
	//grid_size->Add(sync,0,wxEXPAND);
	//grid_size->Add(set_delay_on ,0,wxEXPAND);
	grid_size->Add(instruction1,0,wxEXPAND);
	grid_size->Add(induction1,0,wxEXPAND);
	grid_size->Add(stop,0,wxEXPAND);
	grid_size->Add(test,0,wxEXPAND);
	grid_size->Add(blackscreen,0,wxEXPAND);
	//grid_size->Add(print_test,0,wxEXPAND);
	grid_size->Add(print_value,0,wxEXPAND);
	grid_size->Add(default_,0,wxEXPAND);
	vbox1->Add(grid_size, 1, wxEXPAND);
	//wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
	//vbox2->Add(quit,0,wxEXPAND,1);
	vbox1->Add(quit, 0, wxEXPAND);
	//vbox1->Add(quit, 1, wxEXPAND);
	SetSizer(vbox1); 
	SetMinSize(wxSize(270, 200));
	
	//grid2_size = new wxGridSizer(1,1,0.5,0.5);
	//grid2_size->Add(quit,0,wxEXPAND);
	
	
	
	//connect the buttons to specific programs
	Connect(ID_RUN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(run_exp::OnRun));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(run_exp::OnQuit));
	Connect(ID_INDUCTION,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetInduction));
	Connect(ID_STOP,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetStop_signal));
	Connect(ID_TEST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetTest_movement));
	Connect(ID_BLACKSCREEN,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetBlack_screen));
	Connect(ID_INSTRUCTION,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetInstruction));
	
	//Connect(ID_RUN_TEST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_test));
	//Connect(ID_PRINT_TEST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::print_test));
	
	Connect(ID_print,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::print_value));
	//Connect(ID_SYNC,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_Sync));
	//Connect(ID_SET_DELAY,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_delay));
	Connect(ID_DEFAULT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_default));
	//Connect(ID_OK,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::OnOk));
	//Center();
	
	//set_value= wxT("0");
	instruction=wxT("2");
	induction= wxT("10");
	stop_signal=wxT("2");
	test_movement=wxT("3");
	black_screen=wxT("5");
	
	instruction_max=wxT("1200");
	induction_max= wxT("1200");
	stop_signal_max= wxT("1200");
	test_movement_max= wxT("1200");
	black_screen_max= wxT("1200");
	}

run_exp::~run_exp(){
	Disconnect(ID_RUN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(run_exp::OnRun));
	Disconnect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(run_exp::OnQuit));
	//Disconnect(ID_INC,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetInc));
	//Disconnect(ID_DUR,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetDur));
	//Disconnect(ID_RES,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetRes));
	//Disconnect(ID_NUM,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetNum));
	Disconnect(ID_INDUCTION,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetInduction));
	Disconnect(ID_STOP,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetStop_signal));
	Disconnect(ID_TEST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetTest_movement));
	Disconnect(ID_BLACKSCREEN,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetBlack_screen));
	Disconnect(ID_INSTRUCTION,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::SetInstruction));
	Disconnect(ID_print,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::print_value));
	//Disconnect(ID_SYNC,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_Sync));
	//Disconnect(ID_SET_DELAY,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_delay));
	Disconnect(ID_DEFAULT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(run_exp::Set_default));
	}

//void run_exp::OnRun(wxCommandEvent& WXUNUSED(event)){
	
	//std::string str_1 = std::string(get_text_value(SET_STEP).mb_str());
	//std::string str_2 = std::string(get_text_value(SET_SYNC).mb_str());
	//std::string str_3 = std::string(get_text_value(DURATION).mb_str());
	//std::string str_4 = std::string(get_text_value(NUMBER_OF).mb_str());
	//std::string str_5 = std::string(get_text_value(RESET_TIME).mb_str());
	//std::string str_6 = std::string(get_text_value(SET_VALUE).mb_str());
	//std::string str_total = "./stereoviewGL_delay2 " + str_1 + " " + str_2 + " " + str_3 + " " + str_4 + " " + str_5 + " " + str_6 ;
	////std::string str_total = "./test_call_prog " + str_1 + " " + str_2 + " " + str_3 + " " + str_4 + " " + str_5 + " " + str_6 ;
	//wxString convert_to_string( str_total.c_str(), wxConvUTF8); 

	//wxString launchCommand = convert_to_string;
	//wxEvtHandler *eventHandler = NULL;
	//wxProcess * process1 = new wxProcess(eventHandler,-1);
	//process1->Redirect();
	
	//wxExecute(launchCommand, wxEXEC_ASYNC,process1);
	//Close(true);
	//}	

void run_exp::OnRun(wxCommandEvent& WXUNUSED(event)){
	
	std::string str_0 = std::string(instruction.mb_str());
	std::string str_1 = std::string(induction.mb_str());
	std::string str_2 = std::string(stop_signal.mb_str());
	std::string str_3 = std::string(test_movement.mb_str());
	std::string str_4 = std::string(black_screen.mb_str());
	std::string str_total = "./stereoviewGL_delay3D_version2 " + str_0 + " " + str_1 + " " + str_2 + " " + str_3 + " " + str_4;
	//std::string str_total = "./test_call_prog " + str_1 + " " + str_2 + " " + str_3 + " " + str_4;
	wxString convert_to_string( str_total.c_str(), wxConvUTF8); 

	wxString launchCommand = convert_to_string;
	wxEvtHandler *eventHandler = NULL;
	wxProcess * process1 = new wxProcess(eventHandler,-1);
	process1->Redirect();
	
	wxExecute(launchCommand, wxEXEC_ASYNC,process1);
	Close(true);
	}	
	
void run_exp::OnQuit(wxCommandEvent& WXUNUSED(event)){Close(true);}	


void run_exp::SetInduction(wxCommandEvent& WXUNUSED(event)){
	
	long max_value = wxAtoi(induction_max);
	wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the induction time in s"),wxT("Induction time"),wxT("Induction time"), wxAtoi(induction), 0, max_value);
	if(dialog->ShowModal() == wxID_OK){
		
		int value = dialog->GetValue();
		induction = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,INDUCTION);
	}
	dialog->Destroy();	
	}
	
void run_exp::SetStop_signal(wxCommandEvent& WXUNUSED(event)){
	
	long max_value = wxAtoi(stop_signal_max);
	wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the stop signal time in s"),wxT("stop signal time"),wxT("stop signal time"), wxAtoi(stop_signal), 0, max_value);
	if(dialog->ShowModal() == wxID_OK){
		
		int value = dialog->GetValue();
		stop_signal = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,STOP_SIGNAL);
	}
	dialog->Destroy();	
	}
	
void run_exp::SetTest_movement(wxCommandEvent& WXUNUSED(event)){
	
	long max_value = wxAtoi(test_movement_max);
	wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the test movement time in s"),wxT("test movement time"),wxT("test movement time"), wxAtoi(test_movement), 0, max_value);
	if(dialog->ShowModal() == wxID_OK){
		
		int value = dialog->GetValue();
		test_movement = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,TEST_MOVEMENT);
	}
	dialog->Destroy();	
	}
	
void run_exp::SetBlack_screen(wxCommandEvent& WXUNUSED(event)){
	
	long max_value = wxAtoi(black_screen_max);
	wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the blackscreen time in s"),wxT("blackscreen time"),wxT("blackscreen time"), wxAtoi(black_screen), 0, max_value);
	if(dialog->ShowModal() == wxID_OK){
		
		int value = dialog->GetValue();
		black_screen = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,BLACK_SCREEN);
	}
	dialog->Destroy();	
	}
void run_exp::SetInstruction(wxCommandEvent& WXUNUSED(event)){
	long max_value = wxAtoi(instruction_max);
	wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the instruction time in s"),wxT("instruction time"),wxT("instruction time"), wxAtoi(instruction), 0, max_value);
	if(dialog->ShowModal() == wxID_OK){
		
		int value = dialog->GetValue();
		instruction = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,BLACK_SCREEN);
	}
	dialog->Destroy();	
	
	
	}

void run_exp::print_value(wxCommandEvent& WXUNUSED(event)){
	
	wxString str_0 = instruction;
	wxString str_1 = induction;
	wxString str_2 = stop_signal;
	//long value_sync = wxAtoi(str_2);
	//wxString str_indicate;
	//if(!value_sync){ str_indicate = wxT("sync");}
	//else{str_indicate = wxT("async"); }
	wxString str_3 = test_movement;
	wxString str_4 = black_screen;
	//long value_loop = wxAtoi(str_4);
	//wxString loops;
	//if(value_loop == 1){loops = wxT(" loop ");}
	//else{loops = wxT(" loops ");}
	
	//wxString str_5 = get_text_value(RESET_TIME);
	
	//wxString str_6 = get_text_value(SET_VALUE);
	
	//wxString str_7 = get_text_value(TEST);
	//long value_test = wxAtoi(str_7);
	//wxString str_test;
	//if(!value_test){str_test = wxT("test mode disabled");}
	//else{str_test = wxT("test mode enabled");}
	wxPuts(wxT("The instruction time is ") + str_0 + wxT("s"));
	wxPuts(wxT("The induction time is ") + str_1 + wxT("s"));
    wxPuts(wxT("The stop signal time is ") + str_2 + wxT("s"));
    wxPuts(wxT("The test movement time is ") + str_3 + wxT("s"));
    wxPuts(wxT("The blackscreen time is ") + str_4 + wxT("s"));
	wxString total_;
	total_ = wxT("The instruction time is ") + str_0 + wxT("s\n") + wxT("The induction time is ") + str_1 + wxT("s\n") + wxT("The stop signal time is ") + str_2 + wxT("s\n") + wxT("The test movement time is ") + str_3 + wxT("s\n") + wxT("The blackscreen time is ") + str_4 + wxT("s\n");
	wxMessageDialog *dialog = new wxMessageDialog(this,total_,wxT("Info on the values"), wxOK);
	//wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Write the number of loops"),wxT("Number of loops"),wxT("text3"), wxOK | wxCANCEL);
	dialog->ShowModal();

	//	int value = dialog->GetValue();
	//	str2 = wxString::Format(wxT("%i"), value);
	//	set_text_value(str2,NUMBER_OF);

	//}
	dialog->Destroy();	//}	
	
	}

void run_exp::Set_default(wxCommandEvent& WXUNUSED(event)){
	
	//set_value= wxT("0");
	instruction=wxT("2");
	induction= wxT("10");
	stop_signal=wxT("2");
	test_movement=wxT("3");
	black_screen=wxT("5");
	}
	 
//void run_exp::SetInc(wxCommandEvent& WXUNUSED(event)){
	
	//long max_value = wxAtoi(get_text_value(DURATION));
	//wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the step size in s"),wxT("Step size"),wxT("Step size"), 40, 0, max_value);
	//if(dialog->ShowModal() == wxID_OK){
		
		//int value = dialog->GetValue();
		//str2 = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,SET_STEP);
	//}
	//dialog->Destroy();	
	//}

//void run_exp::SetDur(wxCommandEvent& event){
	//wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the duration in s"),wxT("Duration"),wxT("Duration"), 500, 0, 10000);
	//if(dialog->ShowModal() == wxID_OK){
		////str2= dialog->GetValue();  for text entry
		//int value = dialog->GetValue();
		//str2 = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,DURATION);
		////wxPuts(str2);
		////wxMessageBox(dialog->GetValue(), wxT("Dialog is catched"));}
	//}
	//dialog->Destroy();	}
//void run_exp::SetRes(wxCommandEvent& event){
	//wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the reset time in s"),wxT("Reset time"),wxT("Reset time"), 500, 0, 10000);
	////wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Write the reset time in ms"),wxT("Reset time"),wxT("text3"), wxOK | wxCANCEL);
	//if(dialog->ShowModal() == wxID_OK){
		////str2= dialog->GetValue();  for text entry
		//int value = dialog->GetValue();
		//str2 = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,RESET_TIME);
		//wxPuts(str2);
		////wxMessageBox(dialog->GetValue(), wxT("Dialog is catched"));}
	//}
	//dialog->Destroy();	}
//void run_exp::SetNum(wxCommandEvent& event){
	//wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the number of loops"),wxT("Number of loops"),wxT("Number of loops"), 1, 0, 20);
	////wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Write the number of loops"),wxT("Number of loops"),wxT("text3"), wxOK | wxCANCEL);
	//if(dialog->ShowModal() == wxID_OK){

		//int value = dialog->GetValue();
		//str2 = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,NUMBER_OF);

	//}
	//dialog->Destroy();	}	
	
	
//void run_exp::print_value(wxCommandEvent& WXUNUSED(event)){
	
	//wxString str_1 = get_text_value(SET_STEP);
	//wxString str_2 = get_text_value(SET_SYNC);
	//long value_sync = wxAtoi(str_2);
	//wxString str_indicate;
	//if(!value_sync){ str_indicate = wxT("sync");}
	//else{str_indicate = wxT("async"); }
	//wxString str_3 = get_text_value(DURATION);
	//wxString str_4 = get_text_value(NUMBER_OF);
	//long value_loop = wxAtoi(str_4);
	//wxString loops;
	//if(value_loop == 1){loops = wxT(" loop ");}
	//else{loops = wxT(" loops ");}
	
	//wxString str_5 = get_text_value(RESET_TIME);
	
	//wxString str_6 = get_text_value(SET_VALUE);
	
	//wxString str_7 = get_text_value(TEST);
	//long value_test = wxAtoi(str_7);
	//wxString str_test;
	//if(!value_test){str_test = wxT("test mode disabled");}
	//else{str_test = wxT("test mode enabled");}
	//wxPuts(wxT("The step size is ") + str_1 + wxT("ms"));

	//wxPuts(wxT("The configuration is set to ") + str_indicate);

	//wxPuts(wxT("The duration is ") + str_3 + wxT("ms"));

	//wxPuts(wxT("The configuration is set to ") + str_4 + loops);

	//wxPuts(wxT("The reset time is ") + str_5 + wxT("ms"));
	//wxPuts(wxT("The delay time is ") + str_6 + wxT("ms"));
	//wxPuts(str_test);
	//wxString total_;
	//total_ = wxT("The step size is ") + str_1 + wxT("ms\n") + wxT("The configuration is set to ") + str_indicate + wxT("\n") + wxT("The duration is ") + str_3 + wxT("ms\n") + wxT("The configuration is set to ") + str_4 + loops + wxT("\n") + wxT("The reset time is ") + str_5 + wxT("ms\n") + wxT("The delay time is ") + str_6 + wxT("ms\n")+ str_test;
	//wxMessageDialog *dialog = new wxMessageDialog(this,total_,wxT("Info on the values"), wxOK);
	////wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Write the number of loops"),wxT("Number of loops"),wxT("text3"), wxOK | wxCANCEL);
	//dialog->ShowModal();

	////	int value = dialog->GetValue();
	////	str2 = wxString::Format(wxT("%i"), value);
	////	set_text_value(str2,NUMBER_OF);

	////}
	//dialog->Destroy();	//}	
	
	//}
 

	

//void run_exp::Set_Sync(wxCommandEvent& WXUNUSED(event)){
	
	//if(wxAtoi(get_text_value(SET_SYNC)) == 0){ 
	//set_async(); 
	//sync->SetLabel(wxT("&async"));
	//}
	//else{
		//set_sync(); 
		//sync->SetLabel(wxT("&sync"));
		//}
	
//}

//void run_exp::Set_delay(wxCommandEvent& WXUNUSED(event)){
	
//wxNumberEntryDialog *dialog = new wxNumberEntryDialog(this,wxT("Write the delay time in ms"),wxT("delay time"),wxT("delay time"), 100, 0, 10000);
	////wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Write the reset time in ms"),wxT("Reset time"),wxT("text3"), wxOK | wxCANCEL);
	//if(dialog->ShowModal() == wxID_OK){
		////str2= dialog->GetValue();  for text entry
		//int value = dialog->GetValue();
		//str2 = wxString::Format(wxT("%i"), value);
		//set_text_value(str2,SET_VALUE);
		//wxPuts(str2);
		////wxMessageBox(dialog->GetValue(), wxT("Dialog is catched"));}
	//}
	//dialog->Destroy();	}


//void run_exp::print_test(wxCommandEvent& WXUNUSED(event)){
	////read from file
	//}

//void run_exp::Set_test(wxCommandEvent& WXUNUSED(event)){
	//if(wxAtoi(get_text_value(TEST)) == 0){ enable_test(); set_test->SetLabel(wxT("&test enabled"));}
	//else{disable_test(); set_test->SetLabel(wxT("&test disabled"));}

	//}




