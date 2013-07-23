#ifndef __COMPONENT_ITEM_H__
#define __COMPONENT_ITEM_H__

#include <string>
using namespace std;
#include <Message.h>
#include <ListItem.h>
#include "GlobalVar.h"
#include "Component.h"

class TComponentItem : public BStringItem
{
	public:
		TComponentItem(const char *AName,const char *ATypeName,TComponent *AComponent,BHandler *AHandler,uint32 level = 0, bool expanded = true);
		~TComponentItem();
		const char *GetTypeName(void);
		const char *GetName(void);
		const char *GetClassName(void);
		TComponent *GetComponent(void);
		BHandler *GetHandler(void);
		void SetName(const char *AName);
	protected:
		string FName;
		string FClassName;
		string FTypeName;
		TComponent *FComponent;
		BHandler *FHandler;

};

#endif 