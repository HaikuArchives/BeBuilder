#ifndef __MENU_PROPERTY_EDITOR_CHOICE_H__ 
#define __MENU_PROPERTY_EDITOR_CHOICE_H__ 
#include <MenuField.h>
#include <Menu.h>
class TMenuPropertyEditorChoice: public BMenuField
{
	public: 
		TMenuPropertyEditorChoice(BRect AFrame,const char *AName);
		~TMenuPropertyEditorChoice(void);
		void AttachedToWindow(void);
		void MessageReceived(BMessage *message);
	private: 
};
#endif
