#include "ComponentKindaView.h"
// We dont want to inherit TComponentKindaView from TComponent AND BView... 
TComponentKindaView::TComponentKindaView(const char *AComponentName, const char *AClassName, BView *AView):TComponent(AComponentName,AClassName)
{
	FDebugMode = 1;
	FDebugMessage= "TComponentKindaView ";
	FDebugMessage= FDebugMessage + AComponentName;		
	ShowDebug("ctor");
	FView = NULL;
	FView = AView;
}

TComponentKindaView::~TComponentKindaView()
{
	ShowDebug(" destructor");		
}


void TComponentKindaView::SetFrameProperties(const char *PropertyName, const char *Value,BView *ABView)
{
	bool PropertyAsked = false;
//	ShowDebug("SetFrameProperties Inside.");
	if (FView !=NULL)
	{
//		BRect ANewFrame = ABView->Frame();
		BRect ANewFrame = FView->Frame();
		if (strcmp(PropertyName,PROP_TOP)==0) 
		{	
			ANewFrame.top = StrToDouble(Value);
			PropertyAsked = true;
//			ChangeProperty(PROP_TOP,string(Value));			
		}
		if (strcmp(PropertyName,PROP_LEFT)==0) 
		{
			ANewFrame.left = StrToDouble(Value);
			PropertyAsked = true;			
//			ChangeProperty(PROP_LEFT,string(Value));
		}
		if (strcmp(PropertyName,PROP_RIGHT)==0) 
		{
			ANewFrame.right = StrToDouble(Value);
			PropertyAsked = true;			
//			ChangeProperty(PROP_RIGHT,string(Value));
		}
		if (strcmp(PropertyName,PROP_BOTTOM)==0) 
		{
			ANewFrame.bottom = StrToDouble(Value);
			PropertyAsked = true;			
//			ChangeProperty(PROP_BOTTOM,string(Value));
		}	
		if (PropertyAsked)
		{
			float Left = StrToDouble(FPropertyList->GetPropertyValue(PROP_LEFT).c_str());
			float Top = StrToDouble(FPropertyList->GetPropertyValue(PROP_TOP).c_str());
			float Right = StrToDouble(FPropertyList->GetPropertyValue(PROP_RIGHT).c_str());
			float Bottom = StrToDouble(FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str());
							
			float DiffLeftLeft = abs(ANewFrame.left-Left);
			float DiffTopTop = abs(ANewFrame.top - Top);
	//		ShowDebug(string("DiffLeftLeft=") + FloatToStr(DiffLeftLeft));
	//		ShowDebug(string("DiffTopTop=") + FloatToStr(DiffTopTop));
			
			float DiffRightLeft = abs((ANewFrame.right - ANewFrame.left)-(Right - Left));
			float DiffBottomTop = abs((ANewFrame.bottom - ANewFrame.top) - (Bottom - Top));
	//		ShowDebug(string("DiffRightLeft=") + FloatToStr(DiffRightLeft));
	//		ShowDebug(string("DiffBottomTop=") + FloatToStr(DiffBottomTop));
			if ( (DiffLeftLeft>=1) || (DiffTopTop>=1) || (DiffRightLeft>=1) || (DiffBottomTop>=1))
			{			
				ResizeAndMove(ANewFrame);
			}
		}
	}
//	ShowDebug("SetFrameProperties Quitting.");
}

void TComponentKindaView::SetSizingProperties(const char *PropertyName, const char *Value,BView *ABView)
{
	long res;
	int32 ResizingMode;
	string truc1;
	if (strcmp(PropertyName,PROP_RESIZING_MODE)==0)
	{
		ResizingMode = 0;
		truc1 = Value;
		res = truc1.find("B_FOLLOW_LEFT");
		if (res > 0) ResizingMode |= B_FOLLOW_LEFT;
		res = truc1.find("B_FOLLOW_TOP");
		if (res>0) ResizingMode |= B_FOLLOW_TOP;
		res = truc1.find("B_FOLLOW_RIGHT");	
		if (res>0) ResizingMode |= B_FOLLOW_RIGHT;
		res = truc1.find("B_FOLLOW_LEFT_RIGHT");
		if (res>0) ResizingMode |= B_FOLLOW_LEFT_RIGHT;
		res = truc1.find("B_FOLLOW_H_CENTER");
		if (res>0) ResizingMode |= B_FOLLOW_H_CENTER;
		res = truc1.find("B_FOLLOW_TOP");
		if (res>0) ResizingMode |= B_FOLLOW_TOP;
		res = truc1.find("B_FOLLOW_BOTTOM");
		if (res>0) ResizingMode |= B_FOLLOW_BOTTOM;
		res = truc1.find("B_FOLLOW_TOP_BOTTOM");
		if (res>0) ResizingMode |= B_FOLLOW_TOP_BOTTOM;
		res = truc1.find("B_FOLLOW_V_CENTER");
		if (res>0) ResizingMode |= B_FOLLOW_V_CENTER;													

		ABView->SetResizingMode(ResizingMode);
		ShowDebug("SetSizingProperties In a distant past we devalidate the call to ChangeProperty...");
//		ChangeProperty(PROP_RESIZING_MODE,truc1);
		
	}
}

void TComponentKindaView::SetFlagsProperties(const char *PropertyName, const char *Value,BView *AView)	
{
	long res;
	int32 TheFlags;
	string truc1;
	if (strcmp(PropertyName,PROP_FLAGS)==0)
	{
		TheFlags = 0;
		truc1 = Value;
		res = truc1.find("B_WILL_DRAW");
		if (res>0) TheFlags |= B_WILL_DRAW;	
		res = truc1.find("B_NAVIGABLE");
		if (res>0) TheFlags |= B_WILL_DRAW;	
		AView->SetFlags(TheFlags);
		ShowDebug("SetFlagsProperties In a distant past we devalidate the call to ChangeProperty...");
//		ChangeProperty(PROP_FLAGS,truc1);
	}
}

void TComponentKindaView::DragComponent(const char *ADragName,uint32 AMessageID,BView *AView)
{
	BPoint w2;
	uint32 mods;
	printf("Inside TComponentKindaView::CreateDragMessage\n");	
	bool GO=false;
	if (BWindow *buffer = dynamic_cast<BWindow *>(AView->Parent()))
	{
		if (buffer!= AView->Window())
		{
			GO = true;		
		}
	}
	else
	{
		GO = true;
	}
	if ((GO) && (AView->LockLooper()))
	{
		AView->GetMouse(&w2, &mods);
		if ((mods)) // Le bouton n'a pas ete relache! et deplacement commence!
		{
			printf("Inside TComponent::CreateDragMessage Before Message Drag! \n");	
			BMessage msg(AMessageID);
//			msg.AddPointer(ADragName,AView);
			msg.AddPointer(ADragName,this);
//			msg.AddRect("Contour",AView->Bounds());
			AView->DragMessage(&msg, AView->Bounds());
			printf("Inside TComponent::CreateDragMessage After Message Drag! \n");	
		}
		AView->UnlockLooper();
	}
}

void TComponentKindaView::MouseDownComponent(const char *ADragName,uint32 AMessageID,BView *AView,BPoint point)
{
    uint32 buttons = 0; 
	BRect ARect = AView->Bounds();
//	BRect ARect = AView->Frame();
	float maxX = 10;
	float maxY = 10;
	AView->MakeFocus(true);
	ShowDebug("Before DessineContour(true);");
	TComponentKindaView::DessineContour(true);
	ShowDebug("After DessineContour(true);");
	//printf("TComponent::MouseDownComponent : BRect R: %f, B: %f \n",ARect.right,ARect.bottom);
	//printf("TComponent::MouseDownComponent : BPoint %f, %f \n",point.x,point.y);
	//printf("TComponent::MouseDownComponent : %f, %f \n",(ARect.right-point.x),(ARect.bottom-point.y));
	if (((ARect.right-point.x) < maxX) && (point.x < ARect.right) &&
		((ARect.bottom-point.y) < maxY) && (point.y < ARect.bottom) )
	{
       AView->GetMouse(&point, &buttons, true); 
       while ( buttons ) { 
           snooze(20 * 1000); 
           AView->GetMouse(&point, &buttons, true); 
			AView->ResizeTo((point.x-ARect.left),(point.y - ARect.top));
			AView->Invalidate();
			FrameMovedComponent(AView);
       } 
	}
	else
		DragComponent(ADragName,AMessageID,AView);	
}


void TComponentKindaView::FrameMovedComponent(BView *AView)
{
//	printf("TComponent::FrameMovedComponent for : %s\n",FComponentName.c_str());
	BRect AFrame = AView->Frame();
	AView->Draw(AFrame);		
	AView->Draw(AView->Bounds());		

	if (FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top))) ChangeProperty(PROP_TOP,FloatToStr(AFrame.top));
	if (FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left))) ChangeProperty(PROP_LEFT,FloatToStr(AFrame.left));
	if (FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right))) ChangeProperty(PROP_RIGHT,FloatToStr(AFrame.right)); 
	if (FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom))) ChangeProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));	
	
//	ShowDebug(string("FrameMovedComponent TOP=")+FloatToStr(AFrame.top));
//	ShowDebug(string("FrameMovedComponent LEFT=")+FloatToStr(AFrame.left));
//	ShowDebug(string("FrameMovedComponent RIGHT=")+FloatToStr(AFrame.right));
//	ShowDebug(string("FrameMovedComponent BOTTOM=")+FloatToStr(AFrame.bottom));
}
/*
void TComponentKindaView::OnMessageReceived(BMessage *AMessage)
{
	char  *name; 
	const char *data;
	uint32  type; 
	int32   count;
//	string truc1,truc2; 
	switch(AMessage->what)
	{
		case MSG_PROPERTY_UPDATE :
				for (int32 i = 0; 
				AMessage->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
					if (AMessage->FindString(name,&data)==B_OK)				         	
					{
					//	truc1 = name;
					//	truc2 = data;
					//	ChangeProperty(truc1,truc2);
						ChangeProperty(string(name),string(data));
					}
				}
			break;
		default: FView->MessageReceived(AMessage);
	}
}
*/

void TComponentKindaView::DessineContour(bool IsFocused)
{
	ShowDebug("DessineContour Inside.");
	TComponent::DessineContour(IsFocused);
	if (FView!=NULL)
	{
		if (FView->LockLooper())
		{
			FView->MakeFocus(IsFocused);
		}
	}
	ShowDebug("DessineContour Quitting.");
}

void TComponentKindaView::DroppedOnView(BPoint ANewPos)
{
	ShowDebug(string("Dropped On View inside. ANewPos.x=") +FloatToStr(ANewPos.x) + string(" ANewPos.y=") + FloatToStr(ANewPos.y));
	if (FView!=NULL)
	{
		if (FView->LockLooper())
		{
			FView->MoveTo(ANewPos.x,ANewPos.y);
			//FrameMoved(ANewPos);						
			FrameMovedComponent(FView);
			FView->UnlockLooper();
		}
	}	
}

bool TComponentKindaView::AddChild(TComponent *AComponent)
{
	printf("TComponentKindaView::AddChild inside");
	return true;
}

bool TComponentKindaView::RemoveChild(TComponent *AComponent)
{
	ShowDebug("RemoveChild");
	if (FView!=NULL)
	{
		if (FView->LockLooper())
		{
			TComponent::RemoveChild(AComponent);
			FView->UnlockLooper();
		}
	}
	ShowDebug("RemoveChild Quitting");
	return true;
}



bool TComponentKindaView::ResizeAndMove(BRect ARect) 
{
//	ShowDebug("ResizeAndMove inside.");
	if (FView==NULL)
	{
//		ShowDebug("ResizeAndMove Quitting failed. FView is null.");
		return false;
	}
	if (FView->LockLooper())
	{
		BRect AFrame = FView->Frame();
//		FView->Draw(AFrame);
//		ShowDebug("ResizeAndMove Before AFrame.PrintToStream...");
//		AFrame.PrintToStream();
//		ShowDebug("ResizeAndMove Before ARect.PrintToStream...");
//		ARect.PrintToStream();

//		float DiffLeftLeft = abs(AFrame.left-ARect.left);
//		float DiffTopTop = abs(AFrame.top - ARect.top);
//		ShowDebug(string("DiffLeftLeft=") + FloatToStr(DiffLeftLeft));
//		ShowDebug(string("DiffTopTop=") + FloatToStr(DiffTopTop));
		
//		float DiffRightLeft = abs((AFrame.right - AFrame.left)-(ARect.right - ARect.left));
//		float DiffBottomTop = abs((AFrame.bottom - AFrame.top) - (ARect.bottom - ARect.top));
//		ShowDebug(string("DiffRightLeft=") + FloatToStr(DiffRightLeft));
//		ShowDebug(string("DiffBottomTop=") + FloatToStr(DiffBottomTop));
		
/*		if ((abs(AFrame.left-ARect.left)>=1) || (abs(AFrame.top - ARect.top)>1))
			FView->MoveTo(ARect.left,ARect.top);
		if ((abs((AFrame.right - AFrame.left)-(ARect.right - ARect.left))>1) || (abs((AFrame.bottom - AFrame.top) - (ARect.bottom - ARect.top))>1))
			FView->ResizeTo(ARect.right-ARect.left,ARect.bottom-ARect.top);
*/
//		if ((DiffLeftLeft>1) || (DiffTopTop > 1))
//		{
			ShowDebug("ResizeAndmove Modification Done in Moving");
			FView->MoveTo(ARect.left,ARect.top);
//		}
//		if ((DiffRightLeft>1) || (DiffBottomTop>1))
//		{
			ShowDebug("ResizeAndmove Modification Done in Sizing");
			FView->ResizeTo(ARect.right-ARect.left,ARect.bottom-ARect.top);
//		}
		FView->Invalidate(FView->Frame());
		FView->Draw(FView->Frame());
		FView->UnlockLooper();
		ShowDebug("ResizeAndMove Quitting OK.");
		return true;
	}
	ShowDebug("ResizeAndMove Quitting failed.");
	return false;
}

