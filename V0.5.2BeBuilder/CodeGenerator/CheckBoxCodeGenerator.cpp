#include "CheckBoxCodeGenerator.h"
#include "CheckBoxComponent.h"

TCheckBoxCodeGenerator::TCheckBoxCodeGenerator(TCheckBoxComponent * ACheckBoxComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FCheckBoxComponent = ACheckBoxComponent;
}
/*
void TCheckBoxCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TCheckBoxCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	//GenerateH(APath,ClassName);
	//GenerateCPP(APath,ClassName);	
	//---------NEW METHOD!
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TCheckBoxCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TCheckBoxCodeGenerator::GenerateAll After InsertionMessageREceived \n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TCheckBoxCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");
	
}


bool TCheckBoxCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

	printf("Inside TCheckBoxCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <CheckBox.h>\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBCheckBox *" + FCheckBoxComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;


//In the CPP!
	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
//	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	//BeforeWhat = "}";

	MustBeAdded = "\t BRect ARect" + FCheckBoxComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	
	MustBeAdded = MustBeAdded +"\t" +FCheckBoxComponent->FComponentName +" = new BCheckBox(ARect";

	MustBeAdded = MustBeAdded + FCheckBoxComponent->FComponentName +",\"";
	MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",\"";
	MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",";
	if (FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +"),";
	}
	else
		MustBeAdded = MustBeAdded + "NULL,";
	MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
//	MustBeAdded = MustBeAdded + ");\n";

	MustBeAdded = MustBeAdded + "\tAddChild(" + FCheckBoxComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
//	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());

}

bool TCheckBoxCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

	printf("Inside TCheckBoxCodeGenerator::InsertionMessageReceived \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
//		MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + StrCopy(FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
	
		printf("TCheckBoxCodeGenerator::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the CheckBox here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;

}

bool TCheckBoxCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

//	printf("Inside TCheckBoxCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BView";
		MustBeAdded = "\t" + FCheckBoxComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/
void TCheckBoxCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FCheckBoxComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FCheckBoxComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}
bool TCheckBoxCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	return true;
}
bool TCheckBoxCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <CheckBox.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBCheckBox *F");
	FHeaderLine3->AddProperty(FCheckBoxComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TCheckBoxCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	return true;
}
bool TCheckBoxCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
	string ACtorLabel = FCheckBoxComponent->FParent->FClassName + "::" + FCheckBoxComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BCheckBox(ARect");
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_LABEL,true,false);
	FBodyLine2->AddString("\",");	
	FBodyLine2->BeginBoolean(FCheckBoxComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString("new BMessage(");	
	FBodyLine2->EndBoolean(); 	
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_MESSAGE,true,false);
	FBodyLine2->BeginBoolean(FCheckBoxComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString(")");	
	FBodyLine2->EndBoolean(); 		
	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(F");
	FBodyLine4->AddProperty(FCheckBoxComponent,PROP_NAME,true,true);
	FBodyLine4->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}

bool TCheckBoxCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FCheckBoxComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);
	

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FCheckBoxComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FCheckBoxComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FCheckBoxComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("//Insert the Handler for the button here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");


	return true;
}
bool TCheckBoxCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}

