#include "OutlineListViewCodeGenerator.h"
#include "OutlineListViewComponent.h"

TOutlineListViewCodeGenerator::TOutlineListViewCodeGenerator(TOutlineListViewComponent * AOutlineListViewComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FOutlineListViewComponent = AOutlineListViewComponent;
}

/*
void TOutlineListViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	TComponent *AComponent;
	printf("TOutlineListViewCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TOutlineListViewCodeGenerator::GenerateAll After InsertionContructor \n");	
	AComponent = FOutlineListViewComponent->FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
		AComponent->Generate(APath,AParentFileRWHeader,AParentFileRWCPP);
		AComponent = FOutlineListViewComponent->FChildren->NextComponent(false);	
	}
	printf("TOutlineListViewCodeGenerator::GenerateAll Exit from While\n");
	
	
}


bool TOutlineListViewCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TOutlineListViewCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TListViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <OutlineListView.h>\n";
	MustBeAdded = MustBeAdded + "#include <ScrollView.h>\n";	
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBOutlineListView *F" + FOutlineListViewComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;


//In the CPP!
	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
//	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	//BeforeWhat = "}";

	MustBeAdded = "\t BRect ARect" + FOutlineListViewComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	
	MustBeAdded = MustBeAdded +"\tF" +FOutlineListViewComponent->FComponentName +" = new BOutlineListView(ARect";

	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FComponentName +",\"";
	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",";
	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_LIST_TYPE).c_str() +",";
	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
	MustBeAdded = MustBeAdded + "\t// Adding the the ScrollView! \n";
//	MustBeAdded = MustBeAdded + FListViewComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
	MustBeAdded = MustBeAdded + "\tAddChild(new BScrollView(\"scroll_"+ FOutlineListViewComponent->FComponentName+"\",F";
	MustBeAdded = MustBeAdded + FOutlineListViewComponent->FComponentName;
	MustBeAdded = MustBeAdded + ",B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, true,true));\n";
//	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
}
*/


void TOutlineListViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FOutlineListViewComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FOutlineListViewComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}

bool TOutlineListViewCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return true;
}
bool TOutlineListViewCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <OutlineListView.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <ScrollView.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBListView *F");
	FHeaderLine3->AddProperty(FOutlineListViewComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TOutlineListViewCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return true;
}
bool TOutlineListViewCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{

	string ACtorLabel = FOutlineListViewComponent->FParent->FClassName + "::" + FOutlineListViewComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FOutlineListViewComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FOutlineListViewComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FOutlineListViewComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FOutlineListViewComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FOutlineListViewComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BOutlineListView(ARect");
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",");
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_LIST_TYPE,true,false);
	FBodyLine2->AddString(",");
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");
	FBodyLine2->AddProperty(FOutlineListViewComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n");
	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\t//Adding the ScrollView Now!\n");
	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(new BScrollView(\"scroll_");
	FBodyLine4->AddProperty(FOutlineListViewComponent,PROP_NAME,true,true);
	FBodyLine4->AddString("\",F");
	FBodyLine4->AddProperty(FOutlineListViewComponent,PROP_NAME,true,false);
	FBodyLine4->AddString(",");	
	FBodyLine4->AddProperty(FOutlineListViewComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine4->AddString(",0,true,true));\n");
	
	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}
bool TOutlineListViewCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	return true;
}
bool TOutlineListViewCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}
