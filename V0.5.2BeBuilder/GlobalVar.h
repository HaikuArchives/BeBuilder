#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__
#include <iostream.h>
//For debugging
#define DEBUG 1
#define DEBUGPRINT(x) if(DEBUG) cout <<x<<endl;
//End - For debugging

const uint32 MENU_FILE_ABOUT = 199; 
const uint32 MENU_FILE_NEW_PROJECT = 200; 
const uint32 MENU_FILE_NEW_WINDOW = 201; 
const uint32 MENU_FILE_NEW_VIEW = 202; 
const uint32 MENU_FILE_NEW_EDIT = 203; 
const uint32 MENU_FILE_NEW_BUTTON = 204; 
const uint32 MENU_FILE_NEW_MENUBAR = 205; 
const uint32 MENU_FILE_NEW_MENU = 206; 
const uint32 MENU_FILE_NEW_MENUITEM = 207; 
const uint32 MENU_FILE_NEW_SEPARATOR = 208; 
const uint32 MENU_FILE_NEW_CHECKBOX = 209; 
const uint32 MENU_FILE_NEW_RADIOBUTTON = 210; 

const uint32 MENU_FILE_OPEN_PROJECT = 211; 
const uint32 MENU_FILE_SAVE_PROJECT = 212; 
const uint32 MENU_FILE_SAVEAS_PROJECT = 213; 
const uint32 MENU_FILE_CLOSE_PROJECT = 214;
const uint32 MENU_TOOL_SHOW_TOOLBAR = 215;

const uint32 MENU_TOOL_MAKE = 216;
const uint32 MENU_TOOL_RUN = 217;
const uint32 MENU_TOOL_EDIT_FILE_BODY = 218;
const uint32 MENU_TOOL_EDIT_FILE_HEADER = 219;
const uint32 MENU_TOOL_EDIT_FILE_MAKEFILE = 220;
const uint32 MENU_FILE_PREFERENCES = 221;

const uint32 MENU_TOOL_GENERATE = 250;
const uint32 MSG_WANT_ADDON = 251;
//const uint32 MSG_RECEIVED_ADDON = 252;
//const uint32 ADD_ON_MANAGER = 253;

//-------------Special----------
// Between ViewProperty and Property Editor
const uint32 MSG_WINDOW_PROPERTY = 254;

//---------Message For Loading-- Message from a component to the GUI
const uint32 ADD_ITEM = 260;
const uint32 ADD_ITEM_UNDER = 261;
#define COMPONENT_TO_ADD "ComponentToAdd"
//Message for Saving and Loading 
const uint32 SAVE_PROPERTY = 262;
const uint32 SAVE_PROPERTY_LIST = 263;
const uint32 SAVE_COMPONENT = 264;
#define SAVE_COMPONENT_PARENT_COMPONENT_NAME "SaveComponentParentName"
#define SAVE_COMPONENT_PROPERTY "SaveComponentProperty"
#define SAVE_COMPONENT_CHILDREN "SaveComponentChildren"
#define SAVE_COMPONENT_ADDON_MESSAGE "SaveComponentAddOnMessage"
const uint32 SAVE_COMPONENT_LIST = 265;
//Complement ajoute a MSG_WANT_ADDON dans le cas d'un chargement des donnees.
#define COMPONENT_SAVE_MESSAGE_ADDON "ComponentSaveMessageAddOn" 
#define COMPONENT_ITEM_TO_SELECT "ItemToSelect"
const uint32 SAVE_CODE_GENERATOR = 266;
#define SAVE_COMPONENT_CODE_GENERATOR "ComponentSaveCodeGenerator"
#define SAVE_COMPONENT_CODE_LINE "ComponentSaveCodeLine"
const uint32 SAVE_CODE_LINE = 267;
#define SAVE_CODE_LINE_OLD_VALUE "OldValue" 
#define SAVE_CODE_LINE_INDEX "UniqueIndex" 
#define SAVE_CODE_LINE_FUNCTION_NAME "FunctionName"
#define SAVE_CODE_LINE_BEFORE_LOCATION "BeforeLocation"
#define SAVE_CODE_LINE_AFTER_LOCATION "AfterLocation"

const uint32 SAVE_CODE_FILE = 268;

//--------- Property Types ---------
#define PROP_TYPE_STRING "PropTypeString"
#define PROP_TYPE_FLOAT "PropTypeFloat"
//#define PROP_TYPE_INTEGER "PropTypeInteger"
//--------- Property Group ---------
#define PROP_GENERAL_GROUP "General"
#define PROP_POSITION_GROUP "Position"
//--------- Property Messages ------
#define PROP_MESSAGE_POINTER "PropertyPointer"

//const uint32 MSG_COMPONENTS_LIST = 300; 
const uint32 MSG_OUTLINE_CLICK = 300;
const uint32 MSG_OUTLINE_DELETE = 301;
const uint32 MSG_PROPERTY_LIST = 302;
const uint32 MSG_PROPERTY = 303;
const uint32 MSG_PROPERTY_UPDATE = 304;
const uint32 MSG_PROPERTY_EDIT = 305;
const uint32 MSG_PROPERTY_EDITED = 306;
const uint32 MSG_COMPONENT_FOCUS = 307;
#define COMPONENT_POINTER "ComponentPointerFocus"

// Property Editor Only!
const uint32 PROPERTY_EDITOR_VALIDATE = 400;
const uint32 PROPERTY_EDITOR_CANCEL = 401;
#define PROPERTY_UPDATE_NEW_VALUE "NewPropertyValue"
#define PROPERTY_UPDATE_OLD_VALUE "OldPropertyValue"
#define PROPERTY_UPDATE_INDEX "PropertyIndex"
// Drag And Drop Message
//#define DRAG_BUTTON_COMPONENT_NAME = "ButtonComponent"
//const uint32 DRAG_BUTTON_COMPONENT = 500;
//const uint32 DRAG_TEXTCONTROL_COMPONENT = 501;
//const uint32 DRAG_CHECKBOX_COMPONENT = 502;
//const uint32 DRAG_RADIOBUTTON_COMPONENT = 503;
//const uint32 DRAG_VIEW_COMPONENT = 504;

const uint32 DRAG_COMPONENT = 514;
const uint32 PROPERTY_ADDON = 515;

#define HAUTEUR_MENU 20
#define PREFS_FILENAME "BeBuilder.prefs" // Name of the preference file.
#define BE_BUILDER_VERSION "Release V0.5.2"
#define BE_BUILDER_NAME "BeBuilder"
#define BE_BUILDER_DATE "Montreal, October 15th 1999"
#define BE_BUILDER_COPYRIGHT "Jerome Fillon, Softimedia Inc."
#define BE_BUILDER_EXTENSION ".BeBuilder"
#define BE_BUILDER_MIME "application/x-vnd.BeBuilder"
#define PROJECT_MIME "application/x-BeBuilderProjectV0.5"
#define BE_BUILDER_EDITOR "application/x-mw-BeIDE"
#define BE_BUILDER_GENERATION "/boot/BeBuilder/Generation/"

//-------------PROPERTIES NAME----------------
#define PROP_NAME "Name"
#define PROP_CLASSNAME "ClassName"
#define PROP_TOP "Top"
#define PROP_LEFT "Left"
#define PROP_RIGHT "Right"
#define PROP_BOTTOM "Bottom"
#define PROP_LABEL "Label"
#define PROP_MESSAGE "Message"
#define PROP_RESIZING_MODE "ResizingMode"
#define PROP_FLAGS "Flags"
#define PROP_DEFAULT "Default"
#define PROP_TEXT "Text"
#define PROP_WINDOWTYPE "WindowType"
#define PROP_TITLE "Title"
#define PROP_APP_SIGNATURE "AppSignature"
#define PROP_GENERATION_PATH "GenerationPath"
#define PROP_MENU_LAYOUT "MenuLayout"
#define PROP_MENU_RESIZE_TO_FIT "MenuResizeToFit"
#define PROP_MENU_MODIFIERS "MenuModifiers"
#define PROP_MENU_SHORTCUT "MenuShortcut"
#define PROP_MENU_BORDER "MenuBorder"
#define PROP_MIN "Minimum"
#define PROP_MAX "Maximum"
#define PROP_THUMB "ThumbType"
#define PROP_DIVIDER "Divider"
#define PROP_ENABLED "Enabled"
#define PROP_HIERARCHICAL "Hierarchical"
#define PROP_HORIZONTAL "Horizontal"
#define PROP_VERTICAL "Vertical"
#define PROP_SCROLL_VIEW_CORNER "ScrollViewCorner"
#define PROP_BORDER_STYLE "BorderStyle"
#define PROP_LABEL_FONT "LabelFont"




//---------- OTHERS DEFINITION
#define BOOL_TRUE "TRUE"
#define BOOL_FALSE "FALSE"
#define EQUAL_OPERATION "EQ" // Needed in CodeLine
#define DIFF_OPERATION "DIFF"

#define FIND_STRING_SIZE 1000
//---Position
#define HAUTEUR_MENU 20
#define TOOLBAR_POSITION BRect(184,50,260,140)
#define TOOL_POSITION BRect(292,50,553,215)
#define BUILDER_POSITION BRect(5,50,170,250 + HAUTEUR_MENU)
#define PROPERTY_STANDARD_EDITOR_POSITION BRect(222,287,480,363)
#define PROPERTY_EDITOR_MULTI_POSITION BRect(224,289,445,453)
#define PROPERTY_EDITOR_CHOICE_POSITION BRect(222,287,437,393)
#define OPTION_WINDOW_POSITION BRect(5,50,150,150)
#define OPTION_TITLE "BeBuilder Preferences"
#endif