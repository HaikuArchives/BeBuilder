#ifndef __COMPONENT_KINDA_VIEW_H__
#define __COMPONENT_KINDA_VIEW_H__

#include <string>
#include <cmath>
//#include "ComponentList.h"
using namespace std;
#include "Component.h"
class TComponentKindaView : public TComponent  
{
public:
	TComponentKindaView(const char *AComponentName, const char *AClassName, BView *AView);
	virtual ~TComponentKindaView();
	virtual void SetFrameProperties(const char *PropertyName, const char *Value,BView *ABView);
	virtual void SetSizingProperties(const char *PropertyName, const char *Value,BView *ABView);
	virtual void SetFlagsProperties(const char *PropertyName, const char *Value,BView *AView);
	virtual void DragComponent(const char *ADragName,uint32 AMessageID,BView *AView);
	virtual void MouseDownComponent(const char *ADragName,uint32 AMessageID,BView *AView,BPoint point);
	virtual void FrameMovedComponent(BView *AView);
//	virtual void OnMessageReceived(BMessage *AMessage);
	void DessineContour(bool IsFocused);
	void DroppedOnView(BPoint ANewPos);
	bool AddChild(TComponent *AComponent);
	bool RemoveChild(TComponent *AComponent);	
	bool ResizeAndMove(BRect ARect); 
protected:
	BView *FView;
};

#endif 
