#include "RadioButtonComponent.h"

TRadioButtonComponent::TRadioButtonComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BRadioButton(AFrame,AComponentName,AComponentName,NULL),TComponentKindaView(AComponentName,AClassName,this)
{
	float largeur,hauteur;
	FHandler = this;
	FParent = AFatherComponent;
	FCodeGenerator = new TRadioButtonCodeGenerator(this,true);
	
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_LABEL,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_MESSAGE,"NULL",PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_LEFT | B_FOLLOW_TOP",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_FLAGS,"B_NAVIGABLE | B_WILL_DRAW",PROP_TYPE_FLOAT,true,false,
								"B_WILL_DRAW;B_PULSE_NEEDED;B_FRAME_EVENTS;B_FULL_UPDATE_ON_RESIZE;B_NAVIGABLE;B_NAVIGABLE_JUMP;B_SUBPIXEL_PRECISE",
								PROP_POSITION_GROUP);

	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	

	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);

}

TRadioButtonComponent::~TRadioButtonComponent()
{
	ShowDebug(string("Destructor de TRadioButtonComponent Name=") + FClassName);
	delete FCodeGenerator;	
}

void TRadioButtonComponent::MessageReceived(BMessage *message)
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

void TRadioButtonComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
}

void TRadioButtonComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
}

void TRadioButtonComponent::MouseDown(BPoint point)
{
	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);
		Looper()->Unlock();
	}
}

bool TRadioButtonComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
		SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
		SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
		SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);	
		if (FindPropertyName(APropertyName,PROP_LABEL)) SetLabel(APropertyValue.c_str());

		if (FindPropertyName(APropertyName,PROP_MESSAGE)) ((TRadioButtonCodeGenerator *)FCodeGenerator)->CreateMessageReceived(!FLoaded);
		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}

BMessage* TRadioButtonComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,RADIO_BUTTON_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,RADIO_BUTTON_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,RADIO_BUTTON_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,RADIO_BUTTON_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_FINAL);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,RADIO_BUTTON_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,RADIO_BUTTON_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(RADIO_BUTTON_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(RADIO_BUTTON_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;

}

TComponent* TRadioButtonComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TRadioButtonComponent *ARadioButtonComponent;
  	ARadioButtonComponent = new TRadioButtonComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return ARadioButtonComponent;
}



