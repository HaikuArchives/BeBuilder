//#include "stdafx.h"
#include "ComponentList.h"

TComponentList::TComponentList(TComponent *AParentComponent):TObject("ComponentList")
{
	FDebugMode = 1;
	FDebugMessage= "TComponentList ";
	FParentComponent = AParentComponent;
	FListeNotSorted = new BList();
}

TComponentList::~TComponentList()
{
	DEBUGPRINT("TComponentList::dtor inside.");
/*	for (TComponentCI p = FListe.begin(); p!= FListe.end(); ++p)
	{
		FParentComponent->RemoveChild(p->second);
		delete p->second;
		p->second = NULL;
	}
	*/
	for (int32 ind=0; ind<FListeNotSorted->CountItems(); ind++)
	{
		TComponent * AComponent = (TComponent *)FListeNotSorted->ItemAt(ind);	
		if (AComponent != NULL)
			delete AComponent;
//		(TComponent *)FListeNotSorted->ItemAt(ind) = NULL;
	}
	
	delete FListeNotSorted;
	DEBUGPRINT("TComponentList::dtor quitting.");
}

void TComponentList::AddComponent(TComponent *AComponent)
{
//	DEBUGPRINT("AddCOmponent avant le AddItem");		
	FListe[AComponent->FComponentName]= AComponent;
//	DEBUGPRINT("AddCOmponent avant le AddItem");		
	FListeNotSorted->AddItem(AComponent);	
//	DEBUGPRINT("AddCOmponent Apres le AddItem");		
}

void TComponentList::AddComponent(string AComponentName, string AClassName)
{
	TComponent *AComponent;
	AComponent = new TComponent(AComponentName.data(),AClassName.data());
	AddComponent(AComponent);
}

void TComponentList::RemoveComponent(TComponent *AComponent)
{
	ShowDebug("RemoveComponent inside.");		
	FListe[AComponent->FComponentName]= NULL;
//	DEBUGPRINT("AddCOmponent avant le AddItem");
	if (FListeNotSorted->HasItem(AComponent))		
		FListeNotSorted->RemoveItem(AComponent);	
	else
		ShowDebug("RemoveComponent AComponent can't be found...");
	ShowDebug("RemoveCOmponent quitting.");		
}

bool TComponentList::RemoveAllChild(void)
{
	ShowDebug("RemoveAllChild Inside");
	for (int32 ind=0; ind<FListeNotSorted->CountItems(); ind++)
	{
		if (FParentComponent!=NULL)
		{
			FParentComponent->RemoveChild((TComponent *)FListeNotSorted->ItemAt(ind));	
		}
		else
		{
			return false;
		}
	}
	return true;
}

//void TComponentList::RemoveComponent(string AComponentName, string AClassName)
void TComponentList::RemoveComponent(string AComponentName)
{
	TComponent *AComponent = GetComponent(AComponentName.c_str());
	RemoveComponent(AComponent);
}

TComponent *TComponentList::GetComponent(const char * AComponentName)
{
	string truc(AComponentName);
	return FListe[truc];
}

TComponent *TComponentList::NextComponent(bool FromBeginning)
{
//	static int32 FIndex;
	TComponent *AComp=NULL;
	if (FromBeginning) 
	{
/*		if (FListe.size()==0) return NULL;
		FBufIterator = FListe.begin();
		AComp = FBufIterator->second;*/
//----- Code pour avoir en ordre d'insertion car les map ordonne forcement.
		if (FListeNotSorted->CountItems()==0) return NULL;
		FIndex = 0;
		AComp = (TComponent *) FListeNotSorted->ItemAt(FIndex);	
	}
	else
	{
/*		FBufIterator++;
		if (FBufIterator==FListe.end()) 
			AComp = NULL;
		else
			AComp = FBufIterator->second;
*/
		FIndex++;
		if (FIndex==FListeNotSorted->CountItems())
			AComp = NULL;
		else
			AComp = (TComponent *)FListeNotSorted->ItemAt(FIndex);
	}
	return AComp;
}

void TComponentList::Debug(void)
{
	for (int32 ind=0; ind<FListeNotSorted->CountItems(); ind++)
	{
		printf("Component %ld Name %s\n",ind, ((TComponent *)FListeNotSorted->ItemAt(ind))->FComponentName.c_str());	
	}
//	FListeNotSorted->AddItem(AComponent);	
}

BMessage *TComponentList::SaveData()
{
	ShowDebug("SaveData() Inside.");
	BMessage *AMessage = new BMessage(SAVE_COMPONENT_LIST);
	BMessage *AMessageBuffer; 
	for (int32 ind=0; ind<FListeNotSorted->CountItems(); ind++)
	{
//		ShowDebug(string("SaveData index=") + IntToStr(ind));
		AMessageBuffer = ((TComponent *)FListeNotSorted->ItemAt(ind))->SaveData();	
		AMessage->AddMessage("ComponentToSave",AMessageBuffer);	
	}
	ShowDebug("SaveData() Quitting.");
	return AMessage;
}

bool TComponentList::LoadData(BMessage *AMessage, BHandler *AGuiHandler)
{
	BMessage AComponentMessage;
	BMessage AnAddOnMessage;
	ShowDebug("LoadData Inside.");
	AMessage->PrintToStream();
	for (int32 ind=0;;ind++ )
	{
		ShowDebug(string("LoadData ind=") + IntToStr(ind));
		if (AMessage->FindMessage("ComponentToSave",ind,&AComponentMessage)!=B_OK)
		{
			ShowDebug("LoadData Quitting");
			break;
		}
		if (AComponentMessage.FindMessage(SAVE_COMPONENT_ADDON_MESSAGE,&AnAddOnMessage)!=B_OK)
		{
			ShowDebug("LoadData cant find SAVE_COMPONENT_ADDON_MESSAGE");
			AComponentMessage.PrintToStream();
			return false;
		}
		else
		{
			
			ShowDebug("LoadData Should Launch AddOnMessage");
			AnAddOnMessage.PrintToStream();
			//Adding COMPONENT_SAVE_MESSAGE_ADDON to message
			AnAddOnMessage.AddMessage(COMPONENT_SAVE_MESSAGE_ADDON,&AComponentMessage);
//			AnAddOnMessage.AddPointer(COMPONENT_ITEM_TO_SELECT,FParentComponent->GetStringItem());
			AnAddOnMessage.AddInt32(COMPONENT_ITEM_TO_SELECT,FParentComponent->GetIndexInList());
						
			BMessenger AMessenger(AGuiHandler);
			AMessenger.SendMessage(&AnAddOnMessage);
			ShowDebug("LoadData AddOnMessage Should have been Launched.");
		}	
	}
	ShowDebug("LoadData Quitting.");
	return true;
}