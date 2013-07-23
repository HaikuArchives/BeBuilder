#include "BoxComponent.h"

TBoxComponent::TBoxComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BBox(AFrame,AComponentName),TComponentKindaView(AComponentName,AClassName,this)
{
/*
     BBox(BRect frame, const char *name = NULL, 
         uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
         uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | 
               B_NAVIGABLE_JUMP, 
         border_style border = B_FANCY_BORDER) 
*/
	SetLabel(AComponentName);
//	float largeur,hauteur;
	FParent = AFatherComponent;
	FCodeGenerator = new TBoxCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_LABEL,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	
	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_LEFT | B_FOLLOW_TOP",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_FLAGS,"B_NAVIGABLE | B_WILL_DRAW",PROP_TYPE_FLOAT,true,false,
								"B_WILL_DRAW;B_PULSE_NEEDED;B_FRAME_EVENTS;B_FULL_UPDATE_ON_RESIZE;B_NAVIGABLE;B_NAVIGABLE_JUMP;B_SUBPIXEL_PRECISE",
								PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BORDER_STYLE,"B_FANCY_BORDER",PROP_TYPE_FLOAT,true,false,
								"B_FANCY_BORDER;B_PLAIN_BORDER;B_NO_BORDER",
								PROP_GENERAL_GROUP);
//	GetPreferredSize(&largeur,&hauteur);
//	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);

	FHandler = this; // on fait pointer le FHandler interne du TCOmponent dont on a besoin dans TComponentItem.
	FElement = this;
//	Show(); 
}

TBoxComponent::~TBoxComponent()
{
	ShowDebug(string("Destructor de TBoxComponent Name=") + FClassName);
	delete FCodeGenerator;	
}

void TBoxComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char *data;
	TComponent *AComponent;
	BPoint w2;
	uint32 mods;
	BPoint ABPoint(0,0);
	uint32  type; 
	int32   count;
	string truc1,truc2; 
	BMessenger AMessenger(Parent());
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				ShowDebug("TBoxComponent::Message Received. Message d'update recu!\n");
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (message->FindString(name,&data)==B_OK)				         	
					{
						truc1 = name;
						truc2 = data;
						ChangeProperty(truc1,truc2); 
						
//						FPropertyList->SetPropertyValue(truc1,truc2);												
//						SetStandardProperties(name,data);
//						SetFrameProperties(name,data,this->Parent());																			
//						SetSizingProperties(name,data,this);
//						SetFlagsProperties(name,data,this);	
//						if (strcmp(name,PROP_LABEL)==0) SetLabel(data);
					}
				}
			break;
		case DRAG_COMPONENT:
			if (message->FindPointer("Component",(void **)&AComponent) == B_OK)
			{
				if (AComponent != NULL)
				{
					if (this != AComponent)
					{
						if (message->FindPoint("_drop_offset_",&ABPoint)==B_OK)
						{
							GetMouse(&w2,&mods);
							ABPoint.x = w2.x - ABPoint.x; ABPoint.y = w2.y - ABPoint.y;
							AComponent->DroppedOnView(ABPoint);
						}
					}
					else
					{
//						Parent()->PostMessage(message,NULL);
//						Parent()->PostMessage(message,NULL);
						AMessenger.SendMessage(message);
					}
				}
			}				         	
			break;				
			
		default: BBox::MessageReceived(message);
	}
}

void TBoxComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
}

void TBoxComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
}

void TBoxComponent::MouseDown(BPoint point)
{
	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);
		Looper()->Unlock();
	}
}
/*
void TBoxComponent::DroppedOnView(BPoint ANewPos)
{
	if (Window()->Lock())
	{
		MoveTo(ANewPos.x,ANewPos.y);
		FrameMoved(ANewPos);						
		Window()->Unlock();
	}	
}
*/

BRect TBoxComponent::GetChildRect(const char *AClassName)
{
	string truc = AClassName;
	if (IsFoundInside(truc,"Box"))
	{
		return BRect(15.000000,15.000000,150.000000,50.000000);
	}	
	else
		return TComponent::GetChildRect(AClassName);
}

bool TBoxComponent::WhenAddChild(void)
{
	Show();
	ShowDebug("TBoxComponent::WhenAddChild done! \n");
	return true;
}

bool TBoxComponent::AddChild(TComponent *AComponent)
{
	ShowDebug("TBoxComponent::AddChild");
	if (AComponent->FElement!=NULL)
	{
		ShowDebug("TBoxComponent::AddChild After NOT NULL");
		if (BView *buffer = dynamic_cast<BView *>(AComponent->FElement) )
		{			
			ShowDebug("TBoxComponent::AddChild F->ELement After NOT NULL");
			BBox::AddChild(buffer);
			TComponent::AddChild(AComponent);
		}
		else
			if (BView *buffer = dynamic_cast<BView *>(AComponent) )
			{
				ShowDebug("TBoxComponent::AddChild AComponent After NOT NULL");
				BBox::AddChild(buffer);
				TComponent::AddChild(AComponent);
			}
		
	}
	else
	{
		if (AComponent!=NULL)
		{
			if (BView *buffer = dynamic_cast<BView *>(AComponent) )
			{
				ShowDebug("TBoxComponent::AddChild AComponent After NOT NULL");
				BBox::AddChild(buffer);
				TComponent::AddChild(AComponent);
			}
			else
			{
				ShowDebug("TBoxComponent::AddChild AComponent CANNOT BE ADDED!");
			}		
		}
	}
	ShowDebug("TBoxComponent::AddChild AComponent FIN NORMALE");	
	return true;
}


BMessage* TBoxComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,BOX_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,BOX_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,BOX_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,BOX_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_VIEW);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,BOX_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,BOX_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(BOX_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(BOX_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}
TComponent* TBoxComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TBoxComponent *ABoxComponent;
  	ABoxComponent = new TBoxComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return ABoxComponent;
}

bool TBoxComponent::ChangeProperty(string APropertyName, string APropertyValue)
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

		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}


