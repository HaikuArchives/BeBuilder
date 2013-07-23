/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "BeBuilderEditor.h"

TBeBuilderEditor::TBeBuilderEditor() : BApplication(APP_SIGNATURE)
{
	FWindowCount = 0;
	FNextUntitledNumber = 1;	// Next window is "Untitled 1"

	FListWindow = new BList();
	
	FEditorWindow = new TEditorWindow(AWindowRect);
	
}

void TBeBuilderEditor::MessageReceived(BMessage *message)	
{
	entry_ref ref;
	int32 index;
	BWindow *AWindow=NULL;	
	TEditorWindow *AnEditorWindow=NULL;
//	DEBUGPRINT("TBeBuilderEditor::MessageReceived");
//	message->PrintToStream();
	switch(message->what) 
	{
		case WINDOW_REGISTRY_ADD:
			{
				bool need_id = false;
				BMessage reply(WINDOW_REGISTRY_ADDED);
				
				if (message->FindBool("need_id", &need_id) == B_OK) 
				{
					if (need_id) 
					{
						reply.AddInt32("new_window_number", FNextUntitledNumber);
						FNextUntitledNumber++;
					}
					FWindowCount++;
					DEBUGPRINT("TBeBuilderEditor::MessageReceived inside WINDOW_REGISTRY_ADD "<<FWindowCount);					
				}
				if (message->FindPointer("window_ptr", (void **)&AWindow) == B_OK) 
				{
					if (AWindow) 
					{
						FListWindow->AddItem(AWindow);					
					}
				}
				
				reply.AddRect("rect", AWindowRect);
				AWindowRect.OffsetBy(20,20);
				message->SendReply(&reply);
				break;
			}
		case WINDOW_REGISTRY_SUB:
			DEBUGPRINT("TBeBuilderEditor::MessageReceived inside WINDOW_REGISTRY_SUB "<<FWindowCount);
			if (message->FindPointer("window_ptr", (void **)&AWindow) == B_OK) 
			{
				if (AWindow) 
				{
					FListWindow->RemoveItem(AWindow);					
				}
			}			
			FWindowCount--;
			DEBUGPRINT("TBeBuilderEditor::MessageReceived inside WINDOW_REGISTRY_SUB 2eme "<<FWindowCount);
			if (!FWindowCount) 
			{
				Quit();
			}
			break;
		case B_REFS_RECEIVED:
		case B_SIMPLE_DATA:
			index = 0;
			while ((message->FindRef("refs", index, &ref)) == B_OK) 
			{
				AnEditorWindow = FindEditorWindow(&ref);
				if (AnEditorWindow==NULL) 
				{			
					if (message->WasDropped())
						new TEditorWindow(AWindowRect,&ref);
					else
						FEditorWindow->Reload(&ref);
				}
				else // File not already open...
				{
					int32 ALineNumber = -1;
					int32 AStartSelection = -1;
					int32 ASelectionLength = -1;
					bool AReload = false;
					message->FindInt32("be:line",&ALineNumber);
					message->FindInt32("be:selection_offset",&AStartSelection);
					message->FindInt32("be:selection_length",&ASelectionLength);
					message->FindBool("reload",&AReload);
					if (AReload==true)
					{
						AnEditorWindow->Reload(&ref);
					}
					if (ALineNumber!=-1)
					{
						AnEditorWindow->GotoLine(ALineNumber);
					}
					if ((AStartSelection!=-1) && (ASelectionLength!=-1))
					{
						AnEditorWindow->SelectText(AStartSelection,ASelectionLength);
					}
				}
				index++;
			}
			break;
		default:
			BApplication::MessageReceived(message);
			break;
	}

}

void TBeBuilderEditor :: RefsReceived( BMessage *msg )
{
	MessageReceived(msg);
}

TEditorWindow *TBeBuilderEditor ::FindEditorWindow(entry_ref *ref)
{
	entry_ref tmpref;
	for (int ind=0; ind<FListWindow->CountItems(); ind++)
	{
		((TEditorWindow *)FListWindow->ItemAt(ind))->GetEntryRef(&tmpref);
		if (tmpref==*ref)
		{
			return ((TEditorWindow *)FListWindow->ItemAt(ind));
		}
	}
	return NULL;
}

int main(int argc, char*argv[])
{
	TBeBuilderEditor MyApp;
	MyApp.Run();
	return 0;
}
