#ifndef __MENUFIELD_COMPONENT_H__
#define __MENUFIELD_COMPONENT_H__

#include <MenuField.h>
#include <Menu.h>
#include <MenuItem.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "MenuFieldCodeGenerator.h"
#include "ComponentList.h"

#define MENU_FIELD_MENU_VALUE "MenuField"
#define MENU_FIELD_VERSION_VALUE "1.0.0.0"
#define MENU_FIELD_CLASS_VALUE "TMenuFieldComponent"
#define MENU_FIELD_COMPONENT_VALUE "AMenuFieldComponent"
#define MENU_FIELD_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define MENU_FIELD_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define MENU_FIELD_BITMAP_NAME "Icone" // depends on your resource file!
#define MENU_FIELD_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TMenuFieldComponent : public BMenuField, public TComponentKindaView
{
	public :
		TMenuFieldComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TMenuFieldComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);
		void FrameResized(float width, float height);				
		void MouseDown(BPoint point);
//		void DessineContour(bool IsFocused) { MakeFocus(IsFocused);};
//		void DroppedOnView(BPoint ANewPos);
		bool AddChild(TComponent *AComponent);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
				
};

#endif