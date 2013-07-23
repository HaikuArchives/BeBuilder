#include "ToolView.h"

TToolView::TToolView(BRect frame):BView (frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
{
	SetViewColor(kGray);
	BRect rect (1,1,frame.right,frame.bottom);
//	FOutListe = new BOutlineListView(rect,"Properties...",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_ALL_SIDES);
	FOutListe = new TGeneralOutlineList(rect,"Properties...",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_ALL_SIDES);
	FOutListe->SetViewColor(kGray);
//	FOutListe = new BOutlineListView(BRect rect2(0,0,frame.right,frame.bottom),"Components...",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_ALL_SIDES);
//	AddChild(new BScrollView("Scroll_File",FOutListe,B_FOLLOW_LEFT | B_FOLLOW_TOP,0,true,true,B_FANCY_BORDER));

//	AddChild(new BScrollView("Scroll_File",FOutListe,B_FOLLOW_ALL_SIDES,0,true,true,B_FANCY_BORDER));
//	AddChild(FOutListe);
}

TToolView::~TToolView()
{
	DEBUGPRINT("TToolView::dtor inside ");
	
	DEBUGPRINT("TToolView::dtor quitting");	
}

void TToolView::AttachedToWindow(void)
{
	//FOutListe->SetTarget(this);
//	FBuilderMenu->SetTarget(this);
	BView::AttachedToWindow(); 
}


void TToolView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		default :
			BView::MessageReceived(message);			
	}
}


