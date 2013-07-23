#include "BuilderView.h"
#include "ComponentList.h"
TBuilderView::TBuilderView(BRect frame):BView (frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
{
	SetViewColor(kGray);
	
//	BRect rect (1,1,frame.right,frame.bottom);
	BRect rect =frame;
//	BRect rect (0,0,frame.right - B_V_SCROLL_BAR_WIDTH,frame.bottom- B_H_SCROLL_BAR_HEIGHT);
	
//	FOutListe = new BOutlineListView(rect,"Components...",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_ALL_SIDES);
	FOutListe = new TGeneralOutlineList(rect,"Components...",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_ALL_SIDES);
	FScrollView = NULL;	
//	FScrollView = new BScrollView("Scroll_File",FOutListe,B_FOLLOW_ALL_SIDES,0,true,true,B_NO_BORDER);
//	AddChild(FScrollView);
//	AddChild(FOutListe);
	
	
	FOutListe->SetTarget(this);
	
	FToolWindow = NULL;

/*
	BRect rect;
 	rect.top = 0; 
 	rect.bottom = 19; // 19 
	FBuilderMenu = new TBuilderMenu(rect);	
	AddChild(FBuilderMenu);	
*/
}

TBuilderView::~TBuilderView()
{
	DEBUGPRINT("TBuilderView destructor");	
	if (FToolWindow!=NULL) 
	{
		if (FToolWindow->Lock()) FToolWindow->Quit();
	}
	DEBUGPRINT("TBuilderView Quitting destructor");	

}

void TBuilderView::AttachedToWindow(void)
{
	FOutListe->SetTarget(this);
	BView::AttachedToWindow(); 
}

void TBuilderView::SendPropertyMessage(TComponentItem *AComponentItem)
{
	DEBUGPRINT("TBuilderView::SendPropertyMessage Inside.");
	if (FToolWindow==NULL)
	{
		DEBUGPRINT("TBuilderView::SendPropertyMessage FToolWindow is null.");
//		BRect ToolRect(187,50,337,200);
		FToolWindow = new TToolWindow("Properties",TOOL_POSITION,PREFS_FILENAME);
		DEBUGPRINT("TBuilderView::SendPropertyMessage FToolWindow has been created.");
	}
	FToolWindow->Show();
	DEBUGPRINT("TBuilderView::SendPropertyMessage Avant le SendPropertyMessage");
	AComponentItem->GetComponent()->FPropertyList->SendPropertyMessage(FToolWindow,AComponentItem->GetHandler());
	DEBUGPRINT("TBuilderView::SendPropertyMessage Quitting.");
}
