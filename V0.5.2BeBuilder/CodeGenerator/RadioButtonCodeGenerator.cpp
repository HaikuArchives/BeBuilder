#include "RadioButtonCodeGenerator.h"
#include "RadioButtonComponent.h"

TRadioButtonCodeGenerator::TRadioButtonCodeGenerator(TRadioButtonComponent * ARadioButtonComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FRadioButtonComponent = ARadioButtonComponent;
}
/*
void TRadioButtonCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TRadioButtonCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	//GenerateH(APath,ClassName);
	//GenerateCPP(APath,ClassName);	
	//---------NEW METHOD!
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TRadioButtonCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TRadioButtonCodeGenerator::GenerateAll After InsertionMessageREceived \n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TRadioButtonCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");
	
}


bool TRadioButtonCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

	printf("Inside TRadioButtonCodeGenerator::InsertionContructor \n");
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
	MustBeAdded = "#include <RadioButton.h>\n";

	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBRadioButton *" + FRadioButtonComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;


//In the CPP!
	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
//	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	//BeforeWhat = "}";
	MustBeAdded = "\t BRect ARect" + FRadioButtonComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	
	MustBeAdded = MustBeAdded +"\t" +FRadioButtonComponent->FComponentName +" = new BRadioButton(ARect";

	MustBeAdded = MustBeAdded + FRadioButtonComponent->FComponentName +",\"";
	MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",\"";
	MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",";
	if (FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +"),";
	}
	else
		MustBeAdded = MustBeAdded + "NULL,";
	MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
//	MustBeAdded = MustBeAdded + ");\n";

	MustBeAdded = MustBeAdded + "\tAddChild(" + FRadioButtonComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
//	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());

}

bool TRadioButtonCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

	printf("Inside TRadioButtonCodeGenerator::InsertionMessageReceived \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
//		MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + StrCopy(FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
	
		printf("TRadioButtonCodeGenerator::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the Radiobutton here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;

}

bool TRadioButtonCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{

//	printf("Inside TRadioButtonCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BView";
		MustBeAdded = "\t" + FRadioButtonComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;

}
*/
void TRadioButtonCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FRadioButtonComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FRadioButtonComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	

}
bool TRadioButtonCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	return true;
}
bool TRadioButtonCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <RadioButton.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBRadioButton *F");
	FHeaderLine3->AddProperty(FRadioButtonComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TRadioButtonCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	return true;
}
bool TRadioButtonCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
	string ACtorLabel = FRadioButtonComponent->FParent->FClassName + "::" + FRadioButtonComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BRadioButton(ARect");
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_LABEL,true,false);
	FBodyLine2->AddString("\",");	
	FBodyLine2->BeginBoolean(FRadioButtonComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString("new BMessage(");	
	FBodyLine2->EndBoolean(); 	
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_MESSAGE,true,false);
	FBodyLine2->BeginBoolean(FRadioButtonComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString(")");	
	FBodyLine2->EndBoolean(); 		
	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\tAddChild(F");
	FBodyLine3->AddProperty(FRadioButtonComponent,PROP_NAME,true,true);
	FBodyLine3->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}
bool TRadioButtonCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FRadioButtonComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FRadioButtonComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FRadioButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FRadioButtonComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("\t\t//Insert the Handler for the button here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");

	return true;
}
bool TRadioButtonCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}
