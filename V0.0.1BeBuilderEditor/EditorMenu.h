/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __EDITOR_MENU_H__ 
#define __EDITOR_MENU_H__ 
#include <Rect.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include "GlobalVar.h"
class TEditorMenu: public BMenuBar
{
	public:
		TEditorMenu(BRect AFrame);
		~TEditorMenu(void);
		void MessageReceived(BMessage *message);
		void AttachedToWindow(void);
		bool SetTargetTextView(BHandler *AHandler);
		bool SetTargetView(BHandler *AHandler);
		
	private:
		BMenu *FMenuFile;
		BMenuItem *FMenuNewItem;
		BMenuItem *FMenuOpenItem;
		BMenuItem *FMenuCloseItem;
		BMenuItem *FMenuSaveItem;
		BMenuItem *FMenuSaveAsItem;
		BMenuItem *FMenuPageSetupItem;
		BMenuItem *FMenuPrintItem;
		BMenuItem *FMenuQuitItem;
		BMenu *FMenuEdit;
		BMenuItem *FMenuUndoItem;
		BMenuItem *FMenuCutItem;
		BMenuItem *FMenuCopyItem;
		BMenuItem *FMenuPasteItem;
		BMenuItem *FMenuSelectAllItem;		
		BHandler *FTargetTextView;
		BHandler *FTargetView;

};
#endif
