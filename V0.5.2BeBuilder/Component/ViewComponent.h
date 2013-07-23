#ifndef __VIEW_COMPONENT_H__
#define __VIEW_COMPONENT_H__

//#include <View.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "GlobalVar.h"
#include "ViewCodeGenerator.h"
#include "WindowComponent.h"

#define MENU_VALUE "View"
#define VERSION_VALUE "1.0.0.0"
#define CLASS_VALUE "TViewComponent"
#define COMPONENT_VALUE "AViewComponent"
#define COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define BITMAP_NAME "Icone" // depends on your resource file!
#define BITMAP_OFF_NAME "IconeOff" // depends on your resource file!


class TViewComponent : public BView, public TComponentKindaView
{
	public :
		TViewComponent(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TViewComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);		
		void FrameResized(float width, float height);
		BRect GetChildRect(const char *AClassName);
		void MouseDown(BPoint point);
		bool AddChild(TComponent *AComponent);
		bool RemoveChild(TComponent *AComponent);
		void DroppedOnView(BPoint ANewPos);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);

	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
	
				
};

#endif