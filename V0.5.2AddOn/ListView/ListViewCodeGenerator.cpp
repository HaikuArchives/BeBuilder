#include "ListViewCodeGenerator.h"
#include "ListViewComponent.h"

TListViewCodeGenerator::TListViewCodeGenerator(TListViewComponent * AListViewComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FListViewComponent = AListViewComponent;
}

void TListViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FListViewComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FListViewComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}
/*

bool TButtonCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
//	CreateMessageReceived(ReallyWriteInFile);	//Will be called in the Component Object.
	return true;
}

}
*/
bool TListViewCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return true;
}
bool TListViewCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <ListView.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <ScrollView.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBListView *F");
	FHeaderLine3->AddProperty(FListViewComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TListViewCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return true;
}
bool TListViewCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{

	string ACtorLabel = FListViewComponent->FParent->FClassName + "::" + FListViewComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FListViewComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FListViewComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FListViewComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FListViewComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FListViewComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FListViewComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BListView(ARect");
	FBodyLine2->AddProperty(FListViewComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FListViewComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",");
	FBodyLine2->AddProperty(FListViewComponent,PROP_LIST_TYPE,true,false);
	FBodyLine2->AddString(",");
	FBodyLine2->AddProperty(FListViewComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");
	FBodyLine2->AddProperty(FListViewComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n");
	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\t//Adding the ScrollView Now!\n");
	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(new BScrollView(\"scroll_");
	FBodyLine4->AddProperty(FListViewComponent,PROP_NAME,true,true);
	FBodyLine4->AddString("\",F");
	FBodyLine4->AddProperty(FListViewComponent,PROP_NAME,true,false);
	FBodyLine4->AddString(",");	
	FBodyLine4->AddProperty(FListViewComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine4->AddString(",0,true,true));\n");
	
	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}
bool TListViewCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	return true;
}
bool TListViewCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}


