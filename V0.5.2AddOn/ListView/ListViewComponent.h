#ifndef __LISTVIEW_COMPONENT_H__
#define __LISTVIEW_COMPONENT_H__

#include <ListView.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "AddOn.h"
#include "ListViewCodeGenerator.h"
#include <Point.h>
class TListViewComponent : public BListView, public TComponentKindaView
{
	public :
		TListViewComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		virtual ~TListViewComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);		
		void FrameResized(float width, float height);
		
		void MouseDown(BPoint point);
//		void DessineContour(bool IsFocused) { MakeFocus(IsFocused);};
//		void DroppedOnView(BPoint ANewPos);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		bool PublicChangeProperty(string APropertyName, string APropertyValue);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);

};

#endif