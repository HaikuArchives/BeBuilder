/*********************************************
* Generated Code By BeBuilder Pre-Alpha Release V0.4                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __PROPERTY_EDITOR_MULTI_CHOICE_VIEW_H__ 
#define __PROPERTY_EDITOR_MULTI_CHOICE_VIEW_H__  
#include <ListView.h>
#include "Property.h"
#include "PropertyEditorView.h"
#include <ScrollView.h>
#include <Button.h>
#include <Button.h>
#include <TextControl.h>
#include <View.h>
const uint32 PROPERTY_EDITOR_MULTI_CHOICE_VIEW = 'MUL';
class TPropertyEditorMultiChoiceView: public TPropertyEditorView
{
	public:
		BListView *AListViewComponent12;
//		BButton *AButton11;
//		BButton *AButton10;
//		BTextControl *ATextControl9;
		TPropertyEditorMultiChoiceView(BRect AFrame);
		~TPropertyEditorMultiChoiceView(void);
		void MessageReceived(BMessage *message);
		void AttachedToWindow(void);
		void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);
		
};
#endif
