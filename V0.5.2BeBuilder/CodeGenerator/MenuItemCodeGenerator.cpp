#include "MenuItemCodeGenerator.h"
#include "MenuItemComponent.h"

TMenuItemCodeGenerator::TMenuItemCodeGenerator(TMenuItemComponent * AMenuItemComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FMenuItemComponent = AMenuItemComponent;
}
/*
void TMenuItemCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TMenuItemCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TMenuItemCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TMenuItemCodeGenerator::GenerateAll After InsertionMessageREceived \n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TMenuItemCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");
	
}


bool TMenuItemCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <MenuItem.h>\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor avant test resultat\n");
	if (!resultat) return false;
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor apres test resultat \n");

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="private:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBMenuItem *F" + FMenuItemComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor avant test 2 resultat\n");
	if (!resultat) return false;
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor apres test 2 resultat \n");


//In the CPP!

	if (FMenuItemComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FMenuItemComponent->FParent->FParent->FClassName;
	InsideWhich = "::"; // Finally this is more convenient!
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\tF" + FMenuItemComponent->FComponentName + " = new BMenuItem(\"";
	MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",";
	if (FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +")";
	}
	else
		MustBeAdded = MustBeAdded + "NULL";
	MustBeAdded = MustBeAdded +	");\n";
	MustBeAdded = MustBeAdded +	"\tF" + FMenuItemComponent->FParent->FComponentName + "->AddItem(F";
	MustBeAdded = MustBeAdded +	FMenuItemComponent->FComponentName + ");\n";
	
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());

}

bool TMenuItemCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TMenuItemCodeGenerator::InsertionMessageReceived \n");

	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

	if (FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
		MustBeAdded = MustBeAdded + StrCopy(FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
//In the CPP!	
		printf("FMenuItemComponent::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the MenuItem here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}

bool TMenuItemCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TMenuItemCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BMenuBar";
		MustBeAdded = "\tF" + FMenuItemComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/

/*

bool TMenuItemCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuItemCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;




}

bool TMenuItemCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TMenuItemCodeGenerator::InsertionMessageReceived \n");

	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

	if (FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
		MustBeAdded = MustBeAdded + StrCopy(FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
//In the CPP!	
		printf("FMenuItemComponent::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the MenuItem here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}

bool TMenuItemCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TMenuItemCodeGenerator::InsertionAttachedToWindow \n");

	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BMenuBar";
		MustBeAdded = "\tF" + FMenuItemComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/

void TMenuItemCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FMenuItemComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FMenuItemComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	
}
bool TMenuItemCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	return true;
}
bool TMenuItemCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <MenuItem.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBMenuItem *F");
	FHeaderLine3->AddProperty(FMenuItemComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TMenuItemCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	return true;
}
bool TMenuItemCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
//	string ACtorLabel = FMenuItemComponent->FParent->FParent->FClassName + "::" + FMenuItemComponent->FParent->FParent->FClassName;

	TCodeLine *FBodyLine = new TCodeLine(FBodyCodeFile);
	FBodyLine->AddString("\tF");
	FBodyLine->AddProperty(FMenuItemComponent,PROP_NAME,true,true);
	FBodyLine->AddString("=new BMenuItem(\"");
	FBodyLine->AddProperty(FMenuItemComponent,PROP_LABEL,true,false);
	FBodyLine->AddString("\",");	
	FBodyLine->BeginBoolean(FMenuItemComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine->AddString("new BMessage(");	
	FBodyLine->EndBoolean(); 	
	FBodyLine->AddProperty(FMenuItemComponent,PROP_MESSAGE,true,false);
	FBodyLine->BeginBoolean(FMenuItemComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine->AddString(")");	
	FBodyLine->EndBoolean();
	FBodyLine->AddString(");\n");
//	ShowDebug(string("TMenuItemCodeGenerator::CreateConstructor Ctor=") + ACtorLabel);	
	if (ReallyWriteInFile) FBodyLine->AddLine(NULL,"::",NULL,"}");
	

	if (BMenuField *buffer = dynamic_cast<BMenuField *>(FMenuItemComponent->FParent) )
	{
		TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
		FBodyLine2->AddString("\tMenu()->AddItem(F");
		FBodyLine2->AddProperty(FMenuItemComponent,PROP_NAME,true,true);
		FBodyLine2->AddString(");\n");
//		if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");
		if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::",NULL,"}");
	}
	else
	{
		TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
		FBodyLine3->AddString("\tF");
		FBodyLine3->AddProperty(FMenuItemComponent->FParent,PROP_NAME,true,true);
		FBodyLine3->AddString("->AddItem(F");
		FBodyLine3->AddProperty(FMenuItemComponent,PROP_NAME,true,true);		
		FBodyLine3->AddString(");\n");
//		if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");
		if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,"::",NULL,"}");
	}	
	return true;
}
bool TMenuItemCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FMenuItemComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);
	

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FMenuItemComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FMenuItemComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FMenuItemComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("//Insert the Handler for the MenuItem here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");

	
	return true;
}
bool TMenuItemCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
	return true;
}



