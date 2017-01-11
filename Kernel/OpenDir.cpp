#include "OpenDir.h"

TOpenDir::TOpenDir(BMessenger* target,entry_ref *panel_directory,uint32 node_flavors,
bool allow_multiple_selection,BMessage *message,BRefFilter *filter,
bool modal,bool hide_when_done)
:BFilePanel(B_OPEN_PANEL,target,panel_directory,node_flavors,allow_multiple_selection,message,filter,modal,hide_when_done)
//:BFilePanel(B_OPEN_PANEL,target,panel_directory,B_DIRECTORY_NODE | B_SYMLINK_NODE,allow_multiple_selection,message,filter,modal,hide_when_done)
/*
B_DIRECTORY_NODE, and B_SYMLINK_NODE
*/
{
	BView *background;
	BButton *ACancelButton;
	BRect ARect;
	if (message==NULL)
		FMessage = new BMessage(B_DIR_REFS_RECEIVED);
	else
		FMessage = new BMessage(*message);
	if (Window()->Lock())
	{
		background = Window()->ChildAt(0);
		ACancelButton = (BButton *)background->FindView("cancel button");			
		if (ACancelButton!=NULL)
		{
			ARect = ACancelButton->Frame();
			ARect.left = ARect.left - 200;
			ARect.right = ARect.right - 80;
			FChangeDirButton = new BButton(ARect,"Unbouton","Label",FMessage, B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
			FChangeDirButton->MakeDefault(true);
			if (target!=NULL) 
			{
				FChangeDirButton->SetTarget(*target);
			}
			background->AddChild(FChangeDirButton);
		}
		Window()->Unlock();
	}
	SelectionChanged();
}

TOpenDir::~TOpenDir(void)
{

}

void TOpenDir::SetTarget(BHandler *AnHandler)
{
	FChangeDirButton->SetTarget(AnHandler);
	BMessenger AMessenger(AnHandler);
	BFilePanel::SetTarget(AMessenger);
}


void TOpenDir::SelectionChanged()
{
	entry_ref ARef;
	GetPanelDirectory(&ARef);
	// "refs" field (type B_REF_TYPE) contains entry_ref 
	FMessage->RemoveName("refs");
	FMessage->AddRef("refs",&ARef);
	BEntry AnEntry(&ARef);
	char *name = (char *)malloc(sizeof(char) * B_FILE_NAME_LENGTH);
	AnEntry.GetName(name);
	char *AValue = (char *)malloc(sizeof(char)*(strlen(name) + 12));
	strcpy(AValue,"Select '");
	AValue = strcat(AValue,name);
	AValue = strcat(AValue,"'");
	if (FChangeDirButton->LockLooper())
	{
		FChangeDirButton->SetLabel(AValue);
		FChangeDirButton->UnlockLooper();
	}
	free(AValue);
}


