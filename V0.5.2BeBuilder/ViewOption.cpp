/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "ViewOption.h"
TViewOption::TViewOption(BRect AFrame): BView(AFrame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE | B_WILL_DRAW)
{
	BRect ARect(10,10,150,30);
	BRect truc = Bounds();
	ARect.left = truc.left + 10;
	ARect.right = truc.right -10;
	FEditorOption=new TEditorOption(ARect);
	AddChild(FEditorOption);
}
TViewOption::~TViewOption(void)
{
}
void TViewOption::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		default :
			BView::MessageReceived(message);
			break;
	}
}
void TViewOption::AttachedToWindow(void)
{
	BView::AttachedToWindow();
}
