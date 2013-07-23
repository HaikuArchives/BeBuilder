#ifndef __BBUILDERMENU_H__
#define __BBUILDERMENU_H__
#include <MenuBar.h>
#include <Menu.h> 
#include <MenuItem.h>
#include <File.h> 
#include "GlobalVar.h"

class TBuilderMenu : public BMenuBar
{
	public :
		TBuilderMenu(BRect frame);
		~TBuilderMenu();
	private :
		BMenu *FMenuPrincipal;
		BMenuItem *FAboutMenu;
		BMenuItem *FPreferences;
		BMenuItem *FNewProjectMenu;
		BMenuItem *FSaveProjectMenu;
		BMenuItem *FSaveAsProjectMenu;
		BMenuItem *FOpenProjectMenu;
		BMenuItem *FCloseProjectMenu;			
		BMenuItem *FNewWindowMenu;
		BMenuItem *FNewViewMenu;
		BMenuItem *FNewEditMenu;
		BMenuItem *FNewButtonMenu;		
		BMenu *FNewMenu;
		BMenuItem *FNewMenuBar;
		BMenuItem *FNewMenuMenu;
		BMenuItem *FNewMenuItem;
		BMenuItem *FNewMenuSeparator;

		BMenuItem *FNewCheckBox;
		BMenuItem *FNewRadioButton;
		BMenu *FMenuTool;
		BMenuItem *FGenerateMenu;		
		BMenuItem *FShowToolbarMenu;
		BMenuItem *FMakeMenu;
		BMenuItem *FRunMenu;	
		BMenuItem *FEditCPPFileMenu;
		BMenuItem *FEditHeaderFileMenu;
		BMenuItem *FEditMakeFileMenu;
		

};

#endif
