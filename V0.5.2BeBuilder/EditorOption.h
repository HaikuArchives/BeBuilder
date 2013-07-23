/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __EditorOption_H__ 
#define __EditorOption_H__ 
#include <MenuField.h>
#include <Menu.h>
#include <MenuItem.h>
#include <List.h>
#include <string>
#include <Mime.h>
#include <Message.h>
#include "GlobalVar.h"
#include "BeBuilderOption.h"
class TEditorOption: public BMenuField
{
	public:
		TEditorOption(BRect AFrame);
		~TEditorOption(void);
		bool FindAvailableEditors(void);
		void MessageReceived(BMessage *message);
		void AttachedToWindow(void);
	private:
		BList *FListMimeCode;
};
#endif
