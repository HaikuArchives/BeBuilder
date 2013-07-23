#ifndef __MENU_COMPONENT_H__
#define __MENU_COMPONENT_H__

#include <Menu.h>
#include <stdio.h>
#include "Component.h" 
#include "GlobalVar.h"
#include "MenuCodeGenerator.h"
#include "ViewComponent.h"
#include <MenuItem.h>
#include <Point.h>

#define MENU_MENU_VALUE "Menu"
#define MENU_VERSION_VALUE "1.0.0.0"
#define MENU_CLASS_VALUE "TMenuComponent"
#define MENU_COMPONENT_VALUE "AMenuComponent"
#define MENU_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define MENU_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define MENU_BITMAP_NAME "Icone" // depends on your resource file!
#define MENU_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

//------------- CAS TRES SPECIAL du BMENU ----------------
class TMenuComponent : public BHandler, public TComponent
{
	public :
		TMenuComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TMenuComponent();
		void MessageReceived(BMessage *message);
		bool AddChild(TComponent *AComponent);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		BMenu *FMenu;
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);	
};

#endif