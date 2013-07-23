#include "PropertyList.h"

TPropertyList::TPropertyList():TObject("TPropertyList")
{
	FDebugMode = 1;
	FDebugMessage = "TPropertyList ";
//printf("TPropertyList Constructor\n");		
	FPropertyList = new TStringList();		
}

TPropertyList::~TPropertyList()
{
	DEBUGPRINT("TPropertyList destructor inside.");		
	delete FPropertyList;
	DEBUGPRINT("TPropertyList destructor quitting.");		
	/*
	for (TPropertyCI p=FListe.begin(); p!=FListe.end(); ++p)
    {
		delete p->second;
    }
    */
}

void TPropertyList::AddProperty(string AName,string AValue, string AType, bool AMultipleValue, bool ASimpleValue, string ADefaultList, string AGroupName)
{
	TProperty *truc;
//	if (AValue==NULL) AValue="";
	truc = new TProperty(AName.c_str(),AValue.c_str(),AType.c_str(),AMultipleValue,ASimpleValue,ADefaultList.c_str(),AGroupName.c_str());
//		TProperty(const char *AName, const char *AValue, const char *AType = PROP_TYPE_STRING, bool AMultipleValue = false, bool ASimpleValue = true, const char *ADefaultList = "" ,const char *GroupName = PROP_GENERAL_GROUP, uint32 level = 0, bool expanded = true);

	truc->FName = AName;
	truc->SetValue(AValue);
	truc->FType = AType;
	truc->FDefaultValues = ADefaultList;
	truc->FMultipleValue = AMultipleValue; 
	truc->FGroupName = AGroupName;
//	FListe[AName] = truc;
	FPropertyList->AddItem(AName,truc,true);
}

void TPropertyList::AddProperty(string AName,string AValue)
{
	TProperty *truc;
	ShowDebug("AddProperty Before New TProperty");
	truc = new TProperty(AName.c_str(),AValue.c_str());
	ShowDebug("AddProperty After New TProperty");
	truc->FName = AName;
	truc->SetValue(AValue);
	ShowDebug("AddProperty Before AddItem");
	FPropertyList->AddItem(AName,truc,true); 	
	ShowDebug("AddProperty After AddItem");
}

TProperty *TPropertyList::GetProperty(string AName)
{
//	return FListe[AName];
	return (TProperty *)FPropertyList->GetItem(AName);
}

TProperty *TPropertyList::GetNextProperty(bool FromBegining)
{
	static int32 AnIndex;
	if (FromBegining)
	{
		AnIndex = 0;
	}
	else
	{
		AnIndex++;
	}
	ShowDebug(string("GetNextProperty Index=") + IntToStr(AnIndex));
	if (AnIndex<FPropertyList->GetCount())
		return (TProperty *)FPropertyList->GetItem(AnIndex);
	else
		return NULL;
}

string TPropertyList::GetPropertyValue(string AName)
{
//	return FListe[AName]->GetValue();
	return GetProperty(AName)->GetValue();
}

bool TPropertyList::SetPropertyValue(string AName,string AValue)
{
//	FListe[AName]->SetValue(AValue);
	TProperty *AProp = GetProperty(AName);
//	return (AProp->SetValue(AValue));
	if (AProp->SetValue(AValue))
	{
//		ShowDebug("SetProperty SetValue returns true.");
		return true;
	}
//	ShowDebug("SetProperty SetValue returns false.");	
	return false;
}

void TPropertyList::SendPropertyMessage(BHandler *AHandler,BHandler *AComposantHandler)
{
	ShowDebug("SendPropertyMessage");
	BMessenger Messenger(AHandler);
	BMessage Message(MSG_PROPERTY_LIST);
	for (int ind=0; ind < FPropertyList->GetCount(); ind++)
	{
		Message.AddPointer(PROP_MESSAGE_POINTER,(TProperty *)FPropertyList->GetItem(ind));		
	}
    Message.AddPointer("ComposantHandler",AComposantHandler);
    Messenger.SendMessage(&Message);
	ShowDebug("SendPropertyMessage End.");    
}

void TPropertyList::Debug()
{
	ShowDebug("Debug.");
	for (int ind=0; ind < FPropertyList->GetCount(); ind++)
	{
		((TProperty *)FPropertyList->GetItem(ind))->Debug();		
	}
	ShowDebug("Debug End.");	
}

bool TPropertyList::PreparePropertyMessage(BMessage **AMessage)
{
	DEBUGPRINT("TPropertyList::PreparePropertyMessage Inside");
	if ((AMessage!=NULL) && (*AMessage !=NULL))
	{
//#define PROP_MESSAGE_POINTER "PropertyPointer"
	
		for (TPropertyCI p=FListe.begin(); p!=FListe.end(); ++p)
	    {
			(*AMessage)->AddPointer(PROP_MESSAGE_POINTER,p->second);
//			p->second->AddToMessage(AMessage);
	    }
    	return true;
    }
	return false;
}

BMessage *TPropertyList::SaveData()
{
	BMessage *AnotherMessage=NULL;
	BMessage *AMessage = new BMessage(SAVE_PROPERTY_LIST);
	for (int ind=0; ind < FPropertyList->GetCount(); ind++)
	{
		AnotherMessage = ((TProperty *)FPropertyList->GetItem(ind))->SaveData();		
		if (AnotherMessage != NULL)
		{
			ShowDebug("SaveData: AnotherMessage is not NULL.");
			AMessage->AddMessage("SavePropertyMessage",AnotherMessage);
		}
		else
			ShowDebug("SaveData: AnotherMessage is NULL.");
	}	
	ShowDebug("SaveData: Fin.");
	return AMessage;
}

bool TPropertyList::LoadData(BMessage *AMessage, BHandler *AGuiHandler)
{
	//AGuiHandler is not used in this function.
	printf("LoadData DEBILEEEEEEEEEEEE\n");		
	ShowDebug("LoadData Inside");
	AMessage->PrintToStream();

	BMessage ABufferMessage;
	TProperty *AProperty;
	printf("LoadData Before Finding Message Message...0\n");		
	delete FPropertyList;
	FPropertyList = new TStringList();		
	printf("LoadData Before Finding Message Message...\n");		
	AMessage->PrintToStream();
	for (int32 ind = 0;;ind++ ) 
	{ 
		ShowDebug("LoadData Before Finding Message Message...");	
//		AMessage->PrintToStream();
		if (AMessage->FindMessage("SavePropertyMessage",ind,&ABufferMessage)==B_OK)				         	
		{	
			ShowDebug("LoadData SavePropertyMessage found ABufferMessage...");	
			ABufferMessage.PrintToStream();
			AProperty = new TProperty("ReloadingName","ReloadingValue");
			AProperty->LoadData(&ABufferMessage,AGuiHandler);				
			//Adding the property to the internal list
//			FPropertyList->AddItem(AProperty->FName.c_str(),AProperty,true);			
			FPropertyList->AddItem(AProperty->FName.c_str(),AProperty,false);			
		}
		else
		{
			break;
		}
	}
	ShowDebug("LoadData Quitting.");	
	return true;
}



