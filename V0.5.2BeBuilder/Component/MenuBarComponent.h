#ifndef __MENUBAR_COMPONENT_H__
#define __MENUBAR_COMPONENT_H__

#include <MenuBar.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "MenuBarCodeGenerator.h"
#include "WindowComponent.h"
//#include <Point.h>
#define MENU_BAR_MENU_VALUE "MenuBar"
#define MENU_BAR_VERSION_VALUE "1.0.0.0"
#define MENU_BAR_CLASS_VALUE "TMenuBarComponent"
#define MENU_BAR_COMPONENT_VALUE "AMenuBarComponent"
#define MENU_BAR_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define MENU_BAR_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define MENU_BAR_BITMAP_NAME "Icone" // depends on your resource file!
#define MENU_BAR_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TMenuBarComponent : public BMenuBar, public TComponentKindaView
{
	public :
		TMenuBarComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TMenuBarComponent();
		void MessageReceived(BMessage *message);
		bool AddChild(TComponent *AComponent);
		
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
};

#endif