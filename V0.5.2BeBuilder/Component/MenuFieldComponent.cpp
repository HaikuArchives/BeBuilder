#include "MenuFieldComponent.h"
TMenuFieldComponent::TMenuFieldComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BMenuField(AFrame,AComponentName,"",new BMenu(AComponentName,B_ITEMS_IN_COLUMN),B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE),TComponentKindaView(AComponentName,AClassName,this)
/* 
   BMenuField(BRect frame, const char *name, 
         const char *label, 
         BMenu *menu, 
         uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
         uint32 flags = B_WILL_DRAW | B_NAVIGABLE) 
*/
{
	float largeur,hauteur;
	FHandler = this;
	FParent = AFatherComponent;
	FCodeGenerator = new TMenuFieldCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_LEFT | B_FOLLOW_TOP",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
								
//	FPropertyList->AddProperty(PROP_FLAGS,"B_ITEMS_IN_ROW");
	FPropertyList->AddProperty(PROP_FLAGS,"B_NAVIGABLE | B_WILL_DRAW",PROP_TYPE_FLOAT,true,false,
								"B_WILL_DRAW;B_PULSE_NEEDED;B_FRAME_EVENTS;B_FULL_UPDATE_ON_RESIZE;B_NAVIGABLE;B_NAVIGABLE_JUMP;B_SUBPIXEL_PRECISE",
								PROP_POSITION_GROUP);

	SetDivider(0);
//	FPropertyList->AddProperty(PROP_DIVIDER,FloatToStr(Divider()));
	FPropertyList->AddProperty(PROP_DIVIDER,FloatToStr(Divider()),PROP_TYPE_FLOAT,false,true,"",PROP_GENERAL_GROUP);

	if (IsEnabled())
		FPropertyList->AddProperty(PROP_ENABLED,BOOL_TRUE,PROP_TYPE_FLOAT,false,false,
								"TRUE;FALSE",
								PROP_POSITION_GROUP);
	else
		FPropertyList->AddProperty(PROP_ENABLED,BOOL_FALSE,PROP_TYPE_FLOAT,false,false,
								"TRUE;FALSE",
								PROP_POSITION_GROUP);
		
//	FPropertyList->AddProperty(PROP_LABEL,AComponentName);
	FPropertyList->AddProperty(PROP_LABEL,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FElement = this;
	FHandler = this;
}

TMenuFieldComponent::~TMenuFieldComponent()
{
	ShowDebug(string("Destructor de TMenuFieldComponent Name=") + FClassName);
	for (int32 ind=0; ind < Menu()->CountItems(); ind++)
	{
		Menu()->RemoveItem(ind);
	}	

	delete FCodeGenerator;	
}

void TMenuFieldComponent::MessageReceived(BMessage *message)
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

void TMenuFieldComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
	Draw(Frame());
}

void TMenuFieldComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
	BRect ARect = Frame();
	ARect.right = ARect.left + width;
	ARect.bottom = ARect.top + height;
	Draw(ARect);
}

void TMenuFieldComponent::MouseDown(BPoint point)
{
	if ((modifiers() & B_OPTION_KEY) != B_OPTION_KEY)
	{
		printf("TMenuFieldComponent::MouseDown OPTION_KEY NON pressee %x %x \n",modifiers(),B_OPTION_KEY);
	}
	else
			printf("TMenuFieldComponent::MouseDown OPTION_KEY PRESSEE! \n");

//	if ((Looper()->Lock())&&(modifiers() & B_OPTION_KEY != B_OPTION_KEY))
	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);
		Looper()->Unlock();
	}
	else
	{
		BMenuField::MouseDown(point);
	}
}
/*
void TMenuFieldComponent::DroppedOnView(BPoint ANewPos)
{
//	float largeur,hauteur;	
	if (Window()->Lock())
	{
		MoveTo(ANewPos.x,ANewPos.y);
		FrameMoved(ANewPos);						
		Window()->Unlock();
	}	
}
*/

bool TMenuFieldComponent::AddChild(TComponent *AComponent)
{
	printf("Inside TMenuFieldComponent::AddItem \n");
	if (BMenu *buffer = dynamic_cast<BMenu *>(AComponent->FElement) )
	{
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			be_app->AddHandler(AComponent->FHandler);
			be_app->Unlock();
		}
		TComponent::AddChild(AComponent);
		return Menu()->AddItem(buffer);	
		
	}
	if (BMenuItem *buffer = dynamic_cast<BMenuItem *>(AComponent->FElement))
	{
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			be_app->AddHandler(AComponent->FHandler);
			be_app->Unlock();
		}
		TComponent::AddChild(AComponent);
		return  Menu()->AddItem(buffer);		
	}
	if (AComponent->FElement==NULL)
	{
		TComponent::AddChild(AComponent);
		return Menu()->AddSeparatorItem();
	}

	printf("END ERROR Inside TMenuFieldComponent::AddItem \n");
	return false;
}

BMessage* TMenuFieldComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_FIELD_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,MENU_FIELD_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,MENU_FIELD_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,MENU_FIELD_COMPONENT_VALUE);

	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);

	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_MENU_FIELD);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,MENU_FIELD_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,MENU_FIELD_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_MENU);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(MENU_FIELD_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(MENU_FIELD_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}

TComponent* TMenuFieldComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TMenuFieldComponent *AMenuFieldComponent;
  	AMenuFieldComponent = new TMenuFieldComponent(AComponentName,AClassName,AFrame,AFatherComponent);
  	return AMenuFieldComponent;
}
bool TMenuFieldComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
		SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
		SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
//		SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);	
		if (FindPropertyName(APropertyName,PROP_DIVIDER)) SetDivider(StrToDouble(APropertyValue.c_str()));
		if (FindPropertyName(APropertyName,PROP_ENABLED)) 
		{
		 	if (FindPropertyName(APropertyValue,BOOL_FALSE))
		 	{
		 		SetEnabled(false);
			}		
			else
			{
				SetEnabled(true);
			}
		}
//		if (FindPropertyName(APropertyName,PROP_LABEL)) SetLabel(APropertyValue.c_str());

//		if (FindPropertyName(APropertyName,PROP_MESSAGE)) ((TButtonCodeGenerator *)FCodeGenerator)->CreateMessageReceived(!FLoaded);		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;

	return true;
}
