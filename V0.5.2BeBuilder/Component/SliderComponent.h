#ifndef __SLIDER_COMPONENT_H__
#define __SLIDER_COMPONENT_H__

#include <Slider.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "AddOn.h"
#include "SliderCodeGenerator.h"
#include <Point.h>
#define SLIDER_MENU_VALUE "Slider"
#define SLIDER_VERSION_VALUE "1.0.0.0"
#define SLIDER_CLASS_VALUE "TSliderComponent"
#define SLIDER_COMPONENT_VALUE "ASliderComponent"
#define SLIDER_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define SLIDER_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define SLIDER_BITMAP_NAME "Icone" // depends on your resource file!
#define SLIDER_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TSliderComponent : public BSlider, public TComponentKindaView
{
	public :
		TSliderComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		virtual ~TSliderComponent();
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