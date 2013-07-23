#include "ComponentItem.h"
#include <Messenger.h>
TComponentItem::TComponentItem(const char *AName,const char *ATypeName,TComponent *AComponent,BHandler *AHandler,uint32 level = 0, bool expanded = true)
: BStringItem(AName,level,expanded)
{
	printf("ComponentItem constructor Debut Constructeur FName= %s Type= %s\n",AName,ATypeName);
	FName = AName;
	FComponent = AComponent;
	FClassName = AComponent->FClassName;
	FTypeName = ATypeName;
	FHandler = AHandler;
	printf("ComponentItem constructor HAndler.. Messenger VALID\n");
	
/*
	BMessenger AMessenger2(AHandler);
	if (AMessenger2.IsValid()) 
	{
		printf("CompoenntItem constructor HAndler.. Messenger VALID\n");
	}
	else
	{
		printf("ComponentItem constructor ====WARNING==== Handler.. non valid! \n");				
	}
*/	
}

TComponentItem::~TComponentItem()
{
	printf("TComponentItem destructor\n");	
}

void TComponentItem::SetName(const char *AName)
{
	FName = AName;	
	SetText(AName);
}

const char *TComponentItem::GetTypeName(void)
{
	return FTypeName.c_str();
}

const char *TComponentItem::GetName(void)
{
	return FName.c_str();
}

const char *TComponentItem::GetClassName(void)
{
	return FClassName.c_str();
}

TComponent *TComponentItem::GetComponent(void)
{
	return FComponent;	
}

BHandler *TComponentItem::GetHandler(void)
{
	return FHandler;
}

