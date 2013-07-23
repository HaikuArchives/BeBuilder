#include "GeneralOutlineList.h"

TGeneralOutlineList::TGeneralOutlineList(BRect frame, const char *name, list_view_type type = B_SINGLE_SELECTION_LIST, 
uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE )
:BOutlineListView(frame,name,type,resizingMode,flags) 
{
//empty
}

void TGeneralOutlineList::Draw(BRect ARect)
{
	rgb_color truc;
	truc = ViewColor();
	BOutlineListView::Draw(ARect);
	SetViewColor(truc); // Pour conserver la couleur de fond!
}

void TGeneralOutlineList::MouseDown(BPoint point)
{
	BOutlineListView::MouseDown(point);

	BMessenger messenger(Target());
	BMessage message(MSG_OUTLINE_CLICK);
	if (AddIndexToMessage(&message)) messenger.SendMessage(&message,this);		
		
}

void TGeneralOutlineList::KeyDown(const char *bytes, int32 numBytes)
{
	BOutlineListView::KeyDown(bytes,numBytes);
	if (numBytes=1)
	{
		if (*bytes==0x7f)
		{
			printf("DELETE!");
			BMessenger messenger(Target());
			BMessage message(MSG_OUTLINE_DELETE);
			if (AddIndexToMessage(&message)) messenger.SendMessage(&message,this);
		}
		else
		{
			BMessenger messenger(Target());
			BMessage message(MSG_OUTLINE_CLICK);
			if (AddIndexToMessage(&message)) messenger.SendMessage(&message,this);
		}
	}
}

bool TGeneralOutlineList::AddIndexToMessage(BMessage *AMessage)
{
	for (int32 ind = 0; ind < FullListCountItems(); ind ++)
	{
		if (FullListItemAt(ind)->IsSelected())
		{
			AMessage->AddInt32("index",ind);
			return true;
		}
	}
	return false;		
}