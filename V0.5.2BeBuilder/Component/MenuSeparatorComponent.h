#ifndef __MENU_SEPARATOR_COMPONENT_H__
#define __MENU_SEPARATOR_COMPONENT_H__

#include <Handler.h>
#include <stdio.h>
#include "Component.h" 
#include "GlobalVar.h"
#include "MenuSeparatorCodeGenerator.h"

#define MENU_SEPARATOR_MENU_VALUE "MenuSeparator"
#define MENU_SEPARATOR_VERSION_VALUE "1.0.0.0"
#define MENU_SEPARATOR_CLASS_VALUE "TMenuSeparatorComponent"
#define MENU_SEPARATOR_COMPONENT_VALUE "AMenuSeparatorComponent"
#define MENU_SEPARATOR_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define MENU_SEPARATOR_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define MENU_SEPARATOR_BITMAP_NAME "Icone" // depends on your resource file!
#define MENU_SEPARATOR_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TMenuSeparatorComponent : public TComponent, public BHandler
{
	public :
		TMenuSeparatorComponent(const char *AComponentName, const char *AClassName, TComponent *AFatherComponent);
		~TMenuSeparatorComponent();
		void MessageReceived(BMessage *message);

		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
};

#endif