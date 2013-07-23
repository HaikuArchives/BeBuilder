#ifndef __PROPERTY_EDITOR_STANDARD_H__
#define __PROPERTY_EDITOR_STANDARD_H__
#include "BGeneralWindow.h"
#include "GlobalVar.h"
#include "Message.h"
#include <Application.h>
#include <stdio.h>
#include "PropertyEditorStandardView.h"
#include "PropertyEditorWindow.h"
#include "GeneralException.h"
#include <string>
#include "StringList.h"
//#include "Property.h"

class TPropertyEditorStandard : public TPropertyEditorWindow
{
	public : 
		TPropertyEditorStandard(const char *Title,BRect frame);
		~TPropertyEditorStandard();	
	private :
		BHandler *FToolWindowHandler;
		int32 FEditedIndex; //index de la propriete editee provient du message envoye par la tool window.		
//		void MessageReceived(BMessage * message);
//		bool QuitRequested(void);
};

#endif
