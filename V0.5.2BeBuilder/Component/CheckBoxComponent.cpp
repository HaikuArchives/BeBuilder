#include "CheckBoxComponent.h"

TCheckBoxComponent::TCheckBoxComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BCheckBox(AFrame,AComponentName,AComponentName,NULL),TComponentKindaView(AComponentName,AClassName,this)
{
	float largeur,hauteur;
//	BRect rect5(d,ListBottom + HInter,d+Y,ListBottom + HInter + Hbutton);	
//	butCheck = new BButton(rect5,"butCheck","Check Files",new BMessage(CHECK_FILES),B_FOLLOW_BOTTOM | B_FOLLOW_H_CENTER);
	FHandler = this;

	FParent = AFatherComponent;
	FCodeGenerator = new TCheckBoxCodeGenerator(this,true);
//	FPropertyList->AddProperty(PROP_NAME,AComponentName);
//	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName);

//	FPropertyList->AddProperty(PROP_LABEL,AComponentName);
//	FPropertyList->AddProperty(PROP_MESSAGE,"");
	
	
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_LABEL,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_MESSAGE,"NULL",PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	
	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);

	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_LEFT | B_FOLLOW_TOP",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_FLAGS,"B_NAVIGABLE | B_WILL_DRAW",PROP_TYPE_FLOAT,true,false,
								"B_WILL_DRAW;B_PULSE_NEEDED;B_FRAME_EVENTS;B_FULL_UPDATE_ON_RESIZE;B_NAVIGABLE;B_NAVIGABLE_JUMP;B_SUBPIXEL_PRECISE",
								PROP_POSITION_GROUP);
	
	
//	Show(); 
}

TCheckBoxComponent::~TCheckBoxComponent()
{
	ShowDebug(string("Destructor de TCheckBoxComponent Name=") + FClassName);
	delete FCodeGenerator;	
}


void TCheckBoxComponent::MessageReceived(BMessage *message)
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
/*

void TCheckBoxComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char **data;
//	float largeur,hauteur;
	uint32  type; 
	int32   count;
//	int32 ResizingMode,TheFlags;
//	BRect ANewFrame;
	string truc1,truc2; 
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				printf("TCheckBoxComponent::Message Received. Message d'update recu!\n");
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
						SetFrameProperties(name,*data,this);																			
						SetSizingProperties(name,*data,this);
						SetFlagsProperties(name,*data,this);	
						if (strcmp(name,PROP_LABEL)==0) SetLabel(*data);
//						if (strcmp(name,PROP_MESSAGE)==0) SetLabel(*data); rien!

					}
				}
			break;
		default: BView::MessageReceived(message);
	}
}
*/

bool TCheckBoxComponent::ChangeProperty(string APropertyName, string APropertyValue)
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

		if (FindPropertyName(APropertyName,PROP_MESSAGE)) ((TCheckBoxCodeGenerator *)FCodeGenerator)->CreateMessageReceived(!FLoaded);
		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}


void TCheckBoxComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
}

void TCheckBoxComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
}

void TCheckBoxComponent::MouseDown(BPoint point)
{
//	DragComponent("CheckBoxComponent",DRAG_CHECKBOX_COMPONENT,this);
	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);
		Looper()->Unlock();
	}

}
/*
void TCheckBoxComponent::DroppedOnView(BPoint ANewPos)
{
	float largeur,hauteur;	
	if (Window()->Lock())
	{
		MoveTo(ANewPos.x,ANewPos.y);
//		ResizeTo(Contour.right-Contour.left,Contour.bottom-Contour.top);
		GetPreferredSize(&largeur,&hauteur);
		ResizeTo(largeur,hauteur);
		FrameMoved(ANewPos);						
		Window()->Unlock();
	}	
}
*/
BMessage *TCheckBoxComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,CHECK_BOX_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,CHECK_BOX_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,CHECK_BOX_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,CHECK_BOX_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_FINAL);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,CHECK_BOX_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,CHECK_BOX_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(CHECK_BOX_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(CHECK_BOX_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}

TComponent* TCheckBoxComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TCheckBoxComponent *ACheckBoxComponent;
  	ACheckBoxComponent = new TCheckBoxComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return ACheckBoxComponent;
}





