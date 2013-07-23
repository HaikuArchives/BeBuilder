#include "ViewComponent.h"

TViewComponent::TViewComponent(const char *AComponentName,const char *AClassName, BRect AFrame,TComponent *AFatherComponent)
//: BView (AFrame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW),TComponent(AComponentName,AClassName)
: BView (AFrame,NULL,B_FOLLOW_ALL_SIDES,B_NAVIGABLE|B_WILL_DRAW),TComponentKindaView(AComponentName,AClassName,this)
{
	FDebugMode = 1;
	FDebugMessage= "TViewComponent ";
	FDebugMessage= FDebugMessage + AComponentName ;
	FDebugMessage +=  " ";		
	FCanGenerate = true;
	FParent = AFatherComponent;
	FCodeGenerator = new TViewCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);


	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);

	FPropertyList->AddProperty(PROP_RESIZING_MODE,"B_FOLLOW_ALL_SIDES",PROP_TYPE_FLOAT,true,false,
								"B_FOLLOW_LEFT;B_FOLLOW_RIGHT;B_FOLLOW_LEFT_RIGHT;B_FOLLOW_H_CENTER;B_FOLLOW_TOP;B_FOLLOW_BOTTOM;B_FOLLOW_TOP_BOTTOM;B_FOLLOW_V_CENTER;B_FOLLOW_ALL_SIDES;B_FOLLOW_NONE",
								PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_FLAGS,"B_NAVIGABLE | B_WILL_DRAW",PROP_TYPE_FLOAT,true,false,
								"B_WILL_DRAW;B_PULSE_NEEDED;B_FRAME_EVENTS;B_FULL_UPDATE_ON_RESIZE;B_NAVIGABLE;B_NAVIGABLE_JUMP;B_SUBPIXEL_PRECISE",
								PROP_POSITION_GROUP);

	SetViewColor(kGray);
	FHandler = this;
}

TViewComponent::~TViewComponent()
{
	ShowDebug(string("Destructor de TViewComponent Name=") + FClassName);
	RemoveSelf();
	delete FCodeGenerator;	
	ShowDebug(string("Quitting Destructor de TViewComponent Name=") + FClassName);
}

void TViewComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char *data;
	uint32  type; 
	int32   count;
	string truc1,truc2; 
	TComponent *AComponent;
	BPoint w2;
	uint32 mods;
	BPoint ABPoint(0,0);
	//printf("Inside TViewComponent::MessageReceived! \n");
	//message->PrintToStream();	
	switch(message->what)
	{
	//	printf("Inside TViewComponent::MessageReceived before switch!");
		case MSG_PROPERTY_UPDATE :
				ShowDebug("MessageReceived. Message d'update recu!");
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (message->FindString(name,&data)==B_OK)				         	
					{
						truc1 = name;
						truc2 = data;
						ChangeProperty(truc1,truc2); 
					}
				}
				ShowDebug("MessageReceived. Quitting Message d'update!");
			break;
		case DRAG_COMPONENT:
//			printf("Inside TViewComponent::MessageReceived for Drag_Component!:");
			if (message->FindPointer("Component",(void **)&AComponent) == B_OK)
			{
//				printf("Inside TViewComponent::MessageReceived for Drag_Component Pointer Found!");
				if (AComponent != NULL)
				{
//					printf("Inside TViewComponent::MessageReceived for Drag_Component Pointer Found and NOT NULL!");			
					if (message->FindPoint("_drop_offset_",&ABPoint)==B_OK)
					{
						GetMouse(&w2,&mods);
						ShowDebug(string("MessageReceived. ABPoint.x=") + FloatToStr(ABPoint.x) + string("ABPoint.y=") + FloatToStr(ABPoint.y));
						ShowDebug(string("MessageReceived. w2.x=") + FloatToStr(w2.x) + string("w2.y=") + FloatToStr(w2.y));
						ABPoint.x = w2.x - ABPoint.x; ABPoint.y = w2.y - ABPoint.y;
						AComponent->DroppedOnView(ABPoint);
					}
				}
			}				         	
			break;				
		default: BView::MessageReceived(message);
	}
}

void TViewComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
}

void TViewComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
}

BRect TViewComponent::GetChildRect(const char *AClassName)
{
	string truc = AClassName;
	if (IsFoundInside(truc,"Box"))
	{
		return BRect(16.000000,13.000000,140.000000,130.000000);
	}	
	if (IsFoundInside(truc,"ListView"))
	{
		return BRect(15.000000,15.000000,100.000000,100.000000);	
	}
	return TComponent::GetChildRect(AClassName);
}


void TViewComponent::MouseDown(BPoint point)
{	
	MouseDownComponent("Component",DRAG_COMPONENT,this,point);
}

bool TViewComponent::AddChild(TComponent *AComponent)
{
	ShowDebug("AddChild Inside");
	if (AComponent->FElement!=NULL)
	{
		ShowDebug("AddChild After NOT NULL");
		if (BView *buffer = dynamic_cast<BView *>(AComponent->FElement) )
		{			
			ShowDebug("AddChild F->ELement After NOT NULL");
			BView::AddChild(buffer);
			TComponent::AddChild(AComponent);
		}
		else
			if (BView *buffer = dynamic_cast<BView *>(AComponent) )
			{
				ShowDebug("AddChild AComponent After NOT NULL");
				BView::AddChild(buffer);
				TComponent::AddChild(AComponent);
			}
		
	}
	else
	{
		if (AComponent!=NULL)
		{
			if (BView *buffer = dynamic_cast<BView *>(AComponent) )
			{
				ShowDebug("AddChild AComponent After NOT NULL");
				BView::AddChild(buffer);
				TComponent::AddChild(AComponent);
			}
			else
			{
				ShowDebug("AddChild AComponent CANNOT BE ADDED!");				
				return false;
			}		
		}
	}
	ShowDebug("AddChild AComponent FIN NORMALE\n");
	
	return true;
}

bool TViewComponent::RemoveChild(TComponent *AComponent)
{
	ShowDebug("RemoveChild Inside");
	if (LockLooper())
	{
		if (AComponent->FElement!=NULL)
		{
			ShowDebug("RemoveChild After NOT NULL");
			if (BView *buffer = dynamic_cast<BView *>(AComponent->FElement) )
			{			
				ShowDebug("RemoveChild F->Element After NOT NULL");
				BView::RemoveChild(buffer);
				TComponent::RemoveChild(AComponent);
			}
			else
				if (BView *buffer = dynamic_cast<BView *>(AComponent) )
				{
					ShowDebug("RemoveChild F->Element ELSE After NOT NULL");
					BView::RemoveChild(buffer);
					TComponent::RemoveChild(AComponent);
				}
			
		}
		else
		{
			if (AComponent!=NULL)
			{
				if (BView *buffer = dynamic_cast<BView *>(AComponent) )
				{
					ShowDebug("RemoveChild AComponent After NOT NULL");
					BView::RemoveChild(buffer);
					ShowDebug("RemoveChild AComponent After BView::RemoveChild");
					TComponent::RemoveChild(AComponent);
					ShowDebug("RemoveChild AComponent After TComponent::RemoveChild");
				}
				else
				{
					ShowDebug("RemoveChild AComponent CANNOT BE ADDED!");				
					UnlockLooper();
					return false;
				}		
			}
		}
		ShowDebug("RemoveChild AComponent FIN NORMALE");	
		UnlockLooper();
		return true;
	}
	return false;
}

void TViewComponent::DroppedOnView(BPoint ANewPos)
{
//	
}

bool TViewComponent::ChangeProperty(string APropertyName, string APropertyValue) 
{
	ShowDebug("ChangeProperty Inside");
//	if (FPropertyList->SetPropertyValue(APropertyName,APropertyValue))
//	{						
		ShowDebug("ChangeProperty Before LockLooper");		
		if (LockLooper())
		{
			ShowDebug(string("Propriete=") + APropertyName.c_str() + string(" Valeur=") + APropertyValue.c_str());						
			SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
			SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
			SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
			SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);	
			UnlockLooper();
			ShowDebug("ChangeProperty Quitting OK.");
			return TComponent::ChangeProperty(APropertyName,APropertyValue);
		}
//	}
	ShowDebug("ChangeProperty Quitting failed.");
	return false;
}

BMessage *TViewComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_WINDOW);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_VIEW);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}

TComponent* TViewComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TViewComponent *AViewComponent;
//	AFrame.top = 10;
//	AFrame.bottom = 100;
//	AFrame.left= 10;
//	AFrame.right = 100;
  	AViewComponent = new TViewComponent(AComponentName,AClassName,AFrame,AFatherComponent);
//  	DEBUGPRINT("AddOn TWindowComponent Instance, AName:"<< AComponentName " AClass: "<< AClassName);
  	return AViewComponent;
}





