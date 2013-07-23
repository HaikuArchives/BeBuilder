#ifndef __BUTTON_COMPONENT_H__
#define __BUTTON_COMPONENT_H__

#include <Button.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "ButtonCodeGenerator.h"
#include "ViewComponent.h"
#include <Point.h>

#define BUTTON_MENU_VALUE "Button"
#define BUTTON_VERSION_VALUE "1.0.0.0"
#define BUTTON_CLASS_VALUE "TButtonComponent"
#define BUTTON_COMPONENT_VALUE "AButtonComponent"
#define BUTTON_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define BUTTON_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define BUTTON_BITMAP_NAME "Icone" // depends on your resource file!
#define BUTTON_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!


class TButtonComponent : public BButton, public TComponentKindaView
{
	public :
		TButtonComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TButtonComponent();
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