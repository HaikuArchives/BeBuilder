#ifndef __SCROLL_VIEW_COMPONENT_H__
#define __SCROLL_VIEW_COMPONENT_H__

#include <ScrollView.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "AddOn.h"
#include "ScrollViewCodeGenerator.h"
#include "ListViewComponent.h"
#include <Point.h>

#define LIST_VIEW_MENU_VALUE "ListView"
#define LIST_VIEW_VERSION_VALUE "1.0.0.0"
#define LIST_VIEW_CLASS_VALUE "TListViewComponent"
#define LIST_VIEW_COMPONENT_VALUE "AListViewComponent"
#define LIST_VIEW_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define LIST_VIEW_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define LIST_VIEW_BITMAP_NAME "Icone" // depends on your resource file!
#define LIST_VIEW_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!

class TScrollViewComponent : public BScrollView, public TComponentKindaView
{
	public :
		TScrollViewComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent, TListViewComponent *AnInternalComponent);
		virtual ~TScrollViewComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);		
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);
//		void DessineContour(bool IsFocused) { MakeFocus(IsFocused);};
//		void DroppedOnView(BPoint ANewPos);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		TListViewComponent *FInternalComponent;
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
		
};
#endif