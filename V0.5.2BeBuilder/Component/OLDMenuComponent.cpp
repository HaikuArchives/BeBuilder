#include "MenuComponent.h"
#include "MenuCodeGenerator.h"

TMenuComponent::TMenuComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent):
BMenu(AComponentName,B_ITEMS_IN_COLUMN),TComponent(AComponentName,AClassName)
// BMenu(const char *name, menu_layout layout = B_ITEMS_IN_COLUMN) 
{
//	float largeur,hauteur;
	FParent = AFatherComponent;
	FCodeGenerator = new TMenuCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName);

	FPropertyList->AddProperty(PROP_LABEL,AComponentName);
	FPropertyList->AddProperty(PROP_MENU_LAYOUT,"B_ITEMS_IN_ROW");
/*	GetPreferredSize(&largeur,&hauteur);
	ResizeTo(largeur,hauteur);
	AFrame = Frame();	
	FPropertyList->AddProperty(PROP_TOP,FloatToStr(AFrame.top));
	FPropertyList->AddProperty(PROP_LEFT,FloatToStr(AFrame.left));
	FPropertyList->AddProperty(PROP_RIGHT,FloatToStr(AFrame.right));
	FPropertyList->AddProperty(PROP_BOTTOM,FloatToStr(AFrame.bottom));
*/
}

TMenuComponent::~TMenuComponent()
{
	printf("Destructor de TMenuComponent Name : %s\n",FClassName.c_str());
	delete FCodeGenerator;	
	delete FPropertyList;
}

void TMenuComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	char **data;
	uint32  type; 
	int32   count;
	string truc1,truc2; 
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				printf("TMenuComponent::Message Received. Message d'update recu!\n");
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
//						if (strcmp(name,PROP_LABEL)==0) SetLabel(*data);

//	FPropertyList->AddProperty(PROP_LABEL,AComponentName);
						
//						SetFrameProperties(name,*data,this);																			
//						SetSizingProperties(name,*data,this);
//						SetFlagsProperties(name,*data,this);	
					}
				}
			break;
		default: BView::MessageReceived(message);
	}
}

