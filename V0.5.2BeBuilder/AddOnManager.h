/*********************************************
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __TADDON_MANAGER_H__ 
#define __TADDON_MANAGER_H__ 
#include <stdio.h>
#include <Path.h>
#include <Entry.h>
#include <Application.h>
#include <Messenger.h>
#include <Message.h>
#include <List.h>
#include <Roster.h>
#include <string>
#include <Directory.h>
#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Looper.h>
#include "Object.h" 
#include "AddOn.h"
#include "GlobalVar.h"
#include "Component.h"
#include "ComponentItem.h"
#include <Rect.h>
#include <image.h>
#include "StringList.h"
#include "ToolBar.h"
#include "MenuComponent.h"
#include "MenuBarComponent.h"
#include "MenuItemComponent.h"
#include "MenuSeparatorComponent.h"
#include "MenuFieldComponent.h"
#include "BoxComponent.h"
#include "SliderComponent.h"

class TBuilderWindow; //To have a link to the main window!
class TAddOnManager : public BHandler, public TObject
//class TAddOnManager : public BHandler
{
	public:
		TAddOnManager(void);
		virtual ~TAddOnManager(void);
		bool IsModified(void);
		void SetModified(bool AValue);		
		void ShowToolBar(void);		
		void LoadAddOn(void);
		void AddLooper (BLooper *ALooper);
		bool Remove(void);
		void MessageReceived(BMessage *message);		
		void SetMenuBar(BMenuBar *AMenuBar);
		void SetBuilderWindow(TBuilderWindow *ABuilderWindow);
		bool RegisterProperties(BMessage *ABMessage);
		bool LoadStaticAddOn(void);
		bool SetGenerationPath(const char *AGenerationPath);
		
	private:
		bool FAddOnHasBeenAdded;	
		BList *FListAddOn;
		BMenuBar *FMenuBar;		
		BMenu *FMenu;
		TBuilderWindow *FBuilderWindow;
		BMenu *FindSubMenu(const char *AMenuName);
		TStringList *FListMenu;		
		TStringList *FListInstance;
		TToolBar *FToolBar;
		string FGenerationPath;
};
#endif
