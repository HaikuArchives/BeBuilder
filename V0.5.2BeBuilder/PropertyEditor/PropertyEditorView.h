#ifndef __PROPERTY_EDITOR_VIEW_H__
#define __PROPERTY_EDITOR_VIEW_H__
#include <View.h>
#include <Message.h>
#include <Messenger.h>
#include <Button.h>
#include <TextControl.h>
#include "GlobalVar.h"
#include "Global.h"
#include "Couleur.h"
#include "StringList.h"
#include "GlobalVar.h"
#include <string>
const uint32 BUTTON_VALIDATE = 'BVAL';
const uint32 BUTTON_CANCEL = 'BCAN';
class TProperty;
class TPropertyEditorView : public BView
{
	public :
		TPropertyEditorView(BRect frame);
		virtual ~TPropertyEditorView();
		virtual void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);
		void MessageReceived(BMessage *message);
//	protected :
		BTextControl *FTextEdit;
//	private :	
		BButton *FButValidate;
		BButton *FButCancel;
//		void MessageReceived(BMessage *message);				
//		void AttachedToWindow(void);	
	protected:
		TStringList *Split(string AString, string ASplitter);
		BHandler *FHandler;
		string FOldValue;
		int32 FIndex;
			
};

#endif
