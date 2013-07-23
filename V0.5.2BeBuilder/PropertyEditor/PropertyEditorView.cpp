#include "PropertyEditorView.h"
#include "Property.h"
TPropertyEditorView::TPropertyEditorView(BRect frame):BView (frame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
{
/*
	BRect rect(180,10,frame.right-20,10);
	edtSrc = new BTextControl(rect,"edtSrc",NULL,NULL,NULL,B_FOLLOW_LEFT_RIGHT);
	BRect rect7(10,110,175,110);
	butZIP= new BButton(rect7,"butBrowseZIP","Path and ExeName for ZIP : ",new BMessage(ZIP_BROWSE));;
*/	
/* -- Should be for the really standard PropertyEditorView.
	
	BRect rect(13.000000,14.000000,248.000000,35.000000);	
	FTextEdit = new BTextControl(rect,"edtvalue",NULL,NULL,NULL,B_FOLLOW_LEFT_RIGHT);
	
	BRect rect1(16,46,85,70);	
	
	FButValidate = new BButton(rect1,"butValidate","Validate",new BMessage(PROPERTY_EDITOR_VALIDATE));
	FButValidate->MakeDefault(true);
	
	BRect rect2(179,46,248,70);	
	FButCancel = new BButton(rect2,"butCancel","Cancel",new BMessage(PROPERTY_EDITOR_CANCEL));
	SetViewColor(kGray);

	AddChild(FTextEdit);
	AddChild(FButValidate);
	AddChild(FButCancel);
*/
	FHandler = NULL;
	FIndex = -1;
}

TPropertyEditorView::~TPropertyEditorView()
{

}

TStringList *TPropertyEditorView::Split(string AString, string ASplitter)
{
	string buffer = AString;	
	string::size_type index;
	TStringList *AList = new TStringList();
	while(buffer.length()>0)
	{
		index = buffer.find(ASplitter);
//		DEBUGPRINT("index="<<index<<" element="<<buffer.substr(0,index-1)<<" remaining="<<buffer.substr(index+1,buffer.length()));
		DEBUGPRINT("index="<<index<<" element="<<buffer.substr(0,index-1));
		if (index>100000) break;
		if (index>1)
			AList->Add(buffer.substr(0,index));		
		if (index < buffer.length())
			buffer = buffer.substr(index+1,buffer.length());			
	}
	if (buffer.length()>0)
		AList->Add(buffer);				
	return AList;
}

//							FView->FTextEdit->SetLabel(name);
//							FView->FTextEdit->SetText(data);
void TPropertyEditorView::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	DEBUGPRINT("TPropertyEditorView::SetProperty Inside");
	if (FTextEdit != NULL)
	{
		DEBUGPRINT("TPropertyEditorView::SetProperty Name="<<AProperty->FName.c_str()<<" Value="<<(AProperty->GetValue()).c_str());
		FTextEdit->SetLabel(AProperty->FName.c_str());
		FTextEdit->SetText((AProperty->GetValue()).c_str());
	}
	DEBUGPRINT("TPropertyEditorView::SetProperty Quitting");	
}

/*
void TPropertyEditorView::AttachedToWindow(void)
{
	FButValidate->SetTarget(this);
	FButCancel->SetTarget(this);
	BView::AttachedToWindow(); 
}
*/

void TPropertyEditorView::MessageReceived(BMessage *message)
{
	BMessage *AMessage;
	BMessenger *AMessenger;
	switch(message->what)
	{
		case BUTTON_VALIDATE:
			DEBUGPRINT("Inside TPropertyEditorView::MessageReceived BUTTON_VALIDATE");		
			AMessenger = new BMessenger(FHandler);
			AMessage = new BMessage(MSG_PROPERTY_UPDATE);
			AMessage->AddString(PROPERTY_UPDATE_NEW_VALUE,FTextEdit->Text());
			AMessage->AddString(PROPERTY_UPDATE_OLD_VALUE,FOldValue.c_str());
			AMessage->AddInt32(PROPERTY_UPDATE_INDEX,FIndex);
			AMessenger->SendMessage(AMessage);
			Window()->Quit();
			break;		
		case BUTTON_CANCEL:
			DEBUGPRINT("Inside TPropertyEditorView::MessageReceived BUTTON_CANCEL");		
			Window()->Quit();
			break;					
		default :
			BView::MessageReceived(message);			
	}
}