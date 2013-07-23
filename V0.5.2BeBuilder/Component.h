#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <string>
//#include "ComponentList.h"
using namespace std;
#include "PropertyList.h"
#include "CodeGenerator.h"
#include "FileRW.h"
#include <View.h>
#include <Rect.h>
#include <Point.h>
#include <Handler.h>
#include <Message.h>
#include <TranslationUtils.h> 
#include <Bitmap.h>
#include <image.h>
#include <ListItem.h>

#include "AddOn.h"
#include "Object.h"
//class TComponentItem;
class TComponentList;
class TComponent : public TObject  
{
public:
	TComponent(const char *AComponentName, const char *AClassName);
	virtual ~TComponent();
	string FTypeName;
	string FComponentName;
	string FClassName;
	TComponent *FParent;
	TComponentList *FChildren;
	TPropertyList *FPropertyList;
	bool FCanGenerate;
	bool FLoaded;
	virtual bool Generate(const char *APathName);
//	void SetFrameProperties(const char *PropertyName, const char *Value, BView *ABView);
	void SetStandardProperties(const char *PropertyName, const char *Value);
//	void SetSizingProperties(const char *PropertyName, const char *Value,BView *ABView);
//	void SetFlagsProperties(const char *PropertyName, const char *Value,BView *AView);
//	void DragComponent(const char *ADragName,uint32 AMessageID,BView *AView);
//	void MouseDownComponent(const char *ADragName,uint32 AMessageID,BView *AView,BPoint point);
//	void FrameMovedComponent(BView *AView);
	virtual void DessineContour(bool IsFocused);
	virtual void DroppedOnView(BPoint ANewPos){};
	virtual bool AddChild(TComponent *AComponent);
	virtual bool AddItem(void *AnItem);
	virtual bool WhenAddChild(void);
	virtual bool RemoveChild(TComponent *AComponent);
	virtual bool WhenRemoveChild(void);
	
	virtual bool ResizeAndMove(BRect ARect) {return true;};

	virtual string *GetBodyFileName(void);
	virtual string *GetHeaderFileName(void);
	virtual BRect GetChildRect(const char *AClassName) { return BRect(5,25,100,15);}
	BMessage *SaveData();
	bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);
	bool FindPropertyName(string APropertyName, const char *AValueToFind);
	bool SetAddOnMessage(BMessage *AMessage);
	BMessage * GetAddOnMessage(void);
	bool SetComponentListWindow(BHandler *AHandler);
	BHandler *GetComponentListWindow(void);
//	bool SetComponentItem(TComponentItem *AComponentItem);	
//	TComponentItem *GetComponentItem(void);
	
	bool SetStringItem(BStringItem *AStringItem);	
	BStringItem *GetStringItem(void);
	
	bool SetIndexInList(int32 AnIndexInList);
	int32 GetIndexInList(void);		
	
//private:
	TCodeGenerator *FCodeGenerator;
	BHandler *FHandler; // AddOn when creating a componentItem we need a BHandler
//	BHandler *FElement; // The Internal Element
	BView *FElement; // The Internal Element
	BHandler *FHandlerElement;
	BMessage *FMessageAddOn; // Message that is sent to the MainWindow and that is needed to rebuild from a loading.
	TComponent *FLastChildAdded;
//	TComponentItem *FComponentItem; //This is the associated component Item to the component.
	BStringItem *FStringItem; //This is the associated component Item to the component.
	BHandler *FComponentListWindow; // For Now This handler is the handler to the BuilderWindow;
	string FPathGeneration;
	int32 FIndexInList;
	protected :
		virtual bool ChangeProperty(string APropertyName, string APropertyValue);


};

#endif 
