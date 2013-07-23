#ifndef __OPENDIR_H__ 
#define __OPENDIR_H__ 
#include <FilePanel.h>
#include <alloc.h>
#include <Button.h>
#include <Handler.h>
#define B_DIR_REFS_RECEIVED 1414
class TOpenDir: public BFilePanel
{
	public:
		TOpenDir(BMessenger* target = NULL,entry_ref *panel_directory = NULL,uint32 node_flavors = 0,
				bool allow_multiple_selection = true,BMessage *message = NULL,BRefFilter *filter = NULL,
				bool modal = false,bool hide_when_done = true);
		~TOpenDir(void);
		void SelectionChanged(void);
		void SetTarget(BHandler *AnHandler);
	protected:
		BButton *FChangeDirButton;
		BMessage *FMessage;
//		uint32 OldMenuFieldMessage;
//		void MessageReceived(BMessage *message);
//		void AttachedToWindow(void);
};

#endif