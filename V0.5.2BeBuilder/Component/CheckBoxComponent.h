#ifndef __CHECKBOX_COMPONENT_H__
#define __CHECKBOX_COMPONENT_H__

#include <CheckBox.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "CheckBoxCodeGenerator.h"
//#include "ViewComponent.h"
#include <Point.h>
#define CHECK_BOX_MENU_VALUE "CheckBox"
#define CHECK_BOX_VERSION_VALUE "1.0.0.0"
#define CHECK_BOX_CLASS_VALUE "TCheckBoxComponent"
#define CHECK_BOX_COMPONENT_VALUE "ACheckBoxComponent"
#define CHECK_BOX_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define CHECK_BOX_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define CHECK_BOX_BITMAP_NAME "Icone" // depends on your resource file!
#define CHECK_BOX_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TCheckBoxComponent : public BCheckBox, public TComponentKindaView
{
	public :
		TCheckBoxComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TCheckBoxComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);
//		void DessineContour(bool IsFocused) { MakeFocus(IsFocused);};	
//		void DroppedOnView(BPoint ANewPos);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);

				
};

#endif