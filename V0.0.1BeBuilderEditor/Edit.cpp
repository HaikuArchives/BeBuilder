#include "Edit.h"

TEdit::TEdit(const char *name,BRect AFrame,BRect ATextFrame) : BTextView(AFrame, name, ATextFrame, B_FOLLOW_ALL_SIDES,B_WILL_DRAW | B_PULSE_NEEDED)
{
	FTarget = NULL;
	SetModified(false);	
	SetWordWrap(false);	
	SetDoesUndo(true);
	MakeFocus(true);
	
//	SetWordWrap(true);	
	
}

TEdit::~TEdit()
{
	;
}

void TEdit::MessageReceived(BMessage *message)
{
//	DEBUGPRINT("TEDIT::MEssageReceived ");
//	message->PrintToStream();
	if (FTarget!=NULL)
	{
	//	DEBUGPRINT("TEDIT::MEssageReceived FTarget is not null!");	
		BMessenger AMessenger(FTarget);
		AMessenger.SendMessage(new BMessage(message));
	}
}

bool TEdit::SetTarget (BHandler *AHandler)
{
	FTarget = AHandler;
	return true;
}

void TEdit::InsertText(const char *text, int32 length, int32 offset, const text_run_array *runs)
{
//	DEBUGPRINT("TEdit::InsertText inside.");
	SetModified(true);
	BTextView::InsertText(text,length,offset,runs);
}

void TEdit::DeleteText(int32 start, int32 finish)
{
//	DEBUGPRINT("TEdit::DeleteText inside.");
	SetModified(true);
	BTextView::DeleteText(start,finish);
}

bool TEdit::GetModified(void)
{
	return FModified;
}

bool TEdit::SetModified(bool AValue)
{
	return (FModified = AValue);
}
