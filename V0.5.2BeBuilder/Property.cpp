#include "stdafx.h"
#include "Property.h"
/*
TProperty::TProperty(const char *AName, const char *AValue,uint32 level = 0, bool expanded = true):BStringItem(AName, level, expanded),TObject("TProperty " +AName)
{
	FCodeLineList = new BList(10);
	FName = AName;
	FValue = AValue;
	Refresh();
	FDebugMode = 1;
	FDebugMessage= "TProperty ";
	FDebugMessage= FDebugMessage + AName;		
}
*/

TProperty::TProperty(	const char *AName, const char *AValue, const char *AType = PROP_TYPE_STRING, 
						bool AMultipleValue = false, bool ASimpleValue = true, const char *ADefaultList = "" ,
						const char *GroupName = PROP_GENERAL_GROUP, uint32 level = 0, bool expanded = true)
						:BStringItem(AName, level,expanded),TObject((string("TProperty ") + AName).c_str())
{
	FDebugMode = 1;
	FDebugMessage= "TProperty ";
	FDebugMessage= FDebugMessage + AName;		

	FCodeLineList = new BList(10);
	FCodeFileList = new BList(10);
	FName = AName;
	FValue = AValue;
	FType = AType;
	FDefaultValues = ADefaultList;
	FMultipleValue = AMultipleValue;
	FSimpleValue = ASimpleValue;
	FGroupName = GroupName;
	FHandler = NULL;
	Refresh();

	FGenerateWithOtherValue = false;
	FOtherValue = "";		
	
	
/*
	if (FMultipleValue)
	{
		ShowDebug("Multiple!");
//		DEBUGPRINT("Property="<<AName<<" Multiple! ");
	}
	else
	{
		ShowDebug("NON Multiple!");	
//		DEBUGPRINT("Property="<<AName<<" NON Multiple! ");
	}		
*/
}
/*
TProperty::TProperty(BMessage *AMessage)
{
	TProperty::TProperty("Name","Value",PROP_TYPE_STRING,false,true,"Value1;Value2",PROP_GENERAL_GROUP,0,true) 
	:BStringItem("name",0,true),TObject("Bidule");
}
*/

TProperty::~TProperty()
{
	delete FCodeLineList;
	delete FCodeFileList;
}

void TProperty::Refresh(void)
{
//	ShowDebug("Refresh Inside");
	string truc;
	truc = FName + " = " + FValue; 
	SetText(truc.c_str()); // remet le texte a name = valeur !	
//	ShowDebug(string("Refresh Quitting truc=") + truc);
}

void TProperty::AddToMessage(BMessage *AMessage)
{
	AMessage->AddString(FName.c_str(),FValue.c_str());	
	AMessage->AddPointer(PROP_MESSAGE_POINTER,this);
//	AMessage->AddString(FName.data(),FValue.data());	
	//printf("TProperty::AddToMessage Name: %s Value: %s \n",FName.data(),FValue.data());
}

void TProperty::SendMessage(BHandler *AHandler)
{
	BMessenger Messenger(AHandler);
	BMessage Message(MSG_PROPERTY);
	AddToMessage(&Message);
    Messenger.SendMessage(&Message);
}

void TProperty::Edit(int32 index, BHandler *AHandler)
{
	BRect truc(50,50,150,150);
	DEBUGPRINT("Inside TProperty::Edit");
	if (FSimpleValue)
	{
		DEBUGPRINT("TProperty::Edit Standard");
		FPropertyEditor = new TPropertyEditorStandard("Standard Property Editor",truc);
	}
	else
	{
		if (FMultipleValue)	
		{
	//		FPropertyEditor = new TPropertyEditorMultiChoice("Standard Property Editor",truc,PREFS_FILENAME);	
			DEBUGPRINT("TProperty::Edit Multi Choice");
			FPropertyEditor = new TPropertyEditorMultiChoice("Multiple Choice Property Editor",truc);
		}
		else
		{
	//		FPropertyEditor = new TPropertyEditorChoice("Standard Property Editor",truc,PREFS_FILENAME);	
			DEBUGPRINT("TProperty::Edit Choice");
			FPropertyEditor = new TPropertyEditorChoice("Choice Property Editor",truc);
		}
	}
//	FPropertyEditor = new TPropertyEditorWindow("Standard Property Editor",truc,PREFS_FILENAME);
	DEBUGPRINT("TProperty::Edit Before Show");
	FPropertyEditor->Show();
	BMessenger Messenger(FPropertyEditor);
	BMessage Message(MSG_PROPERTY_EDIT);
	Message.AddInt32("index",index);
	Message.AddPointer("ToolWindowHandler",AHandler);
	AddToMessage(&Message);
	DEBUGPRINT("TProperty::Edit Before Send Message");
    Messenger.SendMessage(&Message);	
	DEBUGPRINT("TProperty::Edit After Send Message");

}

bool TProperty::AddCodeLine(TCodeLine *ACodeLine)
{
	return FCodeLineList->AddItem((void *)ACodeLine);
}

bool TProperty::DeleteCodeLine(TCodeLine *ACodeLine)
{
	return FCodeLineList->RemoveItem((void *)ACodeLine);
}

bool TProperty::AddCodeFile(TCodeFile *ACodeFile)
{
	return FCodeFileList->AddItem((void *)ACodeFile);
}

bool TProperty::DeleteCodeFile(TCodeFile *ACodeFile)
{
	return FCodeFileList->RemoveItem((void *)ACodeFile);
}


bool TProperty::UpdateCode(void)
{
//	ShowDebug("UpdateCode entering.");	
	for (int ind=0; ind < FCodeLineList->CountItems(); ind++)
	{
		((TCodeLine *)FCodeLineList->ItemAt(ind))->UpdateLine(this);
	}
//	ShowDebug("UpdateCode RenameFile.");	
	for (int ind=0; ind < FCodeFileList->CountItems(); ind++)
	{
		((TCodeFile *)FCodeFileList->ItemAt(ind))->RenameFile(FValue.c_str());
	}
//	ShowDebug("UpdateCode quitting.");	
	return true;	
}

string TProperty::GetValue()
{
	return FValue;
}

bool TProperty::SetValue(string AStr)
{
	if (FValue!=AStr)
	{
//		ShowDebug(string("SetValue FValue=") + FValue + string(" AStr=") + AStr);
//		ShowDebug("SetValue These Values are different!");
		FValue = AStr;
		Refresh();
		return true;
	}
	//ShowDebug("SetValue These Values are NOT different!");
	return false;
}

void TProperty::Debug(void)
{
	ShowDebug("Debug.");
	ShowDebug(string("Name=") + FName);
	ShowDebug(string("Value=") + FValue);
	ShowDebug(string("Type=") + FType);
	ShowDebug(string("DefaultValues=") + FDefaultValues);
	ShowDebug(string("GroupName=") + FGroupName);
	ShowDebug("Debug End.");
}

TInteger::TInteger(int32 AnInteger)
{
	FValue = AnInteger;
}

BMessage *TProperty::SaveData()
{
	BMessage *AMessage = new BMessage(SAVE_PROPERTY);
	Debug();
	AMessage->AddString("SavePropertyName",FName.c_str());
	AMessage->AddString("SavePropertyValue",FValue.c_str());
	AMessage->AddString("SavePropertyType",FType.c_str());
	AMessage->AddString("SavePropertyDefaultValues",FDefaultValues.c_str());
	AMessage->AddString("SavePropertyGroupName",FGroupName.c_str());
	AMessage->AddBool("SavePropertyMultipleValue",FMultipleValue);
	AMessage->AddBool("SavePropertySimpleValue",FSimpleValue);	
	return AMessage;
}

bool TProperty::LoadData(BMessage *AMessage, BHandler *AGuiHandler)
{
// In this function AGuiHandler is not needed.
	const char *APropertyName;
	const char *APropertyValue;
	const char *APropertyType;
	const char *APropertyDefaultValues;
	const char *APropertyGroupName;
	bool APropertyMultipleValue;
	bool APropertySimpleValue;
	ShowDebug("LoadData Inside.");
//	AMessage->PrintToStream();
	if (AMessage->FindString("SavePropertyName",&APropertyName)!=B_OK) return false;
	if (AMessage->FindString("SavePropertyValue",&APropertyValue)!=B_OK) return false;
	if (AMessage->FindString("SavePropertyType",&APropertyType)!=B_OK) return false;
	if (AMessage->FindString("SavePropertyDefaultValues",&APropertyDefaultValues)!=B_OK) return false;
	if (AMessage->FindString("SavePropertyGroupName",&APropertyGroupName)!=B_OK) return false;
	if (AMessage->FindBool("SavePropertyMultipleValue",&APropertyMultipleValue)!=B_OK) return false;
	if (AMessage->FindBool("SavePropertySimpleValue",&APropertySimpleValue)!=B_OK) return false;

	FName = APropertyName;
	FValue = APropertyValue;
	FType = APropertyType;
	FDefaultValues = APropertyDefaultValues;
	FMultipleValue = APropertyMultipleValue;
	FSimpleValue = APropertySimpleValue;
	FGroupName = APropertyGroupName;
	Refresh();
	ShowDebug("LoadData Quitting.");
	return true;
}


