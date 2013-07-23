#include "PropertyEditorStandard.h"

TPropertyEditorStandard::TPropertyEditorStandard(const char *Title,BRect frame)
//:TPropertyEditorWindow(Title,frame,PREFS_FILENAME)
:TPropertyEditorWindow(Title,PROPERTY_STANDARD_EDITOR_POSITION,PREFS_FILENAME)
{
	FView = new TPropertyEditorStandardView(Bounds());
	AddChild(FView);
}

TPropertyEditorStandard::~TPropertyEditorStandard()
{

}	
/*
void TPropertyEditorStandard::MessageReceived(BMessage *message)
{
	char  *name; 
//	const char **data=NULL;
	char *data = (char *)malloc(FIND_STRING_SIZE*sizeof(char));
	uint32  type; 
	int32   count; 
	int32 	bidule;
//	TProperty *AProp;
	status_t resultat;	

	switch (message->what)
	{
		case MSG_PROPERTY_EDIT :
			if (message->FindPointer("ToolWindowHandler", (void **)&FToolWindowHandler) == B_OK) 
			{
				if (message->FindInt32("index", &bidule) == B_OK) 
				{								
					if (message->GetInfo(B_STRING_TYPE, 0, &name, &type, &count) == B_OK) 
					{ 
//						if (message->FindString(name,data)==B_OK)				         	
						if (message->FindString(name,&data)==B_OK)				         	
						{
							FEditedIndex = bidule;
						//	printf("TPropertyEditorWindow::MessageReceived name : %s \n",name);
						//	printf("TPropertyEditorWindow::MessageReceived data : %s \n",*data);
							FView->FTextEdit->SetLabel(name);
//							FPropertyEditorView->FTextEdit->SetText(*data);
							FView->FTextEdit->SetText(data);
						}
						else
						{
							GeneralException excep("Can't find the Property name and value in message.","TPropertyEditorWindow::MessageReceived",true);						
//							throw(excep);        	
						}						
					}
					else
					{
						GeneralException excep("Can't find index in message.","TPropertyEditorWindow::MessageReceived",true);						
//						throw(excep);        	
					}						
				}
				else
				{
					GeneralException excep("Can't find the handler in message.","TPropertyEditorWindow::MessageReceived",true);						
//					throw(excep);        	
				}										
			}
			break;	
		case PROPERTY_EDITOR_VALIDATE :
			{
				BMessenger AMessenger(FToolWindowHandler);
				BMessage AMessage(MSG_PROPERTY_EDITED);
				AMessage.AddInt32("index",FEditedIndex); // On renvoi l'index de la propriete edite
				AMessage.AddString(FView->FTextEdit->Label(),FView->FTextEdit->Text());				
				if (AMessenger.IsValid()==false) 
				{
					GeneralException excep("Messenger Invalid!.","TPropertyEditorWindow::MessageReceived",true);
				}
				resultat = AMessenger.SendMessage(&AMessage);
				if (resultat!=B_OK)
				{		
					GeneralException excep("SendMessage had had a problem!.","TPropertyEditorWindow::MessageReceived",true);						
//					throw(excep);        	
				}
				Quit(); //Closing and destroying the Window!							
			}
			break;	

		case PROPERTY_EDITOR_CANCEL :
				ShowMessage("Canceled!");
				Quit(); //Closing and destroying the Window!
			break;	
			
		default: BWindow::MessageReceived(message);			
	}
}

bool TPropertyEditorStandard::QuitRequested(void)
{
//	be_app->PostMessage(B_QUIT_REQUESTED);
	// I don't want to have the normal BGeneralWindow feature!
	return (TRUE);
}
*/