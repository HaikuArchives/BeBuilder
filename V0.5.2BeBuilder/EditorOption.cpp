/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "EditorOption.h"
const uint32 MESSAGE_EDITOR_OPTION = 'EOPT';
TEditorOption::TEditorOption(BRect AFrame): BMenuField(AFrame,"AMenuFieldComponent3","Editor: ",new BMenu("",B_ITEMS_IN_COLUMN),B_FOLLOW_ALL_SIDES | B_FOLLOW_TOP,B_NAVIGABLE | B_WILL_DRAW)
{
	Menu()->SetLabelFromMarked(true);
//	SetPreferredSize();
	SetEnabled(TRUE);
	FListMimeCode = new BList();
	FindAvailableEditors();
}
TEditorOption::~TEditorOption(void)
{
}

bool TEditorOption::FindAvailableEditors(void)
{
	DEBUGPRINT("TEditorOption::FindAvailableEditors inside");
	BMessage msg;
	char *ptr;
	int32 subs=0,supers=0,ind;
	BMimeType mime("text/x-source-code");
//	BMimeType mime("text/plain");
	
//	BMimeType mime("text");
	if (mime.GetSupportingApps(&msg)==B_OK)
		DEBUGPRINT("TEditorOption::FindAvailableEditors GetSupportingApps returns B_OK");	
//	msg.PrintToStream();		
	msg.FindInt32("be:sub",&subs);
	msg.FindInt32("be:super", &supers);
//	DEBUGPRINT("TEditorOption::FindAvailableEditors subs="<<subs);	
//	DEBUGPRINT("TEditorOption::FindAvailableEditors supers="<<supers);	
	for (ind=0; ind < subs; ind++)
	{
		msg.FindString("applications",ind,((const char **)&ptr));
		DEBUGPRINT("TEditorOption::FindAvailableEditors "<<ptr);
/*
	FMenuNewItem = new BMenuItem(MENU_NEW_LABEL, new BMessage(MENU_FILE_NEW), 'N');	
	FMenuFile->AddItem(FMenuNewItem);

*/		
		BMessage *AMessage = new BMessage(MESSAGE_EDITOR_OPTION);
		FListMimeCode->AddItem(new string(ptr));
		BMimeType AMimeType(ptr);
		char Descript[100];
		AMimeType.GetShortDescription(Descript);
//status_t GetShortDescription(char *description) const 		
		AMessage->AddInt32("index",FListMimeCode->CountItems()-1);
		Menu()->AddItem(new BMenuItem(Descript,AMessage));
	}		
//	int32 hold=ind;
//	for (ind=0; ind < supers; ind++)
//	{
//		msg.FindString("applications",ind+hold,&ptr);
//		DEBUGPRINT("TEditorOption::FindAvailableEditors "<<ptr);
//	}	
	return true;
}

void TEditorOption::MessageReceived(BMessage *message)
{
	int32 Index = -1;
	switch(message->what)
	{
		case MESSAGE_EDITOR_OPTION:
			DEBUGPRINT("TEditorOption::MessageReceived MESSAGE_EDITOR_OPTION");
			if (message->FindInt32("index",&Index)==B_OK)
			{
				TBeBuilderOption ABeBuilderOption(PREFS_FILENAME);
				ABeBuilderOption.FEditorMimeType = ((string *)FListMimeCode->ItemAt(Index))->c_str();
				ABeBuilderOption.ApplyUpdates();					
				DEBUGPRINT("TEditorOption::MessageReceived "<<((string *)FListMimeCode->ItemAt(Index))->c_str());
			}
			else
				DEBUGPRINT("TEditorOption::MessageReceived Index not found!");
			break;
		default :
			BMenuField::MessageReceived(message);
			break;
	}
}
void TEditorOption::AttachedToWindow(void)
{
	Menu()->SetTargetForItems(this);
	BMenuField::AttachedToWindow();
}
