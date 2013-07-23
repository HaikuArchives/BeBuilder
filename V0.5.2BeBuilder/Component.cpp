#include "stdafx.h"
#include "Component.h"
#include "ComponentList.h"
#include "ComponentItem.h"
TComponent::TComponent(const char *AComponentName, const char *AClassName):TObject(AComponentName)
{
	FDebugMode = 1;
	FDebugMessage= "TComponent ";
	FDebugMessage= FDebugMessage + AComponentName;		

	FComponentName = AComponentName;
	FClassName = AClassName;
	FParent = NULL;
	FPropertyList = new TPropertyList();
	FChildren = NULL;
	FChildren = new TComponentList(this);
	FHandler = NULL;
	FElement = NULL;
	FCodeGenerator=NULL;
	FHandlerElement	=NULL;
	FMessageAddOn = NULL;	
	FComponentListWindow = NULL;
//	FComponentItem = NULL;
	FLoaded = false;
	FStringItem = NULL;
	FIndexInList = -1;
	
}

TComponent::~TComponent()
{
	ShowDebug("dtor inside.");		
	delete FPropertyList;
	delete FChildren;
	ShowDebug("dtor quitting.");
}

bool TComponent::Generate(const char *APathName)
{
	ShowDebug("Inside Generate.");
	if (FCodeGenerator!=NULL)
	{
		ShowDebug("Generate Call To GenerateAll\n");
		FCodeGenerator->GenerateAll(APathName,FComponentName.c_str());
//		FCodeGenerator->GenerateAll(APathName,FClassName.c_str());
		ShowDebug("Generate End Of Call To GenerateAll\n");
		return true;
	}	
	return false;
}
void TComponent::SetStandardProperties(const char *PropertyName, const char *Value)
{
	if (strcmp(PropertyName,PROP_NAME)==0)
	{
		FComponentName = Value;
		TComponentItem * AComponentItem = (TComponentItem *)GetStringItem();
		if (AComponentItem!=NULL) AComponentItem->SetName(Value);
	}
	if (strcmp(PropertyName,PROP_CLASSNAME)==0) FClassName = Value;	
	
}
void TComponent::DessineContour(bool IsFocused)
{
	ShowDebug("TComponent :: DessineContour Inside.");
	if (FComponentListWindow!=NULL)
	{
		if (IsFocused)
		{
			BMessenger AMessenger(FComponentListWindow);
			if (FComponentListWindow==NULL)
			{
				ShowDebug("FComponentList is NULL.");
			}
			else
			{
				ShowDebug("FComponentList is not NULL");
			}
			if (AMessenger.IsValid()==false)
			{
				printf("TComponent::DessineContour BMessenger is not valid.\n");
			}	
			BMessage AMessage(MSG_COMPONENT_FOCUS);
//			AMessage.AddPointer(COMPONENT_POINTER,FComponentItem);
			AMessage.AddPointer(COMPONENT_POINTER,FStringItem);
			AMessenger.SendMessage(&AMessage);		
		}
	}
	ShowDebug("TComponent::DessineContour Quitting.");
}

bool TComponent::AddChild(TComponent *AComponent)
{
	printf("TComponent::AddChild \n");
	ShowDebug("AddChild");
//	AComponent->WhenAddChild();
	FChildren->AddComponent(AComponent);
	AComponent->FPathGeneration = FPathGeneration;
	AComponent->FParent = this;
	AComponent->WhenAddChild();	
	ShowDebug("AddChild Quitting");
	return true;
}

bool TComponent::AddItem(void *AnItem)
{
	//printf(TComponent::AddItem(void *AnItem));
	return true;
}

bool TComponent::WhenAddChild(void)
{
	printf("TComponent::WhenAddChild \n");
	return true;
}
//Remove...
bool TComponent::RemoveChild(TComponent *AComponent)
{
	ShowDebug("RemoveChild");
	if (AComponent!=NULL)
	{
		ShowDebug("Before WhenRemoveChild");
		AComponent->WhenRemoveChild();
		ShowDebug("Before RemoveComponent");
		FChildren->RemoveComponent(AComponent);
		ShowDebug("After RemoveComponent");
		delete AComponent;
		ShowDebug("RemoveChild after delete AComponent");

	}
	ShowDebug("RemoveChild Quitting");
	return true;
}

bool TComponent::WhenRemoveChild(void)
{
	ShowDebug("WhenRemoveChild");
	return true;
}

string *TComponent::GetBodyFileName(void) 
{
	ShowDebug("Inside GetBodyFileName");
	if (FCanGenerate) 
	{
		ShowDebug("GetBodyFileName FCanGenerate is true");
		string *truc = new string(FComponentName);
		*truc += ".cpp";
		ShowDebug(string("Before quitting GetBodyFileName *truc=") + *truc);
		return truc;
	}
	ShowDebug("GetBodyFileName FCanGenerate is false");
	return NULL;
}

string *TComponent::GetHeaderFileName(void) 
{
	if (FCanGenerate) 
	{
		string *truc = new string(FComponentName);
		*truc += ".h";
		return truc;
	}
	else
		return NULL;
}


BMessage *TComponent::SaveData()
{
	ShowDebug("SaveData Inside.");
	BMessage *AMessage = new BMessage(SAVE_COMPONENT);
	if (FParent!=NULL)
		AMessage->AddString(SAVE_COMPONENT_PARENT_COMPONENT_NAME,FParent->FComponentName.c_str());
	ShowDebug("SaveData Before Saving PropertyList.");
	BMessage *AnotherMessage = FPropertyList->SaveData();	
	ShowDebug("SaveData After Saving PropertyList.");
	AMessage->AddMessage(SAVE_COMPONENT_PROPERTY,AnotherMessage);
	ShowDebug("SaveData Before Saving Children.");
	BMessage *AMessageForIncludedComponent =  FChildren->SaveData();
	ShowDebug("SaveData After Saving Children.");
	AMessage->AddMessage(SAVE_COMPONENT_CHILDREN,AMessageForIncludedComponent);
	ShowDebug("SaveData After AMessageForIncludedComponent.");
	BMessage *AnAddOnMessage = GetAddOnMessage();
	if (AnAddOnMessage==NULL) ShowDebug("SaveData AnAddOnMessage is NULL");	
	else
	{
		ShowDebug("SaveData After GetAddOnMessage()");
		AMessage->AddMessage(SAVE_COMPONENT_ADDON_MESSAGE,AnAddOnMessage);
	}
	ShowDebug("SaveData Before FCodeGenerator->SaveData()");	
	BMessage *AComponentCodeGenerator = FCodeGenerator->SaveData();
	AMessage->AddMessage(SAVE_COMPONENT_CODE_GENERATOR,AComponentCodeGenerator);
	
	
	ShowDebug("SaveData Quitting.");
	return AMessage;
}

bool TComponent::LoadData(BMessage *AMessage, BHandler *AGuiHandler)
{
	BMessage AnotherMessage;
	BMessage AChildrenMessage;
	BMessage AnAddOnMessage;
	BMessage AComponentCodeGenerator;
//	ShowDebug("LoadData Inside Before Getting AddOn Message");
	ShowDebug("LoadData inside.");
	FLoaded = true; //Flag for the generation of code needed in the ChangeProperty for MessageReceived!
	
//	AMessage->PrintToStream();
//	ShowDebug("LoadData Inside After Getting AddOn Message");
	if (AMessage->FindMessage(SAVE_COMPONENT_PROPERTY,&AnotherMessage)!=B_OK) return false;
//	ShowDebug("LoadData Inside After Getting SAVE_COMPONENT_PROPERTY Message");
	if (AMessage->FindMessage(SAVE_COMPONENT_CHILDREN,&AChildrenMessage)!=B_OK) return false;

	ShowDebug("LoadData Inside Before PropertyList->LoadData");
	if (FPropertyList->LoadData(&AnotherMessage,AGuiHandler)==false) return false;
	ShowDebug("LoadData Inside Before FChildren->LoadData");
	if (FChildren->LoadData(&AChildrenMessage,AGuiHandler)==false) return false;	

//	ShowDebug("LoadData ChangeProperty For all.");
	//Now we need to change the value inside the component associated object. 
	int NbFrame=0;//When NbFrame==4 then all the dim are found then... we can resize and move the view.
	BRect AFrameRect;
/*	TProperty *AProperty = FPropertyList->GetNextProperty(true);
	while (AProperty!=NULL)
	{
		ShowDebug(string("LoadData Name=") + AProperty->FName + string(" value=") + AProperty->GetValue());
		AProperty = FPropertyList->GetNextProperty(false);	
	}
*/
	TProperty *AProperty = FPropertyList->GetNextProperty(true);
//	AProperty = FPropertyList->GetNextProperty(true);
	while (AProperty!=NULL)
	{
		ShowDebug(string("LoadData Name=") + AProperty->FName + string(" value=") + AProperty->GetValue());
		if (FindPropertyName(AProperty->FName,PROP_TOP))
		{
			AFrameRect.top = StrToDouble(AProperty->GetValue().c_str());
			NbFrame++;		
		}
		else
			if (FindPropertyName(AProperty->FName,PROP_BOTTOM))
			{
				AFrameRect.bottom = StrToDouble(AProperty->GetValue().c_str());
				NbFrame++;		
			}
			else
				if (FindPropertyName(AProperty->FName,PROP_LEFT))
				{
					AFrameRect.left = StrToDouble(AProperty->GetValue().c_str());
					NbFrame++;		
				}
				else
					if (FindPropertyName(AProperty->FName,PROP_RIGHT))
					{
						AFrameRect.right = StrToDouble(AProperty->GetValue().c_str());
						NbFrame++;		
					}
					else
					{
//						ShowDebug("Before ChangePRoperty");
						ChangeProperty(AProperty->FName,AProperty->GetValue());
//						ShowDebug("After ChangePRoperty");
					}
		if (NbFrame==4)
		{
			ResizeAndMove(AFrameRect);			
		}					
//		ShowDebug("Before GetNextProperty");
		AProperty = FPropertyList->GetNextProperty(false);	
//		ShowDebug("After GetNextProperty");
	}
//	ShowDebug("LoadData Before Finding SAVE_COMPONENT_CODE_GENERATOR");
	if (AMessage->FindMessage(SAVE_COMPONENT_CODE_GENERATOR,&AComponentCodeGenerator)!=B_OK) return false;
//	ShowDebug("LoadData Before Loading FCodeGenerator");
	FCodeGenerator->LoadData(&AComponentCodeGenerator,AGuiHandler);	
	ShowDebug("LoadData, Quitting.");
	return true;
}

bool TComponent::FindPropertyName(string APropertyName, const char *AValueToFind)
{
	long res;
	res = APropertyName.find(AValueToFind);
//	ShowDebug(string("FindPropertyName APropertyName=") + APropertyName + string(" AValueToFind=") + string(AValueToFind) + string(" res=") + IntToStr(res));
	if (res >= 0 )
	{
		return true;
	}
	return false;
}

bool TComponent::SetAddOnMessage(BMessage *AMessage)
{
	if (FMessageAddOn != NULL) delete FMessageAddOn;
	FMessageAddOn = new BMessage(AMessage);
	return true;
}

BMessage * TComponent::GetAddOnMessage(void)
{
	ShowDebug("Inside GetAddOnMessage");
	if (FMessageAddOn==NULL)
	{
		ShowDebug("GetAddOnMessage FMessageAddOn is NULL");
	}
	else
		ShowDebug("getAddOnMessage FMessageAddOn is not NULL");
	return FMessageAddOn;
}

bool TComponent::SetComponentListWindow(BHandler *AHandler)
{
	FComponentListWindow = AHandler;
	return true;
}

BHandler *TComponent::GetComponentListWindow(void)	
{
	return FComponentListWindow;
}
/*
bool TComponent::SetComponentItem(TComponentItem *AComponentItem)	
{
	FComponentItem = AComponentItem;
	return true;
}

TComponentItem * TComponent::GetComponentItem(void)
{
	return FComponentItem;
}
*/

bool TComponent::SetStringItem(BStringItem *AStringItem)	
{
	FStringItem = AStringItem;
	return true;
}

BStringItem * TComponent::GetStringItem(void)
{
	return FStringItem;
}

bool TComponent::SetIndexInList(int32 AnIndexInList)	
{
	FIndexInList = AnIndexInList;
	return true;
}

int32 TComponent::GetIndexInList(void)
{
	return FIndexInList;
}


bool TComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug("ChangeProperty Inside UpdatingCode");
	if (!FLoaded)
	{
		(FPropertyList->GetProperty(APropertyName))->UpdateCode();
	}
	ShowDebug("ChangeProperty After UpdatingCode");
	return true;
}

