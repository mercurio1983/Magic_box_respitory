#include "run_GUI.h"
#include "run_exp.h"
#include "storage.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	
    run_exp *experiment_gui = new run_exp(wxT("Experiment GUI"));
    experiment_gui->Show(true);

    return true;
}
