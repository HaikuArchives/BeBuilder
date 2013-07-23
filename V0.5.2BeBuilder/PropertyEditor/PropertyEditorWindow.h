#ifndef __PROPERTY_EDITOR_WINDOW_H__
#define __PROPERTY_EDITOR_WINDOW_H__
#include "BGeneralWindow.h"
#include "GlobalVar.h"
#include "Message.h"
#include <Application.h>
#include <stdio.h>
#include "PropertyEditorView.h"
#include "GeneralException.h"
#include <string>
#include "StringList.h"
//#include "Property.h"

class TPropertyEditorWindow : public BGeneralWindow
{
	public : 
		TPropertyEditorWindow(const char *Title,BRect frame, const char *Prefs);
		~TPropertyEditorWindow();	
	private :
		BHandler *FToolWindowHandler;
		int32 FEditedIndex; //index de la propriete editee provient du message envoye par la tool window.		
		void MessageReceived(BMessage * message);
		bool QuitRequested(void);
	protected:
		TPropertyEditorView *FView;
		virtual void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);
};
#endif