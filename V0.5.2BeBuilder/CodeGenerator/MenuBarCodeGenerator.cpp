#include "MenuBarCodeGenerator.h"
#include "MenuBarComponent.h"

TMenuBarCodeGenerator::TMenuBarCodeGenerator(TMenuBarComponent * AMenuBarComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FMenuBarComponent = AMenuBarComponent;
}
/*
void TMenuBarCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TMenuBarCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	TComponent *AComponent;
//	printf("TMenuBarCodeGenerator ClassName : %s \n", ClassName);
	GenerateH(APath,ClassName);
	GenerateCPP(APath,ClassName);	
	GenerateMakeFile(APath,"makefile"); // To get a handle to the makefile file!		
	//---------NEW METHOD!
	SkeletonCPP(FCPPRW);
	SkeletonH(FHeaderRW);
	GenerateH(APath,ClassName); //To open normaly the file in reading....
	GenerateCPP(APath,ClassName);		
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);

	BEntry entry(FCPPRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	InsertionMakeFile(FMakeRW,name);		
	
	AComponent = FMenuBarComponent->FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
		printf("TMenuBarCodeGenerator ClassName : %s asking %s to generate \n", ClassName,AComponent->FClassName.c_str());
		AComponent->Generate(APath,FHeaderRW,FCPPRW);
		AComponent = FMenuBarComponent->FChildren->NextComponent(false);	
	}
	printf("TMenuBarCodeGenerator::GenerateAll Exit from While %s \n",ClassName);

}

bool TMenuBarCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	printf("Inside TMenuBarCodeGenerator::SkeletonCPP \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
// Constructeur!	
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
	AFileRW->WriteALine(FMenuBarComponent->FClassName + "::" + FMenuBarComponent->FClassName + "(");
	AFileRW->WriteALine("BRect AFrame): BMenuBar(AFrame,\"" + FMenuBarComponent->FComponentName);
	AFileRW->WriteALine("\")\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
// Destructeur!	
	AFileRW->WriteALine(FMenuBarComponent->FClassName + "::~" + FMenuBarComponent->FClassName + "(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
//--------- Message Received
	AFileRW->WriteALine("void " + FMenuBarComponent->FClassName + "::MessageReceived(BMessage *message)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tswitch(message->what)\n");
	AFileRW->WriteALine("\t{\n");
	AFileRW->WriteALine("\t\tdefaut :\n");
	AFileRW->WriteALine("\t\t\t BMenuBar::MessageReceived(message);\n");
	AFileRW->WriteALine("\t\t\tbreak;\n");
	AFileRW->WriteALine("\t}\n");
	AFileRW->WriteALine("}\n");	
//--------- Attached to Window
	AFileRW->WriteALine("void " + FMenuBarComponent->FClassName + "::AttachedToWindow(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tBMenuBar::AttachedToWindow();\n"); 
	AFileRW->WriteALine("}\n");	
	return true;
}

bool TMenuBarCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
	printf("Inside TMenuBarCodeGenerator::SkeletonH \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	AFileRW->WriteALine("#ifndef __" + FMenuBarComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#define __" + FMenuBarComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#include <MenuBar.h>\n");	
	AFileRW->WriteALine("class " + FMenuBarComponent->FClassName + ": public BMenuBar\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tpublic: \n");	
	AFileRW->WriteALine("\t\t" + FMenuBarComponent->FClassName + "(BRect AFrame);\n");
	AFileRW->WriteALine("\t\t~" + FMenuBarComponent->FClassName + "(void);\n");
	AFileRW->WriteALine("\t\tvoid AttachedToWindow(void);\n");
	AFileRW->WriteALine("\t\tvoid MessageReceived(BMessage *message);\n");
	AFileRW->WriteALine("\tprivate: \n");
	AFileRW->WriteALine("};\n");		
	AFileRW->WriteALine("#endif\n");	
	return true;
}


bool TMenuBarCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuBarCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuBarCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!

// #include "BuilderMenu.h"
//		TBuilderMenu *FBuilderMenu;
	InsideWhich = "#define"; //found the #ifndef
	MustBeAdded = "#include <MenuBar.h>\n" ;

	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
	MustBeAdded = "\t\tBMenuBar *F" + FMenuBarComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");


//In the CPP!
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);		
	InsideWhich = "#"; //found the #ifndef
	MustBeAdded = "#include \"" ;
	MustBeAdded = MustBeAdded + name;	
	MustBeAdded = MustBeAdded + "\"\n";
	resultat = AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");

	if (FMenuBarComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FMenuBarComponent->FParent->FClassName;
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\tBRect Rect" + FMenuBarComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded + "\tF" + FMenuBarComponent->FComponentName + " = new " +FMenuBarComponent->FClassName;
	MustBeAdded = MustBeAdded + "(Rect"+ FMenuBarComponent->FComponentName+");\n";
	MustBeAdded = MustBeAdded + "\tAddChild(F" + FMenuBarComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
}

*/
// From the AddOn
/*

bool TMenuBarCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	printf("Inside TMenuBarCodeGenerator::SkeletonCPP \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
// Constructeur!	
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
	AFileRW->WriteALine(FMenuBarComponent->FClassName + "::" + FMenuBarComponent->FClassName + "(");
	AFileRW->WriteALine("BRect AFrame): BMenuBar(AFrame,\"" + FMenuBarComponent->FComponentName);
	AFileRW->WriteALine("\")\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
// Destructeur!	
	AFileRW->WriteALine(FMenuBarComponent->FClassName + "::~" + FMenuBarComponent->FClassName + "(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
//--------- Message Received
	AFileRW->WriteALine("void " + FMenuBarComponent->FClassName + "::MessageReceived(BMessage *message)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tswitch(message->what)\n");
	AFileRW->WriteALine("\t{\n");
	AFileRW->WriteALine("\t\tdefaut :\n");
	AFileRW->WriteALine("\t\t\t BMenuBar::MessageReceived(message);\n");
	AFileRW->WriteALine("\t\t\tbreak;\n");
	AFileRW->WriteALine("\t}\n");
	AFileRW->WriteALine("}\n");	
//--------- Attached to Window
	AFileRW->WriteALine("void " + FMenuBarComponent->FClassName + "::AttachedToWindow(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tBMenuBar::AttachedToWindow();\n"); 
	AFileRW->WriteALine("}\n");	
	return true;
}

bool TMenuBarCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
}


bool TMenuBarCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuBarCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuBarCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!

// #include "BuilderMenu.h"
//		TBuilderMenu *FBuilderMenu;
	InsideWhich = "#define"; //found the #ifndef
	MustBeAdded = "#include <MenuBar.h>\n" ;

	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
	MustBeAdded = "\t\tBMenuBar *F" + FMenuBarComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");


//In the CPP!
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);		
	InsideWhich = "#"; //found the #ifndef
	MustBeAdded = "#include \"" ;
	MustBeAdded = MustBeAdded + name;	
	MustBeAdded = MustBeAdded + "\"\n";
	resultat = AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");

	if (FMenuBarComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FMenuBarComponent->FParent->FClassName;
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\tBRect Rect" + FMenuBarComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuBarComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded + "\tF" + FMenuBarComponent->FComponentName + " = new " +FMenuBarComponent->FClassName;
	MustBeAdded = MustBeAdded + "(Rect"+ FMenuBarComponent->FComponentName+");\n";
	MustBeAdded = MustBeAdded + "\tAddChild(F" + FMenuBarComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
}



*/

bool TMenuBarCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine = new TCodeLine(FBodyCodeFile);
	FBodyLine->Copyrights();

	TProperty *AProperty = FMenuBarComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FBodyCodeFile);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("#include \"");
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_NAME,true,true);	
	FBodyLine2->AddString(".h\"\n");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FBodyLine3->AddString("::");
	FBodyLine3->AddProperty(FMenuBarComponent,PROP_CLASSNAME,false,false);	
	FBodyLine3->AddString("(BRect AFrame): BMenuBar(AFrame,\"");
	FBodyLine3->AddProperty(FMenuBarComponent,PROP_NAME,true,false);	
	FBodyLine3->AddString("\")\n");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("{\n");

	TCodeLine *FBodyLine5 = new TCodeLine(FBodyCodeFile);
	FBodyLine5->AddString("}\n");

	TCodeLine *FBodyLine6 = new TCodeLine(FBodyCodeFile);
	FBodyLine6->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FBodyLine6->AddString("::~");
	FBodyLine6->AddProperty(FMenuBarComponent,PROP_CLASSNAME,false,false);	
	FBodyLine6->AddString("(void)\n");

	TCodeLine *FBodyLine7 = new TCodeLine(FBodyCodeFile);
	FBodyLine7->AddString("{\n");

	TCodeLine *FBodyLine8 = new TCodeLine(FBodyCodeFile);
	FBodyLine8->AddString("}\n");

	TCodeLine *FBodyLine9 = new TCodeLine(FBodyCodeFile);
	FBodyLine9->AddString("void ");
	FBodyLine9->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FBodyLine9->AddString("::MessageReceived(BMessage *message)\n");

	TCodeLine *FBodyLine10 = new TCodeLine(FBodyCodeFile);
	FBodyLine10->AddString("{\n");

	TCodeLine *FBodyLine11 = new TCodeLine(FBodyCodeFile);
	FBodyLine11->AddString("\tswitch(message->what)\n");

	TCodeLine *FBodyLine12 = new TCodeLine(FBodyCodeFile);
	FBodyLine12->AddString("\t{\n");

	TCodeLine *FBodyLine13 = new TCodeLine(FBodyCodeFile);
	FBodyLine13->AddString("\t\tdefault :\n");

	TCodeLine *FBodyLine14 = new TCodeLine(FBodyCodeFile);
	FBodyLine14->AddString("\t\t\tBMenuBar::MessageReceived(message);\n");

	TCodeLine *FBodyLine15 = new TCodeLine(FBodyCodeFile);
	FBodyLine15->AddString("\t\t\tbreak;\n");

	TCodeLine *FBodyLine16 = new TCodeLine(FBodyCodeFile);
	FBodyLine16->AddString("\t}\n");

	TCodeLine *FBodyLine17 = new TCodeLine(FBodyCodeFile);
	FBodyLine17->AddString("}\n");

	TCodeLine *FBodyLine18 = new TCodeLine(FBodyCodeFile);
	FBodyLine18->AddString("void ");
	FBodyLine18->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FBodyLine18->AddString("::AttachedToWindow(void)\n");

	TCodeLine *FBodyLine19 = new TCodeLine(FBodyCodeFile);
	FBodyLine19->AddString("{\n");

	TCodeLine *FBodyLine20 = new TCodeLine(FBodyCodeFile);
	FBodyLine20->AddString("\tBMenuBar::AttachedToWindow();\n");

	TCodeLine *FBodyLine21 = new TCodeLine(FBodyCodeFile);
	FBodyLine21->AddString("}\n");

	if (ReallyWriteInFile)
	{
		FBodyLine21->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine20->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine19->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine18->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine17->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine16->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine15->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine14->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine13->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine12->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine11->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine10->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine9->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine8->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine7->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine6->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine5->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine4->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine3->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine2->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine->AddLine(NULL,NULL,NULL,NULL);
	}

	return true;
}
bool TMenuBarCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine = new TCodeLine(FHeaderCodeFile);
	FHeaderLine->Copyrights();

	TProperty *AProperty = FMenuBarComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FHeaderCodeFile);
	
	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#ifndef __");
	FHeaderLine2->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine2->AddString("_H__ \n");

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("#define __");
	FHeaderLine3->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine3->AddString("_H__ \n");

	TCodeLine *FHeaderLine4 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine4->AddString("#include <MenuBar.h>\n");

	TCodeLine *FHeaderLine5 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine5->AddString("class ");
	FHeaderLine5->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine5->AddString(": public BMenuBar\n");
	
	TCodeLine *FHeaderLine6 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine6->AddString("{\n");
	
	TCodeLine *FHeaderLine7 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine7->AddString("\tpublic:\n");
	
	TCodeLine *FHeaderLine8 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine8->AddString("\t\t");
	FHeaderLine8->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine8->AddString("(BRect AFrame);\n");
	
	TCodeLine *FHeaderLine9 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine9->AddString("\t\t~");
	FHeaderLine9->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine9->AddString("(void);\n");
	
	TCodeLine *FHeaderLine10 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine10->AddString("\t\tvoid MessageReceived(BMessage *message);\n");

	TCodeLine *FHeaderLine11 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine11->AddString("\t\tvoid AttachedToWindow(void);\n");

	TCodeLine *FHeaderLine12 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine12->AddString("};\n");
	
	TCodeLine *FHeaderLine13 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine13->AddString("#endif\n");
		
	if (ReallyWriteInFile)
	{
		FHeaderLine13->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine12->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine11->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine10->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine9->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine8->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine7->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine6->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine5->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine4->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine3->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine2->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine->AddLine(NULL,NULL,NULL,NULL);
	}
	return true;
}
bool TMenuBarCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	ShowDebug("CreateMakeFile Inside.");
	TCodeLine *FMakeFileLine = new TCodeLine(FMakeFileCodeFile);
	FMakeFileLine->AddString(""); 
	FMakeFileLine->AddProperty(FMenuBarComponent,PROP_NAME,true,true);
	FMakeFileLine->AddString(".cpp "); 
	if (ReallyWriteInFile)
	{
		FMakeFileLine->AddLine(NULL,"SRCS=",NULL,"\n#");
	}
	ShowDebug("CreateMakeFile Quitting.");	
	return true;
}
bool TMenuBarCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{

	TCodeLine *FHeaderLine1 = new TCodeLine(FMenuBarComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine1->AddString("#include <MenuBar.h>\n"); 
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FMenuBarComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine2->AddString("\t\tBMenuBar *F"); 
	FHeaderLine2->AddProperty(FMenuBarComponent,PROP_NAME,true,true); 
	FHeaderLine2->AddString(";\n"); 	
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"class","public:","}");

	string ACtorLabel = FMenuBarComponent->FParent->FClassName + "::" + FMenuBarComponent->FParent->FClassName;
	
	TCodeLine *FBodyLine1 = new TCodeLine(FMenuBarComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine1->AddString("#include \""); 
	FBodyLine1->AddProperty(FMenuBarComponent,PROP_NAME,true,true);
	FBodyLine1->AddString(".h\"\n"); 
	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"#include",NULL,NULL);
//	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"#",NULL,ACtorLabel.c_str());
//	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,NULL,"#include",ACtorLabel.c_str());

	TCodeLine *FBodyLine2 = new TCodeLine(FMenuBarComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine2->AddString("\tF"); 
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new "); 
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_CLASSNAME,true,false);
	FBodyLine2->AddString("(BRect(");	 	
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_LEFT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_TOP,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_RIGHT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuBarComponent,PROP_BOTTOM,true,false);
	FBodyLine2->AddString("));\n"); 	
	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),"{","}");


	TCodeLine *FBodyLine6 = new TCodeLine(FMenuBarComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine6->AddString("\tAddChild(F"); 
	FBodyLine6->AddProperty(FMenuBarComponent,PROP_NAME,true,true);
	FBodyLine6->AddString(");\n"); 	
	if (ReallyWriteInFile) FBodyLine6->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");
	return true;
}
bool TMenuBarCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	return true;	
}

void TMenuBarCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);
	ShowDebug("TMenuBarCodeGenerator::GenerateAll Exit from While");
}

bool TMenuBarCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile)
{
	FHeaderCodeFile = new TCodeFile(AClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(AClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);

	CreateConstructor(ReallyWriteInFile);
	CreateMessageReceived(ReallyWriteInFile);	
	return true;
}

