#include "MenuSeparatorComponent.h"
#include "MenuSeparatorCodeGenerator.h"

TMenuSeparatorComponent::TMenuSeparatorComponent(const char *AComponentName, const char *AClassName, TComponent *AFatherComponent):
TComponent(AComponentName,AClassName),BHandler(AComponentName)
{
	FParent = AFatherComponent;
	FCodeGenerator = new TMenuSeparatorCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
}

TMenuSeparatorComponent::~TMenuSeparatorComponent()
{
	ShowDebug(string("Destructor de TMenuSeparatorComponent Name=") + FClassName);	
	delete FCodeGenerator;	
}

void TMenuSeparatorComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char *data;
	uint32  type; 
	int32   count;
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (message->FindString(name,&data)==B_OK)				         	
					{
						ChangeProperty(string(name),string(data));
					}
				}
			break;
		default: BHandler::MessageReceived(message);
	}
}

BMessage* TMenuSeparatorComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_SEPARATOR_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,MENU_SEPARATOR_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,MENU_SEPARATOR_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,MENU_SEPARATOR_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_MENU);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_MENU_FIELD);	
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_FINAL);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,MENU_SEPARATOR_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,MENU_SEPARATOR_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_MENU);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(MENU_SEPARATOR_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(MENU_SEPARATOR_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;

}

TComponent* TMenuSeparatorComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TMenuSeparatorComponent *AMenuSeparatorComponent;
  	AMenuSeparatorComponent = new TMenuSeparatorComponent(AComponentName,AClassName,AFatherComponent);
  	return AMenuSeparatorComponent;
}

bool TMenuSeparatorComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}

