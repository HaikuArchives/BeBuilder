/*********************************************
* Generated Code By BeBuilder Pre-Alpha Release V0.4                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "PropertyEditorMultiChoiceView.h"
TPropertyEditorMultiChoiceView::TPropertyEditorMultiChoiceView(BRect AFrame)
//: BView(AFrame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW)
:TPropertyEditorView(AFrame)
{
	BRect ARectAListViewComponent12(14.000000,16.000000,194.000000,78.000000);
	AListViewComponent12 = new BListView(ARectAListViewComponent12,"AListViewComponent12",B_MULTIPLE_SELECTION_LIST,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);
	// Adding the the ScrollView! 
	AddChild(new BScrollView("scroll_AListViewComponent12",AListViewComponent12,B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, true,true));
	
	BRect ARectAButton11(139.000000,133.000000,212.000000,157.000000);

//
/*	
	AButton11 = new BButton(ARectAButton11,"AButton11","Cancel",NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AButton11->MakeDefault(false);
	AddChild(AButton11);
*/
	FButCancel = new BButton(ARectAButton11,"FButCancel","Cancel",new BMessage(BUTTON_CANCEL),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	FButCancel->MakeDefault(false);
	AddChild(FButCancel);
	
	BRect ARectAButton10(11.000000,132.000000,85.000000,156.000000);

/*	AButton10 = new BButton(ARectAButton10,"AButton10","Validate",NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AButton10->MakeDefault(true);
	AddChild(AButton10);
*/

	FButValidate = new BButton(ARectAButton10,"FButValidate","Validate",new BMessage(BUTTON_VALIDATE),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	FButValidate->MakeDefault(true);
	AddChild(FButValidate);

/*
	BRect ARectATextControl9(9.000000,100.000000,212.000000,120.000000);
	ATextControl9 = new BTextControl(ARectATextControl9,"ATextControl9",NULL,"Some Text",NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AddChild(ATextControl9);

*/	
	BRect ARectATextControl9(9.000000,100.000000,212.000000,120.000000);
	FTextEdit = new BTextControl(ARectATextControl9,"FTextEdit",NULL,NULL,NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP,B_WILL_DRAW | B_NAVIGABLE);
	AddChild(FTextEdit);
	FTextEdit->MakeFocus();
}
TPropertyEditorMultiChoiceView::~TPropertyEditorMultiChoiceView(void)
{
}
void TPropertyEditorMultiChoiceView::MessageReceived(BMessage *message)
{
	int32 selected;
	BStringItem *AStringItem;
	string truc;
	int32 ind=0;
	DEBUGPRINT("Inside TPropertyEditorMultiChoiceView::MessageReceived");
	switch(message->what)
	{
		case PROPERTY_EDITOR_MULTI_CHOICE_VIEW:
			DEBUGPRINT("TPropertyEditorMultiChoiceView::MessageReceived PROPERTY_EDITOR_MULTI_CHOICE_VIEW");
   			
   			while((selected = AListViewComponent12->CurrentSelection(ind))>=0)
   			{
   				AStringItem = (BStringItem *)AListViewComponent12->ItemAt(selected);
//   				DEBUGPRINT("selected="<<selected<<" Item="<<AStringItem->Text());
   				truc = truc + AStringItem->Text();
   				truc = truc + " | ";
   				ind ++;
   //		if (index < buffer.length())
//			buffer = buffer.substr(index+1,buffer.length());			
				
   			}
   			truc = truc.substr(0,truc.length()-3);
 			FTextEdit->SetText(truc.c_str());
     		break;
		default :
			TPropertyEditorView::MessageReceived(message);
			break;
	}
}
void TPropertyEditorMultiChoiceView::AttachedToWindow(void)
{
	FButValidate->SetTarget(this);
	FButCancel->SetTarget(this);
	BView::AttachedToWindow();
}

void TPropertyEditorMultiChoiceView::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	TPropertyEditorView::SetProperty(AProperty,AnIndex,AHandler);
	DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Inside");
	FIndex = AnIndex;
	FHandler = AHandler;
	FOldValue = AProperty->FName;
	BMessage *AMessage;
	BStringItem *ABufStrItem;
	int AFindInd;
//	BMenuItem *AMenuItem;
	TStringList *AList = Split(AProperty->FDefaultValues,";");
	TStringList *ASelectedList = Split(AProperty->GetValue(),"|");
	DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty After split.");
	//RemoveAddMenuField(AProperty->FName);
	for (int ind=0; ind<AList->GetCount(); ind++)
	{
		AListViewComponent12->AddItem(new BStringItem((AList->GetValue(ind)).c_str()));
	}
	DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Before searching selected List.");
	for (int ind=0; ind <ASelectedList->GetCount();ind++)
	{
		for (int ind2=0; ind2 < AListViewComponent12->CountItems(); ind2++)
		{
			ABufStrItem = (BStringItem *)(AListViewComponent12->ItemAt(ind2));
	//		DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Buffer="<<ABufStrItem->Text()<<" Value="<<ASelectedList->GetValue(ind).c_str());
	//		DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty length="<<strlen(ABufStrItem->Text())<<" Len="<<ASelectedList->GetValue(ind).length());
			AFindInd = ASelectedList->GetValue(ind).find(ABufStrItem->Text());
	//		DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty AFindInd="<<AFindInd);
			if ((AFindInd>=0) && (AFindInd <= ASelectedList->GetValue(ind).length()))
			{
				DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Should Select ind2="<<ind2);
				AListViewComponent12->Select(ind2,ind2,true);		
// void Select(int32 start, int32 finish, bool extend = false)						
			}
/*			if( strcmp(ABufStrItem->Text(),ASelectedList->GetValue(ind).c_str())==0)
			{
				DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Should Select ind2="<<ind2);
				AListViewComponent12->Select(ind2);
			}
*/
		}
		ASelectedList->GetValue(ind);
	}
	AMessage = new BMessage(PROPERTY_EDITOR_MULTI_CHOICE_VIEW);
//		AMessage->AddString("Label",(AList->GetValue(ind)).c_str());
    AListViewComponent12->SetSelectionMessage(AMessage); 
	AListViewComponent12->SetTarget(this);
	DEBUGPRINT("TPropertyEditorMultiChoiceView::SetProperty Quitting");
}

