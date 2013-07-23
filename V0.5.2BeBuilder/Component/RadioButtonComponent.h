#ifndef __RADIO_BUTTON_COMPONENT_H__
#define __RADIO_BUTTON_COMPONENT_H__

#include <RadioButton.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "RadioButtonCodeGenerator.h"
//#include "ViewComponent.h"
#include <Point.h>
#define RADIO_BUTTON_MENU_VALUE "RadioButton"
#define RADIO_BUTTON_VERSION_VALUE "1.0.0.0"
#define RADIO_BUTTON_CLASS_VALUE "TRadioButtonComponent"
#define RADIO_BUTTON_COMPONENT_VALUE "ARadioButtonComponent"
#define RADIO_BUTTON_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define RADIO_BUTTON_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define RADIO_BUTTON_BITMAP_NAME "Icone" // depends on your resource file!
#define RADIO_BUTTON_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TRadioButtonComponent : public BRadioButton, public TComponentKindaView
{
	public :
		TRadioButtonComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TRadioButtonComponent();
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