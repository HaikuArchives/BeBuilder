#ifndef __MENU_ITEM_COMPONENT_H__
#define __MENU_ITEM_COMPONENT_H__

#include <MenuItem.h>
#include <Handler.h>
#include <stdio.h>
#include "Component.h" 
#include "GlobalVar.h"
#include "MenuItemCodeGenerator.h"
#include "ViewComponent.h"
#include <Point.h>
#define MENU_ITEM_MENU_VALUE "MenuItem"
#define MENU_ITEM_VERSION_VALUE "1.0.0.0"
#define MENU_ITEM_CLASS_VALUE "TMenuItemComponent"
#define MENU_ITEM_COMPONENT_VALUE "AMenuItemComponent"
#define MENU_ITEM_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define MENU_ITEM_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define MENU_ITEM_BITMAP_NAME "Icone" // depends on your resource file!
#define MENU_ITEM_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TMenuItemComponent : public BMenuItem, public TComponent, public BHandler
{
	public :
		TMenuItemComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TMenuItemComponent();
		void MessageReceived(BMessage *message);
//		void FrameMoved(BPoint screenPoint);		
//		void MouseDown(BPoint point);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
};

#endif