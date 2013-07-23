#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <string>
using namespace std;
#include <Message.h>
#include <ListItem.h>
#include <List.h>
#include "GlobalVar.h"
#include "PropertyEditorStandard.h"
#include "PropertyEditorChoice.h"
#include "PropertyEditorMultiChoice.h"
#include "Object.h"
#include "StringList.h"
#include "CodeLine.h"

class TProperty : public BStringItem, public TObject
{
	public:
		TProperty(const char *AName, const char *AValue, const char *AType = PROP_TYPE_STRING, bool AMultipleValue = false, bool ASimpleValue = true, const char *ADefaultList = "" ,const char *GroupName = PROP_GENERAL_GROUP, uint32 level = 0, bool expanded = true);
		virtual ~TProperty();
		void Refresh(void);
		void AddToMessage(BMessage *AMessage);
		void SendMessage(BHandler *AHandler);		
		void Edit(int32 index, BHandler *AHandler);
		bool AddCodeLine(TCodeLine *ACodeLine);
		bool DeleteCodeLine(TCodeLine *ACodeLine);
		bool AddCodeFile(TCodeFile *ACodeFile);
		bool DeleteCodeFile(TCodeFile *ACodeFile);
		
		bool UpdateCode(void);
		string GetValue();
		bool SetValue(string AStr);		
		void Debug(void);
// Save and Load
		BMessage *SaveData();
		bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);

/*
		TProperty(const char *AName, const char *AValue, const char *AType = PROP_TYPE_STRING, bool AMultipleValue = true, const char *ADefaultList = "" ,const char *GroupName = PROP_GENERAL_GROUP, uint32 level = 0, bool expanded = true);

//		TProperty(const char *AName, const char *AValue);
		virtual ~TProperty();
		void Refresh(void);
//		void AddToMessage(BMessage **AMessage);
//		void SendMessage(BHandler *AHandler);		
		void Edit(int32 index, BHandler *AHandler);
		string FName;
		string FValue;
*/


		string FName;


		string FType;
		string FDefaultValues;
		bool FMultipleValue; // MultipleValue is values that can be choosed together. 
		bool FSimpleValue; // Value must be inserted via a text box.
		string FGroupName;
		
//		TComponent *FComp; //Component Pere... peut-etre nul!
		BHandler *FHandler; // Handler pour l'envoi de message de la tool window vers le composant interesse!
//		TPropertyEditorWindow *FPropertyEditor;		
		BWindow *FPropertyEditor;		
		
//		TStringList *FCodeLineList;
		BList *FCodeLineList;
		BList *FCodeFileList;
		//Special this says to the CodeLine to generate the code with a different property's value
		bool FGenerateWithOtherValue;
		string FOtherValue;		
	private :
		string FValue;		
};
class TInteger
{
	public:
		TInteger(int32 AnInteger);
		int32 FValue;
};

#endif 
