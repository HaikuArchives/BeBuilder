#include "TextControlCodeGenerator.h"
#include "TextControlComponent.h"

TTextControlCodeGenerator::TTextControlCodeGenerator(TTextControlComponent * ATextControlComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FTextControlComponent = ATextControlComponent;
}
/*
void TTextControlCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TTextControlCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
//	GenerateH(APath,ClassName);
//	GenerateCPP(APath,ClassName);	
	//---------NEW METHOD!
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TTextControlCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TTextControlCodeGenerator::GenerateAll After InsertionMessageREceived \n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TTextControlCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");

}


bool TTextControlCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TTextControlCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	printf("Inside TTextControlCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <TextControl.h>\n";

	printf("TTextControlCodeGenerator::InsertionContructor Before AddInFunction\n");
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	printf("TTextControlCodeGenerator::InsertionContructor After AddInFunction\n");
	if (!resultat) return false;
	printf("TTextControlCodeGenerator::InsertionContructor continue!\n");

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBTextControl *" + FTextControlComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;


//In the CPP!
	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	AfterWhat = "{";
	BeforeWhat = "}";

	MustBeAdded = "\t BRect ARect" + FTextControlComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FTextControlComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FTextControlComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FTextControlComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FTextControlComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded +"\t" +FTextControlComponent->FComponentName +" = new BTextControl(ARect";
	MustBeAdded = MustBeAdded + FTextControlComponent->FComponentName +",\"";
	if (FTextControlComponent->FPropertyList->GetPropertyValue(PROP_LABEL).length()>0)
	{
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",\"";	
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",\"";
	}
	else
	{
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",NULL,\"";
	}

	MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_TEXT).c_str() +"\",";
	if (strlen(FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str())>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +"),";
	}
	else
		MustBeAdded = MustBeAdded + "NULL,";
	MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
//	ATextControl12->SetDivider((ATextControl12->Frame().right-ATextControl12->Frame().left)/2);
	MustBeAdded = MustBeAdded + "\tAddChild(" + FTextControlComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
//	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());

}

bool TTextControlCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TViewCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (strlen(FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str())>0)
	{
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
//		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + StrCopy(FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());

// In the CPP!
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the TextControl here!\n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());

	#define B_BUTTON_MESSAGE  'SAGE'
	#define B_MESSAGE_EDIT 'EDIT'


	}
	return false;
}
*/
/*
bool TTextControlCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TTextControlCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BView";
		MustBeAdded = "\t" + FTextControlComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/
void TTextControlCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FTextControlComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FTextControlComponent->FParent->FCodeGenerator->FBodyCodeFile;

	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	

}

bool TTextControlCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	return true;
}

bool TTextControlCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <TextControl.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBTextControl *F");
	FHeaderLine3->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}

bool TTextControlCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	return true;
}

bool TTextControlCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
	string ACtorLabel = FTextControlComponent->FParent->FClassName + "::" + FTextControlComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FTextControlComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FTextControlComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FTextControlComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FTextControlComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BTextControl(ARect");
	FBodyLine2->AddProperty(FTextControlComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_LABEL,true,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_TEXT,true,false);
	FBodyLine2->AddString("\",");	
	FBodyLine2->BeginBoolean(FTextControlComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString("new BMessage(");	
	FBodyLine2->EndBoolean(); 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_MESSAGE,true,false);
	FBodyLine2->BeginBoolean(FTextControlComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString(")");	
	FBodyLine2->EndBoolean(); 		
	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FTextControlComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\tF");
	FBodyLine3->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FBodyLine3->AddString("->SetDivider(");
	FBodyLine3->BeginBoolean(FTextControlComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine3->AddString("(ARect");
	FBodyLine3->AddProperty(FTextControlComponent,PROP_NAME,false,false);
	FBodyLine3->AddString(".right - ARect");
	FBodyLine3->AddProperty(FTextControlComponent,PROP_NAME,false,false);
	FBodyLine3->AddString(".left)/2);\n");
	FBodyLine3->EndBoolean(); 	
	FBodyLine3->BeginBoolean(FTextControlComponent,PROP_MESSAGE,EQUAL_OPERATION,"NULL",false,false);
	FBodyLine3->AddString("0);\n");	
	FBodyLine3->EndBoolean(); 	

	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(F");
	FBodyLine4->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FBodyLine4->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}

bool TTextControlCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FTextControlComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);
	

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FTextControlComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FTextControlComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FTextControlComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("\t\t//Insert the Handler for the TextControl here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");


	return true;
}

bool TTextControlCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}



