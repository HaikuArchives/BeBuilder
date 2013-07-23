/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "EditorMenu.h"
TEditorMenu::TEditorMenu(BRect AFrame): BMenuBar(AFrame,"EditorMenu")
{
	// Add File menu to menu bar
	
	FMenuFile = new BMenu(MENU_FILE_LABEL);
	FMenuNewItem = new BMenuItem(MENU_NEW_LABEL, new BMessage(MENU_FILE_NEW), 'N');	
	FMenuFile->AddItem(FMenuNewItem);
	FMenuFile->AddItem(FMenuOpenItem = new BMenuItem(MENU_OPEN_LABEL B_UTF8_ELLIPSIS,new BMessage(MENU_FILE_OPEN), 'O'));
	
	FMenuFile->AddItem(FMenuCloseItem = new BMenuItem(MENU_CLOSE_LABEL, new BMessage(MENU_FILE_CLOSE), 'W'));
	FMenuFile->AddSeparatorItem();
	FMenuFile->AddItem(FMenuSaveItem=new BMenuItem(MENU_SAVE_LABEL, new BMessage(MENU_FILE_SAVE), 'S'));
	FMenuFile->AddItem(FMenuSaveAsItem = new BMenuItem(MENU_SAVE_AS_LABEL B_UTF8_ELLIPSIS,new BMessage(MENU_FILE_SAVEAS)));
	FMenuFile->AddSeparatorItem();
	FMenuFile->AddItem(FMenuPageSetupItem=new BMenuItem(MENU_PAGE_SETUP_LABEL B_UTF8_ELLIPSIS,new BMessage(MENU_FILE_PAGESETUP)));
	FMenuPageSetupItem->SetEnabled(false);
	FMenuFile->AddItem(FMenuPrintItem=new BMenuItem(MENU_PRINT_LABEL B_UTF8_ELLIPSIS,new BMessage(MENU_FILE_PRINT), 'P'));
	FMenuPrintItem->SetEnabled(false);
	FMenuFile->AddSeparatorItem();
	FMenuFile->AddItem(FMenuQuitItem = new BMenuItem(MENU_QUIT_LABEL, new BMessage(MENU_FILE_QUIT), 'Q'));
	AddItem(FMenuFile);
	

	// Add the Edit menu to the menu bar

	FMenuEdit = new BMenu(MENU_EDIT_LABEL);
	FMenuEdit->AddItem(FMenuUndoItem=new BMenuItem(MENU_UNDO_LABEL, new BMessage(B_UNDO), 'Z'));
	FMenuEdit->AddSeparatorItem();
	FMenuEdit->AddItem(FMenuCutItem=new BMenuItem(MENU_CUT_LABEL, new BMessage(B_CUT), 'X'));
	FMenuEdit->AddItem(FMenuCopyItem=new BMenuItem(MENU_COPY_LABEL, new BMessage(B_COPY), 'C'));
	FMenuEdit->AddItem(FMenuPasteItem=new BMenuItem(MENU_PASTE_LABEL, new BMessage(B_PASTE), 'V'));
	FMenuEdit->AddSeparatorItem();
	FMenuEdit->AddItem(FMenuSelectAllItem=new BMenuItem(MENU_SELECT_ALL_LABEL, new BMessage(B_SELECT_ALL), 'A'));
	AddItem(FMenuEdit);

}
TEditorMenu::~TEditorMenu(void)
{
}
void TEditorMenu::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		default :
			BMenuBar::MessageReceived(message);
			break;
	}
}
void TEditorMenu::AttachedToWindow(void)
{
	if (FMenuEdit->SetTargetForItems(FTargetView)!=B_OK)
		DEBUGPRINT("TEditorMenu::AttachedToWindow Target1 failed.");
	if (FMenuFile->SetTargetForItems(FTargetTextView)!=B_OK)
		DEBUGPRINT("TEditorMenu::AttachedToWindow Target2 failed.");
	
	BMenuBar::AttachedToWindow();	
}

bool TEditorMenu::SetTargetTextView(BHandler *AHandler)
{
	FTargetTextView = AHandler;
	return true;
}
bool TEditorMenu::SetTargetView(BHandler *AHandler)
{
	FTargetView = AHandler;
	return true;
}

