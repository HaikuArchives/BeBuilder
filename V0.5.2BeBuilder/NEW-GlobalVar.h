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


const uint32 MENU_TOOL_GENERATE = 250;
//const uint32 MSG_WANT_ADDON = 251;
//const uint32 MSG_RECEIVED_ADDON = 252;
//const uint32 ADD_ON_MANAGER = 253;

//-------------Special----------
// Between ViewProperty and Property Editor
const uint32 MSG_WINDOW_PROPERTY = 250;

//--------- Property Types ---------
#define PROP_TYPE_STRING "PropTypeString"
#define PROP_TYPE_FLOAT "PropTypeFloat"
//#define PROP_TYPE_INTEGER "PropTypeInteger"
//--------- Property Group ---------
#define PROP_GENERAL_GROUP "General"
#define PROP_POSITION_GROUP "Position"
//--------- AddOn Manager ----------
const uint32 AM_WANT_ADDON = 251;
#define AM_ADDON_ID "AddOnId"
#define AM_PARENT "ParentItem"
#define AM_CONTAINER "ContainerName"
#define AM_CLASS "ClassName"
#define AM_COMPONENT "ComponentName"
#define AM_OBJECT_ID "ObjectID"
#define AM_MESSAGE_PLUS "MessagePlus"

//const uint32 MSG_COMPONENTS_LIST = 300; 
const uint32 MSG_OUTLINE_CLICK = 300;
const uint32 MSG_PROPERTY_LIST = 301;
const uint32 MSG_PROPERTY = 302;
const uint32 MSG_PROPERTY_UPDATE = 303;
#define PROPERTY_UPDATE_NEW_VALUE "NewValue"
#define PROPERTY_UPDATE_OLD_VALUE "OldValue"
const uint32 MSG_PROPERTY_EDIT = 304;
const uint32 MSG_PROPERTY_EDITED = 305;

// Property Editor Only!
const uint32 PROPERTY_EDITOR_VALIDATE = 400;
const uint32 PROPERTY_EDITOR_CANCEL = 401;

// Drag And Drop Message
const uint32 DRAG_COMPONENT = 514;


#define HAUTEUR_MENU 20
#define PREFS_FILENAME "BPP.prefs" // Name of the preference file.
#define BE_BUILDER_VERSION "Pre-Alpha Release V0.1"
#define BE_BUILDER_NAME "BPP"
#define BE_BUILDER_DATE "Montreal, April 2nd 1999"
#define BE_BUILDER_COPYRIGHT "Dan Berlin, Jerome Fillon (Softimedia Inc.)"

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


//-------------- OBJECT MANAGER ----------------
const uint32 OM_ADDOBJECT = 600;
#define OM_ADDOBJECT_PTR "PTR"
#define OM_ADDOBJECT_FATHER_TYPE "ComponentFatherType"
#define OM_ADDOBJECT_ID "ID"
#define OM_ADDOBJECT_MESSAGE_PLUS "MessagePlus"
const uint32 OM_REMOVE_OBJECT = 601;
const uint32 OM_SET_CURRENT_OBJECT = 602;
#define OM_CURRENT_OBJECT "Element"
const uint32 OM_GENERATE = 603;
const uint32 OM_ADD_COMPONENT = 604;
#define OM_COMPONENT_NAME "ComponentName"
#define OM_CLASS_NAME "ClassName"
#define OM_PARAM_VALUE "ParamValue"
#define OM_CONTAINER_NAME "ContainerName"
#define OM_CONTAINER_CLASS "ContainerClass"
#define OM_CALLER_NAME "CallerName"
#define OM_PARENT_TYPE "ParentType"
#define OM_ADDON_ID "AddOnID"
const uint32 OM_MESSAGE_PLUS = 605;
#define OM_PARENT_OBJID "ParentObjId"
#define OM_PARENT_OBJNAME "ParentObjName"
//-----
#define OM_CALLER_NAME_PM "PM"
#define OM_CALLER_NAME_GM "GM"

//------------- Parser Manager ------------
const uint32 PM_ADD_UPDATE = 800;
#define PM_CONTAINER_NAME "ContainerName"
#define PM_CODE_HEADER "CodeHeader"
#define PM_CODE_BODY "CodeBody"
#define PM_FUNCTION_TYPE "FunctionType"
//------- FUNCTION TYPE
#define PM_CONSTRUCTOR "Constructor"
#define PM_DESTRUCTOR "Destructor"
#define PM_MESSAGE_RECEIVED "MessageReceived"


//---------- OTHERS DEFINITION
#define BOOL_TRUE "TRUE"
#define BOOL_FALSE "FALSE"

#endif