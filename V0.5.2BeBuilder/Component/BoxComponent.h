#ifndef __BOX_COMPONENT_H__
#define __BOX_COMPONENT_H__

#include <Box.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "AddOn.h"
#include "BoxCodeGenerator.h"
#include <Point.h>
#define BOX_MENU_VALUE "Box"
#define BOX_VERSION_VALUE "1.0.0.0"
#define BOX_CLASS_VALUE "TBoxComponent"
#define BOX_COMPONENT_VALUE "ABoxComponent"
#define BOX_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define BOX_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define BOX_BITMAP_NAME "Icone" // depends on your resource file!
#define BOX_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TBoxComponent : public BBox, public TComponentKindaView
{
	public :
		TBoxComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		virtual ~TBoxComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);
		void FrameResized(float width, float height);				
		void MouseDown(BPoint point);
//		void DessineContour(bool IsFocused) { MakeFocus(IsFocused);};
//		void DroppedOnView(BPoint ANewPos);
		BRect GetChildRect(const char *AClassName);
		bool WhenAddChild(void);
		bool AddChild(TComponent *AComponent);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
		
		
};

#endif