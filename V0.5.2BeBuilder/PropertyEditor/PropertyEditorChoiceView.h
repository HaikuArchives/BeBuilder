#ifndef __PROPERTY_EDITOR_CHOICE_VIEW_H__ 
#define __PROPERTY_EDITOR_CHOICE_VIEW_H__ 
#include <MenuField.h>
#include <MenuItem.h>
#include <Button.h>
#include <Button.h>
#include <TextControl.h>
#include <View.h>
#include <string>
#include "StringList.h"
#include "PropertyEditorView.h"
class TProperty;
const uint32 PROPERTY_EDITOR_CHOICE_VIEW = 'PECV';

//class TPropertyEditorChoiceView: public BView
class TPropertyEditorChoiceView: public TPropertyEditorView
{
	public:
		BMenuField *FAMenuFieldComponent18;
//		BButton *AButton17;
//		BButton *AButton16;
//		BTextControl *ATextControl15;
		TPropertyEditorChoiceView(BRect AFrame);
		~TPropertyEditorChoiceView(void);
		void MessageReceived(BMessage *message);
		void AttachedToWindow(void);
		void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);
	private:
//		int32 FIndex;
	//	BHandler *FHandler;		
//		string FOldValue;
//		TStringList *Split(string AString, string ASplitter);
		void RemoveAddMenuField(string AName);
};
#endif
