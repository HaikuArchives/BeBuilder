#include "MenuCodeGenerator.h"
#include "MenuComponent.h"

TMenuCodeGenerator::TMenuCodeGenerator(TMenuComponent * AMenuComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FMenuComponent = AMenuComponent;
}

void TMenuCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FMenuComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FMenuComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}

bool TMenuCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return true;
}
bool TMenuCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <Menu.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBMenu *F");
	FHeaderLine3->AddProperty(FMenuComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TMenuCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return true;
}
	
bool TMenuCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{
//	string ACtorLabel = FMenuComponent->FParent->FClassName + "::" + FMenuComponent->FParent->FClassName;
	string ACtorLabel = "::"; 

	TCodeLine *FBodyLine = new TCodeLine(FBodyCodeFile);
	FBodyLine->AddString("\tF");
	FBodyLine->AddProperty(FMenuComponent,PROP_NAME,true,true);
	FBodyLine->AddString("=new BMenu(\"");
	FBodyLine->AddProperty(FMenuComponent,PROP_LABEL,true,false);
	FBodyLine->AddString("\");\n");	

	if (ReallyWriteInFile) FBodyLine->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	if (TMenuComponent *buffer = dynamic_cast<TMenuComponent *>(FMenuComponent->FParent) )
	{
		TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
		FBodyLine2->AddString("\tF");
		FBodyLine2->AddProperty(buffer,PROP_NAME,true,true);
		FBodyLine2->AddString("->AddItem(F");
		FBodyLine2->AddProperty(FMenuComponent,PROP_NAME,true,true);
		FBodyLine2->AddString(");\n");	
		if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),"{","}");
	}
	else
	{
		if (BMenuField *buffer = dynamic_cast<BMenuField *>(FMenuComponent->FParent) )
		{
			TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
			FBodyLine3->AddString("\tMenu()->AddItem(F");
			FBodyLine3->AddProperty(FMenuComponent,PROP_NAME,true,true);
			FBodyLine3->AddString(");\n");	
			if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),"{","}");
		}
		else
		{
			TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
			FBodyLine4->AddString("\tAddItem(F");
			FBodyLine4->AddProperty(FMenuComponent,PROP_NAME,true,true);
			FBodyLine4->AddString(");\n");	
			if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),"{","}");	
		}
	}
	TCodeLine *FBodyLine5 = new TCodeLine(FBodyCodeFile);
	FBodyLine5->AddString("\tF");
	FBodyLine5->AddProperty(FMenuComponent,PROP_NAME,true,true);
	FBodyLine5->AddString("->SetTargetForItems(this);\n");	
	if (ReallyWriteInFile) FBodyLine5->AddLine(NULL,ACtorLabel.c_str(),"{","}");	

	return true;
}
bool TMenuCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	return true;
}
bool TMenuCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}


