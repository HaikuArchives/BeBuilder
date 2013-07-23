#include "EditorWindow.h"

TEditorWindow::TEditorWindow(BRect frame): BWindow(frame, "Untitled ", B_DOCUMENT_WINDOW, 0) 
{
	BRect r = Bounds();
	FEditorView = new TEditorView(r);
	AddChild(FEditorView);
	
	_InitWindow();
	Show();
}

TEditorWindow::TEditorWindow(BRect frame, entry_ref *ref): BWindow(frame, "Untitled ", B_DOCUMENT_WINDOW, 0) 
{
	BRect r = Bounds();
	FEditorView = new TEditorView(r);
	AddChild(FEditorView);
	FEditorView->LoadText(ref);
	_InitWindow();
	Show();
	SetTitle(FEditorView->GetTitle());
	FEntry = new BEntry(ref);
}

void TEditorWindow::_InitWindow(void) 
{
	FEntry = NULL;
	Register(true);
	Minimize(true);
}

void TEditorWindow::GetEntryRef(entry_ref *ref)
{
	if (FEntry==NULL)
	{
		FEntry = FEditorView->GetEntry();
	}
	if (FEntry!=NULL)
	{
		FEntry->GetRef(ref);
	}
}

bool TEditorWindow::Reload(entry_ref *ref)
{
	FEditorView->LoadText(ref);
	SetTitle(FEditorView->GetTitle());
	if (FEntry!=NULL) delete FEntry;
	FEntry = new BEntry(ref);
	return true;	
}

bool TEditorWindow::GotoLine(int32 ALineNumber)
{
	return FEditorView->GotoLineNumber(ALineNumber);
}

bool TEditorWindow::SelectText(int32 AStartOffset, int32 ALength)
{
	return FEditorView->SelectText(AStartOffset,ALength);
}


void TEditorWindow::FrameResized(float width, float height) 
{
	FEditorView->FrameResized(width,height);
	BWindow::FrameResized(width,height);
}


TEditorWindow::~TEditorWindow() 
{
	Unregister();
}

void TEditorWindow::MessageReceived(BMessage *message) 
{
	switch(message->what) 
	{
		case WINDOW_REGISTRY_ADDED:
			{
				char s[22];
				BRect rect;
				if (message->FindInt32("new_window_number", &window_id) == B_OK) 
				{
					if (FEditorView->GetTitle()==NULL)
					{
						sprintf(s, "Untitled %ld", window_id);
						SetTitle(s);
					}
				}
				if (message->FindRect("rect", &rect) == B_OK) {
					MoveTo(rect.LeftTop());
					ResizeTo(rect.Width(), rect.Height());
				}
				Minimize(false);
			}
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

void TEditorWindow::Register(bool need_id) 
{
	BMessenger messenger(APP_SIGNATURE);
	BMessage message(WINDOW_REGISTRY_ADD);
	
	message.AddBool("need_id", need_id);
	message.AddPointer("window_ptr", this);

	messenger.SendMessage(&message, this);
}


void TEditorWindow::Unregister(void) 
{
	BMessenger messenger(APP_SIGNATURE);
	BMessage message(WINDOW_REGISTRY_SUB);	
	message.AddPointer("window_ptr", this);	
	messenger.SendMessage(&message);
}


bool TEditorWindow::QuitRequested() 
{
	return FEditorView->CanCloseBuffer(false);
}