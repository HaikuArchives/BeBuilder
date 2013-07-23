#ifndef __TOOLWINDOW_H__
#define __TOOLWINDOW_H__
#include <PictureButton.h>
#include <Application.h>
#include "BGeneralWindow.h"
#include "GlobalVar.h"
#include "Message.h"
#include "ToolView.h"
#include "Property.h"
#include "StringList.h"
#include "GeneralException.h"

class TToolWindow : public BGeneralWindow
{
	public : 
		TToolWindow(const char *Title,BRect frame, const char *Prefs);
		~TToolWindow();	
	private :
		void MessageReceived(BMessage * message);
		bool DisplayProperties(BMessage *message);
		TToolView *FToolView;
		bool QuitRequested(void);
};

#endif
