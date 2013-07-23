#ifndef __OUTLINE_LISTVIEW_COMPONENT_H__
#define __OUTLINE_LISTVIEW_COMPONENT_H__

#include <OutlineListView.h>
#include <ListItem.h>
#include <stdio.h>
#include "ComponentKindaView.h" 
#include "AddOn.h"
#include "OutlineListViewCodeGenerator.h"
#include <Point.h>
class TOutlineListViewComponent : public BOutlineListView, public TComponentKindaView
{
	public :
		TOutlineListViewComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		virtual ~TOutlineListViewComponent();
		void MessageReceived(BMessage *message);
		void FrameMoved(BPoint screenPoint);		
		void FrameResized(float width, float height);
		
		void MouseDown(BPoint point);
		bool AddChild(TComponent *AComponent);
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		bool PublicChangeProperty(string APropertyName, string APropertyValue);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
		
};

#endif