#include "PropertyEditorChoiceView.h"
#include "MenuPropertyEditorChoice.h"
#include "Property.h"
TPropertyEditorChoiceView::TPropertyEditorChoiceView(BRect AFrame)
//: BView(AFrame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
:TPropertyEditorView(AFrame)
{
	
	BRect ARectAButton17(137.000000,80.000000,211.000000,104.000000);
	
/*	AButton17 = new BButton(ARectAButton17,"AButton17","Cancel",new BMessage(BUTTON_CANCEL),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AButton17->MakeDefault(false);
	AddChild(AButton17);
*/

	FButCancel = new BButton(ARectAButton17,"FButCancel","Cancel",new BMessage(BUTTON_CANCEL),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	FButCancel->MakeDefault(false);
	AddChild(FButCancel);
	
	BRect ARectAButton16(6.000000,78.000000,80.000000,102.000000);
	
	FButValidate = new BButton(ARectAButton16,"FButValidate","Validate",new BMessage(BUTTON_VALIDATE),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	FButValidate->MakeDefault(true);
	AddChild(FButValidate);
	
	BRect ARectATextControl15(3.000000,48.000000,209.000000,69.000000);
	
	FTextEdit = new BTextControl(ARectATextControl15,"FTextEdit",NULL,NULL,NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AddChild(FTextEdit);
	FTextEdit->MakeFocus();
	FAMenuFieldComponent18 = NULL;
}

TPropertyEditorChoiceView::~TPropertyEditorChoiceView(void)
{
}

void TPropertyEditorChoiceView::RemoveAddMenuField(string AName)
{
	if (FAMenuFieldComponent18!=NULL)
	{
		RemoveChild(FAMenuFieldComponent18);
		delete FAMenuFieldComponent18;
	}
	BRect RectAMenuFieldComponent18(7.000000,14.000000,208.000000,36.000000);	
	FAMenuFieldComponent18 = new TMenuPropertyEditorChoice(RectAMenuFieldComponent18,AName.c_str());
	AddChild(FAMenuFieldComponent18);	
}

void TPropertyEditorChoiceView::MessageReceived(BMessage *message)
{
	const char *AMenuLabel;
	DEBUGPRINT("Inside TPropertyEditorChoiceView::MessageReceived");
//	BMessenger *AMessenger;
//	BMessage *AMessage;
	switch(message->what)
	{
		case PROPERTY_EDITOR_CHOICE_VIEW:
			DEBUGPRINT("Inside TPropertyEditorChoiceView::MessageReceived PROPERTY_EDITOR_CHOICE_VIEW");
			if (message->FindString("Label",&AMenuLabel)==B_OK)
			{
				DEBUGPRINT("Inside TPropertyEditorChoiceView::MessageReceived PROPERTY_EDITOR_CHOICE_VIEW Label="<<AMenuLabel);
				FTextEdit->SetText(AMenuLabel);			
			}
			break;
/*		case BUTTON_VALIDATE:
			DEBUGPRINT("Inside TPropertyEditorChoiceView::MessageReceived BUTTON_VALIDATE");		
			AMessenger = new BMessenger(FHandler);
			AMessage = new BMessage(MSG_PROPERTY_UPDATE);
			AMessage->AddString(PROPERTY_UPDATE_NEW_VALUE,FTextEdit->Text());
			AMessage->AddString(PROPERTY_UPDATE_OLD_VALUE,FOldValue.c_str());
			AMessenger->SendMessage(AMessage);
			break;		
*/
		default :
			 TPropertyEditorView::MessageReceived(message);
			break;
	}
}
void TPropertyEditorChoiceView::AttachedToWindow(void)
{
	FButValidate->SetTarget(this);
	FButCancel->SetTarget(this);
	BView::AttachedToWindow();
}

void TPropertyEditorChoiceView::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	TPropertyEditorView::SetProperty(AProperty,AnIndex,AHandler);

//	string::size_type index;
DEBUGPRINT("TPropertyEditorChoiceView::SetProperty Inside");
	FIndex = AnIndex;
	FHandler = AHandler;
	FOldValue = AProperty->FName;
	BMessage *AMessage;
	BMenuItem *AMenuItem;
	TStringList *AList = Split(AProperty->FDefaultValues,";");
	DEBUGPRINT("TPropertyEditorChoiceView::SetProperty After split.");
	RemoveAddMenuField(AProperty->FName);
//	FAMenuFieldComponent18->SetLabel((AProperty->FName).c_str());
	for (int ind=0; ind<AList->GetCount(); ind++)
	{
		AMessage = new BMessage(PROPERTY_EDITOR_CHOICE_VIEW);
		AMessage->AddString("Label",(AList->GetValue(ind)).c_str());
// BMenuItem(const char *label, BMessage *message, 
//         char shortcut = NULL, uint32 modifiers = NULL) 		
		AMenuItem = new BMenuItem((AList->GetValue(ind)).c_str(),AMessage);
		FAMenuFieldComponent18->Menu()->AddItem(AMenuItem);
		AMenuItem->SetTarget(this);
		
	}
	//Values.find(";");
	DEBUGPRINT("TPropertyEditorChoiceView::SetProperty Quitting");
	
}
/*
TStringList *TPropertyEditorChoiceView::Split(string AString, string ASplitter)
{
	string buffer = AString;	
	string::size_type index;
	TStringList *AList = new TStringList();
	while(buffer.length()>0)
	{
		index = buffer.find(ASplitter);
		DEBUGPRINT("index="<<index<<" element="<<buffer.substr(0,index-1)<<" remaining="<<buffer.substr(index+1,buffer.length()));
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
*/