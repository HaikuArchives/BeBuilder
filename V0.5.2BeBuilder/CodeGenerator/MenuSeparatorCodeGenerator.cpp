#include "MenuSeparatorCodeGenerator.h"
#include "MenuSeparatorComponent.h"

TMenuSeparatorCodeGenerator::TMenuSeparatorCodeGenerator(TMenuSeparatorComponent * AMenuSeparatorComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FMenuSeparatorComponent = AMenuSeparatorComponent;
}
/*
void TMenuSeparatorCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TMenuSeparatorCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	//GenerateH(APath,ClassName);
	//GenerateCPP(APath,ClassName);	
	//---------NEW METHOD!
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	
}

bool TMenuSeparatorCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuSeparatorCodeGenerator::InsertionContructor \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuSeparatorCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (FMenuSeparatorComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FMenuSeparatorComponent->FParent->FParent->FClassName;
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\tF" + FMenuSeparatorComponent->FParent->FComponentName + "->AddSeparatorItem();\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
}
*/

void TMenuSeparatorCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FMenuSeparatorComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FMenuSeparatorComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}

bool TMenuSeparatorCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return true;
}

bool TMenuSeparatorCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	return true;
}

bool TMenuSeparatorCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return true;
}

bool TMenuSeparatorCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{
//	string ACtorLabel = FMenuSeparatorComponent->FParent->FClassName + "::" + FMenuSeparatorComponent->FParent->FClassName;
	string ACtorLabel = "::";


	if (BMenuField *buffer = dynamic_cast<BMenuField *>(FMenuSeparatorComponent->FParent) )
	{
		TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
		FBodyLine1->AddString("\tMenu()->AddSeparatorItem();\n");
		if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");
	}
	else
	{
		TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
		FBodyLine1->AddString("\tF");
		FBodyLine1->AddProperty(FMenuSeparatorComponent->FParent,PROP_NAME,true,true);
		FBodyLine1->AddString("->AddSeparatorItem();\n");	
		if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");
	}
	return true;
}
bool TMenuSeparatorCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	return true;
}
bool TMenuSeparatorCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}
