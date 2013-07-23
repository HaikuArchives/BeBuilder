#include "CodeLine.h"
#include "PropertyList.h"
#include "Component.h"

TCodeLine::TCodeLine(TCodeFile *ACodeFile):TObject("TCodeLine")
{
	FCodeFile = ACodeFile;
	FCodeList = new TStringList();
	FCachedCodeList = new TStringList();
	FPropertyList = new TPropertyList();
	FParser = new TParser();	
	FUniqueIndex = -1;		
	
	//Set Line Position
	FFunctionName = NULL;
	FBeforeLocation = NULL;
	FAfterLocation = NULL;
	
	// For Debugging Only!
	FDebugMode = 1;
	FDebugMessage = "TCodeLine";
	ShowDebug("Inside ctor");
}

TCodeLine::~TCodeLine(void)
{
	delete FCodeList;
	delete FCachedCodeList;
	delete FPropertyList;		
}

bool TCodeLine::AddString(string AStr)
{
	FCodeList->AddItem("STRING",new string(AStr),false);
	return true;	
}

TBoolean::TBoolean(TProperty *AProperty, const char *AnOperation, const char *AValue):TObject("TBoolean")
{
	FProperty = AProperty;
	FOperation = AnOperation;
	FValue = AValue;	
}

bool TBoolean::Evaluate()
{
	if (IsFoundInside(FOperation,EQUAL_OPERATION))	
	{
		if (strcmp(FProperty->GetValue().c_str(),FValue.c_str())==0)
		{
			ShowDebug(string("TBoolean::Evaluate return true EQUALOPERATION Property=") +  FProperty->GetValue() + string(" Value=") + FValue);
			return true;
		}
		else
		{
			ShowDebug(string("TBoolean::Evaluate return false EQUALOPERATION Property=") +  FProperty->GetValue() + string(" Value=") + FValue);
			return false;
		}
	}
	if (IsFoundInside(FOperation,DIFF_OPERATION))	
	{
		if (strcmp(FProperty->GetValue().c_str(),FValue.c_str())!=0)
		{
			ShowDebug(string("TBoolean::Evaluate return true DIFF_OPERATION Property=") +  FProperty->GetValue() + string(" Value=") + FValue);
			return true;
		}
		else
		{
			ShowDebug(string("TBoolean::Evaluate return false DIFF_OPERATION Property=") +  FProperty->GetValue() + string(" Value=") + FValue);
			return false;
		}
	}
	return false;
}

bool TCodeLine::BeginBoolean(TComponent *AComponent, const char *APropertyName,const char *AnOperation, const char *AValue, bool AddToProperty, bool AddToCodeGeneratorList)
{
	TProperty *AProperty = AComponent->FPropertyList->GetProperty(APropertyName);
	if (AddToProperty)
	{
		AProperty->AddCodeLine(this);
	}
	TBoolean *ABoolean = new TBoolean(AProperty,AnOperation,AValue);

	FCodeList->AddItem("BOOLEAN",ABoolean,false);

	if (AddToCodeGeneratorList)
	{
		AComponent->FCodeGenerator->AddCodeLine(this);
	}
	return true;	
	
}

bool TCodeLine::EndBoolean()
{
	FCodeList->AddItem("BOOLEAN",NULL,false); // NULL shows to the code generation that this is the end of the generation block.
	return true;
}

/*
bool TCodeLine::AddProperty(TProperty *AProperty)
{
	FCodeList->AddItem("PROPERTY",AProperty,false);
	return true;		
}
*/
bool TCodeLine::AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList)
{
	TProperty *AProperty = AComponent->FPropertyList->GetProperty(APropertyName);
	if (AddToProperty)
	{
		AProperty->AddCodeLine(this);
	}
	FCodeList->AddItem("PROPERTY",AProperty,false);
	if (AddToCodeGeneratorList)
	{
		AComponent->FCodeGenerator->AddCodeLine(this);
	}
	return true;	
}

bool TCodeLine::ReplaceLine(TProperty *AProperty)
{
	return true;
}				

bool TCodeLine::DeleteLine(TProperty *AProperty) // AProperty can be null!
{
	return true;
}

bool TCodeLine::UpdateLine(TProperty *AProperty)
{
	ShowDebug("Entering UpdateLine Before GenerateLine");
	string ALine = GenerateLine(AProperty);	
	ShowDebug("After GenerateLine");
	BFile AFile;
	if (FCodeFile == NULL) ShowDebug("AddLine FCodeFile is NULL");
	else ShowDebug("AddLine FCodeFile is NOT NULL.");
	
	ShowDebug(string("AddLine before creating BFile") + string(FCodeFile->GetFilePath()) + string(FCodeFile->GetFileName()));
	
	AFile.SetTo((string(FCodeFile->GetFilePath()) + string(FCodeFile->GetFileName())).c_str(),B_READ_WRITE | B_CREATE_FILE );
	if (AFile.InitCheck()==B_NO_INIT) return false;

	ShowDebug("UpdateLine before testing");

//	if (FOldLine.length()>0)
//	{
		ShowDebug("UpdateLine before ReplaceString\n");
		if (FParser->ReplaceString(0,FOldLine,ALine,&AFile)==false)
		{
			ShowDebug("UpdateLine after ReplaceString returns FALSE\n");
			return false;
		}
		ShowDebug("UpdateLine after ReplaceString \n");

		FOldLine = ALine;		
		return true;
//	}
	return false;	
}


bool TCodeLine::AddLine(TProperty *AProperty,const char* AFunctionName, const char* AnAfterLocation, const char* ABeforeLocation) // AProperty can be null!
{
	ShowDebug("Entering AddLine\n");
	off_t resultat = 0;
	ShowDebug("AddLine before generateLine\n");

	string ALine = GenerateLine(AProperty);	
	ShowDebug(string("AddLine GenerateLine=") + ALine.c_str());
	if (FCodeFile == NULL) ShowDebug("AddLine FCodeFile is NULL");
	else ShowDebug("AddLine FCodeFile is NOT NULL.");
	
	ShowDebug(string("AddLine before creating BFile ") + string(FCodeFile->GetFilePath()) + string(FCodeFile->GetFileName()));

	BFile AFile;
	AFile.SetTo((string(FCodeFile->GetFilePath()) + string(FCodeFile->GetFileName())).c_str(),B_READ_WRITE | B_CREATE_FILE );
	if (AFile.InitCheck()==B_NO_INIT) return false;
	ShowDebug("AddLine before testing");

	if (AFunctionName!=NULL)
	{
		ShowDebug("AddLine before FindInFile for AFunctionName start= 0");
		resultat = FParser->FindInFile(0,string(AFunctionName),&AFile);
		ShowDebug(string("AddLine after FindInFile for AFunctionName stop=") + IntToStr((long)resultat));
		if (resultat==-1) return false;
		resultat += strlen(AFunctionName);
	}
	if (AnAfterLocation!=NULL)
	{
		ShowDebug(string("AddLine before FindInFile for AnAfterLocation start=") + IntToStr((long)resultat));
		resultat = FParser->FindInFile(resultat,AnAfterLocation,&AFile);
		ShowDebug(string("AddLine after FindInFile for AnAfterLocation stop=") + IntToStr((long)resultat));
		if (resultat==-1) return false;
		resultat += strlen(AnAfterLocation);
	}
	if (ABeforeLocation!=NULL)
	{
		ShowDebug(string("AddLine before FindInFile for ABeforeLocation start=") + IntToStr((long)resultat));
		resultat = FParser->FindInFile(resultat,ABeforeLocation,&AFile);
		ShowDebug(string("AddLine after FindInFile for ABeforeLocation stop=") + IntToStr((long)resultat));
		if (resultat==-1) return false;
	}
	else
	{
		ShowDebug("AddLine before FindNextLine");
		if ((AFunctionName!=NULL) || (AnAfterLocation!=NULL))
		{
			resultat = FParser->FindNextLine(resultat,&AFile); // We need to fin where to insert!
			if (resultat==-1)  return false;
		}
		ShowDebug("AddLine after FindNextLine");
	}

	ShowDebug("AddLine Everything has been found inserting Data NOW!");
	
	FParser->InsertString(resultat,ALine,&AFile);
	ShowDebug("AddLine after InsertString.");

	AFile.Sync();
	AFile.Unset();
	FOldLine = ALine;
	ShowDebug("AddLine Quitting.");
	return true;	
}

bool TCodeLine::SetLinePosition(const char* AFunctionName, const char* AnAfterLocation, const char* ABeforeLocation)
{
	FFunctionName = AFunctionName;
	FAfterLocation = AnAfterLocation;
	FBeforeLocation = ABeforeLocation;
	return true;
}

bool TCodeLine::AddLine(void) //Can be called only if SetLinePosition has been called before.
{
	if ((FFunctionName==NULL) && (FAfterLocation==NULL) && (FBeforeLocation==NULL))
	{
		return false;
	}
	AddLine(NULL,FFunctionName,FAfterLocation,FBeforeLocation);
	return true;
}


void TCodeLine::Copyrights(void)
{
	AddString("/*********************************************\n");
	AddString("* Generated Code By ");
	AddString(BE_BUILDER_NAME);
	AddString(" ");
	AddString(BE_BUILDER_VERSION);
	AddString("                \n");
	AddString("* Written by Jerome Fillon (Softimedia Inc.) \n");
	AddString("* Copyrights ");
	AddString(BE_BUILDER_COPYRIGHT); 
	AddString("\n");	
	AddString("**********************************************/\n");		
}

void TCodeLine::CopyrightsMakeFile(void)
{
	AddString("####################################################\n");
	AddString("# Generated Code By ");
	AddString(BE_BUILDER_NAME);
	AddString(" ");
	AddString(BE_BUILDER_VERSION);
	AddString("                  \n");
	AddString("# Written by Jerome Fillon ,Softimedia Inc.   \n");
	AddString("# Copyrights ");
	AddString(BE_BUILDER_COPYRIGHT); 
	AddString("\n");	
	AddString("####################################################\n");
}


BMessage *TCodeLine::SaveData(void)
{
	ShowDebug("SaveData Inside.");
	string AStr;
	BMessage *AMessage = new BMessage(SAVE_CODE_LINE);
	//We only Save the OldValue that's the only value we need.
	AMessage->AddString(SAVE_CODE_LINE_OLD_VALUE,FOldLine.c_str()); 
	AMessage->AddInt32(SAVE_CODE_LINE_INDEX,FUniqueIndex); 

	if (FFunctionName!=NULL) AMessage->AddString(SAVE_CODE_LINE_FUNCTION_NAME,FFunctionName); 
	if (FBeforeLocation!=NULL) AMessage->AddString(SAVE_CODE_LINE_BEFORE_LOCATION,FBeforeLocation); 
	if (FAfterLocation!=NULL) AMessage->AddString(SAVE_CODE_LINE_AFTER_LOCATION,FAfterLocation); 

	// FUniqueIndex is set by the code generator when adding this codeline to its internal list.

	ShowDebug(string("SaveData Quitting. OLDVALUE=") +FOldLine + string(" LINE_INDEX=") + IntToStr(FUniqueIndex));
	return AMessage;
}

bool TCodeLine::LoadData(BMessage *AMessage, BHandler *AGuiHandler)
{
	const char *AnOldValue;
	ShowDebug("LoadData Inside.");
	AMessage->FindString(SAVE_CODE_LINE_FUNCTION_NAME,&FFunctionName);
	AMessage->FindString(SAVE_CODE_LINE_BEFORE_LOCATION,&FBeforeLocation);
	AMessage->FindString(SAVE_CODE_LINE_AFTER_LOCATION,&FAfterLocation);
	if (AMessage->FindString(SAVE_CODE_LINE_OLD_VALUE,&AnOldValue)==B_OK)
	{
		FOldLine = AnOldValue;
		ShowDebug(string("LoadData Quitting OK. OldLine=") + FOldLine);
		return true;
	}
	ShowDebug("LoadData Quitting Failed.");
	return false;
}

// Private or protected functions.		
bool TCodeLine::Update(TProperty *AProperty) // APropert can be null!
{
	string AStr = GenerateLine(AProperty);

	FOldLine = AStr;
	return true;
}

string TCodeLine::GenerateLine(TProperty *AProperty) // APropert can be null!
{
	TProperty *ATmpProperty;
	TBoolean *ATmpBoolean;
	ShowDebug("Inside GenerateLine");
	string AStr;
	string result;
	bool IncludeTheseLines = true;
	for (int ind=0; ind <FCodeList->GetCount();ind++)
	{
		AStr = FCodeList->GetValue(ind);	
		ShowDebug(string("AStr=") + AStr);
//		if (AStr.find("PROPERTY")!=-1)
		if (IsFoundInside(AStr,"PROPERTY") && IncludeTheseLines)
		{
			ShowDebug("PROPERTY FOUND");
			ATmpProperty = (TProperty *)FCodeList->GetItem(ind);
			if (ATmpProperty==NULL)
			{
				ShowDebug(string("AProperty is null.\n result=") + result );	
									
			}
			else
			{
//				ShowDebug("AProperty is NOT null");
				AStr = ATmpProperty->GetValue();
//				ShowDebug(string("ATmpProperty GetValue = ") + AStr);
			}
			result = result + ATmpProperty->GetValue();			
		}
		else
		{
//			if (AStr.find("STRING")!=-1)
			if ((IsFoundInside(AStr,"STRING")) &&(IncludeTheseLines))
			{
				ShowDebug("STRING FOUND");
				result = result + ((string *)FCodeList->GetItem(ind))->c_str();			
//				ShowDebug("STRING FOUND end.");
			}	
			else
			{
				if (IsFoundInside(AStr,"BOOLEAN"))
				{
					ShowDebug("BOOLEAN FOUND");
					IncludeTheseLines = true;
					ATmpBoolean = (TBoolean *)FCodeList->GetItem(ind);
					if (ATmpBoolean!=NULL)
					{
						IncludeTheseLines = ATmpBoolean->Evaluate();
					}	
					if (IncludeTheseLines) ShowDebug("IncludeTheseLines is true");
					else ShowDebug("IncludeTheseLines is false");				
				}
			}	
		}
	}
//	AStr = "---------------------\nGenerateLine=" + result;
	AStr = "GenerateLine=" + result;
//	AStr = AStr + "\n------------------------------";
//	ShowDebug(AStr);
	return result;
}
