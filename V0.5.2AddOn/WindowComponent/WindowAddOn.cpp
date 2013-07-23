#include <TranslationUtils.h> 
#include <Bitmap.h>
#include "WindowComponent.h"
#include "Component.h"
#include <image.h>
#include <Rect.h>
#include <string.h>
#include "AddOn.h"
#define MENU_VALUE "New Window"
#define VERSION_VALUE "1.0.0.0"
#define CLASS_VALUE "TWindowComponent"
#define COMPONENT_VALUE "AWindowComponent"
#define COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define BITMAP_NAME "Icone" // depends on your resource file!
#define BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

//****************************************
extern "C" _EXPORT TComponent* Instance(const char *,const char *,BRect,TComponent *);
extern "C" _EXPORT void Properties(BMessage *);
//****************************************
TComponent* Instance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
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

void Properties(BMessage *AMessage)
{
	AMessage->RemoveName(MENU_NAME);
	AMessage->AddString(MENU_NAME,MENU_VALUE);
	AMessage->RemoveName(VERSION_NAME);
	AMessage->AddString(VERSION_NAME,VERSION_VALUE);
	AMessage->RemoveName(CLASS_NAME);
	AMessage->AddString(CLASS_NAME,CLASS_VALUE);
	AMessage->RemoveName(COMPONENT_NAME);
	AMessage->AddString(COMPONENT_NAME,COMPONENT_VALUE);
	AMessage->RemoveName(PARENT_COMPONENT_NAME);
	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_PROJECT);
//	AMessage->AddString(PARENT_COMPONENT_NAME,COMPONENT_ITEM_NONE); //Should be replaced only for tests...
	AMessage->RemoveName(COMPONENT_ITEM_NAME);
	AMessage->AddString(COMPONENT_ITEM_NAME,COMPONENT_ITEM_WINDOW);

	AMessage->RemoveName(COPYRIGHTS_NAME);
	AMessage->AddString(COPYRIGHTS_NAME,COPYRIGHTS_VALUE);
	AMessage->RemoveName(WRITTEN_NAME);
	AMessage->AddString(WRITTEN_NAME,WRITTEN_VALUE);

	AMessage->RemoveName(COMPONENT_GROUP_NAME);
	AMessage->AddString(COMPONENT_GROUP_NAME,GROUP_NAME_STANDARD);


	AMessage->RemoveName(ICON_NAME);
	BBitmap *icon = BTranslationUtils::GetBitmap(BITMAP_NAME);
	AMessage->AddPointer(ICON_NAME,(void *)icon);

	AMessage->RemoveName(ICON_OFF_NAME);
	BBitmap *iconOff = BTranslationUtils::GetBitmap(BITMAP_OFF_NAME);
	AMessage->AddPointer(ICON_OFF_NAME,(void *)iconOff);
}