#ifndef __TEXTCONTROL_COMPONENT_H__
#define __TEXTCONTROL_COMPONENT_H__

#include <TextControl.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "TextControlCodeGenerator.h"
#include "ViewComponent.h"
#include <Point.h>

#define TEXT_CONTROL_MENU_VALUE "TextControl"
#define TEXT_CONTROL_VERSION_VALUE "1.0.0.0"
#define TEXT_CONTROL_CLASS_VALUE "TTextControlComponent"
#define TEXT_CONTROL_COMPONENT_VALUE "ATextControlComponent"
#define TEXT_CONTROL_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define TEXT_CONTROL_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define TEXT_CONTROL_BITMAP_NAME "Icone" // depends on your resource file!
#define TEXT_CONTROL_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!


class TTextControlComponent : public BTextControl, public TComponentKindaView
{
	public :
		TTextControlComponent(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TTextControlComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);		
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);

		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
		
		
};

#endif