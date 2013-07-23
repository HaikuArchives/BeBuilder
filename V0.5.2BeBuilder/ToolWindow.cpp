#include "ToolWindow.h"

TToolWindow::TToolWindow(const char *Title,BRect frame, const char *Prefs):BGeneralWindow(Title,frame,Prefs,B_FLOATING_WINDOW,0)
{
	BRect ARect = Bounds();
	ARect.right -= B_V_SCROLL_BAR_WIDTH;
	ARect.bottom -= B_H_SCROLL_BAR_HEIGHT;
	FToolView = new TToolView(ARect);	

//	AddChild(new BScrollView("ScrollBuilderView",FToolView,B_FOLLOW_ALL_SIDES,0,true,true));
	AddChild(new BScrollView("ScrollBuilderView",FToolView->FOutListe,B_FOLLOW_ALL_SIDES,0,true,true));

//	FToolView = new TToolView(Bounds());	
//	AddChild(FToolView);

//	FToolView = new TToolView(Bounds());	
//	AddChild(FToolView);
	
}

TToolWindow::~TToolWindow()
{
	DEBUGPRINT("TToolWindow::destructor");
}	

void TToolWindow::MessageReceived(BMessage *message)
{
	char  *name; 
//	const char **data=NULL;
//	char data[1000];
	const char *data;
	const char *ANewValue;
	const char *AnOldValue;
	//data = (char *)malloc(FIND_STRING_SIZE*sizeof(char));
	uint32  type; 
	int32   count; 
	TProperty *AProp;
	BHandler *AHand;
	switch (message->what)
	{
		case MSG_PROPERTY_LIST :
			DEBUGPRINT("ToolWindow::MessageReceived MSG_PROPERTY_LIST");
//			message->PrintToStream();
			FToolView->FOutListe->MakeEmpty();
			if (message->FindPointer("ComposantHandler",(void **)&AHand)==B_OK)
			{			
				DisplayProperties(message);					
			}
			break;	
		case MSG_OUTLINE_CLICK :
			int32 bidule;
			//ShowMessage("Outline Inside ToolWindow");
			if (message->FindInt32("index", &bidule) == B_OK) 
			{
				AProp = ((TProperty *)(FToolView->FOutListe->ItemAt(bidule)));
				AProp->Edit(bidule,this);
			}		
			break;	
		case MSG_PROPERTY_EDITED :
				DEBUGPRINT("ToolWindow::MessageReceived MSG_PROPERTY_EDITED inside.");
				if (message->GetInfo(B_STRING_TYPE, 0, &name, &type, &count) == B_OK) 
				{ 
					if (message->FindString(name,&data)==B_OK)				         	
					{
						if (message->FindInt32("index", &bidule) == B_OK) 
						{
							AProp = ((TProperty *)(FToolView->FOutListe->ItemAt(bidule)));
							AProp->SetValue(string(data));
							AProp->Refresh(); //Renouveler l'affichage de l'element!					
							FToolView->FOutListe->Draw(FToolView->FOutListe->Bounds());							
							FToolView->FOutListe->Invalidate(FToolView->FOutListe->Bounds());
							Hide();
							Show();
//							BMessenger AMessenger(AProp->FHandler);
//							if (!AMessenger.IsValid()) {printf("AMessenger is not Valid!");}
							if (AProp->FHandler==NULL) {printf("AProp Handler is NULL!");}
							BMessage AMessage(MSG_PROPERTY_UPDATE);
							AProp->AddToMessage(&AMessage);
//							AMessenger.SendMessage(&AMessage);
							AProp->FHandler->MessageReceived(&AMessage);
							DEBUGPRINT("ToolWindow::MessageReceived Message Sent.");					
						}
					}
				}
				DEBUGPRINT("ToolWindow::MessageReceived MSG_PROPERTY_EDITED Quitting.");					
			break;
		case MSG_PROPERTY_UPDATE :
			if (message->FindString(PROPERTY_UPDATE_NEW_VALUE,&ANewValue)==B_OK)
			{
				if (message->FindString(PROPERTY_UPDATE_OLD_VALUE,&AnOldValue)==B_OK)
				{
					if (message->FindInt32(PROPERTY_UPDATE_INDEX,&bidule)==B_OK)
					{
						AProp = ((TProperty *)(FToolView->FOutListe->ItemAt(bidule)));
						AProp->SetValue(string(ANewValue));
						AProp->Refresh(); //Renouveler l'affichage de l'element!					
						FToolView->FOutListe->Draw(FToolView->FOutListe->Bounds());							
						BMessenger AMessenger(AProp->FHandler);
						if (!AMessenger.IsValid()) {GeneralException excep("AMessenger is not Valid!","TToolWindow::MessageReceived",true);}
						if (AProp->FHandler==NULL) {GeneralException excep("AProp Handler is NULL!","TToolWindow::MessageReceived",true);}
						BMessage AMessage(MSG_PROPERTY_UPDATE);
						AProp->AddToMessage(&AMessage);
						AMessenger.SendMessage(&AMessage);
						FToolView->FOutListe->Invalidate(FToolView->FOutListe->Bounds());					
					}
				}
			}
			break;
		default: BWindow::MessageReceived(message);			
	}
}

bool TToolWindow::DisplayProperties(BMessage *message)
{
//	DEBUGPRINT("Inside TToolWindow::DisplayProperties");
	if (LockLooper())
	{
		TProperty *AProperty;
		TStringList *FListGroup = new TStringList();		
		FToolView->FOutListe->MakeEmpty();
				
		BStringItem *AStrItem;		
		BHandler *AHand;
		if (message->FindPointer("ComposantHandler",(void **)&AHand)==B_OK)
		{
			for (int32 index = 0; ; index++) 
			{
				if (message->FindPointer(PROP_MESSAGE_POINTER,index,(void **)&AProperty) != B_OK)
				{
//					DEBUGPRINT("Inside TToolWindow::DisplayProperties EXITING index="<<index);
					break;							
				}
				else
				{
//					DEBUGPRINT("Property Name="<<AProperty->FName<<" Value="<<AProperty->GetValue()<<" FType="<<AProperty->FType<<" Default="<<AProperty->FDefaultValues);
					AProperty->FHandler = AHand;
					AStrItem = (BStringItem *)FListGroup->GetItem(AProperty->FGroupName);
					if (AStrItem!=NULL)
					{
	//					DEBUGPRINT("Inside TToolWindow::DisplayProperties AnInteger is not null GroupName="<<AProperty->FGroupName.c_str());
						FToolView->FOutListe->AddUnder(AProperty,FToolView->FOutListe->ItemAt(FToolView->FOutListe->IndexOf(AStrItem)));
					}
					else
					{
	//					DEBUGPRINT("Inside TToolWindow::DisplayProperties ELSE");
						AStrItem = new BStringItem(AProperty->FGroupName.c_str());
	//					DEBUGPRINT("Inside TToolWindow::DisplayProperties ELSE STrItem="<<AProperty->FGroupName.c_str());
						FToolView->FOutListe->AddItem(AStrItem);
						int32 NewIndex = FToolView->FOutListe->IndexOf(AStrItem);			
						FListGroup->AddItem(AProperty->FGroupName,(void *)AStrItem);												
	
						FToolView->FOutListe->AddUnder(AProperty,FToolView->FOutListe->ItemAt(NewIndex));
					}
				}
			}
		}
		UnlockLooper();
		if (FListGroup!=NULL) delete FListGroup;
		return true;
	}
	return false;
}

bool TToolWindow::QuitRequested(void)
{
	Hide();
	return false;
}

