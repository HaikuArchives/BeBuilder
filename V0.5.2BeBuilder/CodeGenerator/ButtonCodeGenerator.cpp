#include "ButtonCodeGenerator.h"
#include "ButtonComponent.h"

TButtonCodeGenerator::TButtonCodeGenerator(TButtonComponent * AButtonComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FButtonComponent = AButtonComponent;
}
/*
void TButtonCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TButtonCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	//GenerateH(APath,ClassName);
	//GenerateCPP(APath,ClassName);	
	//---------NEW METHOD!
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TButtonCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TButtonCodeGenerator::GenerateAll After InsertionMessageREceived \n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TButtonCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");
	
}

*/
/*
bool TButtonCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
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

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <Button.h>\n";

//	printf("TViewCodeGenerator::InsertionContructor Before AddInFunction\n");
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TViewCodeGenerator::InsertionContructor After AddInFunction\n");
	if (!resultat) return false;
//	printf("TViewCodeGenerator::InsertionContructor continue!\n");

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBButton *" + FButtonComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;

*/
//In the CPP!
/*
	InsideWhich = "#"; //found the #ifndef
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);		
	MustBeAdded = "#include \"" ;
	MustBeAdded = MustBeAdded + name;	
	MustBeAdded = MustBeAdded + "\"\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
*/
/*	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
//	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	//BeforeWhat = "}";

	MustBeAdded = "\t BRect ARect" + FButtonComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FButtonComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FButtonComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FButtonComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FButtonComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	
	MustBeAdded = MustBeAdded +"\t" +FButtonComponent->FComponentName +" = new BButton(ARect";

	MustBeAdded = MustBeAdded + FButtonComponent->FComponentName +",\"";
	MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",\"";
	MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",";
	if (FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +"),";
	}
	else
		MustBeAdded = MustBeAdded + "NULL,";
	MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";
//	MustBeAdded = MustBeAdded + ");\n";
	MustBeAdded = MustBeAdded + "\t" + FButtonComponent->FComponentName +"->MakeDefault(";
	MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_DEFAULT).c_str() +");\n";
*/
/*
	BRect rect7(10,110,175,110);
	butZIP= new BButton(rect7,"butBrowseZIP","Path and ExeName for ZIP : ",new BMessage(ZIP_BROWSE));;

*/
/*	MustBeAdded = MustBeAdded + "\tAddChild(" + FButtonComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
//	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());

}
*/
/*
bool TButtonCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TButtonCodeGenerator::InsertionMessageReceived \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
//		MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + StrCopy(FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
	
		printf("TButtonCodeGenerator::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the button here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}

bool TButtonCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TButtonCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BView";
		MustBeAdded = "\t" + FButtonComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/
bool TButtonCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return true;
}
bool TButtonCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <Button.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBButton *F");
	FHeaderLine3->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TButtonCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return true;
}

bool TButtonCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{
	string ACtorLabel = FButtonComponent->FParent->FClassName + "::" + FButtonComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FButtonComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FButtonComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FButtonComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FButtonComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BButton(ARect");
	FBodyLine2->AddProperty(FButtonComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FButtonComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FButtonComponent,PROP_LABEL,true,false);
	FBodyLine2->AddString("\",");	
	FBodyLine2->BeginBoolean(FButtonComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString("new BMessage(");	
	FBodyLine2->EndBoolean(); 	
	FBodyLine2->AddProperty(FButtonComponent,PROP_MESSAGE,true,false);
	FBodyLine2->BeginBoolean(FButtonComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString(")");	
	FBodyLine2->EndBoolean(); 		
	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FButtonComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FButtonComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\tF");
	FBodyLine3->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FBodyLine3->AddString("->MakeDefault(");
	FBodyLine3->AddProperty(FButtonComponent,PROP_DEFAULT,true,false);
	FBodyLine3->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(F");
	FBodyLine4->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FBodyLine4->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}

bool TButtonCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FButtonComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);
	

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FButtonComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FButtonComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("//Insert the Handler for the button here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");


	return true;
}

void TButtonCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FButtonComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FButtonComponent->FParent->FCodeGenerator->FBodyCodeFile;
//	FHeaderCodeFile = new TCodeFile(ClassName,APath,"h");
//	FBodyCodeFile = new TCodeFile(ClassName,APath,"cpp");
//	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}


bool TButtonCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
//	CreateMessageReceived(ReallyWriteInFile);	//Will be called in the Component Object.
	return true;
}
