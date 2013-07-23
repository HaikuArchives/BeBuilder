#ifndef __CODE_LINE_H__
#define __CODE_LINE_H__
#include <malloc.h>
#include <string>
//#include <string.h>
#include <stdio.h>
#include <Entry.h>
#include "Parser.h"
#include "FileRW.h"
#include "GlobalVar.h"
#include "StringList.h"
#include "Object.h"
#include "CodeFile.h"
#include "Global.h"
class TProperty;
class TPropertyList;
class TComponent;
//#include "CodeGenerator.h" // Only to use the AddInFunctionPlus for the moment
#include "CodeFile.h"
class TCodeLine : public TObject
{
	public :
		TCodeLine(TCodeFile *ACodeFile);
		virtual ~TCodeLine(void);
		virtual bool AddString(string AStr);
//		virtual bool AddProperty(TProperty *AProperty);
//		virtual bool AddProperty(TComponent *AComponent, const char *APropertyName);
		virtual bool AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList);

		virtual bool ReplaceLine(TProperty *AProperty);				
		virtual bool DeleteLine(TProperty *AProperty); // AProperty can be null!
		virtual bool UpdateLine(TProperty *AProperty);
		//Everything can be NULL in the AddLine function.
		virtual bool AddLine(TProperty *AProperty,const char* AFunctionName, const char* AnAfterLocation, const char* ABeforeLocation); 
		virtual bool SetLinePosition(const char* AFunctionName, const char* AnAfterLocation, const char* ABeforeLocation);
		virtual bool AddLine(void); //Can be called only if SetLinePosition has been called before.

		virtual bool BeginBoolean(TComponent *AComponent, const char *APropertyName,const char *AnOperation, const char *AValue, bool AddToProperty, bool AddToCodeGeneratorList);
		virtual bool EndBoolean(void);



		void Copyrights(void);
		void CopyrightsMakeFile(void);
		string FOldLine; //Ancienne Ligne.
		virtual BMessage *SaveData(void);
		virtual bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);
		int32 FUniqueIndex;		
		
//	private :
	protected :
		TCodeFile *FCodeFile;
		TParser *FParser;
		TStringList *FCodeList; // This list contains TProperty pointer and string.
		TStringList *FCachedCodeList; //This List contains strings Only!
		TPropertyList *FPropertyList;
		const char *FFunctionName;
		const char *FBeforeLocation;
		const char *FAfterLocation;

		virtual bool Update(TProperty *AProperty); // APropert can be null!
		virtual string GenerateLine(TProperty *AProperty); // APropert can be null!
};

class TBoolean : public TObject
{
	public :
		TBoolean(TProperty *AProperty, const char *AnOperation, const char *AValue);
		bool Evaluate();
		string FOperation;
		string FValue;
		TProperty *FProperty;		

};

#endif