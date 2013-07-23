#ifndef __BBUILDERWINDOW_H__
#define __BBUILDERWINDOW_H__
#include "BGeneralWindow.h"
#include "GlobalVar.h"
#include "BuilderMenu.h"
#include "BuilderView.h"
#include "Component.h"
#include "WindowComponent.h"
#include "ViewComponent.h"
#include "ButtonComponent.h"
#include "TextControlComponent.h"
#include "ProjectComponent.h"
#include "ComponentItem.h"
#include <Node.h>
#include <Bitmap.h>
#include <Entry.h>
#include <Path.h>
#include <NodeInfo.h>
/*
#include "MenuBarComponent.h"
#include "MenuComponent.h"
#include "MenuItemComponent.h"
#include "MenuSeparatorComponent.h"
*/
#include "RadioButtonComponent.h"
#include "CheckBoxComponent.h"
#include "AddOnManager.h"
#include "FileRW.h"
#include <Application.h>
#include <FilePanel.h>
#include <List.h>
#include <Path.h>
#include <Alert.h>
#include "OpenDir.h"
#include "BeBuilderOption.h"
#include "WindowOption.h"

class TBuilderWindow : public BGeneralWindow
{
	public : 
		TBuilderWindow(const char *Title,BRect frame, const char *Prefs);
		~TBuilderWindow();	

		TBuilderView *FBuilderView;
		TProjectComponent *FComponentProject;
		string FAddOnStr;
	private :
//		TWindowComponent *FComponentWindow;
//		TViewComponent *FComponentView;
//		TButtonComponent *FComponentButton;
//		TTextControlComponent *FComponentTextControl;
//		TCheckBoxComponent *FComponentCheckBox;
//		TRadioButtonComponent *FComponentRadioButton;
		TOpenDir *FOpenDir;
		TBuilderMenu *FBuilderMenu;
		TAddOnManager *FAddOnManager;
		void MessageReceived(BMessage *);
		bool SaveIfNeeded(void);
		bool QuitRequested(void);		
		bool SaveProject(const char* APath, const char * AName, BMessage *ASaveMessage);
		bool RunCmd(const char* ACommande);
		bool OpenFile(string truc);
		TBeBuilderOption *FBeBuilderOption;
		TWindowOption *FWindowOption;
		
//		void AttachedToWindow(void);
		
		
};

#endif
