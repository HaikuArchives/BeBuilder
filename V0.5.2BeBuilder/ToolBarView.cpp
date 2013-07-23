#include "ToolBarView.h"

TToolBarView::TToolBarView(BRect frame)
:BView (frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
{
/*	BRect rect(13.000000,14.000000,248.000000,35.000000);	
	FTextEdit = new BTextControl(rect,"edtvalue",NULL,NULL,NULL,B_FOLLOW_LEFT_RIGHT);
	
	BRect rect1(16,46,85,70);	
	
	FButValidate = new BButton(rect1,"butValidate","Validate",new BMessage(PROPERTY_EDITOR_VALIDATE));
	FButValidate->MakeDefault(true);
	
	BRect rect2(179,46,248,70);	
	FButCancel = new BButton(rect2,"butCancel","Cancel",new BMessage(PROPERTY_EDITOR_CANCEL));
	SetViewColor(kGray);

	AddChild(FTextEdit);
	AddChild(FButValidate);
	AddChild(FButCancel);*/
}

TToolBarView::~TToolBarView()
{
	DEBUGPRINT("TToolBarView destructor Inside");	
	DEBUGPRINT("TToolBarView destructor Quitting");	
}
