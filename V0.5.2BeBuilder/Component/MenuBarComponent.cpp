#include "MenuBarComponent.h"
TMenuBarComponent::TMenuBarComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
//BMenuBar(AFrame,AComponentName,B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP,B_ITEMS_IN_ROW,true),TComponent(AComponentName,AClassName)
BMenuBar(AFrame,AComponentName,B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP,B_ITEMS_IN_ROW,true),TComponentKindaView(AComponentName,AClassName,this)
/*      BMenuBar(BRect frame, const char *name, 
         uint32 resizingMode = B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, 
         menu_layout layout = B_ITEMS_IN_ROW, 
         bool resizeToFit = true) 
*/
{
	float largeur,hauteur;
	FCanGenerate = true;
	FParent = AFatherComponent;
	FCodeGenerator = new TMenuBarCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_LEFT | B_FOLLOW_TOP",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
//	FPropertyList->AddProperty(PROP_MENU_LAYOUT,"B_ITEMS_IN_ROW");

	FPropertyList->AddProperty(PROP_MENU_LAYOUT,"B_ITEMS_IN_ROW",PROP_TYPE_FLOAT,false,false,
								"B_ITEMS_IN_COLUMN;B_ITEMS_IN_ROW",
								PROP_GENERAL_GROUP);
	
//	FPropertyList->AddProperty(PROP_MENU_RESIZE_TO_FIT,"true");
	FPropertyList->AddProperty(PROP_MENU_RESIZE_TO_FIT,BOOL_FALSE,PROP_TYPE_FLOAT,false,false,
								"TRUE;FALSE",
								PROP_GENERAL_GROUP);
	
//	FPropertyList->AddProperty(PROP_MENU_BORDER,"B_BORDER_FRAME");
	FPropertyList->AddProperty(PROP_MENU_BORDER,"B_BORDER_FRAME",PROP_TYPE_FLOAT,false,false,
								"B_BORDER_FRAME;B_BORDER_CONTENTS;B_BORDER_EACH_ITEM",
								PROP_GENERAL_GROUP);



	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
}

TMenuBarComponent::~TMenuBarComponent()
{
	ShowDebug(string("Destructor de TMenuBarComponent Name=") + FClassName);	

	for (int32 ind=0; ind < CountItems(); ind++)
	{
		RemoveItem(ind);
	}	
	delete FCodeGenerator;	
}

void TMenuBarComponent::MessageReceived(BMessage *message)
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
		default: BView::MessageReceived(message);
	}
}

bool TMenuBarComponent::AddChild(TComponent *AComponent)
{
	ShowDebug("Inside AddItem \n");
	if (BMenu *buffer = dynamic_cast<BMenu *>(AComponent->FElement) )
	{
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			ShowDebug("AddItem Before AddHandler");		
			if (AComponent->FHandler==NULL) ShowDebug("TMenuBarComponent's handler is NULL \n");
			be_app->AddHandler(AComponent->FHandler);
			be_app->Unlock();
		}
		TComponent::AddChild(AComponent);
		return BMenuBar::AddItem(buffer);	
	}
	ShowDebug("END ERROR Inside AddItem");
}



BMessage* TMenuBarComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_BAR_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,MENU_BAR_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,MENU_BAR_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,MENU_BAR_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_MENUBAR);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,MENU_BAR_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,MENU_BAR_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_MENU);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(MENU_BAR_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(MENU_BAR_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}

TComponent* TMenuBarComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TMenuBarComponent *AMenuBarComponent;
	AFrame.top = 0;
	AFrame.left = 0;	
  	AMenuBarComponent = new TMenuBarComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return AMenuBarComponent;
}
bool TMenuBarComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
		SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
		SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
//		SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);	
//		if (FindPropertyName(APropertyName,PROP_LABEL)) SetLabel(APropertyValue.c_str());

		if (FindPropertyName(APropertyName,PROP_MESSAGE)) ((TMenuBarCodeGenerator *)FCodeGenerator)->CreateMessageReceived(!FLoaded);
	
		if (FindPropertyName(APropertyName,PROP_MENU_BORDER))
		{
			if (FindPropertyName(APropertyValue,"B_BORDER_FRAME")) SetBorder(B_BORDER_FRAME);
			if (FindPropertyName(APropertyValue,"B_BORDER_CONTENTS")) SetBorder(B_BORDER_CONTENTS);
			if (FindPropertyName(APropertyValue,"B_BORDER_EACH_ITEM")) SetBorder(B_BORDER_EACH_ITEM);
		}
		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}


