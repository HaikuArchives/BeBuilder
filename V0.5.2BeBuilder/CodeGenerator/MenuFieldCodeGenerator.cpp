#include "MenuFieldCodeGenerator.h"
#include "MenuFieldComponent.h"

TMenuFieldCodeGenerator::TMenuFieldCodeGenerator(TMenuFieldComponent * AMenuFieldComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FMenuFieldComponent = AMenuFieldComponent;
}
/*
void TMenuFieldCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TMenuFieldCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	TComponent *AComponent;
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
	
	AComponent = FMenuFieldComponent->FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
		printf("TMenuFieldCodeGenerator ClassName : %s asking %s to generate \n", ClassName,AComponent->FClassName.c_str());
		AComponent->Generate(APath,FHeaderRW,FCPPRW);
		AComponent = FMenuFieldComponent->FChildren->NextComponent(false);	
	}
	printf("TMenuFieldCodeGenerator::GenerateAll Exit from While %s \n",ClassName);

}

bool TMenuFieldCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	printf("Inside TMenuFieldCodeGenerator::SkeletonCPP \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
// Constructeur!	
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
	AFileRW->WriteALine(FMenuFieldComponent->FClassName + "::" + FMenuFieldComponent->FClassName + "(");
	AFileRW->WriteALine("BRect AFrame): BMenuField(AFrame,\"");
	AFileRW->WriteALine(FMenuFieldComponent->FComponentName + "\",\"\",new BMenu(\"");
	AFileRW->WriteALine(FMenuFieldComponent->FComponentName + "\",B_ITEMS_IN_COLUMN),");
	AFileRW->WriteALine(FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str());
	AFileRW->WriteALine(",");
	AFileRW->WriteALine(FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str());
	AFileRW->WriteALine(")\n{\n\tSetDivider(");
	AFileRW->WriteALine(FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_DIVIDER).c_str());
	AFileRW->WriteALine(");\n" );
	if (strcmp(FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_ENABLED).c_str(),BOOL_TRUE)==0)
		AFileRW->WriteALine("SetEnabled(true);\n}\n");
	else
		AFileRW->WriteALine("SetEnabled(false);\n}\n");	
// Destructeur!	
	AFileRW->WriteALine(FMenuFieldComponent->FClassName + "::~" + FMenuFieldComponent->FClassName + "(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
//--------- Message Received
	AFileRW->WriteALine("void " + FMenuFieldComponent->FClassName + "::MessageReceived(BMessage *message)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tswitch(message->what)\n");
	AFileRW->WriteALine("\t{\n");
	AFileRW->WriteALine("\t\tdefaut :\n");
	AFileRW->WriteALine("\t\t\t BMenuField::MessageReceived(message);\n");
	AFileRW->WriteALine("\t\t\tbreak;\n");
	AFileRW->WriteALine("\t}\n");
	AFileRW->WriteALine("}\n");	
//--------- Attached to Window
	AFileRW->WriteALine("void " + FMenuFieldComponent->FClassName + "::AttachedToWindow(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tBMenuField::AttachedToWindow();\n"); 
	AFileRW->WriteALine("}\n");	
	return true;
}

bool TMenuFieldCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
	printf("Inside TMenuFieldCodeGenerator::SkeletonH \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	AFileRW->WriteALine("#ifndef __" + FMenuFieldComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#define __" + FMenuFieldComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#include <MenuField.h>\n");	
	AFileRW->WriteALine("#include <Menu.h>\n");	
	AFileRW->WriteALine("class " + FMenuFieldComponent->FClassName + ": public BMenuField\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tpublic: \n");	
	AFileRW->WriteALine("\t\t" + FMenuFieldComponent->FClassName + "(BRect AFrame);\n");
	AFileRW->WriteALine("\t\t~" + FMenuFieldComponent->FClassName + "(void);\n");
	AFileRW->WriteALine("\t\tvoid AttachedToWindow(void);\n");
	AFileRW->WriteALine("\t\tvoid MessageReceived(BMessage *message);\n");
	AFileRW->WriteALine("\tprivate: \n");
	AFileRW->WriteALine("};\n");		
	AFileRW->WriteALine("#endif\n");	
	return true;
}


bool TMenuFieldCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TMenuFieldCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TMenuFieldCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!

// #include "BuilderMenu.h"
//		TBuilderMenu *FBuilderMenu;
	InsideWhich = "#define"; //found the #ifndef
	MustBeAdded = "#include <MenuField.h>\n" ;

	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
	MustBeAdded = "\t\tBMenuField *F" + FMenuFieldComponent->FComponentName ;
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

	if (FMenuFieldComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FMenuFieldComponent->FParent->FClassName;
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\tBRect Rect" + FMenuFieldComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FMenuFieldComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded + "\tF" + FMenuFieldComponent->FComponentName + " = new " + FMenuFieldComponent->FClassName;
	MustBeAdded = MustBeAdded + "(Rect"+ FMenuFieldComponent->FComponentName + ");\n";
			MustBeAdded = MustBeAdded + "\tAddChild(F" + FMenuFieldComponent->FComponentName;
			MustBeAdded = MustBeAdded + ");\n";
//		}
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
}

*/

void TMenuFieldCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);
	ShowDebug("TMenuBarCodeGenerator::GenerateAll Exit from While");
}
bool TMenuFieldCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	TCodeLine *FBodyLine = new TCodeLine(FBodyCodeFile);
	FBodyLine->Copyrights();

	TProperty *AProperty = FMenuFieldComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeFile(FBodyCodeFile);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("#include \"");
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_NAME,true,true);	
	FBodyLine2->AddString(".h\"\n");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FBodyLine3->AddString("::");
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,false,false);	
	FBodyLine3->AddString("(BRect AFrame): BMenuField(AFrame,\"");
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_NAME,true,false);	
	FBodyLine3->AddString("\",\"\",new BMenu(\"");
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_NAME,false,false);	
	FBodyLine3->AddString("\",B_ITEMS_IN_COLUMN),");
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_RESIZING_MODE,true,false);	
	FBodyLine3->AddString(",");
	FBodyLine3->AddProperty(FMenuFieldComponent,PROP_FLAGS,true,false);	
	FBodyLine3->AddString(")\n");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("{\n");

	TCodeLine *FBodyLine5 = new TCodeLine(FBodyCodeFile);
	FBodyLine5->AddString("\tSetDivider(");
	FBodyLine5->AddProperty(FMenuFieldComponent,PROP_DIVIDER,true,true);	
	FBodyLine5->AddString(");\n");

	TCodeLine *FBodyLine6 = new TCodeLine(FBodyCodeFile);
	FBodyLine6->AddString("\tSetEnabled(");
	FBodyLine6->AddProperty(FMenuFieldComponent,PROP_ENABLED,true,true);	
	FBodyLine6->AddString(");\n");



	TCodeLine *FBodyLine7 = new TCodeLine(FBodyCodeFile);
	FBodyLine7->AddString("}\n");

	TCodeLine *FBodyLine8 = new TCodeLine(FBodyCodeFile);
	FBodyLine8->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FBodyLine8->AddString("::~");
	FBodyLine8->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,false,false);	
	FBodyLine8->AddString("(void)\n");

	TCodeLine *FBodyLine9 = new TCodeLine(FBodyCodeFile);
	FBodyLine9->AddString("{\n");

	TCodeLine *FBodyLine10 = new TCodeLine(FBodyCodeFile);
	FBodyLine10->AddString("}\n");

	TCodeLine *FBodyLine11 = new TCodeLine(FBodyCodeFile);
	FBodyLine11->AddString("void ");
	FBodyLine11->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FBodyLine11->AddString("::MessageReceived(BMessage *message)\n");

	TCodeLine *FBodyLine12 = new TCodeLine(FBodyCodeFile);
	FBodyLine12->AddString("{\n");

	TCodeLine *FBodyLine13 = new TCodeLine(FBodyCodeFile);
	FBodyLine13->AddString("\tswitch(message->what)\n");

	TCodeLine *FBodyLine14 = new TCodeLine(FBodyCodeFile);
	FBodyLine14->AddString("\t{\n");

	TCodeLine *FBodyLine15 = new TCodeLine(FBodyCodeFile);
	FBodyLine15->AddString("\t\tdefault :\n");

	TCodeLine *FBodyLine16 = new TCodeLine(FBodyCodeFile);
	FBodyLine16->AddString("\t\t\tBMenuField::MessageReceived(message);\n");

	TCodeLine *FBodyLine17 = new TCodeLine(FBodyCodeFile);
	FBodyLine17->AddString("\t\t\tbreak;\n");

	TCodeLine *FBodyLine18 = new TCodeLine(FBodyCodeFile);
	FBodyLine18->AddString("\t}\n");

	TCodeLine *FBodyLine19 = new TCodeLine(FBodyCodeFile);
	FBodyLine19->AddString("}\n");

	TCodeLine *FBodyLine20 = new TCodeLine(FBodyCodeFile);
	FBodyLine20->AddString("void ");
	FBodyLine20->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FBodyLine20->AddString("::AttachedToWindow(void)\n");

	TCodeLine *FBodyLine21 = new TCodeLine(FBodyCodeFile);
	FBodyLine21->AddString("{\n");

	TCodeLine *FBodyLine22 = new TCodeLine(FBodyCodeFile);
	FBodyLine22->AddString("\tBMenuField::AttachedToWindow();\n");

	TCodeLine *FBodyLine23 = new TCodeLine(FBodyCodeFile);
	FBodyLine23->AddString("}\n");

	if (ReallyWriteInFile)
	{
		FBodyLine23->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine22->AddLine(NULL,NULL,NULL,NULL);
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
bool TMenuFieldCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	TCodeLine *FHeaderLine = new TCodeLine(FHeaderCodeFile);
	FHeaderLine->Copyrights();

	TProperty *AProperty = FMenuFieldComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeFile(FHeaderCodeFile);
	
	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#ifndef __");
	FHeaderLine2->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine2->AddString("_H__ \n");

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("#define __");
	FHeaderLine3->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine3->AddString("_H__ \n");

	TCodeLine *FHeaderLine4 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine4->AddString("#include <MenuField.h>\n");

	TCodeLine *FHeaderLine5 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine5->AddString("#include <Menu.h>\n");

	TCodeLine *FHeaderLine6 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine6->AddString("class ");
	FHeaderLine6->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine6->AddString(": public BMenuField\n");
	
	TCodeLine *FHeaderLine7 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine7->AddString("{\n");
	
	TCodeLine *FHeaderLine8 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine8->AddString("\tpublic:\n");
	
	TCodeLine *FHeaderLine9 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine9->AddString("\t\t");
	FHeaderLine9->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine9->AddString("(BRect AFrame);\n");
	
	TCodeLine *FHeaderLine10 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine10->AddString("\t\t~");
	FHeaderLine10->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,true);	
	FHeaderLine10->AddString("(void);\n");
	
	TCodeLine *FHeaderLine11 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine11->AddString("\t\tvoid MessageReceived(BMessage *message);\n");

	TCodeLine *FHeaderLine12 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine12->AddString("\t\tvoid AttachedToWindow(void);\n");

	TCodeLine *FHeaderLine13 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine13->AddString("};\n");
	
	TCodeLine *FHeaderLine14 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine14->AddString("#endif\n");
		
	if (ReallyWriteInFile)
	{
		FHeaderLine14->AddLine(NULL,NULL,NULL,NULL);
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
bool TMenuFieldCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	ShowDebug("CreateMakeFile Inside.");
	TCodeLine *FMakeFileLine = new TCodeLine(FMakeFileCodeFile);
	FMakeFileLine->AddString(""); 
	FMakeFileLine->AddProperty(FMenuFieldComponent,PROP_NAME,true,true);
	FMakeFileLine->AddString(".cpp "); 
	if (ReallyWriteInFile)
	{
		FMakeFileLine->AddLine(NULL,"SRCS=",NULL,"\n#");
	}
	ShowDebug("CreateMakeFile Quitting.");	
	return true;
}
bool TMenuFieldCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{
/*
*/
	TCodeLine *FHeaderLine1 = new TCodeLine(FMenuFieldComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine1->AddString("#include <MenuField.h>\n"); 
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FMenuFieldComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine2->AddString("\t\tBMenuField *F"); 
	FHeaderLine2->AddProperty(FMenuFieldComponent,PROP_NAME,true,true); 
	FHeaderLine2->AddString(";\n"); 	
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"class","public:","}");

//	string ACtorLabel = FMenuFieldComponent->FParent->FClassName + "::" + FMenuFieldComponent->FParent->FClassName;
	string ACtorLabel = "::";
	
	TCodeLine *FBodyLine1 = new TCodeLine(FMenuFieldComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine1->AddString("#include \""); 
	FBodyLine1->AddProperty(FMenuFieldComponent,PROP_NAME,true,true);
	FBodyLine1->AddString(".h\"\n"); 
	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"#include",NULL,NULL);
//	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"#",NULL,ACtorLabel.c_str());
//	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,NULL,"#include",ACtorLabel.c_str());

	TCodeLine *FBodyLine2 = new TCodeLine(FMenuFieldComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine2->AddString("\tF"); 
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new "); 
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_CLASSNAME,true,false);
	FBodyLine2->AddString("(BRect(");	 	
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_LEFT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_TOP,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_RIGHT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FMenuFieldComponent,PROP_BOTTOM,true,false);
	FBodyLine2->AddString("));\n"); 	
	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),"{","}");


	TCodeLine *FBodyLine6 = new TCodeLine(FMenuFieldComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine6->AddString("\tAddChild(F"); 
	FBodyLine6->AddProperty(FMenuFieldComponent,PROP_NAME,true,true);
	FBodyLine6->AddString(");\n"); 	
	if (ReallyWriteInFile) FBodyLine6->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");
	return true;
}
bool TMenuFieldCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	return true;
}
bool TMenuFieldCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	FHeaderCodeFile = new TCodeFile(AClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(AClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);

	CreateConstructor(ReallyWriteInFile);
	CreateMessageReceived(ReallyWriteInFile);	
	return true;
}

