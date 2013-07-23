#ifndef __PROPERTYLIST_H__
#define __PROPERTYLIST_H__
#include <string>
#include <map>
#include <Message.h>
#include "Property.h"
#include "GlobalVar.h"
#include "Global.h"
#include "StringList.h"
#include "Object.h"
//#include "Component.h"
using namespace std;
typedef  map<string,TProperty *>::const_iterator TPropertyCI;

//class TComponent;

class TPropertyList: public TObject  
{
	public:
		TPropertyList();
		virtual ~TPropertyList();
		void AddProperty(string AName,string AValue);
		void AddProperty(string AName,string AValue, string AType, bool AMultipleValue, bool ASimpleValue, string ADefaultList, string AGroupName);

		TProperty *GetProperty(string AName);
		TProperty *GetNextProperty(bool FromBegining);
		string GetPropertyValue(string AName);
		bool SetPropertyValue(string AName,string AValue);
		void SendPropertyMessage(BHandler *AHandler,BHandler *AComposantHandler);		
		void Debug(void);
		bool PreparePropertyMessage(BMessage **AMessage);
//Loading And Saving
		BMessage *SaveData(void);
		bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);
				
	private:
		map<string,TProperty *> FListe;
		TStringList *FPropertyList;		

};

#endif
