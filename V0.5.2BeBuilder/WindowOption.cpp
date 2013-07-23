/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "WindowOption.h"
TWindowOption::TWindowOption(char *AWindowTitle, BRect AFrame):BGeneralWindow(AWindowTitle,AFrame,PREFS_FILENAME,B_TITLED_WINDOW,0)
{
//	FViewOption=new TViewOption(BRect(0.000000,0.000000,267.000000,186.000000));
	FViewOption=new TViewOption(Bounds());
	rgb_color kGray = {219,219,219,255};
	FViewOption->SetViewColor(kGray);
	AddChild(FViewOption);
	Show();
	Hide();
}
TWindowOption::~TWindowOption(void)
{

}

void TWindowOption::WindowActivated(bool active)
{
//	DEBUGPRINT("TWindowOption::WindowActivated");
//	FViewOption->FEditorOption->FindAvailableEditors();	
}

bool TWindowOption::QuitRequested(void)
{
	Hide();
	return false;
}
