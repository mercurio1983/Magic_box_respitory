#include "run_GUI_3.h"
#include "run_exp_3.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	
    run_exp *experiment_gui = new run_exp(wxT("Experiment GUI"));
    experiment_gui->Show(true);

    return true;
}
