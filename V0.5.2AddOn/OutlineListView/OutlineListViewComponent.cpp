#include "OutlineListViewComponent.h"

TOutlineListViewComponent::TOutlineListViewComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BOutlineListView(AFrame,AComponentName),TComponentKindaView(AComponentName,AClassName,this)
{
	float largeur,hauteur;

	FParent = AFatherComponent;
	FCodeGenerator = new TOutlineListViewCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_LIST_TYPE,"B_SINGLE_SELECTION_LIST",PROP_TYPE_FLOAT,false,false,
								"B_SINGLE_SELECTION_LIST;B_MULTIPLE_SELECTION_LIST",
								PROP_GENERAL_GROUP);
	
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

	FHandler = this; // on fait pointer le FHandler interne du TCOmponent dont on a besoin dans TComponentItem.
	FElement = this;
//	Show(); 
}

TOutlineListViewComponent::~TOutlineListViewComponent()
{
	printf("Destructor de TListViewComponent Name : %s\n",FClassName.c_str());
	ShowDebug(string("Destructor de TOutlineListViewComponent Name=") + FClassName);
	delete FCodeGenerator;	
	delete FPropertyList;
}

void TOutlineListViewComponent::MessageReceived(BMessage *message)
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

void TOutlineListViewComponent::FrameMoved(BPoint screenPoint)		
{
	printf("TListViewComponent::FrameMoved....\n");
	BRect AFrame = Parent()->Bounds();
	ResizeTo(AFrame.right-AFrame.left,AFrame.bottom-AFrame.top);
}

void TOutlineListViewComponent::FrameResized(float width, float height)
{
	printf("TListViewComponent::FrameResized....\n");
	BRect AFrame = Parent()->Bounds();
	ResizeTo(AFrame.right-AFrame.left,AFrame.bottom-AFrame.top);

}


void TOutlineListViewComponent::MouseDown(BPoint point)
{
	printf("TListViewComponent::MouseDown....\n");
	FrameMoved(point);		
	Parent()->MouseDown(point);
}
bool TOutlineListViewComponent::AddChild(TComponent *AComponent)
{
	printf("TOutlineListViewComponent::AddChild\n");
	if (BStringItem *buffer = dynamic_cast<BStringItem *>(AComponent->FElement) )
	{
		printf("TOutlineListViewComponent::AddChild 1\n");
		TComponent::AddChild(AComponent);	
		if ((be_app->Lock()) && (AComponent->FHandler!=NULL))
		{
			printf("TOutlineListViewComponent::AddChild 2\n");
			be_app->AddHandler(AComponent->FHandler);
			printf("TOutlineListViewComponent::AddChild 3\n");
			be_app->Unlock();
			if (((BOutlineListView*)FElement)->Window()->Lock())
			{
				((BOutlineListView*)FElement)->AddItem(buffer);	
				((BOutlineListView*)FElement)->Window()->Unlock();
				printf("TOutlineListViewComponent::AddChild 4\n");
				return true;
			}
			else
				printf("TOutlineListViewComponent::AddChild Can't lock BOutlineListView\n");
				
		}
		else
		{
			printf("TOutlineListViewComponent::AddChild be_app can't be locked or Handler is NULL \n");
			return false;
		}
	}
	
	return false;
}

BMessage* TOutlineListViewComponent::GetProperties(void)
{
	return NULL;
}

TComponent* TOutlineListViewComponent::GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
	return NULL;
}

bool TOutlineListViewComponent::PublicChangeProperty(string APropertyName, string APropertyValue)
{
	return ChangeProperty(APropertyName,APropertyValue);
}

bool TOutlineListViewComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug(string("ChangeProperty Name=") + APropertyName + string(" Value=") + APropertyValue);
	if (LockLooper())
	{
		FPropertyList->SetPropertyValue(APropertyName,APropertyValue);												
		SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
		SetFrameProperties(APropertyName.c_str(),APropertyValue.c_str(),this);																			
		SetSizingProperties(APropertyName.c_str(),APropertyValue.c_str(),this);
		SetFlagsProperties(APropertyName.c_str(),APropertyValue.c_str(),this);		
		UnlockLooper();
		return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	}
	return false;
}