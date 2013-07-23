#include "ScrollViewComponent.h"

TScrollViewComponent::TScrollViewComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent, TListViewComponent *AnInternalComponent):
BScrollView("ScrollView",dynamic_cast<BView *>(AnInternalComponent),B_FOLLOW_LEFT | B_FOLLOW_TOP,0,true,true,B_FANCY_BORDER),TComponentKindaView(AComponentName,AClassName,this)
{
/*
 BScrollView(const char *name, BView *target, 
         uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
         uint32 flags = 0, 
         bool horizontal = false, 
         bool vertical = false, 
         border_style border = B_FANCY_BORDER)

  BListView(BRect frame, const char *name, 
         list_view_type type = B_SINGLE_SELECTION_LIST, 
         uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flags = B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS
)
*/
	FInternalComponent = AnInternalComponent;
//	float largeur,hauteur;

	FParent = AFatherComponent;
	FCodeGenerator = new TScrollViewCodeGenerator(this,true);
	FPropertyList = AnInternalComponent->FPropertyList;

	FHandler = this; // on fait pointer le FHandler interne du TCOmponent dont on a besoin dans TComponentItem.
//	FElement = AnInternalComponent;
	FElement = this;

//	BRect AFrame = this->Frame();
//	printf("TScrollViewComponent::constructor : BRect T: %f, L: %f, R: %f, B: %f \n",AFrame.top,AFrame.left,AFrame.right,AFrame.bottom);
//	AFrame = ChildAt(0)->Frame();
//	printf("TScrollViewComponent::constructor : BRect T: %f, L: %f, R: %f, B: %f \n",AFrame.top,AFrame.left,AFrame.right,AFrame.bottom);

	
//	Show(); 
}

TScrollViewComponent::~TScrollViewComponent()
{
	printf("Destructor de TScrollViewComponent Name : %s\n",FClassName.c_str());
	delete FCodeGenerator;	
//	delete FPropertyList;
}

void TScrollViewComponent::MessageReceived(BMessage *message)
{
//	char  *name; 
//	char **data;
//	float largeur,hauteur;
//	uint32  type; 
//	int32   count;
//	int32 ResizingMode,TheFlags;
//	BRect ANewFrame;
//	string truc1,truc2; 
	BMessenger *AMes;
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				printf("TScrollViewComponent::Message Received. Message d'update recu!\n");
				AMes = new BMessenger(FInternalComponent->FHandler);
				if (AMes->IsValid())
				{
					AMes->SendMessage(message); // Send the message to the real ListView!
				}
				delete AMes;
				/*
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
//						if (strcmp(name,PROP_LABEL)==0) SetLabel(*data);
//						if (strcmp(name,PROP_MESSAGE)==0) SetLabel(*data); rien!
					}
				}
				*/
			break;
		default: BView::MessageReceived(message);
	}
}

void TScrollViewComponent::FrameMoved(BPoint screenPoint)		
{
	printf("TScrollViewComponent::FrameMoved....\n");
	Invalidate();
	BView *child; 
   	if ( child = ChildAt(0) ) 
   	{
   		child->Invalidate();
   		child->FrameResized(0,0);
		BRect AFrame = this->Frame();
		BRect AFrame2 = child->Frame();
		printf("TScrollViewComponent::FrameMoved Getting ScrollBar\n");
		BScrollBar *truc = this->ScrollBar(B_HORIZONTAL);
		AFrame2 = truc->Frame();
		FPropertyList->SetPropertyValue(PROP_BOTTOM,FloatToStr(AFrame.bottom -2 -((AFrame2.bottom - AFrame2.top))));
		truc = this->ScrollBar(B_VERTICAL);		
		AFrame2 = truc->Frame();
		FPropertyList->SetPropertyValue(PROP_RIGHT,FloatToStr(AFrame.right -2 - ((AFrame2.right-AFrame2.left))));
		FPropertyList->SetPropertyValue(PROP_TOP,FloatToStr(AFrame.top + 2));
		FPropertyList->SetPropertyValue(PROP_LEFT,FloatToStr(AFrame.left + 2));
   	}
   	BScrollView::FrameMoved(screenPoint);
//	FrameMovedComponent(FInternalComponent);
//	FInternalComponent->FrameMovedComponent(FInternalComponent);
}

void TScrollViewComponent::FrameResized(float width, float height)
{
	printf("TScrollViewComponent::FrameResized....\n");
//	FrameMovedComponent(this->Parent());
//	FrameMovedComponent(FInternalComponent);
//	BPoint truc(0,0);
//	FrameMoved(truc);	
   	BScrollView::FrameResized(width,height);
}

void TScrollViewComponent::MouseDown(BPoint point)
{
	printf("TScrollViewComponent::MouseDown X: %f Y: %f\n",point.x,point.y);

	if (Looper()->Lock())
	{
		MouseDownComponent("Component",DRAG_COMPONENT,this,point);	
		Looper()->Unlock();
	}
	//BPoint truc(0,0);
	FrameMoved(point);		
	
}
/*
void TScrollViewComponent::DroppedOnView(BPoint ANewPos)
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

BMessage* TScrollViewComponent::GetProperties(void)
{
	BMessage *AMessage = new BMessage(PROPERTY_ADDON); 
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,LIST_VIEW_MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,LIST_VIEW_VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,LIST_VIEW_CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,LIST_VIEW_COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_VIEW);
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_LIST_VIEW);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,LIST_VIEW_COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,LIST_VIEW_WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(LIST_VIEW_BITMAP_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties icon is NULL");
	AMessage->AddPointer(ICON_NAME,(void *)icon);
	//AMessage->AddData(ICON_NAME,B_ANY_TYPE,(void *)icon,icon->BitsLength());

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(LIST_VIEW_BITMAP_OFF_NAME);
	if (icon==NULL) DEBUGPRINT("GetProperties iconOff is NULL");
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
//	AMessage->AddData(ICON_OFF_NAME,B_ANY_TYPE,(void *)iconOff,iconOff->BitsLength());
	DEBUGPRINT("GetProperties End.");
	return AMessage;
}

TComponent* TScrollViewComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	TListViewComponent *AListViewComponent;
	TScrollViewComponent *AScrollViewComponent;
//	AFrame.left = 10;
//	AFrame.top = 10;
//	AFrame.right = 100;
//	AFrame.bottom = 100;
  	AListViewComponent = new TListViewComponent(AComponentName,AClassName,AFrame,AFatherComponent); 	
	AScrollViewComponent = new TScrollViewComponent(AComponentName,AClassName,AFrame,AFatherComponent,AListViewComponent);
  	return AScrollViewComponent;
}

bool TScrollViewComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	return FInternalComponent->PublicChangeProperty(APropertyName, APropertyValue);
}


