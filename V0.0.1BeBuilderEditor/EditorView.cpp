#include "EditorView.h"
#include "EditorWindow.h"

TEditorView::TEditorView(BRect frame): BView(frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE | B_WILL_DRAW) 
{
	_InitView();
}

void TEditorView::MessageReceived (BMessage *message)
{
//	DEBUGPRINT("TEditorView::MessageReceived");
//	message->PrintToStream();
	entry_ref ref;
	switch(message->what) 
	{		
		case MENU_FILE_OPEN:
			FOpenPanel->SetTarget(this);			
			FOpenPanel->Show();
			break;

		case MENU_FILE_NEW:
			{
				BRect r;
				r = Frame();
				new TEditorWindow(r);
			}
			break;
		case MENU_FILE_CLOSE:
			Window()->Quit();
			break;
		case MENU_FILE_QUIT:
			be_app->PostMessage(B_QUIT_REQUESTED);
			break;
		case MENU_FILE_SAVE:
			if (FEntry!=NULL)
			{
				Save(NULL);
				break;
			}
		case MENU_FILE_SAVEAS:
			FSavePanel->SetTarget(this);
			FSavePanel->Show();
			break;
		case B_SAVE_REQUESTED:
			Save(message);
			break;
		case B_REFS_RECEIVED:
		case B_SIMPLE_DATA:
			be_app->MessageReceived(new BMessage(message));
			break;
		default:
			BView::MessageReceived(message);
			break;
	}
}

TEditorView::TEditorView(BRect frame, entry_ref *ref): BView(frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE | B_WILL_DRAW)
{
	
	_InitView();
	LoadText(ref);	
	// Open the file
	
	Show();
}

bool TEditorView::LoadText(entry_ref *ref)
{
	BFile file;
	if (CanCloseBuffer(false))
	{
		if (file.SetTo(ref, B_READ_ONLY) == B_OK) 
		{
			off_t length;
			char *text;
			file.GetSize(&length);		// Get the file length;
			text = (char *) malloc(length);
			if (text && (file.Read(text, length) >= B_OK)) 
			{
				savemessage = new BMessage(B_SAVE_REQUESTED);
				if (savemessage) 
				{
					BEntry entry(ref, true);
					BEntry parent;
					entry_ref parent_ref;
					char name[B_FILE_NAME_LENGTH];
					
					entry.GetParent(&parent);		// Get parent directory
					entry.GetName(name);
					parent.GetRef(&parent_ref);
					savemessage->AddRef("directory", &parent_ref);
					savemessage->AddString("name", name);
					if (LockLooper())
					{
						FEdit->SetText(text, length);
						UnlockLooper();
					}
					FEdit->SetModified(false);
					if (FEntry!=NULL) delete FEntry;
						FEntry = new BEntry(ref);
					SetTitle(name);
				}
				free(text);
				return true;			
			}
		}
	}	
	return false;
}

bool TEditorView::CanCloseBuffer(bool ForceSave)
{
	bool ARes = true;
	if (FEdit->GetModified())
	{
		string truc = GetTitle();
		truc +=  SAVE_MESSAGE;
		BAlert *AnAlert;
		FLocker->Lock();
		if (ForceSave==false)
		{
			AnAlert = new BAlert (EDITOR_NAME,truc.c_str(),BUTTON_SAVE,BUTTON_DONT_SAVE,BUTTON_CANCEL,B_WIDTH_FROM_LABEL);
			(AnAlert->ButtonAt(2))->MakeDefault(false);
			(AnAlert->ButtonAt(0))->MakeDefault(true);
			AnAlert->SetShortcut(2,B_ESCAPE);
			AnAlert->SetShortcut(0,B_ENTER);
		}
		else
		{
			AnAlert = new BAlert (EDITOR_NAME,truc.c_str(),BUTTON_SAVE,BUTTON_DONT_SAVE,NULL,B_WIDTH_FROM_LABEL);
			(AnAlert->ButtonAt(1))->MakeDefault(false);
			(AnAlert->ButtonAt(0))->MakeDefault(true);
			AnAlert->SetShortcut(0,B_ENTER);		
		}
		
		int32 AValue = AnAlert->Go();		
		if (AValue==0) //Save
		{
			if (savemessage!=NULL)
			{
				Save(NULL);		
				ARes = true;
			}
			else
			{
				ARes = false;
				MessageReceived(new BMessage(MENU_FILE_SAVEAS));
			}
		}
		if (AValue==1) // Don't Save
		{
			ARes = true;
			if (FLocker->IsLocked())
				FLocker->Unlock();
			
		}
		if (AValue==2) //Cancel
		{
			ARes = false;			
			if (FLocker->IsLocked())
				FLocker->Unlock();			
		}
	}
	return ARes;
}

bool TEditorView::_InitView(void)
{
	//FilePanel creation
	FOpenPanel = new BFilePanel(B_OPEN_PANEL,NULL,NULL,0,true,NULL,NULL,true,true);
	FSavePanel = new BFilePanel(B_SAVE_PANEL,NULL,NULL,0,true,NULL,NULL,true,true);

	//SaveMessage
	savemessage = NULL;

	//Entry
	FEntry = NULL;	
	//Locker
	FLocker = new BLocker();
	
	BRect r = Bounds();
//	DEBUGPRINT("TEditorView::_InitView apres r=");
//	r.PrintToStream();
	r.bottom = r.top + GetHauteurMenu();
	FEditorMenu = new TEditorMenu(r);
	
	AddChild(FEditorMenu);

	BRect textframe = Bounds();
//	DEBUGPRINT("TEditorView::_InitView textframe=");
//	textframe.PrintToStream();
	textframe.top = FEditorMenu->Bounds().bottom + 1.0;
	textframe.right -= B_V_SCROLL_BAR_WIDTH;
	textframe.bottom -= B_H_SCROLL_BAR_HEIGHT;
	
//	DEBUGPRINT("TEditorView::_InitView apres textframe=");
//	textframe.PrintToStream();
	
//	textframe.bottom -= B_H_SCROLL_BAR_HEIGHT;
	
	BRect textrect = textframe;
	textrect.OffsetTo(B_ORIGIN);
//	DEBUGPRINT("TEditorView::_InitView apres textrect=");
//	textrect.PrintToStream();
	r.InsetBy(3.0,3.0);
//	DEBUGPRINT("TEditorView::_InitView apres r=");
//	r.PrintToStream();
	
	FEdit = new TEdit("Rien",textframe,textrect);

	FScrollView = new BScrollView("scroll_view",FEdit,B_FOLLOW_ALL_SIDES, 0, true, true, B_NO_BORDER);

	FEdit->SetTarget((BHandler *)this); // I want to get the message sent to this view in this module!
	AddChild(FScrollView);

	if (FEditorMenu->SetTargetTextView(FEdit)==false)
		DEBUGPRINT("TEditorView::_InitView() PasCapable!");
	if (FEditorMenu->SetTargetView(this)==false)
		DEBUGPRINT("TEditorView::_InitView() PasCapable2!");
	
	return true;
}

void TEditorView::FrameResized(float width, float height) 
{
	BRect textrect = FEdit->TextRect();
	textrect.right = textrect.left + (width - B_V_SCROLL_BAR_WIDTH - 3.0);
	FEdit->SetTextRect(textrect);
}

TEditorView::~TEditorView() 
{
	if (FEdit)
	{
//		if (WaitForSaveToBeDone())
//		{
			delete FEdit;			
//          		}
	}
	if (savemessage) 
	{
		delete savemessage;
	}	
}

status_t TEditorView::Save(BMessage *message) 
{
	if (FEdit->GetModified()==false)
		return B_OK;
	entry_ref ref;		// For the directory to save into
	status_t err;		// For the return code
	const char *name;	// For the filename
	BPath path;		// For the pathname
	BEntry entry;		// Used to make the path
	FILE *f;		// Standard Posix file
	
	// If a NULL is passed for the message pointer, use
	// the value we've cached; this lets us do saves without
	// thinking.
	
	if (!message) 
	{
		message = savemessage;
		if (!message) 
		{
			return B_ERROR;
		}
	}
	
	// Peel the entry_ref and name of the directory and
	// file out of the message.
	
	if ((err=message->FindRef("directory", &ref)) != B_OK) 
	{
		return err;
	}
	if ((err=message->FindString("name", &name)) != B_OK) 
	{
		return err;
	}
	
	// Take the directory and create a pathname out of it
	
	if ((err=entry.SetTo(&ref)) != B_OK) 
	{
		return err;
	}
	entry.GetPath(&path);		// Create a pathname for the directory
	path.Append(name);			// Tack on the filename
	
	// Now we can save the file.
	
	if (!(f = fopen(path.Path(), "w"))) 
	{
		return B_ERROR;
	}
	
	err = fwrite(FEdit->Text(), 1, FEdit->TextLength(), f);
	fclose(f);
	if (err >= 0) 
	{
		SetTitle(name);
		if (savemessage != message) 
		{
			if (savemessage) 
			{
				delete savemessage;
			}
			savemessage = new BMessage(message);
		}
	}
	if (err==B_OK) 
	{
		FEdit->SetModified(false);
		if (FEntry !=NULL ) delete FEntry;
			FEntry = new BEntry(&ref);
	}	
	if (FLocker->IsLocked())
		FLocker->Unlock();			
	return err;	
}

bool TEditorView::SetTitle(const char * ATitle)
{
	FTitle = ATitle;
	return true;
}

const char * TEditorView::GetTitle(void)
{
	if (FTitle.length()!=0)
		return FTitle.c_str();
	else
	{
		if (Window()!=NULL)
		{
			SetTitle(Window()->Title());
			return FTitle.c_str();			
		}
		else
		{
			return NULL;			
		}
		
	}
}

BEntry	*TEditorView::GetEntry(void)
{
	return FEntry;
}

float TEditorView::GetHauteurMenu(void)
{
	return 20;	
}

bool TEditorView::GotoLineNumber(int32 ALineNumber)
{
	FEdit->GoToLine(ALineNumber);
	return true;
}

bool TEditorView::SelectText(int32 AStartOffset, int32 ALength)
{
	FEdit->Highlight(AStartOffset,AStartOffset + ALength);
	return true;
}

bool TEditorView::WaitForSaveToBeDone(void)
{
	if (CanCloseBuffer(true))
	{
/*		while (FLocker->IsLocked())
		{
			snooze(15000);	
		}
	*/
/*		if (FLocker->LockWithTimeout(B_INFINITE_TIMEOUT))
		{
			FLocker->Unlock();
			return true;
		}
	*/
	}
	return false;
}



