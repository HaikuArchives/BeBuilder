#include "stdafx.h"
#include <stdio.h>
#include "FileWriter.h"
#include "FileReader.h"
#include "BuilderApp.h"
//#include "BuilderWindow.h"
#include "GlobalVar.h"

//TBuilderApp::TBuilderApp() : BApplication("application/x-vnd.BeBuilder")
TBuilderApp::TBuilderApp() : BApplication(BE_BUILDER_MIME)
{
	//Testing BeBuilder MimeType
	BMimeType AMimeType(PROJECT_MIME);
	AMimeType.SetPreferredApp(BE_BUILDER_MIME);
	AMimeType.SetLongDescription("BeBuilder V0.5 project file. (C) 1998-1999 Softimedia Inc. Written by Jerome Fillon (Softimedia Inc.) jerome@softimedia.com ");
	AMimeType.SetShortDescription("BeBuilder V0.5 project file.");
	AMimeType.SetPreferredApp(BE_BUILDER_MIME);
	
	if (AMimeType.IsInstalled()==false)
	{
		AMimeType.Install();
	}

	BizWindow = new TBuilderWindow("BeBuilder",BUILDER_POSITION,PREFS_FILENAME);	
//	SetPreferredHandler(BizWindow);

	BizWindow->Show();
	
}

void TBuilderApp :: RefsReceived( BMessage *msg )
{
//	ShowMessage("TBuilderApp::RefsReceived. Message found!");
	BizWindow->PostMessage(msg,NULL);	
}


int main(int argc, char* argv[])
{
	TBuilderApp MyApp;
	MyApp.Run();
	return 0;
}