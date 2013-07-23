#include "BuilderMenu.h"

TBuilderMenu::TBuilderMenu(BRect frame):BMenuBar(frame,"BuilderMenu")
{

	FMenuPrincipal = new BMenu("File"); 

	FNewProjectMenu = new BMenuItem("New Project",new BMessage(MENU_FILE_NEW_PROJECT));

	FSaveProjectMenu = new BMenuItem("Save",new BMessage(MENU_FILE_SAVE_PROJECT));
	FSaveAsProjectMenu = new BMenuItem("Save As...",new BMessage(MENU_FILE_SAVEAS_PROJECT));
	FOpenProjectMenu = new BMenuItem("Open",new BMessage(MENU_FILE_OPEN_PROJECT));
	FCloseProjectMenu = new BMenuItem("Close",new BMessage(MENU_FILE_CLOSE_PROJECT));
	FPreferences = new BMenuItem("Preferences",new BMessage(MENU_FILE_PREFERENCES));

	FNewWindowMenu = new BMenuItem("New Window",new BMessage(MENU_FILE_NEW_WINDOW));
	FNewViewMenu = new BMenuItem("New View",new BMessage(MENU_FILE_NEW_VIEW));
	FNewEditMenu = new BMenuItem("New TextControl",new BMessage(MENU_FILE_NEW_EDIT));
	FNewButtonMenu = new BMenuItem("New Button",new BMessage(MENU_FILE_NEW_BUTTON));		


	FNewMenu = new BMenu("New Menu");
	FNewMenuBar = new BMenuItem("New MenuBar",new BMessage(MENU_FILE_NEW_MENUBAR));		
	FNewMenuMenu = new BMenuItem("New Menu",new BMessage(MENU_FILE_NEW_MENU));		
	
	FNewMenuItem = new BMenuItem("New MenuItem",new BMessage(MENU_FILE_NEW_MENUITEM));		
	FNewMenuSeparator = new BMenuItem("New MenuSeparator",new BMessage(MENU_FILE_NEW_SEPARATOR));		

	FNewMenu->AddItem(FNewMenuBar);

	FNewMenu->AddSeparatorItem();
	FNewMenu->AddItem(FNewMenuMenu);
	FNewMenu->AddItem(FNewMenuItem);
	FNewMenu->AddItem(FNewMenuSeparator);
		
	FNewCheckBox = new BMenuItem("New CheckBox",new BMessage(MENU_FILE_NEW_CHECKBOX));		
	FNewRadioButton = new BMenuItem("New RadioButton",new BMessage(MENU_FILE_NEW_RADIOBUTTON));		

	FAboutMenu = new BMenuItem("About...",new BMessage(MENU_FILE_ABOUT));

	FMenuPrincipal->AddItem(FNewProjectMenu);
	FMenuPrincipal->AddItem(FOpenProjectMenu);
	FMenuPrincipal->AddItem(FSaveProjectMenu);
	FMenuPrincipal->AddItem(FSaveAsProjectMenu);
	FMenuPrincipal->AddItem(FCloseProjectMenu);
	FMenuPrincipal->AddSeparatorItem();
	FMenuPrincipal->AddItem(FPreferences);
	FMenuPrincipal->AddSeparatorItem();

//	FMenuPrincipal->AddItem(FNewWindowMenu);
//	FMenuPrincipal->AddItem(FNewViewMenu);
//	FMenuPrincipal->AddItem(FNewEditMenu);
//	FMenuPrincipal->AddItem(FNewButtonMenu);
//	FMenuPrincipal->AddItem(FNewCheckBox);
//	FMenuPrincipal->AddItem(FNewRadioButton);
	
//--------- SUB MENU
//	FMenuPrincipal->AddItem(FNewMenu);
//	FMenuPrincipal->AddSeparatorItem();
	FMenuPrincipal->AddItem(FAboutMenu);
	AddItem(FMenuPrincipal);
	
	FMenuTool = new BMenu("Tools");
	FGenerateMenu = new BMenuItem("Generate Code",new BMessage(MENU_TOOL_GENERATE));
	FShowToolbarMenu = new BMenuItem("Show ToolBar",new BMessage(MENU_TOOL_SHOW_TOOLBAR));	

	FMakeMenu = new BMenuItem("Make",new BMessage(MENU_TOOL_MAKE));	
	FRunMenu = new BMenuItem("Run",new BMessage(MENU_TOOL_RUN));	
	FEditCPPFileMenu = new BMenuItem("Edit CPP File",new BMessage(MENU_TOOL_EDIT_FILE_BODY));	
	FEditHeaderFileMenu = new BMenuItem("Edit Header File",new BMessage(MENU_TOOL_EDIT_FILE_HEADER));	
	FEditMakeFileMenu = new BMenuItem("Edit makefile",new BMessage(MENU_TOOL_EDIT_FILE_MAKEFILE));	

	
//	FMenuTool->AddItem(FGenerateMenu);
	FMenuTool->AddItem(FShowToolbarMenu);
	FMenuTool->AddSeparatorItem();
	FMenuTool->AddItem(FEditCPPFileMenu);
	FMenuTool->AddItem(FEditHeaderFileMenu);
	FMenuTool->AddItem(FEditMakeFileMenu);
	
	FMenuTool->AddSeparatorItem();
	FMenuTool->AddItem(FMakeMenu);
	FMenuTool->AddItem(FRunMenu);
	AddItem(FMenuTool);		

	
}

TBuilderMenu::~TBuilderMenu()
{
/*	delete AboutMenu;
	delete NewProjectMenu;
	delete NewWindowMenu;
	delete NewViewMenu;
	delete NewEditMenu;
	delete NewButtonMenu;		
	delete MenuPrincipal;
	*/
}
