#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__



const uint32 WINDOW_REGISTRY_ADD = 'WRad';
const uint32 WINDOW_REGISTRY_SUB = 'WRsb';
const uint32 WINDOW_REGISTRY_ADDED = 'WRdd';
// Messages for menu commands

const uint32 MENU_FILE_NEW				= 'MFnw';
const uint32 MENU_FILE_OPEN				= 'MFop';
const uint32 MENU_FILE_CLOSE			= 'MFcl';
const uint32 MENU_FILE_SAVE				= 'MFsv';
const uint32 MENU_FILE_SAVEAS			= 'MFsa';
const uint32 MENU_FILE_PAGESETUP		= 'MFps';
const uint32 MENU_FILE_PRINT			= 'MFpr';
const uint32 MENU_FILE_QUIT				= 'MFqu';

const uint32 B_SAVE_FORCED				= 'SFor';
const uint32 B_SAVE_ASKED				= 'SAsk';
const uint32 B_RELOAD					= 'RLOD';
const uint32 B_GOTO						= 'GOTO';

//*/
#include <iostream.h>
//For debugging
#define DEBUG 1 
#define DEBUGPRINT(x) if(DEBUG) cout <<x<<endl;
#define APP_SIGNATURE "application/x-vnd.BeBuilderEditorV0.0.1"

#define HAUTEUR_MENU 20
#define EDITOR_NAME "BeBuilder Editor"
#define EDITOR_COPYRIGHTS "Softimedia Inc., Montreal"
#define EDITOR_WRITTEN "Jerome Fillon"
#define EDITOR_VERSION "V0.0.1"

#define MENU_FILE_LABEL "File"
#define MENU_NEW_LABEL "New"
#define MENU_OPEN_LABEL "Open"
#define MENU_CLOSE_LABEL "Close"
#define MENU_SAVE_LABEL "Save"
#define MENU_SAVE_AS_LABEL "SaveAs"
#define MENU_PAGE_SETUP_LABEL "Setup"
#define MENU_PRINT_LABEL "Print"
#define MENU_QUIT_LABEL "Quit"

#define MENU_EDIT_LABEL "Edit"
#define MENU_UNDO_LABEL "Undo"
#define MENU_CUT_LABEL "Cut"
#define MENU_COPY_LABEL "Copy"
#define MENU_PASTE_LABEL "Paste"
#define MENU_SELECT_ALL_LABEL "Select All"


#define UNTITLED_WINDOW "Untitled"
#define SAVE_MESSAGE " has been modified but is not saved. What do you want to do?"
#define BUTTON_SAVE "Save"
#define BUTTON_DONT_SAVE "Don't Save"
#define BUTTON_CANCEL "Cancel"

#endif