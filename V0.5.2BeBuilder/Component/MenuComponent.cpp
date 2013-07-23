#include "MenuComponent.h"
#include "MenuCodeGenerator.h"

TMenuComponent::TMenuComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BHandler(AComponentName),TComponent(AComponentName,AClassName)
// BMenu(const char *name, menu_layout layout = B_ITEMS_IN_COLUMN) 
{
	FMenu = NULL;
	FMenu = new BMenu(AComponentName,B_ITEMS_IN_COLUMN);
	FElement = FMenu;
	FHandler = this;	
//	float largeur,hauteur;
	FParent = AFatherComponent;
	FCodeGenerator = new TMenuCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_LABEL,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
//	FPropertyList->AddProperty(PROP_MENU_LAYOUT,"B_ITEMS_IN_COLUMN");
	FPropertyList->AddProperty(PROP_MENU_LAYOUT,"B_ITEMS_IN_COLUMN",PROP_TYPE_FLOAT,false,false,
								"B_ITEMS_IN_COLUMN;B_ITEMS_IN_ROW",
								PROP_GENERAL_GROUP);
	
	
/*	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top));
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left));
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right));
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));
*/
}

TMenuComponent::~TMenuComponent()
{
	printf("Destructor de TMenuComponent Name : %s\n",FClassName.c_str());
	for (int32 ind=0; ind < FMenu->CountItems(); ind++)
	{
		FMenu->RemoveItem(ind);
	}	
	delete FMenu;
	delete FCodeGenerator;	
}

void TMenuComponent::MessageReceived(BMessage *message)
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

bool TMenuComponent::AddChild(TComponent *AComponent)
{
	ShowDebug("Inside TMenuComponent::AddItem");
	if (BMenu *buffer = dynamic_cast<BMenu *>(AComponent->FElement) )
	{
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			be_app->AddHandler(AComponent->FHandler);
			be_app->Unlock();
		}
		TComponent::AddChild(AComponent);	
		return FMenu->AddItem(buffer);	
	}
	if (BMenuItem *buffer = dynamic_cast<BMenuItem *>(AComponent))
	{
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			be_app->AddHandler(AComponent->FHandler);
			be_app->Unlock();
		}
		TComponent::AddChild(AComponent);
		return FMenu->AddItem(buffer);		
	}
	//On arrive ici ssi l'objet est un separator...
	if (AComponent->FElement==NULL)
	{
		TComponent::AddChild(AComponent);
		return FMenu->AddSeparatorItem();
	}

	ShowDebug("END ERROR Inside TMenuComponent::AddItem");
}

BMessage* TMenuComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,MENU_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,MENU_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,MENU_COMPONENT_VALUE);

	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_MENUBAR);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_MENU);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_MENU_FIELD);

	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_MENU);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,MENU_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,MENU_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_MENU);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(MENU_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(MENU_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
	DEBUGPRINT("GetProperties End.");
	return AMessage;

}

TComponent* TMenuComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TMenuComponent *AMenuComponent;
  	AMenuComponent = new TMenuComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return AMenuComponent;
}

bool TMenuComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
/*

	char  *name; 
	const char **data=NULL;
	uint32  type; 
	int32   count;
	string truc1,truc2; 
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				printf("TMenuComponent::Message Received. Message d'update recu!\n");
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (message->FindString(name,data)==B_OK)				         	
					{
						truc1 = name;
						truc2 = *data;
						FPropertyList->SetPropertyValue(truc1,truc2);												
						SetStandardProperties(name,*data);
						//--------- Attention special component... FMenu...
					}
				}
			break;
		default: BHandler::MessageReceived(message);
	}
*/

	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
//		SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
//		SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
//		SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);	
//		if (FindPropertyName(APropertyName,PROP_LABEL)) SetLabel(APropertyValue.c_str());

//		if (FindPropertyName(APropertyName,PROP_MESSAGE)) ((TButtonCodeGenerator *)FCodeGenerator)->CreateMessageReceived(!FLoaded);
/*	
		if (FindPropertyName(APropertyName,PROP_MENU_BORDER))
		{
			if (FindPropertyName(APropertyValue,"B_BORDER_FRAME")) SetBorder(B_BORDER_FRAME);
			if (FindPropertyName(APropertyValue,"B_BORDER_CONTENTS")) SetBorder(B_BORDER_CONTENTS);
			if (FindPropertyName(APropertyValue,"B_BORDER_EACH_ITEM")) SetBorder(B_BORDER_EACH_ITEM);
		}
*/		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}

