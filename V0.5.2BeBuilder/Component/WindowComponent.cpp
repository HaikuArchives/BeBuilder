#include "WindowComponent.h"

TWindowComponent::TWindowComponent(const char *AComponentName, const char *AClassName,BRect AFrame,TComponent *AFatherComponent) 
//TWindowComponent::TWindowComponent(const char *AComponentName,const char *AClassName,const char *ATitle, BRect AFrame)
:BWindow(AFrame,AComponentName,B_TITLED_WINDOW,0),TComponent(AComponentName,AClassName)
{
	FDebugMode=1;
	FDebugMessage= "TWindowComponent ";
	FDebugMessage= FDebugMessage + AComponentName ;
	FDebugMessage +=  " ";		
	FCanGenerate = true;
	ShowDebug("Constructeur!");
	FHandler = this;
	
	FCodeGenerator = new TWindowCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_TITLE,Title(),PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom),PROP_TYPE_FLOAT,false,true,"",PROP_POSITION_GROUP);

	FPropertyList->AddProperty(PROP_WINDOWTYPE,"B_TITLED_WINDOW",PROP_TYPE_FLOAT,false,false,"B_UNTYPED_WINDOW;B_MODAL_WINDOW;B_BORDERED_WINDOW;B_TITLED_WINDOW;B_DOCUMENT_WINDOW;B_FLOATING_WINDOW",PROP_POSITION_GROUP);
	FPropertyList->AddProperty(PROP_FLAGS,"0",PROP_TYPE_FLOAT,true,false,
								"B_NOT_MOVABLE;B_NOT_H_RESIZABLE;B_NOT_V_RESIZABLE;B_NOT_RESIZABLE;B_NOT_CLOSABLE;B_NOT_ZOOMABLE;B_NOT_MINIMIZABLE;B_AVOID_FRONT;B_AVOID_FOCUS;B_WILL_ACCEPT_FIRST_CLICK;B_OUTLINE_RESIZE;B_NO_WORKSPACE_ACTIVATION;B_NOT_ANCHORED_ON_ACTIVATE",
								PROP_POSITION_GROUP);
	Show(); //ShowWindow
}

TWindowComponent::~TWindowComponent()
{
	ShowDebug("destructor inside.");	
	delete FCodeGenerator;
	ShowDebug("destructor quitting.");
}

void TWindowComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char *data;
//	data=(char *)malloc(FIND_STRING_SIZE*sizeof(char));
	uint32  type; 
	int32   count;
//	window_type TypeWindow = 0;
//	uint32 FlagWindow = 0;
	string truc1,truc2; 
//	long res;

//	BRect ANewFrame;
//	ShowDebug("MessageReceived Inside.");
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (message->FindString(name,&data)==B_OK)				         	
					{
						truc1 = name;
//						truc2 = *data;
						truc2 = data;
						ShowDebug("MessageReceived Before ChangeProperty");
						ChangeProperty(truc1,truc2);
						ShowDebug("MessageREceived After ChangeProperty");
					}
				}
			break;
		default: BWindow::MessageReceived(message);
	}
}
/*
void TWindowComponent::FrameMoved(BPoint screenPoint)		
{
	FrameMovedComponent(this);
}

void TWindowComponent::FrameResized(float width, float height)
{
	FrameMovedComponent(this);
}
*/
/*
void TButtonComponent::MouseDown(BPoint point)
{
	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);
		Looper()->Unlock();
	}
}

void TButtonComponent::DroppedOnView(BPoint ANewPos)
{
	float largeur,hauteur;	
	if (Window()->Lock())
	{
		MoveTo(ANewPos.x,ANewPos.y);
		FrameMoved(ANewPos);						
		Window()->Unlock();
	}	
}
*/

void TWindowComponent::WindowActivated(bool active)		
{
	ShowDebug("WindowActivated.");
	BRect AFrame = Frame();
//	AFrame.PrintToStream();
	if (FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top))) ChangeProperty(PROP_TOP,FloatToStr(AFrame.top));
	if (FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left))) ChangeProperty(PROP_LEFT,FloatToStr(AFrame.left));
	if (FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right))) ChangeProperty(PROP_RIGHT,FloatToStr(AFrame.right)); 
	if (FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom))) ChangeProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));	
	
	TComponent *AComponent = FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
//		AComponent->ResizeAndMove(Bounds());
		if (TViewComponent *buffer = dynamic_cast<TViewComponent *>(AComponent) )
		{
			buffer->FrameResized(10,10);
//			ShowDebug("AddChild Window!");
//			BWindow::AddChild(buffer);
//			TComponent::AddChild(AComponent);
//			ShowDebug("AddChild Window! Quitting");
		}
		else
		{
			printf("TWindowComponent::WindowActivated Dynamic_cast fucked!\n");
			return false;
		}
//		ShowDebug("AddChild Quitting.");

		AComponent = FChildren->NextComponent(false);		
	}
}

void TWindowComponent::FrameMoved(BPoint screenPoint)		
{
/* 	uint32 buttons = 0; 
    GetMouse(&point, &buttons, true); 
    while ( buttons ) 
    { 

    } 
*/
/*
	ShowDebug("FrameMoved.");
   // snooze(300 * 1000); 	
	BRect AFrame = Frame();
//	AFrame.PrintToStream();
	if (FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top))) ChangeProperty(PROP_TOP,FloatToStr(AFrame.top));
	if (FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left))) ChangeProperty(PROP_LEFT,FloatToStr(AFrame.left));
	if (FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right))) ChangeProperty(PROP_RIGHT,FloatToStr(AFrame.right)); 
	if (FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom))) ChangeProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));	
*/
}

void TWindowComponent::FrameResized(float width, float height)
{
/*
	BRect AFrame = Frame();
	if (FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top))) ChangeProperty(PROP_TOP,FloatToStr(AFrame.top));
	if (FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left))) ChangeProperty(PROP_LEFT,FloatToStr(AFrame.left));
	if (FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right))) ChangeProperty(PROP_RIGHT,FloatToStr(AFrame.right)); 
	if (FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom))) ChangeProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));	
*/
//	FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top));
//	FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left));
//	FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right));
//	FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom));	
}

BRect TWindowComponent::GetChildRect(const char *AClassName)
{
	string truc = AClassName;
	if (IsFoundInside(truc,"View"))
	{
		return Bounds();
	}	
	else
		return TComponent::GetChildRect(AClassName);
}

bool TWindowComponent::AddChild(TComponent *AComponent)	
{
	ShowDebug("AddChild Inside.");
	if (TViewComponent *buffer = dynamic_cast<TViewComponent *>(AComponent) )
	{
		ShowDebug("AddChild Window!");
		BWindow::AddChild(buffer);
		TComponent::AddChild(AComponent);
		ShowDebug("AddChild Window! Quitting");
	}
	else
	{
		printf("TWindowComponent::AddChild Dynamic_cast fucked!\n");
		return false;
	}
	ShowDebug("AddChild Quitting.");
	return true;		
}

bool TWindowComponent::RemoveChild(TComponent *AComponent)	
{
	ShowDebug("RemoveChild Inside.");
	if (TViewComponent *buffer = dynamic_cast<TViewComponent *>(AComponent) )
	{
		ShowDebug("RemoveChild Window!");
		BWindow::RemoveChild(buffer);
		TComponent::RemoveChild(AComponent);
		ShowDebug("RemoveChild Window! Quitting");
	}
	else
	{
		printf("TWindowComponent::RemoveChild Dynamic_cast fucked!\n");
		return false;
	}
	ShowDebug("RemoveChild Quitting.");
	return true;		
}

bool TWindowComponent::WhenRemoveChild(void)
{
	ShowDebug("WhenAddChild");
	BMessenger AMessenger(this);
	BMessage AMessage(B_QUIT_REQUESTED);
	AMessenger.SendMessage(&AMessage);	
	return true;
}



bool TWindowComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
//	ShowDebug(string("ChangeProperty Inside. NAME=") + APropertyName + string(" value=") + APropertyValue);
	window_type TypeWindow = 0;
	uint32 FlagWindow = 0;
	if (FDebugMode==1)
	{
		if (FindPropertyName(APropertyName,PROP_NAME))
		{
			FDebugMessage= "TWindowComponent ";
			FDebugMessage= FDebugMessage + APropertyValue ;
			FDebugMessage +=  " ";		
		}
	}

	FPropertyList->SetPropertyValue(APropertyName,APropertyValue);						

	if (FindPropertyName(APropertyName,PROP_TITLE))
	{
//		ShowDebug("ChangeProperty Before SetTitle");			
		SetTitle(APropertyValue.c_str());
	}
	
	SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
	
	BRect ANewFrame = Frame();
	if (FindPropertyName(APropertyName,PROP_TOP)) ANewFrame.top = StrToDouble(APropertyValue.c_str());	
	if (FindPropertyName(APropertyName,PROP_LEFT)) ANewFrame.left = StrToDouble(APropertyValue.c_str());	
	if (FindPropertyName(APropertyName,PROP_RIGHT)) ANewFrame.right = StrToDouble(APropertyValue.c_str());	
	if (FindPropertyName(APropertyName,PROP_BOTTOM)) ANewFrame.bottom = StrToDouble(APropertyValue.c_str());	
	ResizeAndMove(ANewFrame);
//	MoveTo(ANewFrame.left,ANewFrame.top);
//	ResizeTo(ANewFrame.right-ANewFrame.left,ANewFrame.bottom-ANewFrame.top);																		

	if (FindPropertyName(APropertyName,PROP_WINDOWTYPE))
	{
		if (FindPropertyName(APropertyValue,"B_UNTYPED_WINDOW")) TypeWindow = B_UNTYPED_WINDOW;
		if (FindPropertyName(APropertyValue,"B_MODAL_WINDOW")) TypeWindow = B_MODAL_WINDOW;
		if (FindPropertyName(APropertyValue,"B_BORDERED_WINDOW")) TypeWindow = B_BORDERED_WINDOW;
		if (FindPropertyName(APropertyValue,"B_TITLED_WINDOW")) TypeWindow = B_TITLED_WINDOW;
		if (FindPropertyName(APropertyValue,"B_DOCUMENT_WINDOW")) TypeWindow = B_DOCUMENT_WINDOW;
		if (FindPropertyName(APropertyValue,"B_FLOATING_WINDOW")) TypeWindow = B_FLOATING_WINDOW;
		SetType(TypeWindow);
	}

	if (FindPropertyName(APropertyName,PROP_FLAGS))
	{//
		if (FindPropertyName(APropertyValue,"0")) FlagWindow = 0;
		if (FindPropertyName(APropertyValue,"B_NOT_MOVABLE")) FlagWindow |= B_NOT_MOVABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_H_RESIZABLE")) FlagWindow |= B_NOT_H_RESIZABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_V_RESIZABLE")) FlagWindow |= B_NOT_V_RESIZABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_RESIZABLE")) FlagWindow |= B_NOT_RESIZABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_CLOSABLE")) FlagWindow |= B_NOT_CLOSABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_ZOOMABLE")) FlagWindow |= B_NOT_ZOOMABLE;
		if (FindPropertyName(APropertyValue,"B_NOT_MINIMIZABLE")) FlagWindow |= B_NOT_MINIMIZABLE;
		if (FindPropertyName(APropertyValue,"B_AVOID_FRONT")) FlagWindow |= B_AVOID_FRONT;
		if (FindPropertyName(APropertyValue,"B_AVOID_FOCUS")) FlagWindow |= B_AVOID_FOCUS;
		if (FindPropertyName(APropertyValue,"B_WILL_ACCEPT_FIRST_CLICK")) FlagWindow |= B_WILL_ACCEPT_FIRST_CLICK;
		if (FindPropertyName(APropertyValue,"B_OUTLINE_RESIZE")) FlagWindow |= B_OUTLINE_RESIZE;
		if (FindPropertyName(APropertyValue,"B_NO_WORKSPACE_ACTIVATION")) FlagWindow |= B_NO_WORKSPACE_ACTIVATION;
		if (FindPropertyName(APropertyValue,"B_NOT_ANCHORED_ON_ACTIVATE")) FlagWindow |= B_NOT_ANCHORED_ON_ACTIVATE;		
	}
	return TComponent::ChangeProperty(APropertyName,APropertyValue);
}

BMessage *TWindowComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,WINDOW_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,WINDOW_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,WINDOW_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,WINDOW_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_PROJECT);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_WINDOW);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,WINDOW_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,WINDOW_WRITTEN_VALUE);

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

TComponent* TWindowComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TWindowComponent *AWindowComponent;
	AFrame.top = 100;
	AFrame.bottom = 250;
	AFrame.left= 100;
	AFrame.right = 200;
  	AWindowComponent = new TWindowComponent(AComponentName,AClassName,AFrame,AFatherComponent);
//  	DEBUGPRINT("AddOn TWindowComponent Instance, AName:"<< AComponentName " AClass: "<< AClassName);
  	return AWindowComponent;
}

bool TWindowComponent::ResizeAndMove(BRect ARect) 
{
	MoveTo(ARect.left,ARect.top);
	ResizeTo(ARect.right-ARect.left,ARect.bottom-ARect.top);
	return true;
}


