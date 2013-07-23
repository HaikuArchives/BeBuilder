#include "PropertyEditorWindow.h"

TPropertyEditorWindow::TPropertyEditorWindow(const char *Title,BRect frame, const char *Prefs):BGeneralWindow(Title,frame,Prefs,B_FLOATING_WINDOW,0)
{
	FView=NULL;
//	FView = new TPropertyEditorView(Bounds());
//	AddChild(FView);
}

TPropertyEditorWindow::~TPropertyEditorWindow()
{

}	

void TPropertyEditorWindow::MessageReceived(BMessage *message)
{
	char  *name; 
//	char *data = (char *)malloc(FIND_STRING_SIZE*sizeof(char));
	const char *data;
	uint32  type; 
	int32   count; 
	int32 	bidule;
	TProperty *AProperty;
	status_t resultat;	

	switch (message->what)
	{
		case MSG_PROPERTY_EDIT :
			DEBUGPRINT("Inside PropertyEditorWindow::MessageReceived MSG_PROPERTY_EDIT");
			if (message->FindPointer("ToolWindowHandler", (void **)&FToolWindowHandler) == B_OK) 
			{
				if (message->FindInt32("index", &bidule) == B_OK) 
				{								
					if (message->GetInfo(B_STRING_TYPE, 0, &name, &type, &count) == B_OK) 
					{ 
						if (message->FindString(name,&data)==B_OK)				         	
						{
							FEditedIndex = bidule;
							FView->FTextEdit->SetLabel(name);
							FView->FTextEdit->SetText(data);
						}
						else
						{
							GeneralException excep("Can't find the Property name and value in message.","TPropertyEditorWindow::MessageReceived",true);						
						}						
					}
					else
					{
						GeneralException excep("Can't find index in message.","TPropertyEditorWindow::MessageReceived",true);						
					}
					DEBUGPRINT("Inside PropertyEditorWindow::MessageReceived Before FindPointer");
					if (message->FindPointer(PROP_MESSAGE_POINTER,(void **)&AProperty)==B_OK)				         	
					{
						//AProperty
						DEBUGPRINT("Inside PropertyEditorWindow::MessageReceived Before SetProperty");
						SetProperty(AProperty,bidule,FToolWindowHandler);
						DEBUGPRINT("Inside PropertyEditorWindow::MessageReceived After SetProperty");
					}
					else
					{
						DEBUGPRINT("Can't find the Property pointer in message.");						
					}						
				}
				else
				{
					DEBUGPRINT("Can't find the handler in message.");						
				}										
			}
			break;	
		case PROPERTY_EDITOR_VALIDATE :
			{
			//	ShowMessage("Validate!");
				BMessenger AMessenger(FToolWindowHandler);
				BMessage AMessage(MSG_PROPERTY_EDITED);
				AMessage.AddInt32("index",FEditedIndex); // On renvoi l'index de la propriete edite
				AMessage.AddString(FView->FTextEdit->Label(),FView->FTextEdit->Text());				
				if (AMessenger.IsValid()==false) 
				{
					DEBUGPRINT("PROPERTY_EDITOR_UPDATE Messenger Invalid!");
				}
				resultat = AMessenger.SendMessage(&AMessage);
				if (resultat!=B_OK)
				{		
					DEBUGPRINT("PROPERTY_EDITOR_UPDATE SendMessage had had a problem! ");						
				}
				Quit(); //Closing and destroying the Window!							
			}
			break;	

		case PROPERTY_EDITOR_CANCEL :
			//	ShowMessage("Canceled!");
				Quit(); //Closing and destroying the Window!
			break;	
			
		default: BWindow::MessageReceived(message);			
	}
}

void TPropertyEditorWindow::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	if (FView!=NULL)
		FView->SetProperty(AProperty,AnIndex,AHandler);
}

bool TPropertyEditorWindow::QuitRequested(void)
{
//	be_app->PostMessage(B_QUIT_REQUESTED);
	// I don't want to have the normal BGeneralWindow feature!
	return (TRUE);
}
